#ifndef MIDIFILE_H
#define MIDIFILE_H

#include "NoteStream.h"

#include<string>
    using std::string;
#include<vector>
    using std::vector;
#include<fstream>
    using std::ifstream;
    using std::ofstream;
    using std::streampos;

class MidiFile
{
    public:

        MidiFile(string file_name);

        int filesize();

        void construct_header(ifstream& midi);

        void parse_track(ifstream& midi, ofstream& desmos);
        void meta_event(int event_type, ifstream& midi, ofstream& desmos);
        void note_on(NoteStream& r, ifstream& midi);
        void note_off(NoteStream& r, ifstream& midi, ofstream& desmos);

    private:

        string file_name;
        int type;
        int track_count;
        int ticks_per_beat;

        int line_on;
        int ticks_passed = 0;

        int note_index = 0;

        int dec_con(vector<char>);
    
};

#endif