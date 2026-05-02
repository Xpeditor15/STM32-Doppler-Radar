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
#include "adc.h"
#include "comp.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */
//TIM_HandleTypeDef htim1;
//UART_HandleTypeDef huart2;

//variables for comparator
int flag = 0;

int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 50);
	return ch;
}

char uart_buf[50] = "\0";
int uart_buf_len = 0;

ADC_PARAM ADC_parameter = {0};
FFT_RESULTS FFT_results = {0};
Velocity velocity = {0};
bool adcIsReady = false;

char TxData[16];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

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
	char uart_buf[50] = "\0";
	int uart_buf_len = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_COMP1_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  HAL_COMP_Start(&hcomp1);
  HAL_TIM_Base_Start_IT(&htim1);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);

  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
  HAL_ADC_Start_DMA(&hadc1, ADC_BUFFER, ADC_BUFFER_SIZE);



  initFFT(&ADC_params, &FFT_res);
  HAL_Delay(100);
  initComp();
  HAL_Delay(100);
  lcdInit();
  HAL_Delay(100);
  lcdClear();
  HAL_Delay(10);

  lcdSetCursor(0, 0);
  lcdPrint("System");
  lcdSetCursor(1, 0);
  lcdPrint("Initialized!");

  HAL_Delay(100);
  lcdClear();

  lcdSetCursor(0, 0);
  lcdPrint("Freq: ");






  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*int freqResult = (int)ceil(FFT_res.favg);
	  	  if (freqResult != previousADCFreq || freqResult == previousADCFreq) {
	  		  previousADCFreq = freqResult;
	  		  lcdClear();
	  		  lcdSetCursor(0, 0);
	  		  lcdPrint("Freq: ");
	  		  lcdSetCursor(1, 0);
	  		  char freqString[10];
	  		  sprintf(freqString, "%d Hz", freqResult);
	  		  lcdPrint(freqString);
	  	  }
	  	uart_buf_len = sprintf(uart_buf, "Bruh \r\n");
	  	HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 10);*/
	  /*int freqResult = (int)ceil(FFT_res.favg);
	  lcdClear();
	  lcdSetCursor(0, 0);
	  lcdPrint("Freq: ");
	  lcdSetCursor(1, 0);
	  char freqString[10];
	  sprintf(freqString, "%d Hz", freqResult);
	  lcdPrint(freqString);
	  uart_buf_len = sprintf(uart_buf, "Bleh \r\n");
	  HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 10);*/
	  //calcFreqComp();

	  //if (adcIsReady) {
		  //calcFreqAvg();
		  /*int freqResult = (int)ceil(FFT_res.favg);
		  lcdClear();
		  lcdSetCursor(0, 0);
		  lcdPrint("Freq: ");
		  lcdSetCursor(1, 0);
		  char freqString[10];
		  sprintf(freqString, "%d Hz", freqResult);
		  lcdPrint(freqString);*/
		  //adcPage();
		  /*calcFreqComp();
		  comPage();
		  uart_buf_len = sprintf(uart_buf, "HALO \r\n");
		  HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 10);
		  adcIsReady = false;
	  }*/

	  mapButtons();
	  displayPage();
	  HAL_Delay(50);

	  /*uint8_t test = 5;
	  //uint8_t bcd = velocityToPacket(test);
	  sendPacket(&test);*/

	  /*
	   Right: 0
	   Up: 750
	   Down: 1810
	   Left: 2860
	   Select: 4095
	   */

	  /*if (adcIsReady) {
	  	calcFreqAvg();
	  }
	  HAL_ADC_Start(&hadc2);
	  HAL_ADC_PollForConversion(&hadc2, 100);
	  uint16_t raw = (uint16_t) HAL_ADC_GetValue(&hadc2);
	  uart_buf_len = sprintf(uart_buf, "%u \r\n", raw);
	  HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 100);
		*/

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
