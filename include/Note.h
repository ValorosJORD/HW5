#ifndef NOTE_H
#define NOTE_H

#include<string>
    using std::string;
    using std::to_string;
#include<iostream>
    using std::cout;

class Note
{
    public:

        Note(int value, int start_time);

        int get_value() const;
        int get_start_time() const;
        int get_end_time() const;

        string get_formatted_time(int ticks_per_beat) const;

        void set_value(int v);
        void set_start_time(int st);
        void set_end_time(int et);

    private:

        int value;
        int start_time;
        int end_time;

};

#endif