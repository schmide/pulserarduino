#define TEXT_OUTPUT_ON
#include "pulserarduino.h"

/*

  Example for testing Pulser function

  linear function with floor, ceiling, and center dead zone

*/

// for showing callbacks
void CallDummy(float analog)
{
  Serial.print("I'm a dumb analog = ");
  Serial.println(analog);
}

float speeds[] = {
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

const char *pulseText[] = {
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

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  TestPulser(maxPulse, pulses, speeds, pulseText, pulseCallbacks);
}

void loop() {

}
