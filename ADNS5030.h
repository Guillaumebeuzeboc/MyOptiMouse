/*
 ADNS5030.h - Part of optical mouse sensor library for Arduino

 Based on sketches by Benoît Rousseau.
*/

#ifndef ADNS5030_h
#define ADNS5030_h

//#include "WProgram.h"
#include "Arduino.h"
#include <inttypes.h>

#include "OptiMouse.h"

class ADNS5030 : public OptiMouse
{
  private:
  public:
        ADNS5030(uint8_t, uint8_t,uint8_t,uint8_t);
	signed char dx(void);
	signed char dy(void);
        bool motion();
};

#endif
