/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "comp.h"
/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

extern ADC_HandleTypeDef hadc2;

/* USER CODE BEGIN Private defines */
#define ADC_BUFFER_SIZE 4096

typedef struct ADC_PARAM {
	uint32_t clockSpeed;
	int prescaler;
	int bits;
	double samplingTime;
	uint16_t *ADC_buffer;
	uint16_t ADC_buffer_size;
} ADC_PARAM;

typedef struct FFT_RESULTS {
	double samplingFreq;
	double fdominant;
	double magnitude;
	int favg;
	uint32_t index;
} FFT_RESULTS;

typedef struct Velocity {
	double kmh;
	double mph;
	double ms;
} Velocity;

extern ADC_PARAM ADC_params;
extern FFT_RESULTS FFT_res;
extern Velocity velocity;
extern uint16_t ADC_BUFFER[ADC_BUFFER_SIZE];
extern int lastAdcFreq;
extern uint32_t globalAdcError;


void initFFT(ADC_PARAM *ADC_parameter, FFT_RESULTS *FFT_results);
void calcFFT();
double calcFreqADC(uint16_t *beginning, uint16_t length);
void calcFreqAvg();
void calcVelocity(Velocity *velocity);
void calcVelo(int mode);


/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void MX_ADC2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

