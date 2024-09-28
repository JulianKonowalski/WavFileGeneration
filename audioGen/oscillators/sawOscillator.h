#ifndef SAWOSCILLATOR_H
#define SAWOSCILLATOR_H

#include "oscillator.h"
#include <cmath>

class SawOscillator : public Oscillator {
public:
    using Oscillator::Oscillator;

	float process(void) {
		float sample = _amplitude * 2 * (_angle - floor(_angle + 0.5));
		_angle += _sawOffset;
		return sample;
	}

	void setFrequency(float frequency) {
		_frequency = frequency;
		_sawOffset = _frequency / _sampleRate;
	}

private:
	float _sawOffset = _frequency / _sampleRate;
};

#endif