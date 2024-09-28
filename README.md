# Wav Generation Program
Here's a simple PCM .wav generation program. It has 4 built-in oscillators (sine, triangle, saw and square), a wavFile object class and a notation parser, allowing for audio generation from .txt files.

# Usage
### WavFile Class
This class is responsible for easy PCM .wav file creation. It takes care of creating the file and writing each of its chunks. The only parameters that need to be specified are:
* the file path (for example "../test.wav", remember to give the full absolute or relative file path, with the filename and .wav extension)
* number of audio channels (int)
* sample rate (Hz)
* bit depth (a multiple of 8 like 16, 24, 32)

Writing to the file can be done with `.write(int vale, int size)` method. The value parameter is meant for the sample value and size should always be equal to bit-depth / 8. After you're done writing to a file use the `.close()` method and the object will automatically fill in missing file data and close itself.

### Notation Parser
The Notation Parser reads through a .txt file and returns the first element of a one-directional linked list of notes. Each note stores its frequency (Hz) and duration (seconds). You can later loop though the notes, manipulating the oscillator's properties to play back the melody that's notated in the .txt file.

### txt file structure
The .txt file structure required for the proper functioning of the Notation Parser is very simple:
```
73 16
70 16
68 16
70 16
77 8
0 16
77 8
0 16
75 4
0 8
```
Each line consists of two integers. The first one is a MIDI note number and the second is its duration. Duration is being stored as a denominator of the equivalent note in music terms, so to put it simply:
* 8 means 1/8th note
* 16 means 1/16th note
* 1 means a whole note

etc. Remember that the file **cannot have any empty lines or end with the `\n` character**. If you want to put in a rest (silence), input it as a note with the MIDI value of 0 and the duration you wish to have.

### Oscillators
Each oscillator has it's distinct sound. To initialise an oscillator use:
```
<typeOfOscillator>(frequency, amplitude, angle, sampleRate);
```
The 4 parameters allow you to set these properties:
* frequency (Hz)
* amplitude (ranging from 0 to 1)
* angle (oscillator's phase in radians)
* sampleRate (oscillator's sample rate in Hz)

Amplitude and frequency can be changed after initialisation by using `.setFrequency(float frequency)` and `.setAmplitude(float amplitude)` methods.

When using an oscillator you need to call the `.process(void)` method in some kind of loop. Each oscillator can store and update it's state, so you don't need to worry about passing in any parameters.
