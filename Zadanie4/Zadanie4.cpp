#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

int wybor;
fstream logFile;

void Zapis_Logow(string msg)
{
    string ss;
    time_t currentTime = time(NULL);
    string txttime = (string)asctime(localtime(&currentTime));
    txttime = txttime.substr(0, txttime.length() - 1);
    ss = (string)"T: " + txttime + " M: " + msg + "\n";
    logFile << ss.c_str();
    logFile.flush();
    cout << ss.c_str();
    cout.flush();
}

void Otwarcie_loga(string fileName)
{
    logFile.open(fileName.c_str(), ios_base::app);
    if (!logFile.good() == true)
    {
        cout << "Brak pliku log " << "log.txt" << endl;
    }
    Zapis_Logow("Log zostal otwarty");
}


void closeLog(void)
{
    Zapis_Logow("Log jest zamkniety!");
    logFile.close();
}

void tworzeniepliku1(const string name, const int count, const char value)
{
    fstream f;
    f.open(name.c_str(), ios::binary | ios::out);
    for (int i = 0; i < count; i++)
    {
        f.write((char*)&value, 1);
    }
    f.close();
}

void tworzenie()
{
    Otwarcie_loga("log.txt");

    Zapis_Logow("Brak danych od uzytkownika");
    Zapis_Logow("Tworzenie testowych plikow");
    //test 1
    tworzeniepliku1("plik1.1.bin", 100, 0x55);
    tworzeniepliku1("plik1.2.bin", 100, 0x55);
    //test 2

    tworzeniepliku1("plik2.1.bin", 100, 0x55);
    tworzeniepliku1("plik2.2.bin", 100, 0x48);

    //test 3
    tworzeniepliku1("plik3.1.bin", 419430400, 0x55);
    tworzeniepliku1("plik3.2.bin", 419430400, 0x50);

    Zapis_Logow("Testowe pliki sa tworzone");
}



int main(int argc, char* argv[])
{
    if (argc != 3) {
        tworzenie();
        do {
            cout << "Kalkulator BER 0.2\n";
            cout << "1. Obliczenie BER" << endl << "2. Test 1" << endl << "3. Test 2" << endl << "4. Test 3" << endl << "0. Quit\n";
            
            cin >> wybor;

            switch (wybor)
            {
            case 0:
                cout << "Quit\n";
                return 0;
            case 1:
                cout << "Obliczenie\n";
                break;
            case 2:
                cout << "Test1\n";
                break;
            case 3:
                cout << "Test2\n";
                break;
            case 4:
                cout << "Test3\n";
                break;
            }
        } 
        while (wybor!=0);
    }
}
