/*
 * transmitter.c
 *
 *  Created on: Feb 9, 2026
 *      Author: stanl
 */


#include "transmitter.h"
#include "usart.h"

uint8_t velocityToPacket(int velo) { // Converts the velocity decimal to a binary in the form 0000 0000
	uint8_t tens = velo / 10; // Separate the numbers into individual parts
	uint8_t ones = velo % 10;

	uint8_t TxData = (tens << 4) | ones;
	return TxData;
}


void sendPacket(uint8_t* packet) {
	//pullDeHigh();
	HAL_UART_Transmit(&huart4, packet, 1 , 1000);
	while (__HAL_UART_GET_FLAG(&huart4, UART_FLAG_TC) == RESET);
	//pullDeLow();
}

void sendPacketDouble(double *packet) {
	int rounded = (int)round(*packet);

	uint8_t data = (uint8_t)rounded;
	sendPacket(&data);
}
