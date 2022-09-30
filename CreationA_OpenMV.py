import sensor, image, time, pyb

def calc_blod(blods):
    x_sum = 0
    y_sum = 0
    pix_sum = 0
    index = 0
    xi_sum = 0

    for c in blods:
        x_sum += c.x()
        y_sum += c.y()
        pix_sum += c.pixels()
        xi_sum += c.x() * index
        index += 1

    x_aver = x_sum // 10
    y_aver = y_sum // 10
    pix_aver = pix_sum // 10

    # x方向上预测
    b = (xi_sum - 45 * x_aver) / 285
    a = x_aver - 4.5 * b
    x_pred = 15 * b + a

    if(x_pred < 0):
        x_pred = 0
    elif(x_pred > 255):
        x_pred = 255

    return (int(x_pred), y_aver, pix_aver)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.HQVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking

uart = pyb.UART(3, 9600)
tx = 0

clock = time.clock()
res = []

while(True):
    clock.tick()
    img = sensor.snapshot().lens_corr(1.8)
    img.rotation_corr(z_rotation = 180)

    thresholds = [(15, 100, 0, 128, 24, 128)]

    img.binary(thresholds, invert = True, zero = True)
    img.draw_string(0, 0, str(clock.fps()), (255, 255, 0))

    blobs = img.find_blobs(thresholds)

    if(blobs != []):
        # 寻找最大色块
        max_blob = []
        for c in blobs:
            # 若不在识别边界,利用色块长宽比与色块与外框面积比确定是否为圆形
            if(c.y() >= 70 or c.x() >= 200 or c.x() <= 40 or (c.w() / c.h() > 0.8 and c.h() / c.w() > 0.8 and c.pixels() / (c.w() * c.h()) > 0.6 and c.pixels() / (c.w() * c.h()) < 0.85)):
                img.draw_rectangle(c.x(), c.y(), c.w(), c.h(), color = 255)
                img.draw_rectangle(c.x(), c.y(), 15, 10, color = 255, fill = True)
                img.draw_string(c.x(), c.y(), str(c.pixels()), (255, 255, 255))

                if(max_blob == [] or c.pixels() > max_blob.pixels()):
                    max_blob = c

        if(max_blob != []):
            img.draw_cross(max_blob.cx(), max_blob.cy(), color = (255, 0, 0), size = 5)
            res.append(max_blob)

        # 取近10次结果的平均值
        if(len(res) > 10):
            res.pop(0)
            aver = calc_blod(res)
            img.draw_string(0, 60, str(aver), (255, 255, 0))

            # 发送信息
            # 传输格式:0x03 + 0x45 + 'F' + x坐标 + y坐标 + 色块大小低8位 + 色块大小高8位
            tx = b"\x03\x45F" + bytes([aver[0], aver[1], aver[2] % 256, aver[2] // 256])
        else:
            img.draw_string(0, 60, str(len(res)), (255, 255, 0))
            tx = b"\x03\x45P\x00\x00\x00\x00"
    else:
        img.draw_string(0, 60, "Not found!", (255, 255, 0))
        res = []
        tx = b"\x03\x45N\x00\x00\x00\x00"

    img.draw_string(0, 120, "tx=" + str(tx), (255, 255, 0))
    uart.write(tx)
    pyb.delay(10)



