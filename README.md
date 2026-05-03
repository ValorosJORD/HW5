# Midi-to-Desmos
In short, this project aims to convert the music file format, MIDI (.mid), into lines of LaTeX (https://www.latex-project.org/about/) that are designed to be copy and pasted into a Desmos file that will be able to emulate to some degree of sophistication the contents of the converted MIDI.
## Purpose
This project largely serves as an educational endeavor to further familiarize myself with C++ as a language, parsing files byte-by-byte (and in some cases bit-by-bit), and operating a git repository. To serve this purpose, the MIDI parser is being completely hand-developed by me. This means that there is very likely to be a plethora of issues. At each commit, I will update this file to reflect the current state of the project. 
## Current State
At this moment, its capability is largely only effective for simple one-track one-channel files. If it runs into something a command it doesn't recognize, it will barrel straight through it, which can give unexpected results. When it runs through multiple track, it treats it all as a type 2 file. This means that the start of track 2 will begin directly after the end of track 1. It is completely defective with multi-channel, as the parser does not yet recognize note-on events for specific channels, only channel zero. However, creating a note sequence in FL Studio and exporting that MIDI file will produce something capable of being parsed here
## For Programming Languages Class
To run, build the file using cmake (run cmake --build build in the terminal) and then run the file which should be located at "./build/Debug/MtD.exe" You will be prompted to either use the example file or enter the aboslute file path for your own. IT would probably be easiest to use the example file. The output will be inserted into DesmosOutput.txt, but you also have the option to save it directly to your clipboard. Go to https://www.desmos.com/calculator to paste in everything. To play through the quick musical example, go to add, select ticker, and make it so that the ticker reads "run p every r ms". Make sure to unmute and then press play on the ticker. 

For the three requirements:
User Defined Type: /src/Note.cpp Line 3
Conditional Expression: /src/main.cpp Line 22
Multiway Selection Statement: /src/MidiFile.cpp Line 115
