/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern UART_HandleTypeDef huart2;
osMutexId_t mutexId;

volatile uint16_t CCR1Value = 1000;
volatile int flagLeft = 0;
volatile int flagRight = 0;
const int MAX_TURN_RIGHT = 500;
const int MAX_TURN_LEFT = 2600;
int turnValue = 100;
int servoPin = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t servotaskHandle;
const osThreadAttr_t servotask_attributes = {
    .name = "ServoTask",
    .attr_bits = osThreadDetached,
    .cb_mem = NULL,
    .cb_size = 0,
    .stack_mem = NULL,
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
    .tz_module = 0,
    .reserved = 0};

osThreadId_t rotaryencodertaskHandle;
const osThreadAttr_t rotaryencodertask_attributes = {
    .name = "RotaryEncoderTask",
    .attr_bits = osThreadDetached,
    .cb_mem = NULL,
    .cb_size = 0,
    .stack_mem = NULL,
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal1,
    .tz_module = 0,
    .reserved = 0};

osThreadId_t uartrecievetaskHandle;
const osThreadAttr_t uartrecievetask_attributes = {
    .name = "UartRecieveTask",
    .attr_bits = osThreadDetached,
    .cb_mem = NULL,
    .cb_size = 0,
    .stack_mem = NULL,
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal2,
    .tz_module = 0,
    .reserved = 0};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartServoTask(void *argument);
void StartRotaryEncoderTask(void *argument);
void StartUartRecieveTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
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
  /* creation of defaultTask */
  rotaryencodertaskHandle = osThreadNew(StartRotaryEncoderTask, NULL, &rotaryencodertask_attributes);
  servotaskHandle = osThreadNew(StartServoTask, NULL, &servotask_attributes);
  uartrecievetaskHandle = osThreadNew(StartUartRecieveTask, NULL, &uartrecievetask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */

extern "C" void EXTI1_IRQHandler(void) 
{ 
  if ((GPIOA->IDR & GPIO_IDR_4) != 0) 
  {
    flagRight = 1;
  }
  else if ((GPIOA->IDR & GPIO_IDR_4) == 0)
  {
    flagLeft = 1;
  }
  
  EXTI->PR = EXTI_PR_PR1; 
}

void CheckUartReceive()
{
  char rxChar = '\0';

  HAL_UART_Receive(&huart2, (uint8_t*)&rxChar, 1, 10);

  switch(rxChar)
  {
    case 'r':
      CCR1Value = MAX_TURN_RIGHT;
      TIM2->CCR1 = CCR1Value;
      break;

    case 'l':
      CCR1Value = MAX_TURN_LEFT;
      TIM2->CCR1 = CCR1Value;
      break;

    case 'c':
      CCR1Value = (MAX_TURN_RIGHT + MAX_TURN_LEFT) / 2;
      TIM2->CCR1 = CCR1Value;
      break;
  }
}

void TurnServoRight()
{
  CCR1Value -= turnValue;
  if(CCR1Value < MAX_TURN_RIGHT)
  {
    CCR1Value = MAX_TURN_RIGHT;
  }

  TIM2->CCR1 = CCR1Value;
}

void TurnServoLeft()
{
  CCR1Value += turnValue;
  if(CCR1Value >= MAX_TURN_LEFT)
  {
    CCR1Value = MAX_TURN_LEFT;
  }
  TIM2->CCR1 = CCR1Value;
}

void CheckFlags()
{
  if(flagLeft)
  {
    TurnServoLeft();
    flagLeft = 0;
  }
  else if (flagRight)
  {
    TurnServoRight();

    flagRight = 0;
  }
}

void InitRotoryEncoder(GPIO_TypeDef* port)
{
  SYSCFG->EXTICR[1] = (SYSCFG->EXTICR[1] & ~SYSCFG_EXTICR1_EXTI1) | (0b0000 << SYSCFG_EXTICR1_EXTI1_Pos); // PA1 -> EXTI1
  EXTI->FTSR = EXTI_FTSR_TR1; 
  EXTI->IMR = EXTI_IMR_MR1; 
  NVIC_EnableIRQ(EXTI1_IRQn);
}

void InitPWMTimerAndGPIOAFReg(TIM_TypeDef* timer, IRQn_Type interruptPort, GPIO_TypeDef* port, uint8_t pin)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN_Msk << RCC_APB1ENR_TIM2EN_Pos;

  timer->PSC = (72-1);
  timer->ARR = 20000;

  timer->CCMR1 |= ((0x3) << 5);
  timer->CCR1 = CCR1Value; //set begin position
  timer->CCER |= TIM_CCER_CC1E; //0x1 << 0;
  timer->CR1 |= TIM_CR1_CEN; //0x1 << 0;

  port->MODER = (port->MODER & ~(pin * 2)) | (0b10 << (pin * 2)); //init alternate function
  port->AFR[0] = (port->AFR[0] & ~(pin)) | (0b0001 << (pin * 4)); //set alternate function af1 to pa0
}

void StartServoTask(void *argument)
{
  InitPWMTimerAndGPIOAFReg(TIM2, TIM2_IRQn, GPIOA, 0);

  for (;;)
  {

  }
}

void StartUartRecieveTask(void *argument)
{
  for (;;)
  {
    osMutexAcquire(mutexId, osWaitForever);
    CheckUartReceive();
    osMutexRelease(mutexId);
    osDelay(20);
  }
}

void StartRotaryEncoderTask(void *argument)
{
  InitRotoryEncoder(GPIOA);

  for (;;)
  {
    osMutexAcquire(mutexId, osWaitForever);
    CheckFlags();

    char buffer[100];
    sprintf(buffer, "CCR1Value: %d\n", CCR1Value);
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 10);

    osMutexRelease(mutexId);
    osDelay(20);
  }
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
