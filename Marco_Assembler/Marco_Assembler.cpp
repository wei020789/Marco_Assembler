# include "process.h"

int main()
{
    file.open("input.txt");
    ofstream nametable, deftab, argtab, ExpandingProgram;
    nametable.open("nametab.txt");
    deftab.open("deftab.txt");
    argtab.open("argtab.txt");
    ExpandingProgram.open("ExpandingProgram.txt");

    if (file.is_open())
    {
        while (!file.eof())
        {
            GETLINE();
            PROCESSLINE();
        }

        nametable << "NAMETAB：" << endl;
        for (int i = 0; i < NAMETAB.size(); i++)
        {
            nametable << NAMETAB[i].first << ' ' << NAMETAB[i].second.first << ' ' << NAMETAB[i].second.second << endl;
        }
        nametable.close();
        deftab << "\nDEFTAB：" << endl;
        for (int i = 0; i < DEFTAB.size(); i++)
        {
            deftab << DEFTAB[i] << endl;
        }
        deftab.close();
        argtab << "\nARGTAB：" << endl;
        for (int i = 0; i < ARGTAB.size(); i++)
        {
            argtab << ARGTAB[i] << endl;
        }
        argtab.close();
        ExpandingProgram << "\nOUTPUT：" << endl;
        for (int i = 0; i < OUTPUT.size(); i++)
            ExpandingProgram << OUTPUT[i] << endl;
        ExpandingProgram.close();

        cout << "Output success!" << endl << "argtab.txt、deftab.txt、expandingProgram.txt.nametab.txt 已建好" << endl;
    }
    else
        cout << "open file error!" << endl;
    file.close();
    system("PAUSE");
    return 0;
}

