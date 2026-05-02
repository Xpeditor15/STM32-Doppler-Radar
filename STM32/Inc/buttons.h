#include "main.h"
#include "transmitter.h"

extern uint16_t ModeValue;
extern uint16_t buttonAdcValue;
extern uint32_t globalCompError;

void readButtons();
void mapButtons();
void displayPage();

void adcPage();
void comPage();

double chooseSpeed();
void chooseUnit(char **unit);
