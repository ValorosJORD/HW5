#include "MidiFile.h"

Note::Note(int value, int start_time)
{
    this->value      = value;
    this->start_time = start_time;
    end_time         = start_time;
}

int Note::get_value() const
{
    return value;
}

int Note::get_start_time() const
{
    return start_time;
}

int Note::get_end_time() const
{
    return end_time;
}

string Note::get_formatted_time(int ticks_per_beat) const
{

    double start = static_cast<double>(start_time) 
                 / static_cast<double>(ticks_per_beat);

    double end = static_cast<double>(end_time)
               / static_cast<double>(ticks_per_beat);
               
    string st = to_string(start);
    string et = to_string(end);

    string s = "\\left\\{" + st + "\\le t<" +  et + "\\right\\}";

    return s;
}

void Note::set_value(int v)
{
    value = v;
}

void Note::set_start_time(int st)
{
    start_time = st;
}

void Note::set_end_time(int et)
{
    end_time = et;
}