/*
 OptiMouse.cpp - Part of optical mouse sensor library for Arduino

 Based on sketches by Benoît Rousseau.
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "OptiMouse.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/

OptiMouse::OptiMouse(uint8_t sclkPin, uint8_t misoPin,uint8_t mosiPin,uint8_t ncsPin)
{
  _sclkPin = sclkPin;
  _misoPin = misoPin;
  _mosiPin = mosiPin;
  _ncsPin = ncsPin;
  pinMode (_sclkPin, OUTPUT);
  pinMode (_misoPin, INPUT);
  pinMode (_mosiPin, OUTPUT);
  pinMode (_ncsPin, OUTPUT);
}


/******************************************************************************
 * User API
 ******************************************************************************/

void OptiMouse::begin(void)
{
        // Re-sync
        // Toggle the SLCK line from high to low to high....    // TODO: check if necessairy
	digitalWrite(_sclkPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_sclkPin, LOW);
	delayMicroseconds(1);
	digitalWrite(_sclkPin, HIGH);

        digitalWrite(_ncsPin, HIGH); // lock communication

	// Wait at least tSIWTT (0.9 second?) for the
	// OptiMouse serial transaction timer to time out:
	delay(1000);
}

// Private Methods /////////////////////////////////////////////////////////////


uint8_t OptiMouse::readRegister(uint8_t address)
{
	int i = 7;
	uint8_t r = 0;

	// Write the address of the register we want to read:
        digitalWrite(_ncsPin,LOW); // unlock communication
	delayMicroseconds(100);
	for (; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
                digitalWrite (_mosiPin, address & (1 << i));
		digitalWrite (_sclkPin, HIGH);
	}

	// Wait a bit...
	delayMicroseconds(100);

	// Fetch the data!
	for (i=7; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
		digitalWrite (_sclkPin, HIGH);
                r |= (digitalRead (_misoPin) << i);
	}
	delayMicroseconds(100);
        digitalWrite(_ncsPin,HIGH); // lock communication
	return r;
}

void OptiMouse::writeRegister(uint8_t address, uint8_t data) // need to test
{
	int i = 7;

	// Set MSB high, to indicate write operation:
	address |= 0x80;

	// Write the address:
	for (; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
                digitalWrite (_mosiPin, address & (1 << i));
		digitalWrite (_sclkPin, HIGH);
	}

	// Write the data:
	for (i=7; i>=0; i--)
	{
		digitalWrite (_sclkPin, LOW);
                digitalWrite (_mosiPin, data & (1 << i));
		digitalWrite (_sclkPin, HIGH);
	}

}
