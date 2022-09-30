/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "spi.h"
#include "ps2.h"
#include "motor.h"
#include "beep.h"
#include "tft.h"
#include "malloc.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MV_LEN 7
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t ps2_rx[9] = {0};
uint8_t mv_rx[MV_LEN] = {0};

motor* motor_lf = NULL;
motor* motor_lb = NULL;
motor* motor_rf = NULL;
motor* motor_rb = NULL;

robot_state state;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId Image_TaskHandle;
osThreadId PS2_Recv_TaskHandle;
osThreadId MotorServo_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartImageTask(void const * argument);
void StartPS2Task(void const * argument);
void StartMotorServoTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Image_Task */
  osThreadDef(Image_Task, StartImageTask, osPriorityNormal, 0, 128);
  Image_TaskHandle = osThreadCreate(osThread(Image_Task), NULL);

  /* definition and creation of PS2_Recv_Task */
  osThreadDef(PS2_Recv_Task, StartPS2Task, osPriorityNormal, 0, 128);
  PS2_Recv_TaskHandle = osThreadCreate(osThread(PS2_Recv_Task), NULL);

  /* definition and creation of MotorServo_Task */
  osThreadDef(MotorServo_Task, StartMotorServoTask, osPriorityNormal, 0, 128);
  MotorServo_TaskHandle = osThreadCreate(osThread(MotorServo_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  HAL_TIM_Base_Start(&htim5);   //delay_us
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);   //控制蜂鸣�????????
  TIM8->ARR = 0;
  TIM8->CCR3 = 0;
  Beep_Play(music_ready);
  state.control = INIT;
  /* Infinite loop */
  
  for(;;)
  {
    if(state.music) Beep_Play(music_thank);
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartImageTask */
/**
* @brief Function implementing the Image_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartImageTask */
void StartImageTask(void const * argument)
{
  /* USER CODE BEGIN StartImageTask */
  TFT_Init();
  TFT_Fill(1, 0, 240, 320, 0);
  TFT_Test();

  TFT_DrawStr(16, 10, "CONNECTION:", RGB2565(200, 184, 248));
  TFT_DrawStr(50, 30, "VISUAL:", RGB2565(200, 184, 248));
  TFT_DrawStr(42, 50, "CONTROL:", RGB2565(200, 184, 248));
  TFT_DrawStr(42, 70, "X_SPEED:", RGB2565(200, 184, 248));
  TFT_DrawStr(42, 90, "Y_SPEED:", RGB2565(200, 184, 248));
  TFT_DrawStr(42, 110, "W_SPEED:", RGB2565(200, 184, 248));
  TFT_DrawStr(48, 130, "FRAME:", RGB2565(200, 184, 248));
  /* Infinite loop */
  for(;;)
  {
    HAL_UART_Receive_DMA(&huart3, mv_rx, MV_LEN);
    //Openmv收到的数据可能错位
    int index = -1;
    for(int i = 0; i <= MV_LEN - 1; i++)
    {
      if(mv_rx[i] == 0x03)
      {
        if(mv_rx[(i + 1) % MV_LEN] == 0x45)
        {
          index = i;
          break;
        }
      }
    }

    //判断与Openmv通信情况
    if(index != -1)
    {
      state.connect = SUCCEED;
      TFT_DrawStr(122, 10, "SUCCEED", RGB2565(0, 255, 0));

      switch (mv_rx[(index + 2) % MV_LEN])
      {
      case 'F':
        state.ballx = mv_rx[(index + 3) % MV_LEN];
        state.bally = mv_rx[(index + 4) % MV_LEN];
        state.ballpix = mv_rx[(index + 5) % MV_LEN] + (mv_rx[(index + 6) % MV_LEN] << 8);
        TFT_DrawStr(122, 30, "FIND    ", RGB2565(0, 255, 0));
        break;
      case 'N':
      case 'P':
        state.ballx = 0;
        state.bally = 0;
        state.ballpix = 0;
        TFT_DrawStr(122, 30, "NOT FIND", RGB2565(255, 30, 30));
        break;
      }
    }
    else
    {
      state.connect = FAILED;
      state.ballx = 0;
      state.bally = 0;
      state.ballpix = 0;
      TFT_DrawStr(122, 10, "FAILED ", RGB2565(255, 30, 30));
    }

    //显示运动信息
    if(state.control == REMOTE) TFT_DrawStr(122, 50, "REMOTE", RGB2565(142, 214, 232));
    else TFT_DrawStr(122, 50, "AUTO  ", RGB2565(255, 209, 53));

    TFT_DrawStr(122, 70, TFT_Itoa(state.vx), RGB2565(255, 128, 192));
    TFT_DrawStr(122, 90, TFT_Itoa(state.vy), RGB2565(255, 128, 192));
    TFT_DrawStr(122, 110, TFT_Itoa(state.rorate), RGB2565(255, 128, 192));

    if(state.frame == UP) TFT_DrawStr(122, 130, "UP  ", RGB2565(142, 214, 232));
    else TFT_DrawStr(122, 130, "DOWN", RGB2565(255, 209, 53));
    
    osDelay(1);
  }
  /* USER CODE END StartImageTask */
}

/* USER CODE BEGIN Header_StartPS2Task */
/**
* @brief Function implementing the PS2_Recv_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPS2Task */
void StartPS2Task(void const * argument)
{
  /* USER CODE BEGIN StartPS2Task */
  /* Infinite loop */
  for(;;)
  {
    PS2_ReadData(ps2_rx);
    PS2_Solve(&state, ps2_rx);
    osDelay(1);
  }
  /* USER CODE END StartPS2Task */
}

/* USER CODE BEGIN Header_StartMotorServoTask */
/**
* @brief Function implementing the MotorServo_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotorServoTask */
void StartMotorServoTask(void const * argument)
{
  /* USER CODE BEGIN StartMotorServoTask */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

  motor_lf = (motor*)malloc(sizeof(motor));
  motor_rf = (motor*)malloc(sizeof(motor));
  motor_rb = (motor*)malloc(sizeof(motor));
  motor_lb = (motor*)malloc(sizeof(motor));

  Motor_Init(motor_lf, &TIM2->CCR1, GPIOA, GPIO_PIN_8, GPIO_PIN_9);
  Motor_Init(motor_rf, &TIM2->CCR2, GPIOA, GPIO_PIN_11, GPIO_PIN_10);
  Motor_Init(motor_rb, &TIM2->CCR3, GPIOC, GPIO_PIN_11, GPIO_PIN_10);
  Motor_Init(motor_lb, &TIM2->CCR4, GPIOB, GPIO_PIN_5, GPIO_PIN_4);

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

  state.frame = UP;
  state.vx = 0;
  state.vy = 0;
  state.rorate = 0;
  state.direct = RIGHT;
  /* Infinite loop */
  for(;;)
  {
    Motor_Control(motor_lf, motor_rf, motor_rb, motor_lb, &state);

    if(state.frame == UP)
    {
      TIM4->CCR1 = TIM4-> ARR * 0.06;
      TIM4->CCR2 = TIM4-> ARR * 0.09;
    }
    else if(state.frame == DOWN)
    {
      TIM4->CCR1 = TIM4-> ARR * 0.03;
      TIM4->CCR2 = TIM4-> ARR * 0.12;
    }

    osDelay(1);
  }
  /* USER CODE END StartMotorServoTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

