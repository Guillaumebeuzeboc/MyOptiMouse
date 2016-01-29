/*
 ADNS5030.cpp - Part of optical mouse sensor library for Arduino

 Based on sketches by Benoît Rousseau.
*/

/******************************************************************************
 * Doc
 * http://datasheet.octopart.com/ADNS-5030-Avago-datasheet-10314086.pdf
 * ADNS 5030
******************************************************************************/
/******************************************************************************
 * Includes
 ******************************************************************************/

#include "ADNS5030.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

#define Delta_Y				0x04
#define Delta_X				0x03
#define Motion_Status                   0x02

#define Mask_Motion			0x80
#define Mask_DYOVF			0x10
#define Mask_DXOVF			0x08

/******************************************************************************
 * Constructors
 ******************************************************************************/


ADNS5030::ADNS5030(uint8_t sclkPin, uint8_t misoPin,uint8_t mosiPin,uint8_t ncsPin) : OptiMouse::OptiMouse(sclkPin, misoPin,mosiPin,ncsPin)
{

}

/******************************************************************************
 * User API
 ******************************************************************************/
signed char ADNS5030::dx(void)
{
	return (signed char) readRegister(Delta_X);
}

signed char ADNS5030::dy(void)
{
	return (signed char) readRegister(Delta_Y);
}

bool ADNS5030::motion()
{
        return readRegister(Motion_Status);
}

// Private Methods /////////////////////////////////////////////////////////////

