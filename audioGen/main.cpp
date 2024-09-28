#include <iostream>
#include <ios>
#include <fstream>

#include "wavFile.h"

#include "oscillators/oscillator.h"
#include "oscillators/sineOscillator.h"
#include "oscillators/squareOscillator.h"
#include "oscillators/sawOscillator.h"
#include "oscillators/triangleOscillator.h"

const int numberOfChannels = 1;
const int sampleRate = 44100; 
const int bitDepth = 16;
const int time_s = 1;
const int maxAmplitude = pow(2, bitDepth - 1) - 1;

void writeToFile(std::ofstream& file, int value, int size) {
	file.write(reinterpret_cast<const char*> (&value), size);
}

int main(void) {

	WavFile* wavFile = new WavFile("../audio.wav", numberOfChannels, sampleRate, bitDepth);

	//Oscillators Initialisation
	Oscillator* sineOscillator = new SineOscillator(440, 0.5, 0, sampleRate);
	Oscillator* squareOscillator = new SquareOscillator(440, 0.5, 0, sampleRate);
	Oscillator* sawOscillator = new SawOscillator(440, 0.5, 0, sampleRate);
	Oscillator* triangleOscillator = new TriangleOscillator(440, 0.5, 0, sampleRate);

	//Audio Generation
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (sineOscillator->process() * maxAmplitude);
		wavFile->write(sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (triangleOscillator->process() * maxAmplitude);
		wavFile->write(sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (sawOscillator->process() * maxAmplitude);
		wavFile->write(sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (squareOscillator->process() * maxAmplitude);
		wavFile->write(sample, 2);
	}
	wavFile->close();

	std::cout << "Done!" << std::endl;
	return 0;
}