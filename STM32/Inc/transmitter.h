/*
 * transmitter.h
 *
 *  Created on: Feb 9, 2026
 *      Author: stanl
 */

#ifndef INC_TRANSMITTER_H_
#define INC_TRANSMITTER_H_

#include "main.h"
#include "stdint.h"

#define TX_EN_GPIO_Port GPIOA
#define TX_EN_Pin GPIO_PIN_15
#define TX_GPIO_Port GPIOC
#define TX_Pin GPIO_PIN_10


uint8_t velocityToPacket(int velo);
void sendPacket(uint8_t *packet);
void sendPacketDouble(double *packet);

#endif /* INC_TRANSMITTER_H_ */
