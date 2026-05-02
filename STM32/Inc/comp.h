/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    comp.h
  * @brief   This file contains all the function prototypes for
  *          the comp.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMP_H__
#define __COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern COMP_HandleTypeDef hcomp1;

/* USER CODE BEGIN Private defines */
#define IDLE 0
#define DONE 1

extern uint32_t lastGlobalCompFreq;
extern uint32_t globalCompFreq;

/*
volatile uint8_t State;
volatile uint32_t T1;
volatile uint32_t T2;
volatile uint32_t Ticks;
volatile uint32_t TIM1_OVC;
volatile uint32_t Freq;

static uint32_t TIM1_Clock_Hz;

uint32_t last_uart_print;
uint32_t last_display_update;
uint32_t last_freq_change;
uint32_t lastFreqSnapshot;
uint8_t no_signal_displayed;*/
/* USER CODE END Private defines */

void MX_COMP1_Init(void);

/* USER CODE BEGIN Prototypes */
void initComp();
void calcFreqComp();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __COMP_H__ */

