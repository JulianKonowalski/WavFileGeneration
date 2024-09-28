#ifndef SQUAREOSCILLATOR_H
#define SQUAREOSCILLATOR_H

#include "oscillator.h"
#include <cmath>
#define PI 3.14159265358979323846 //cmath's M_PI doesn't compile sometimes

int sgn(float value) {
    return (float(0) < value) - (value < float(0));
}

class SquareOscillator : public Oscillator {
public:
    using Oscillator::Oscillator;

	float process(void) {
		float sample = _amplitude * sgn(sin(_angle));
		_angle += _offset;
		return sample;
	}
};

#endif