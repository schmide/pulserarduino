// pulserarduino.h 
//
/*

Map pulses (int lengths) to a linear multi-function (floats)

even entries flat
odd entries slope
_   _
 \_/

#define TEXT_OUTPUT_ON for testing output,

otherwise only analog values returned

#define TEXT_STANDARD for std::cout

arduino Serial otherwise

*/

//#define TEXT_OUTPUT_ON

#ifdef TEXT_OUTPUT_ON
#define TEXTOUTPUT_FUNCTION Serial
#define TEXTOUTPUT(a, b, c, d) (a).print(b); (a).print(c); (a).println(d)
#else 
#define TEXTOUTPUT(a, b, c, d)
#endif

struct pulser_callback {
  void (*function)(float);
};

float Pulser(unsigned int pulse, unsigned int maxPulse, unsigned int *pulses, float *speeds, const char *pulseText[] = 0, pulser_callback *callbacks = 0);
void TestPulser(unsigned int maxPulse, unsigned int *pulses, float *speeds, const char *pulseText[] = 0, pulser_callback *callbacks = 0, unsigned int step = 2, bool linear = true);

float Pulser(unsigned int pulse, unsigned int maxPulse, unsigned int *pulses, float *speeds, const char *pulseText[], pulser_callback *callbacks)
{
	unsigned int index = 0;
	do {
		if (pulse < pulses[index])
			break;
	} while (++index < maxPulse);
	float analog;
	unsigned int halfIndex = index >> 1;
	if (index & 1) { // odd
		if (index < maxPulse >> 1) { // rising
			analog = speeds[halfIndex + 1] + (speeds[halfIndex] - speeds[halfIndex + 1]) * (pulses[index] - pulse) / (pulses[index] - pulses[index - 1]);
		} else {
			analog = speeds[halfIndex] + (speeds[halfIndex + 1] - speeds[halfIndex]) * (pulse - pulses[index - 1]) / (pulses[index] - pulses[index - 1]);
		}
	} else {
		analog = speeds[halfIndex];
	}
	TEXTOUTPUT(TEXTOUTPUT_FUNCTION, pulse, pulseText ? pulseText[index] : " = ", analog);
	if (callbacks) {
		if (callbacks[index].function) {
			callbacks[index].function(analog);
		}
	}
	return analog;
}

void TestPulser(unsigned int maxPulse, unsigned int *pulses, float *speeds, const char *pulseText[], pulser_callback *callbacks, unsigned int step, bool linear)
{
	if (linear) {
		unsigned int index = 0;
    unsigned int last = pulses[maxPulse - 1] + pulses[0];
		do {
			Pulser(index, maxPulse, pulses, speeds, pulseText, callbacks);
			index += step;
		} while (index < last);
	} else {
		Pulser(0, maxPulse, pulses, speeds, pulseText, callbacks);
	}
}
