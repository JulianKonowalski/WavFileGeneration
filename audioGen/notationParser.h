#ifndef NOTATIONPARSER_H
#define NOTATIONPARSER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <cmath>

#define A4FREQ 440

class Note {
public:
	Note(float frequency, float duration, Note* next = nullptr) : _frequency(frequency), _duration(duration), _next(next) {}
	float getFrequency(void) { return _frequency; }
	float getDuration(void) { return _duration; }
	void setNext(Note* next) { _next = next; }
	Note* getNext(void) { return _next; }

private:
	float _frequency;
	float _duration; //duration in seconds
	Note* _next;
};

class NotationParser {

public:
	NotationParser(float tempo) : _tempo(tempo / 4.0){} //tempo is /4 because usually the quarternote (1/4 of full note) is counted as one beat

	Note* parse(const char* path) {
		Note* head = nullptr, * ptr = nullptr;
		std::ifstream notationFile(path);
		if (!notationFile.is_open()) {
			return nullptr;
		}
		std::string line;
		int noteVal; //MIDI note number
		int duration; //denominator of the note fraction -- 8 for 1/8th etc
		while (std::getline(notationFile, line)) {
			std::istringstream in(line);
			in >> noteVal >> duration;
			float frequency = A4FREQ * pow(2.0, (noteVal - 69)/12.0);
			float duration_s = 60.0 / (_tempo * duration);
			Note* note = new Note(frequency, duration_s);
			if (head == nullptr) {
				head = ptr = note;
				continue;
			}
			ptr->setNext(note);
			ptr = ptr->getNext();
		}
		return head;
	}

private:
	const float _tempo;
};

#endif
