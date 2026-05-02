/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    comp.c
  * @brief   This file provides code for the configuration
  *          of the COMP instances.
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
#include "comp.h"

/* USER CODE BEGIN 0 */

volatile uint8_t State;
volatile uint32_t T1;
volatile uint32_t T2;
volatile uint32_t Ticks;
volatile uint32_t TIM1_OVC;
volatile uint32_t Freq;

uint32_t lastUartPrint;
uint32_t lastDisplayUpdate;
uint32_t lastFreqChange;
uint32_t lastFreqSnapshot;
uint8_t noSignalDisplayed;

static uint32_t TIM1_Clock_Hz;
uint32_t lastGlobalCompFreq;
uint32_t globalCompFreq;
uint32_t globalCompError = 0;

COMP_HandleTypeDef hcomp1;

void initComp() {
	State = IDLE;
	T1 = 0;
	T2 = 0;
	Ticks = 0;
	TIM1_OVC = 0;
	Freq = 0;

	lastUartPrint = HAL_GetTick();
	lastDisplayUpdate = HAL_GetTick();
	lastFreqChange = HAL_GetTick();
	lastFreqSnapshot = 0;
	noSignalDisplayed = 0;

	TIM1_Clock_Hz = HAL_RCC_GetPCLK2Freq(); // / (htim1.Init.Prescaler + 1U); 1.598

	printf("Comparator initialized!");
}

void calcFreqComp() {
	uint32_t now = HAL_GetTick();
	uint32_t currentFreq = Freq;

	if (currentFreq != lastFreqSnapshot) {
		lastFreqSnapshot = currentFreq;
		lastFreqChange = now;
		noSignalDisplayed = 0;
	}

	if ((currentFreq == 0) && (now - lastFreqChange > 2000) && !noSignalDisplayed) {
		lcdClear();
		lcdSetCursor(0, 0);
		lcdPrint("No signal detected!");
		noSignalDisplayed = 1;
		globalCompError = 1;
	}

	if (now - lastUartPrint >= 500) {
		//printf("State:%d  T1:%lu  T2:%lu  Ticks:%lu  OVC:%lu  Freq:%lu Hz\r\n",
		//State, T1, T2, Ticks, TIM1_OVC, currentFreq);
		globalCompFreq = currentFreq;
		lastUartPrint = now;
	}

	if ((currentFreq > 0) && (now - lastDisplayUpdate >= 500)) {
		//lcdClear();
		//lcdSetCursor(0, 0);
		//char FreqString[20];
		//sprintf(FreqString, "%lu Hz", currentFreq);
		//lcdPrint(FreqString);
		globalCompFreq = currentFreq;

		lastDisplayUpdate = now;
		noSignalDisplayed = 0;
	}

	HAL_Delay(10);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
		uint32_t ARR = __HAL_TIM_GET_AUTORELOAD(htim) + 1U;

		if (State == IDLE) {
			T1 = TIM1->CCR1;
			TIM1_OVC = 0;
			State = DONE;
		}
		else if (State == DONE) {
			T2 = TIM1->CCR1;

			if (T2 >= T1) {
				Ticks = (T2 - T1) + (TIM1_OVC * ARR);
			}
			else {
				Ticks = (ARR - T1) + T2 + ((TIM1_OVC - 1U) * ARR);
			}

			if (Ticks > 0 && TIM1_Clock_Hz > 0) {
				Freq = TIM1_Clock_Hz / Ticks;
			}
			else {
				Freq = 0;
			}

			State = IDLE;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM1) {
		TIM1_OVC++;

		if (TIM1_OVC > 1000) {
			TIM1_OVC = 0;
			Freq = 0;
			State = IDLE;
		}
	}
}
/* USER CODE END 0 */

COMP_HandleTypeDef hcomp1;

/* COMP1 init function */
void MX_COMP1_Init(void)
{

  /* USER CODE BEGIN COMP1_Init 0 */

  /* USER CODE END COMP1_Init 0 */

  /* USER CODE BEGIN COMP1_Init 1 */

  /* USER CODE END COMP1_Init 1 */
  hcomp1.Instance = COMP1;
  hcomp1.Init.InvertingInput = COMP_INPUT_MINUS_1_4VREFINT;
  hcomp1.Init.NonInvertingInput = COMP_INPUT_PLUS_IO1;
  hcomp1.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp1.Init.Hysteresis = COMP_HYSTERESIS_HIGH;
  hcomp1.Init.BlankingSrce = COMP_BLANKINGSRC_NONE;
  hcomp1.Init.Mode = COMP_POWERMODE_HIGHSPEED;
  hcomp1.Init.WindowMode = COMP_WINDOWMODE_DISABLE;
  hcomp1.Init.TriggerMode = COMP_TRIGGERMODE_NONE;
  if (HAL_COMP_Init(&hcomp1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP1_Init 2 */

  /* USER CODE END COMP1_Init 2 */

}

void HAL_COMP_MspInit(COMP_HandleTypeDef* compHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(compHandle->Instance==COMP1)
  {
  /* USER CODE BEGIN COMP1_MspInit 0 */

  /* USER CODE END COMP1_MspInit 0 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**COMP1 GPIO Configuration
    PC5     ------> COMP1_INP
    PB0     ------> COMP1_OUT
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_COMP1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN COMP1_MspInit 1 */

  /* USER CODE END COMP1_MspInit 1 */
  }
}

void HAL_COMP_MspDeInit(COMP_HandleTypeDef* compHandle)
{

  if(compHandle->Instance==COMP1)
  {
  /* USER CODE BEGIN COMP1_MspDeInit 0 */

  /* USER CODE END COMP1_MspDeInit 0 */

    /**COMP1 GPIO Configuration
    PC5     ------> COMP1_INP
    PB0     ------> COMP1_OUT
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);

  /* USER CODE BEGIN COMP1_MspDeInit 1 */

  /* USER CODE END COMP1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
