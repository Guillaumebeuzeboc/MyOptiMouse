// Based on the sketches by Benoit Rousseau


#include "ADNS5030.h"


#define SCLK 2                            // Serial clock pin on the Arduino
#define MISO 3// Serial data output pin on the Arduino
#define MOSI 4// Serial data (I/O) pin on the Arduino
#define NCS 5// enable serial com

ADNS5030 Optical1 = ADNS5030(SCLK, MOSI,MISO,NCS);   // Create an instance of the PAN3101 object

signed long x = 0;                        // CPI (count per inch)
signed long y = 0;                        //
signed long x_m=0;                        // distance in mm
signed long y_m=0;

int c = 0;                                // Counter variable for coordinate reporting

void setup()
{
  Serial.begin(38400);
  Optical1.begin();                       // Resync (not really necessary?)
}

void loop()
{

  if (Optical1.motion())                  // If the 'Motion' status bit is set,
  {
    
    //x += Optical1.dx();                   // Read the dX register and in/decrease X with that value
    x += Optical1.dx();                   // Read the dX register and in/decrease X with that value
    //y += Optical1.dy();                   // Same thing for dY register.....
    y += Optical1.dy();                   // Same thing for dY register.....
    x_m=x*0.0508;                         // based on cpi doc
    y_m=y*0.0508;

  }
  
  if (c++ & 0x80)
  {                                       // Report the coordinates once in a while...
    Serial.print("x=");
    Serial.print(x, DEC);
    Serial.print(" y=");
    Serial.print(y, DEC);
    Serial.println();
    Serial.print("x in mm: ");Serial.print(x_m);
    Serial.print(" y in mm: ");Serial.println(y_m);
    //Serial.print(" motion =");Serial.println(Optical1.motion());
    c = 0;                                // Reset the report counter
  }
}

