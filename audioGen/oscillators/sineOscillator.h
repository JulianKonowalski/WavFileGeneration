#ifndef SINEOSCILLATOR_H
#define SINEOSCILLATOR_H

#include "oscillator.h"
#include <cmath>
#define PI 3.14159265358979323846 //cmath's M_PI doesn't compile sometimes

class SineOscillator : public Oscillator {
public:
    using Oscillator::Oscillator;

	float process(void) {
		float sample = _amplitude * sin(_angle);
		_angle += _offset;
		return sample;
	}
};

#endif