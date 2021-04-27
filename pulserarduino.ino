#define TEXT_OUTPUT_ON
#include "pulserarduino.h"

/*
#define SIMPLE

linear function with floor, ceiling, and center dead zone

//#define SIMPLE

7 levels - floor, ceiling, center dead zone, high(cruse), low(slow) min and max

*/

// for showing callbacks
void CallDummy(float analog)
{
  Serial.print("I'm a dumb analog = ");
  Serial.println(analog);
}

#define SIMPLE
#ifdef SIMPLE

float speed[] = {
  -1.0,
  0,
  1.0
};

unsigned int pulses[] = {
  10,
  45,
  55,
  90
};

char *pulseText[] = {
" reverse full, analog = ",
" reverse, analog = ",
" neutral, analog = ",
" forward, analog = ",
" forward full, analog = "
};

unsigned int maxPulse = sizeof(pulses) / sizeof(*pulses);

struct pulser_callback pulseCallbacks[] = {
  { CallDummy },
  { 0 },
  { 0 },
  { 0 },
  { 0 }
};

#else

float speed[] = {
  -1.0,
  -0.5,
  -0.25,
  0.0,
  0.25,
  0.5,
  1.0,
};

unsigned int pulses[] = {
  10,
  20,
  30,
  40,
  50,
  60,
  70,
  80,
  90,
  100,
  110,
  120
};

unsigned int maxPulse = sizeof(pulses) / sizeof(*pulses);

char *pulseText[] = {
  " reverse full, analog = ",
  " reverse full to cruse, analog = ",
  " reverse cruse, analog = ",
  " reverse cruse to slow, analog = ",
  " reverse slow, analog = ",
  " reverse slow to neutral, analog = ",
  " neutral, analog = ",
  " forward neutral to slow, analog = ",
  " forward slow, analog = ",
  " forward slow to cruse, analog = ",
  " forward cruse, analog = ",
  " forward cruse to full, analog = ",
  " forward full, analog = "
};

struct pulser_callback pulseCallbacks[] = {
  { CallDummy },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 },
  { 0 }
};

#endif

void setup()
{
  TestPulser(maxPulse, pulses, speed, pulseText, pulseCallbacks); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
