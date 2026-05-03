#include "NoteStream.h"

#include<stdexcept>
    using std::out_of_range;

Note& NoteStream::at(int value)
{
    int size = notes.size();
    int index = -1;

    for (int i = 0; i < size; i++)
    {
        if (value == notes[i].get_value())
        {
            index = i;
        }
    }

    if (index == -1)
    {
        throw out_of_range{"This note is not in the note stream. (At)"};
    }

    return notes[index];
}

int NoteStream::get_index(int value)
{
    int size = notes.size();
    int index = -1;

    for (int i = 0; i < size; i++)
    {
        if (value == notes[i].get_value())
        {
            index = i;
        }
    }

    if (index == -1)
    {
        throw out_of_range{"This note is not in the note stream. (Index)"};
    }

    return index;
}

void NoteStream::erase(int index)
{
    int size = notes.size();

    if (index >= size || index < 0)
    {
        throw out_of_range{"This note is not in the note stream. (Erase)"};
    }

    notes.erase(notes.begin() + index);
}

void NoteStream::push_back(Note n)
{
    notes.push_back(n);
}