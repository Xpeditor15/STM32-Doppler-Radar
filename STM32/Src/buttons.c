#include "buttons.h"
#include "main.h"

/*
	   Right: 0
	   Up: 750
	   Down: 1810
	   Left: 2860
	   Select: 4095

	   Right Left -> Change unit
	   Up Down -> ADC COMP
	   */

uint16_t ModeValue = 0; //Mode = 0 -> ADC, Mode = 1 -> COM
uint16_t speedMode = 0;
uint16_t previousSpeedMode = 0;
uint16_t buttonAdcValue;
bool isButtonPressed = false;

void readButtons() {
	  HAL_ADC_Start(&hadc2);
	  HAL_ADC_PollForConversion(&hadc2, 10);
	  buttonAdcValue = (uint16_t) HAL_ADC_GetValue(&hadc2);
	  HAL_ADC_Stop(&hadc2);
}

void mapButtons() {
	readButtons();

	if (buttonAdcValue < 20) {
		if (!isButtonPressed) {
			speedMode = (speedMode + 1) % 3;
			isButtonPressed = true;
		}
	} else if (buttonAdcValue < 780) {
		if (!isButtonPressed) {
			ModeValue = (ModeValue + 1) % 2;
			isButtonPressed = true;
		}
	} else if (buttonAdcValue < 1830) {
		if (!isButtonPressed) {
			ModeValue = (ModeValue + 1) % 2;
			isButtonPressed = true;
		}
	} else if (buttonAdcValue < 2880) {
		if (!isButtonPressed) {
			speedMode = ((speedMode - 1) + 3) % 3;
			isButtonPressed = true;
		}
	} else {
		isButtonPressed = false;
	}
}

void displayPage() {
	if (ModeValue == 0) {
		adcPage();
	} else if (ModeValue == 1) {
		comPage();
	}
}

void adcPage() {
	if (adcIsReady) {
		calcFreqAvg();
	}

	if (globalAdcError) {
		lcdClear();
		lcdSetCursor(0, 0);
		char firstString[20];
		sprintf(firstString, "[ADC]Freq:%s \r\n", "Error");
		lcdPrint(firstString);
		globalAdcError = 0;
		return;
	}
	if (FFT_res.favg == lastAdcFreq && previousSpeedMode == speedMode) return;
	lcdClear();
	lcdSetCursor(0, 0);
	int freqResult = (int)ceil(FFT_res.favg);
	char firstString[20];
	sprintf(firstString, "[ADC]Freq:%d Hz \r\n", freqResult);
	lcdPrint(firstString);
	char secondString[20];
	calcVelo(0);
	double speed = chooseSpeed();
	char *unit;
	chooseUnit(&unit);
	sprintf(secondString, "V: %.2lf %s", speed, unit);
	lcdSetCursor(1, 0);
	lcdPrint(secondString);
	previousSpeedMode = speedMode;
	sendPacketDouble(&speed);
}

void comPage() {
	calcFreqComp();
	if (globalCompError) {
			lcdClear();
			lcdSetCursor(0, 0);
			char firstString[20];
			sprintf(firstString, "[COM]Freq:%s \r\n", "Error");
			lcdPrint(firstString);
			globalCompError = 0;
			return;
	}
	if (globalCompFreq == lastGlobalCompFreq && previousSpeedMode == speedMode) return;
	lcdClear();
	lcdSetCursor(0, 0);
	int freqResult = globalCompFreq;
	char firstString[20];
	sprintf(firstString, "[COM]Freq:%d Hz \r\n", freqResult);
	lcdPrint(firstString);
	char secondString[20];
	calcVelo(1);
	double speed = chooseSpeed();
	char *unit;
	chooseUnit(&unit);
	sprintf(secondString, "V: %.2lf %s", speed, unit);
	lcdSetCursor(1, 0);
	lcdPrint(secondString);
	lastGlobalCompFreq = globalCompFreq;
	previousSpeedMode = speedMode;
	sendPacketDouble(&speed);
}

double chooseSpeed() { //0 -> ms, 1 -> mph, 2 -> kmh
	double speed;
	if (speedMode == 0) speed = velocity.ms;
	else if (speedMode == 1) speed = velocity.mph;
	else if (speedMode == 2) speed = velocity.kmh;
	return speed;
}

void chooseUnit(char **unit) {
	if (speedMode == 0) {
		*unit = "ms";
	} else if (speedMode == 1) {
		*unit = "mph";
	} else if (speedMode == 2) {
		*unit = "kmh";
	}
}
