#ifndef SINEOSCILLATOR_H
#define SINEOSCILLATOR_H

#include "oscillator.h"
#include <cmath>

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