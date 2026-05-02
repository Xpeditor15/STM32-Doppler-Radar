/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
double dcOffset = 1.7;
int MAX_BUFFER = ADC_BUFFER_SIZE - 1;
double adcFreq;
uint32_t globalAdcError = 0;

ADC_PARAM ADC_params;
FFT_RESULTS FFT_res;
//Velocity velocity;

lastAdcFreq = 0;

uint16_t ADC_BUFFER[ADC_BUFFER_SIZE];

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV32;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_92CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}
/* ADC2 init function */
void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV32;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_92CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

static uint32_t HAL_RCC_ADC_CLK_ENABLED=0;

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    HAL_RCC_ADC_CLK_ENABLED++;
    if(HAL_RCC_ADC_CLK_ENABLED==1){
      __HAL_RCC_ADC_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN6
    PA4     ------> ADC1_IN9
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Request = DMA_REQUEST_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */
    /* ADC2 clock enable */
    HAL_RCC_ADC_CLK_ENABLED++;
    if(HAL_RCC_ADC_CLK_ENABLED==1){
      __HAL_RCC_ADC_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC2 GPIO Configuration
    PA0     ------> ADC2_IN5
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC2_MspInit 1 */

  /* USER CODE END ADC2_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC_CLK_ENABLED--;
    if(HAL_RCC_ADC_CLK_ENABLED==0){
      __HAL_RCC_ADC_CLK_DISABLE();
    }

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN6
    PA4     ------> ADC1_IN9
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_4);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC_CLK_ENABLED--;
    if(HAL_RCC_ADC_CLK_ENABLED==0){
      __HAL_RCC_ADC_CLK_DISABLE();
    }

    /**ADC2 GPIO Configuration
    PA0     ------> ADC2_IN5
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void initFFT(ADC_PARAM *ADC_parameter, FFT_RESULTS *FFT_results) {
	ADC_params = *ADC_parameter;
	FFT_res = *FFT_results;
	ADC_params.clockSpeed = 64000000;
	ADC_params.prescaler = 32;
	ADC_params.bits = 12;
	ADC_params.samplingTime = 92.5;
	ADC_params.ADC_buffer = ADC_BUFFER;
	ADC_params.ADC_buffer_size = ADC_BUFFER_SIZE;
	HAL_Delay(2000);
}

void calcFFT() {
	static float adc_float[ADC_BUFFER_SIZE];

	for (int i = 0; i < ADC_BUFFER_SIZE; i++) {
		adc_float[i] = (float) ADC_BUFFER[i] - 2048.0f;
	}

	arm_rfft_fast_instance_f32 S;
	arm_rfft_fast_init_f32(&S, ADC_BUFFER_SIZE);

	static float fft_output[ADC_BUFFER_SIZE];

	arm_rfft_fast_f32(&S, adc_float, fft_output, 0);

	static float results[ADC_BUFFER_SIZE / 2];

	arm_cmplx_mag_f32(fft_output, results, ADC_BUFFER_SIZE/2);
	results[0]=0;

	arm_max_f32(results, ADC_BUFFER_SIZE/2, &FFT_res.magnitude, &FFT_res.index);

	double measurementDuration;
	if (ADC_params.bits == 12) {
		measurementDuration = 12.5;
	}

	double conversionTime = ADC_params.samplingTime + measurementDuration;
	double samplingFreq = (float) (ADC_params.clockSpeed + 50000) / (float) ADC_params.prescaler / conversionTime;
	float bin = (float) ADC_params.clockSpeed / (float) ADC_params.prescaler / conversionTime / (float) ADC_BUFFER_SIZE;
	//float bin = (float) bin / (float) ADC_BUFFER_SIZE;

	FFT_res.fdominant = FFT_res.index * bin;
}

double calcFreqADC(uint16_t *beginning, uint16_t length) {
	int offsetADC = round(4096/3.3*dcOffset);

	bool wasAbove = false;
	bool currentlyAbove = false;

	bool firstTime = true;

		int indexLimit = 1000;

		int indexTracker[indexLimit];
		int indexTrackerLength = 0;

		for (int i = 0; i<length; i++) { //iterate through ADC buffer and identify zero crossings
				currentlyAbove = (beginning[i] > offsetADC);

				if (firstTime) {
					wasAbove = currentlyAbove;
					firstTime = false;
					continue;
				}

				if (abs(beginning[i] - offsetADC) < 320) { //if the value is close to offset value -> crossing zero
					if ((wasAbove && !currentlyAbove) || (!wasAbove && currentlyAbove)) { //if from >0 change to <0 or vice versa
						if (indexTrackerLength < indexLimit) {
							indexTracker[indexTrackerLength] = i;
							indexTrackerLength++; //checked, able to identify values close to 2110+-
						} else break;
					}
				}
				wasAbove = currentlyAbove;
			}

		double adcClkSpeed = ADC_params.clockSpeed / ADC_params.prescaler;
		double samplingTime = (12.5 + 92.5) * 1 / adcClkSpeed;

		//check if indexTracker is valid and even
		if (indexTrackerLength % 2 != 0 && indexTrackerLength > 1) indexTrackerLength -= 1; //it is odd length
		else if (indexTrackerLength % 2 != 0 && indexTrackerLength < 2) return -1; //indicate that no correct signal is found

		double elapsedTime = 0;

		for (int i = 1; i < indexTrackerLength; i++) {
			double deltaTick = indexTracker[i] - indexTracker[i-1];
			double deltaTime = deltaTick * samplingTime;
			//uart_buf_len = sprintf(uart_buf, "Delta Time: %lf\r\n", deltaTime);
			//uartPrint();
			elapsedTime += deltaTime;
		}

		double averageTime = (elapsedTime / (indexTrackerLength - 1)) * 2;

		//uart_buf_len = sprintf(uart_buf, "Average time: %lf \r\n", averageTime);
		//uartPrint();


		return 1/averageTime;
}

void calcFreqAvg() {
	lastAdcFreq = FFT_res.favg;
	double frequency = calcFreqADC(ADC_BUFFER, ADC_BUFFER_SIZE/2);
	calcFFT();
	double averageFreq = (0 * frequency + 2 * FFT_res.fdominant) / 2;
	int test = (int)ceil(frequency);
	int freqResult = (int)ceil(averageFreq);
	uart_buf_len = sprintf(uart_buf, "%d \r\n", freqResult);
	HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 100);
	if (freqResult > 1000 || freqResult < 0) {
		globalAdcError = 1;
		return;
	}
	FFT_res.favg = freqResult;;
}

void calcVelocity(Velocity *velocity) {
	if (FFT_res.fdominant == 0) {
		return;
	}

	double transmittedFreq = 10.525e9;
	double speedOfLight = 3e8;
	double ms = FFT_res.fdominant * speedOfLight / 2 / transmittedFreq;
	double mph = ms * 2.23694;
	double kmh = ms * 3.6;
	velocity->ms = ms;
	velocity->mph = mph;
	velocity->kmh = kmh;
}

void calcVelo(int mode) { //mode = 0 -> ADC, mode = 1 -> COMP
	uint32_t freqSource;
	if (mode == 0) {
		freqSource = FFT_res.favg;
		uart_buf_len = sprintf(uart_buf, "Frequency Source: ADC \r\n");
	} else if (mode == 1) {
		freqSource = globalCompFreq;
		uart_buf_len = sprintf(uart_buf, "Frequency Source: COM \r\n");
	}
	//HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 10);

	double transmittedFreq = 10.525e9;
	double speedOfLight = 3e8;
	double ms = freqSource * speedOfLight / 2 / transmittedFreq;
	double mph = ms * 2.23694;
	double kmh = ms * 3.6;
	velocity.ms = ms;
	velocity.mph = mph;
	velocity.kmh = kmh;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	//double frequency = calcFreqADC(&ADC_BUFFER[ADC_BUFFER_SIZE/2], ADC_BUFFER_SIZE/2);
	//adcFreq = frequency;
	//uart_buf_len = sprintf(uart_buf, "%s %lf \r\n", "F: ", frequency);
	//HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 100);
	//calcFFT();
	//calcFreqAvg();
	//uart_buf_len = sprintf(uart_buf, "Freq: %lf \r\n", FFT_res.fdominant);
	//HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 10);
	adcIsReady = true;
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc) {
	//double frequency = calcFreqADC(ADC_BUFFER, ADC_BUFFER_SIZE/2);
	//adcFreq = frequency;
	//uart_buf_len = sprintf(uart_buf, "%s %lf \r\n", "F: ", frequency);
	//HAL_UART_Transmit(&huart2, uart_buf, uart_buf_len, 100);
	//calcFFT();
}


/* USER CODE END 1 */
