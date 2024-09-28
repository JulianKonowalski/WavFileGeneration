#ifndef TRIANGLEOSCILLATOR_H
#define TRIANGLEOSCILLATOR_H

#include "oscillator.h"
#include <cmath>

class TriangleOscillator : public Oscillator {
public:
	using Oscillator::Oscillator;

	float process(void) {
		float sample = _amplitude * (4 * fabs(_angle - floor(_angle + 0.75) + 0.25) - 1);
		_angle += _triOffset;
		return sample;
	}

	void setFrequency(float frequency) {
		_frequency = frequency;
		_triOffset = _frequency / _sampleRate;
	}

private:
	float _triOffset = _frequency / _sampleRate;

};

#endif
