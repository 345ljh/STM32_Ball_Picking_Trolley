#include "beep.h"

//以H_Xi的ARR为基准,通过乘一定比例确定其它音的ARR
#define BASE 500

#define L_Do (BASE * 7.553)
#define L_Re (BASE * 6.739)
#define L_Mi (BASE * 5.994)
#define L_Fa (BASE * 5.658)
#define L_So (BASE * 5.041)
#define L_La (BASE * 4.490)
#define L_Xi (BASE * 4)
#define M_Do (BASE * 3.777)
#define M_Re (BASE * 3.364)
#define M_Mi (BASE * 3.016)
#define M_Fa (BASE * 2.828)
#define M_So (BASE * 2.519)
#define M_La (BASE * 2.245)
#define M_Xi (BASE * 2)
#define H_Do (BASE * 1.887)
#define H_Re (BASE * 1.682)
#define H_Mi (BASE * 1.498)
#define H_Fa (BASE * 1.413)
#define H_So (BASE * 1.259)
#define H_La (BASE * 1.122)
#define H_Xi (BASE * 1)

song music_ready = {23, 
                    {L_So, 0, M_Do, 0, 0, M_Mi, M_Re, 0, M_Do, 0, 0, 0,
                     M_Mi, 0, M_So, 0, 0, M_La, M_Xi, 0, H_Do, H_Do, H_Do} };

song music_thank = {34, 
                    {M_Do, 0, M_Re, 0, M_Mi, 0, M_So, 0, M_Mi, 0, M_Mi, M_Mi, 0, 
                    M_Re, 0, M_Re, M_Do, 0, M_Re, M_Re, 0, 
                    M_Do, 0, L_La, 0, M_Do, 0, M_Re, 0, M_Mi, M_Mi, M_Mi, M_Mi, 0} };

void Beep_Play(song music)
{
    for(int i = 0; i <= music.size - 1; i++)
    {
        TIM8->ARR = music.buf[i];
        TIM8->CCR3 = TIM8->ARR * 0.1;
        HAL_Delay(100);
    }
    TIM8->ARR = 0;
    TIM8->CCR3 = 0;
}