/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
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
#define INPUTMODE 0b00
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint16_t CCR1Value = 700;
volatile uint8_t flagLeft = 0;
volatile uint8_t flagRight = 0;
const int MSGBUFSIZE = 80;
const int MAX_TURN_RIGHT = 500;
const int MAX_TURN_LEFT = 2600;
int turnValue = 150;
int servoPin = 0;
char msgBuf[MSGBUFSIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */  
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  // ES Course Comments: Uncomment the three lines below to enable FreeRTOS.
  //osKernelInitialize(); /* Call init function for freertos objects (in freertos.c) */
  //MX_FREERTOS_Init();
  //osKernelStart(); /* Start scheduler */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  InitRotoryEncoder(GPIOA);

  InitPWMTimerAndGPIOAFReg(TIM2, TIM2_IRQn, GPIOA, servoPin);

  // const int MSGBUFSIZE = 80;
  // char msgBuf[MSGBUFSIZE];
  // snprintf(msgBuf, MSGBUFSIZE, "%s", "Hello World!\r\n");
  // HAL_UART_Transmit(&huart2, (uint8_t *)msgBuf, strlen(msgBuf), HAL_MAX_DELAY);
  while (1)
  {
    CheckUartReceive();

    CheckFlags();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
