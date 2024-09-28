#include <iostream>
#include <ios>
#include <fstream>

#include "oscillators/oscillator.h"
#include "oscillators/sineOscillator.h"
#include "oscillators/squareOscillator.h"
#include "oscillators/sawOscillator.h"
#include "oscillators/triangleOscillator.h"

const int sampleRate = 44100; 
const int bitDepth = 16;
const int time_s = 1;
const int maxAmplitude = pow(2, bitDepth - 1) - 1;

void writeToFile(std::ofstream& file, int value, int size) {
	file.write(reinterpret_cast<const char*> (&value), size);
}

int main(void) {
	std::ofstream audioFile;
	audioFile.open("../audio.wav", std::ios::binary);

	//Header chunk
	audioFile << "RIFF";
	audioFile << "----";
	audioFile << "WAVE";

	//Format chunk
	audioFile << "fmt ";
	writeToFile(audioFile, 16, 4); //size
	writeToFile(audioFile, 1, 2); //compression code
	writeToFile(audioFile, 1, 2); //number of channels
	writeToFile(audioFile, sampleRate, 4); //sample rate
	writeToFile(audioFile, sampleRate * bitDepth / 8, 4); //byte rate
	writeToFile(audioFile, bitDepth / 8, 2); //block align
	writeToFile(audioFile, bitDepth, 2); //bit depth

	//Data chunk
	audioFile << "data";
	audioFile << "----";

	int preAudioPosition = audioFile.tellp();

	//Audio Generation
	Oscillator* sineOscillator = new SineOscillator(440, 0.5, 0, sampleRate);
	Oscillator* squareOscillator = new SquareOscillator(440, 0.5, 0, sampleRate);
	Oscillator* sawOscillator = new SawOscillator(440, 0.5, 0, sampleRate);
	Oscillator* triangleOscillator = new TriangleOscillator(440, 0.5, 0, sampleRate);
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (sineOscillator->process() * maxAmplitude);
		writeToFile(audioFile, sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (triangleOscillator->process() * maxAmplitude);
		writeToFile(audioFile, sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (sawOscillator->process() * maxAmplitude);
		writeToFile(audioFile, sample, 2);
	}
	for (int i = 0; i < sampleRate * time_s; ++i) {
		int sample = static_cast<int> (squareOscillator->process() * maxAmplitude);
		writeToFile(audioFile, sample, 2);
	}
	int postAudioPosition = audioFile.tellp();

	//info for the file
	audioFile.seekp(4, std::ios::beg);
	writeToFile(audioFile, postAudioPosition - 8, 4);
	audioFile.seekp(preAudioPosition - 4);
	writeToFile(audioFile, postAudioPosition - preAudioPosition, 4);
	
	audioFile.close();

	std::cout << "Done!" << std::endl;
	return 0;
}