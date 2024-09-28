#ifndef SAWOSCILLATOR_H
#define SAWOSCILLATOR_H

#include "oscillator.h"
#include <cmath>
#define PI 3.14159265358979323846 //cmath's M_PI doesn't compile sometimes

class SawOscillator : public Oscillator { //doesn't work
public:
    using Oscillator::Oscillator;

	float process(void) {
		float sample = _amplitude * 2 * (_angle - floor(_angle)) - 0.5;
		_angle += sawOffset;
		return sample;
	}

private:
	float sawOffset = _frequency / _sampleRate;
};

#endif