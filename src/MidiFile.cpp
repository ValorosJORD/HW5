#include "MidiFile.h"

#include<iostream>
    using std::cout;
#include<cmath>

MidiFile::MidiFile(string file_name)
{
    this->file_name = file_name;

    ifstream midi;
    midi.open(file_name);

    ofstream desmos;
    desmos.open("DesmosOutput.txt");

    desmos << "p=\\left(t\\to t+\\frac{1}{30}\\left\\{0\\le t\\le\\left(l-1\\right)"
           << "\\right\\}\\right),\\left(t\\to0\\left\\{t>\\left(l-1\\right)\\right\\}\\r"
           << "ight)\n";

    char c1,c2;

    midi.ignore(8);
    midi.get(c1);
    midi.get(c2);
    type = dec_con({c2,c1});
    midi.get(c1);
    midi.get(c2);
    track_count = dec_con({c2,c1});;
    midi.get(c1);
    midi.get(c2);
    ticks_per_beat = dec_con({c2,c1});;

    for (int i = 0; i < track_count; i++)
    {
        parse_track(midi, desmos);
    }

    desmos << "l=" << ((ticks_passed / ticks_per_beat) + 4) << '\n';
    desmos << "t=0\n";
    desmos << "f\\left(x\\right)=\\frac{o}{12}"
           << "440\\cdot2^{\\frac{x}{12}}\n";
    desmos << "o=12\n";
    
    midi.close();
    desmos.close();
}

int MidiFile::dec_con(vector<char> c)
{
    int size = c.size();

    int total = 0;

    for (int i = (size - 1); i >= 0; i--)
    {
        int j = c[i];
        if (j < 0)
        {
            j += 256;
        }
        total += (j * pow(16, (i * 2)));
    }

    return total;
}

int MidiFile::filesize()
{
    ifstream midi;
    midi.open(file_name);

    int running_total = 0;

    while (!midi.eof())
    {
        running_total++;
        midi.get();
    }

    midi.close();

    return running_total - 1;
}

void MidiFile::parse_track(ifstream& midi, ofstream& desmos)
{
    NoteStream roll;

    midi.ignore(4);

    char c1,c2,c3,c4;

    midi.get(c1);
    midi.get(c2);
    midi.get(c3);
    midi.get(c4);
    int size = dec_con({c4,c3,c2,c1});

    char c;
    midi.get(c);
    int i = dec_con({c});
    int j = 0;

    while (j < size)
    {
        i = dec_con({c});
        while (i == 0)
        {
            midi.get(c);
            i = dec_con({c});
            j++;
        }

        if (i == 255)
        {
            midi.get(c);
            i = dec_con({c});
            if (i == 47)
            {
                j = size;
            }
            else
            {
                meta_event(i, midi, desmos); 
            }
        }
        else if (i == 240)
        {
            while (i != 247)
            {
                midi.get(c);
                i = dec_con({c});
            }
        }
        else if (i == 144)
        {
            note_on(roll, midi);
        }
        else if (i == 128)
        {
            note_off(roll, midi, desmos);
        }
        else
        {
            if (i < 128)
            {
                ticks_passed += i;
            }
            else
            {

                int i1 = c;
                midi.get(c);
                int i2 = c;

                int i3 = i1 & 0x7F;
                int i4 = i2 & 0x7F;

                ticks_passed += (((i3*pow(16,2))/2) + i4);
            }
        }
        if (i != 47)
        {
            midi.get(c);
            j++;
        }
    }
    midi.ignore(1);
}

void MidiFile::meta_event(int event_type, ifstream& midi, ofstream& desmos)
{
    char c;
    if (event_type == 88)
    {
        midi.ignore(5);
    }
    else if (event_type == 81)
    {
        midi.ignore();
        char c1,c2,c3;
        midi.get(c1);
        midi.get(c2);
        midi.get(c3);
        int MPQN = dec_con({c3,c2,c1});
        int MPM = 60000000;

        int BPM = MPM/MPQN;
        int TPMS = 60000/BPM;

        desmos << "r=" << "\\frac{" << TPMS << "}{30}" << '\n';
    }
    else if (event_type == 3)
    {
        midi.get(c);
        int j = dec_con({c});

        midi.ignore(j);
    }
}

void MidiFile::note_on(NoteStream& r, ifstream& midi)
{
    char c;
    midi.get(c);
    int i = dec_con({c});

    int value = i;
    midi.ignore();

    r.push_back({value, ticks_passed});
}

void MidiFile::note_off(NoteStream& r, ifstream& midi, ofstream& desmos)
{
    char c;
    midi.get(c);
    int i = dec_con({c});
    midi.ignore();

    r.at(i).set_end_time(ticks_passed);

    int locate_index = r.get_index(i);


    desmos << "A_{" << (note_index + 1) << "}=\\left[" 
            << (i - 57) << "\\right]\n";
    desmos << "\\operatorname{tone}\\left(f\\left(A_{" 
            << (note_index + 1) << "}\\right)" 
            << r.at(i).get_formatted_time(ticks_per_beat) << "\\right)\n";

    r.erase(locate_index);

    note_index++;
}