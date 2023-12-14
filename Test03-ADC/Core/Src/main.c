/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../../myLib/Src/myLib.c" // same level with project
									  // Core/Test03-ADC/ARM/myLib .....
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

/* USER CODE BEGIN PV */
short dValue[2] = { 0 }; // char(1) short(2) int(4, old int 2) long(4)

int xValue = -1; // "-1" is not generated from ADC, ADC => 0 ~ 4095
int yValue = -1;
int n = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* Single Conversion ------------------- */
//int getADCValue()
//{
//	HAL_ADC_Start(&hadc1); // Sampling -> Shift -> Shift Register & adding dummy process start
//
//	HAL_ADC_PollForConversion(&hadc1, 100); // stay until conversion finish, waiting()
//
//	int val = HAL_ADC_GetValue(&hadc1); // just read data (0 ~ 4095)
//
//	return val;
//}
/* ------------------------------------ */

//void noOperation()
//{
//
//}
//
//void myDelay(int ms)
//{
//	// make some delay with do nothing
//	for(int j = 0; j < ms; j++)
//	{
//		for(int i = 0; i < 500; i++)
//		{
//			noOperation();
//		}
//	}
//}

/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) // it only use 1 time
{
	// not used in main function
	// can't use return value

	// n is for channel info, Interrupt has no channel info

	if(!n)
	{
		xValue = HAL_ADC_GetValue(&hadc1);

		n++;
	}
	else
	{
		yValue = HAL_ADC_GetValue(&hadc1);
		printf("(interrupt) X value : %d\r\n", xValue);
		printf("(interrupt) Y value : %d\r\n", yValue);
		printf("(interrupt) Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));

		n = 0;
	}

	myDelay(5000);
//
//	HAL_ADC_Start_IT(&hadc1); // make ready for next interrupt
}*/

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

//  HAL_TIM_Base_Start(&htim2);
//
//  htim2.Instance->CNT = 0;
//  for(int i = 0; i < 100; i++)
//  {
//	  noOperation();
//  }
//  volatile int tt = htim2.Instance->CNT;
//
//  printf("noOperation function calling time : %d\r\n", tt);

  printf("\033[1J\033[1;1HProgram Started......\r\n");

  HAL_TIM_Base_Start(&htim3);

  //HAL_ADC_Start_IT(&hadc1);

  HAL_ADC_Start_DMA(&hadc1, (int*)dValue, sizeof(short)); // pData => DMA Memory address

  printf("ADC DMA started.....\r\n");

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Single Conversion --------------------- */
//	  printf("X value : %d\r\n", getADCValue());
//	  printf("Y value : %d\r\n", getADCValue());
//	  printf("Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));
//
//	  HAL_Delay(500);
	  /* --------------------------------------- */

	  /* Interrupt ----------------------------- */

	  // can't move out from interrupt loop

	  /* --------------------------------------- */

	  /* DMA ----------------------------------- */

	  printf("X value : %d\r\n", dValue[0]); // access to DMA Array
	  printf("Y value : %d\r\n", dValue[1]);
	  printf("Z value : %d\r\n\n", HAL_GPIO_ReadPin(Zaxis_GPIO_Port, Zaxis_Pin));

	  int targetVal = dValue[0] * 1000 / 4095;

	  printf("Conversion : %d\r\n", targetVal);

	  htim2.Instance->CCR1 = targetVal;

	  myDelay(500*1000);

	  /* --------------------------------------- */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
