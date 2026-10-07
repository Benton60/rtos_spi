/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
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

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for genPrimes */
osThreadId_t genPrimesHandle;
uint32_t MyBufferTask02[ 128 ];
osStaticThreadDef_t MycontrolBlocTask02;
const osThreadAttr_t genPrimes_attributes = {
  .name = "genPrimes",
  .stack_mem = &MyBufferTask02[0],
  .stack_size = sizeof(MyBufferTask02),
  .cb_mem = &MycontrolBlocTask02,
  .cb_size = sizeof(MycontrolBlocTask02),
  .priority = (osPriority_t) osPriorityLow7,
};
/* Definitions for formatter */
osThreadId_t formatterHandle;
uint32_t MyBufferTask03[ 128 ];
osStaticThreadDef_t MycontrolBlocTask03;
const osThreadAttr_t formatter_attributes = {
  .name = "formatter",
  .stack_mem = &MyBufferTask03[0],
  .stack_size = sizeof(MyBufferTask03),
  .cb_mem = &MycontrolBlocTask03,
  .cb_size = sizeof(MycontrolBlocTask03),
  .priority = (osPriority_t) osPriorityAboveNormal4,
};
/* Definitions for SPIOut */
osThreadId_t SPIOutHandle;
uint32_t MyBufferTask04[ 128 ];
osStaticThreadDef_t MycontrolBlocTask04;
const osThreadAttr_t SPIOut_attributes = {
  .name = "SPIOut",
  .stack_mem = &MyBufferTask04[0],
  .stack_size = sizeof(MyBufferTask04),
  .cb_mem = &MycontrolBlocTask04,
  .cb_size = sizeof(MycontrolBlocTask04),
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for formatterToSPI */
osMutexId_t formatterToSPIHandle;
osStaticMutexDef_t myMutexControlBlock01;
const osMutexAttr_t formatterToSPI_attributes = {
  .name = "formatterToSPI",
  .cb_mem = &myMutexControlBlock01,
  .cb_size = sizeof(myMutexControlBlock01),
};
/* Definitions for primesToFormatter */
osMessageQueueId_t primesToFormatterHandle;
uint8_t myQueueBuffer01[ 16 * sizeof( uint16_t ) ];
osStaticMessageQDef_t myQueueControlBlock01;
const osMessageQueueAttr_t primesToFormatter_attributes = {
  .name = "primesToFormatter",
  .cb_mem = &myQueueControlBlock01,
  .cb_size = sizeof(myQueueControlBlock01),
  .mq_mem = &myQueueBuffer01,
  .mq_size = sizeof(myQueueBuffer01)
};
/* Definitions for asciiFromFormatter */
osMessageQueueId_t asciiFromFormatterHandle;
uint8_t myQueueBuffer02[ 5 * sizeof( uint32_t ) ];
osStaticMessageQDef_t myQueueControlBlock02;
const osMessageQueueAttr_t asciiFromFormatter_attributes = {
  .name = "asciiFromFormatter",
  .cb_mem = &myQueueControlBlock02,
  .cb_size = sizeof(myQueueControlBlock02),
  .mq_mem = &myQueueBuffer02,
  .mq_size = sizeof(myQueueBuffer02)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* creation of formatterToSPI */
  formatterToSPIHandle = osMutexNew(&formatterToSPI_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */
  /* creation of primesToFormatter */
  primesToFormatterHandle = osMessageQueueNew (16, sizeof(uint16_t), &primesToFormatter_attributes);
  /* creation of asciiFromFormatter */
  asciiFromFormatterHandle = osMessageQueueNew (5, sizeof(uint32_t), &asciiFromFormatter_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of genPrimes */
  genPrimesHandle = osThreadNew(genPrimesMain, NULL, &genPrimes_attributes);

  /* creation of formatter */
  formatterHandle = osThreadNew(formatterMain, NULL, &formatter_attributes);

  /* creation of SPIOut */
  SPIOutHandle = osThreadNew(SPIOutMain, NULL, &SPIOut_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_genPrimesMain */
/**
* @brief Function implementing the genPrimes thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_genPrimesMain */
void genPrimesMain(void *argument)
{
  /* USER CODE BEGIN genPrimes */
  /* Infinite loop */
  for(;;) {

     int16_t n = (GPIOC->IDR >> 3) & 0x7FF;

     uint8_t isPrime = 1;
     if (n <= 1)
         isPrime = 0;
     else if (n == 2)
         isPrime = 1;
     else if (n % 2 == 0)
	     isPrime = 0;
     else {
         for (int i = 3; i * i <= n; i += 2) {
             if (n % i == 0) {
                 isPrime = 0;
                 break;
             }
          }
      }
      if (isPrime == 0){
    	  n = -n;
      }
	  osMessageQueuePut(primesToFormatterHandle, &n, 0, osWaitForever);
	  osDelay(2000);
   }
  /* USER CODE END genPrimes */
}

/* USER CODE BEGIN Header_formatterMain */
/**
* @brief Function implementing the formatter thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_formatterMain */
void formatterMain(void *argument)
{
  /* USER CODE BEGIN formatter */
  /* Infinite loop */
	static char numbers[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '+'};
	static char digits_in_ascii[5] = {' ', ' ', ' ', ' ', ' '};
  for(;;)
  {
	  int16_t number = 0;
	  osMessageQueueGet(primesToFormatterHandle, &number, 0, osWaitForever);
	  osMutexAcquire(formatterToSPIHandle, osWaitForever);

	  //sign
	  if (number < 0){
		  number = -number;
		  digits_in_ascii[0] = numbers[10];
	  }else{
		  digits_in_ascii[0] = numbers[11];
	  }


	  for(int i = 4; i > 0; i--){
		  digits_in_ascii[i] = numbers[number % 10];
		  number = number / 10;
	  }

	  char * pointer_to_ascii = digits_in_ascii;

	  osMessageQueuePut(asciiFromFormatterHandle, &pointer_to_ascii, 0, osWaitForever); //Pointer to a pointer :(
	  osMutexRelease(formatterToSPIHandle);
  }
  /* USER CODE END formatter */
}

/* USER CODE BEGIN Header_SPIOutMain */
/**
* @brief Function implementing the SPIOut thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SPIOutMain */
void SPIOutMain(void *argument)
{
  /* USER CODE BEGIN SPIOut */
	LL_SPI_Enable(SPI1);
	uint8_t local_array[5];
	uint8_t peripheral_init_bytes[4] = {0x13, 0x17, 0x3f, 0xaa};
	uint8_t *pointer_to_array;

	  /* Send SPI initialization bytes */
    GPIOC->ODR &= ~0x0004;
	for(int i = 0; i < 4; i++){
		LL_SPI_TransmitData8(SPI1, peripheral_init_bytes[i]);
		for (int j = 0; j < 1234; j++){
			if(!LL_SPI_IsActiveFlag_BSY(SPI1))
				break;
		}
	}
    GPIOC->ODR |= 0x0004;
  /* Infinite loop */
	for(;;)
	{
	    osMessageQueueGet(asciiFromFormatterHandle, &pointer_to_array, 0, osWaitForever);

	    osMutexAcquire(formatterToSPIHandle, osWaitForever);

	    for(int i = 0; i < 5; i++) {
	        local_array[i] = pointer_to_array[i];
	    }

	    osMutexRelease(formatterToSPIHandle);
	    GPIOC->ODR &= ~0x0004;
	    for(int i = 0; i < 5; i++) {
	        LL_SPI_TransmitData8(SPI1, local_array[i]);
	        for (int j = 0; j < 1234; j++){
	        	if(!LL_SPI_IsActiveFlag_BSY(SPI1))
	        		break;
	        }
	    }
	    GPIOC->ODR |= 0x0004;
	}

  /* USER CODE END SPIOut */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

