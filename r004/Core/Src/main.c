/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

#include "main.h"
#include "string.h"
// #include "cmsis_os.h" 
// cmsis 라이브러리 대신에 freertos 라이브러리를 사용, 이유 ?  세마포어 카운팅에 대해 좀더 쉽게 설명
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "string.h"






/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>  
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
UART_HandleTypeDef huart3;

//osThreadId taskHandle1;
//osThreadId taskHandle2;
//osThreadId taskHandle3;

//osSemaphoreId semephoreHandle;



TaskHandle_t HPThandler;
TaskHandle_t MPThandler;
TaskHandle_t LPThandler;
TaskHandle_t VLPThandler;
/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
void hptTask(void const * argument);
void mptTask(void const * argument);
void lptTask(void const * argument);
void vlptTask(void const * argument);

SemaphoreHandle_t CountingSem;

int resource[3] = {111,222,333};
int indx = 0;

uint8_t rx_data = 0;



/* USER CODE BEGIN PFP */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t indx = 0;
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
  MX_USART3_UART_Init();
  HAL_UART_Receive_IT(&huart3, &rx_data,1); //  마지막 사이즈
  CountingSem  = xSemaphoreCreateCounting(3,0) ; // 3개의 자원을 가진 세마포어 생성, 초기값은 0
  if(CountingSem == NULL){ // NULL이면 세마포어 생성 실패
    const char *str1 = "Semaphore Create Failed\r\n";
    HAL_UART_Transmit(&huart3, (uint8_t *)str1, strlen(str1), 100); // 25는 문자열 길이, 100 은 타임아웃
  } else{
    const char *str2 = "Semaphore Create Success\r\n\r\n";
    HAL_UART_Transmit(&huart3, (uint8_t *)str2, strlen(str2), 100); // 25는 문자열 길이, 100 은 타임아웃
  }



  
  
  // BaseType_t xTaskCreate(	
               // TaskFunction_t pxTaskCode,
							// const char * const pcName,		/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
							// const configSTACK_DEPTH_TYPE usStackDepth,
							// void * const pvParameters,
							// UBaseType_t uxPriority,
							// TaskHandle_t * const pxCreatedTask )

  xTaskCreate(hptTask, "HPT", 128, NULL, 3, & HPThandler ); 
  xTaskCreate(mptTask, "MPT", 128, NULL, 2, & MPThandler ); 
  xTaskCreate(lptTask, "LPT", 128, NULL, 1, & LPThandler ); 
  xTaskCreate(vlptTask, "VLPT", 128, NULL, 0, & VLPThandler ); 

  vTaskStartScheduler();
  
  xSemaphoreTake(CountingSem, portMAX_DELAY); // 세마포어를 획득, 3개의 자원중 하나를 획득
  


  /* USER CODE BEGIN 2 */
  

  /* USER CODE END 2 */
  


   
   
   

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

/* 

  osPriorityIdle          = -3,          ///< priority: idle (lowest)
  osPriorityLow           = -2,          ///< priority: low
  osPriorityBelowNormal   = -1,          ///< priority: below normal
  osPriorityNormal        =  0,          ///< priority: normal (default)
  osPriorityAboveNormal   = +1,          ///< priority: above normal
  osPriorityHigh          = +2,          ///< priority: high
  osPriorityRealtime      = +3,          ///< priority: realtime (highest)
  osPriorityError         =  0x84        ///< system cannot determine priority or thread has illegal priority
} osPriority;
*/
/*

osSemaphoreId semephoreHandle;
osSemaphoreDef(BinSem);
osSemaphoreCreate(osSemaphore(BinSem), 1);
osSemaphoreWait(semephoreHandle, osWaitForever);
osSemaphoreRelease(semephoreHandle);
osSemaphoreWait(semephoreHandle, osWaitForever);
osSemaphoreRelease(semephoreHandle);

*/

  osSemaphoreDef(TestBinary);
  semephoreHandle = osSemaphoreCreate(osSemaphore(TestBinary), 1);
  osThreadDef(task1, oneTask, osPriorityBelowNormal, 0, 128);
  osThreadDef(task2, twoTask, osPriorityNormal, 0, 128);
  osThreadDef(task3, threeTask, osPriorityHigh, 0, 128);
  taskHandle1 = osThreadCreate(osThread(task1), NULL);
  taskHandle2 = osThreadCreate(osThread(task2), NULL);
  taskHandle3 = osThreadCreate(osThread(task3), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);



  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void oneTask(void const * argument){
  /* Infinite loop */
  for(;;)
  {
		char *str1 = "Entered LOWTask and waiting for semaphore\r\n";
		HAL_UART_Transmit(&huart3, (uint8_t *) str1, strlen (str1), 100);

		osSemaphoreWait(semephoreHandle, osWaitForever);

		char *str3 = "Semaphore acquired by LOW Task\n";
		HAL_UART_Transmit(&huart3, (uint8_t *) str3, strlen (str3), 100);

		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait till the pin go low

		char *str2 = "Leaving LOWTask and releasing Semaphore\r\n\n";
		HAL_UART_Transmit(&huart3, (uint8_t *) str2, strlen (str2), 100);

		osSemaphoreRelease(semephoreHandle);
		osDelay(500);
  }
}
void twoTask(void const * argument){
  /* Infinite loop */
 /* Infinite loop */
  for(;;)
  {
		char *str1 = "Entered MediumTask\n";
		HAL_UART_Transmit(&huart3, (uint8_t *) str1, strlen (str1), 100);


		char *str2 = "Leaving MediumTask\n\n";
		HAL_UART_Transmit(&huart3, (uint8_t *) str2, strlen (str2), 100);
		osDelay(500);
  }
}
void threeTask(void const * argument){
  /* Infinite loop */
  /* Infinite loop */
  for(;;)
  {
	char *str1 = "Entered HighTask and waiting for Semaphore\r\n";
	HAL_UART_Transmit(&huart3, (uint8_t *) str1, strlen (str1), 100);

	osSemaphoreWait(semephoreHandle, osWaitForever);

	char *str3 = "Semaphore acquired by HIGH Task\n";
	HAL_UART_Transmit(&huart3, (uint8_t *) str3, strlen (str3), 100);

	char *str2 = "Leaving HighTask and releasing Semaphore\r\n\n";
	HAL_UART_Transmit(&huart3, (uint8_t *) str2, strlen (str2), 100);

	osSemaphoreRelease(semephoreHandle);
    osDelay(500);
  }
}





/* USER CODE END 4 */





/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
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

#ifdef  USE_FULL_ASSERT
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
