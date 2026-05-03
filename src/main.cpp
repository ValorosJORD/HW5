#include "MidiFile.h"

#include <windows.h>
#include<iostream>
    using std::cout;
    using std::cin;
#include<fstream>
    using std::ifstream;
#include<string>
    using std::string;
    using std::getline;

int main()
{
    bool passedChoice = false;
    string s;

    while (!passedChoice) {
        cout << "Use example file? (Y/n)";
        char choice;
        cin >> choice;
        if (choice == 'n') {
            cout << "Enter a midi file name: ";
            cin >> s;
            cout << '\n';
            passedChoice = true;
        } else if (choice == 'Y') {
            s = "examples\\g.mid";
            passedChoice = true;
        } else {
            cout << "Invalid Choice.";
        }
    }
    
    MidiFile mid(s);

    cout << "Desmos output text can be found in \"DesmosOutput.txt\"\n"
         << "To use, ctrl+A entire file, ctrl+C, click into first\n"
         << "line of new Desmos file, and ctrl+V.\n\n";
    cout << "Or, copy directly to clipboard (Y/n)\n";
    char choice = 'c';
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        ifstream desmos;
        desmos.open("DesmosOutput.txt");

        string soutput = "";
        const char* output;

        if (desmos)
        {
            string s = "1";
            string output = "";
            while (s != "")
            {
                getline(desmos, s);
                soutput += '\n';
                soutput += s;
            }
        }

        output = soutput.c_str();
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
    }

    return 0;
}
