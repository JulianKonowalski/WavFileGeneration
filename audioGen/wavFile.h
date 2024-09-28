#ifndef WAVFILE_H
#define WAVFILE_H

#include <iostream>
#include <ios>
#include <fstream>

#define PCM 1

class WavFile {
public:

	WavFile(const char* file, int numberOfChannels, int sampleRate, int bitDepth) : _numberOfChannels(numberOfChannels), _sampleRate(sampleRate), _bitDepth(bitDepth) {
		open(file);
		writeHeaderChunk();
		writeFormatChunk();
		writeDataChunkHeader();
		_preAudioPosition = audioFile.tellp();
	}

	void write(int value, int size) {
		audioFile.write(reinterpret_cast<const char*> (&value), size);
	}

	void close(void) {
		_postAudioPosition = audioFile.tellp();
		audioFile.seekp(4, std::ios::beg);
		write(_postAudioPosition - 8, 4);
		audioFile.seekp(_preAudioPosition - 4);
		write(_postAudioPosition - _preAudioPosition, 4);
		audioFile.close();
	}

private:

	void open(const char* file) {
		audioFile.open(file, std::ios::binary);
	}

	void writeHeaderChunk(void) {
		audioFile << "RIFF";
		audioFile << "----";
		audioFile << "WAVE";
	}

	void writeFormatChunk(void) {
		audioFile << "fmt ";
		write(16, 4); //size
		write(PCM, 2); //compression code
		write(_numberOfChannels, 2); //number of channels
		write(_sampleRate, 4); //sample rate
		write(_sampleRate * _bitDepth * _numberOfChannels / 8, 4); //byte rate
		write(_bitDepth * _numberOfChannels / 8, 2); //block align
		write(_bitDepth, 2); //bit depth
	}

	void writeDataChunkHeader(void) {
		audioFile << "data";
		audioFile << "----";
	}

	std::ofstream audioFile;
	const int _sampleRate;
	const int _bitDepth;
	const int _numberOfChannels;
	int _preAudioPosition;
	int _postAudioPosition;
};

#endif // !WAVFILE_H

