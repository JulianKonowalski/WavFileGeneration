#include <iostream>
#include <ios>
#include <fstream>

#include "wavFile.h"
#include "notationParser.h"

#include "oscillators/oscillator.h"
#include "oscillators/sineOscillator.h"

const int numberOfChannels = 1;
const int sampleRate = 44100; 
const int bitDepth = 16;
const int sampleSize = bitDepth / 8;
const int maxAmplitude = pow(2, bitDepth - 1) - 1;

const int tempo = 115;
const float amplitude = 0.5;

int main(void) {
	WavFile* wavFile = new WavFile("../generated.wav", numberOfChannels, sampleRate, bitDepth);
	NotationParser* parser = new NotationParser(tempo);
	Note* notes = parser->parse("../notes.txt");
	Oscillator* oscillator = new SineOscillator(440, amplitude, 0, sampleRate);
	std::cout << "Generating..." << std::endl;
	while (notes != nullptr) {
		float frequency = notes->getFrequency();
		if (frequency <= 20) {
			oscillator->setAmplitude(0);
		} else {
			oscillator->setAmplitude(amplitude);
			oscillator->setFrequency(frequency);
		}
		for (int i = 0; i < notes->getDuration() * sampleRate; ++i) {
			int sample = static_cast<int> (oscillator->process() * maxAmplitude);
			wavFile->write(sample, sampleSize);
		}
		notes = notes->getNext();
	}
	wavFile->close();
	std::cout << "Done!" << std::endl;
	return 0;
}