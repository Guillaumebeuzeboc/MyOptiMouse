/*
 OptiMouse.h - Part ofoptical mouse sensor library for Arduino

 Based on sketches by Benoît Rousseau.

*/

#ifndef OptiMouse_h
#define OptiMouse_h

//#include "WProgram.h"
#include "Arduino.h"
#include <inttypes.h>

class OptiMouse
{
  private:
  protected:
	uint8_t _sclkPin;
        uint8_t _misoPin;
        uint8_t _mosiPin;
        uint8_t _ncsPin;
	uint8_t readRegister(uint8_t);
	void writeRegister(uint8_t, uint8_t);
  public:
        OptiMouse(uint8_t, uint8_t,uint8_t,uint8_t);
        void begin(void);
	signed char dx(void);
	signed char dy(void);
};

#endif
