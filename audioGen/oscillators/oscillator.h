#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <cmath>
#define PI 3.14159265358979323846 //cmath's M_PI doesn't compile sometimes

class Oscillator {
public:
	Oscillator(float frequency, float amplitude, float angle, float sampleRate) : _frequency(frequency), _amplitude(amplitude), _angle(angle), _sampleRate(sampleRate){
		_offset = 2 * PI * _frequency / _sampleRate;
		_angle = 0;
	}

    void setFrequency(float frequency) {
        _frequency = frequency;
        _offset = 2 * PI * _frequency / _sampleRate;
    }

    void setAmplitude(float amplitude) {
        _amplitude = amplitude;
    }

    virtual float process(void) = 0;

protected:
	float _frequency;
	float _amplitude;
	float _sampleRate;
	float _angle;
	float _offset;
};

#endif