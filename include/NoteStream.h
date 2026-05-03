#ifndef NOTESTREAM_H
#define NOTESTREAM_H

#include "Note.h"

#include<vector>
    using std::vector;
#include<iostream>
    using std::ostream;
    using std::cout;

class NoteStream
{
    public:

        NoteStream() = default;

        Note& at(int value);
        void push_back(Note n);

        int get_index(int value);
        void erase(int index);

        void write(ostream& desmos, int ticks_per_beat);

    public:

        vector<Note> notes;
        
};

#endif