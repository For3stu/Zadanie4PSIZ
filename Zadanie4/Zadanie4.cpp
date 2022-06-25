#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

int wybor;
fstream logFile;

struct berResults
{
    double Ilosc; 
    double Bledy; 
    float ber;  
    clock_t t1; 
    clock_t t2; 
};

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


void zamkniecieloga(void)
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

uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2; 
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}

berResults obliczenieBer(string fpath1, string fpath2)
{
    std::fstream f1, f2; 
    berResults results;
    results.t1 = 0;
    results.t2 = 0;
    results.ber = 0;
    results.Bledy = 0;
    results.Ilosc = 0;

    Zapis_Logow("Liczenie BER...");
    f1.open(fpath1.c_str(), std::ios::binary | std::ios::in);
    f2.open(fpath2.c_str(), std::ios::binary | std::ios::in);
    char a = 0x00;
    char b = 0x00;
    results.t1 = clock();

    while (!f1.eof())
    {
        f1 >> a; 
        f2 >> b;
        if (!f1.eof()) 
        {
            results.Bledy += hammingDistance(a, b);
            results.Ilosc += 8; 
        }
    }

    results.ber = (float)results.Bledy / results.Ilosc;
    results.t2 = clock();
    Zapis_Logow("Obliczenie zakonczone pomyslnie");
    return results;
}

void wyswietlwynik(berResults results)
{
    stringstream message;
    message << "Wynik: " << endl;
    message << "BER: " << results.ber << endl;
    message << "Ilosc: " << results.Ilosc << endl;
    message << "Bledy: " << results.Bledy << endl;
    message << "Czas obliczenia: " << ((float)results.t2 - results.t1) / CLOCKS_PER_SEC << " sec " << endl;
    Zapis_Logow(message.str());
}

int main(int argc, char* argv[])
{
    berResults WynikBer;

    if (argc != 3) {
        tworzenie();
        do {
            cout << "Kalkulator BER 2.0\n";
            cout << "1. Test 1" << endl << "2. Test 2" << endl << "3. Test 3" << endl << "0. Quit\n";
            
            cin >> wybor;

            switch (wybor)
            {
            case 0:
                cout << "Quit\n";
                return 0;
            case 1:
                cout << "Test1\n";
                WynikBer=obliczenieBer("plik1.1.bin", "plik1.2.bin");
                wyswietlwynik(WynikBer);
                break;
            case 2:
                cout << "Test2\n";
                WynikBer=obliczenieBer("plik2.1.bin", "plik2.2.bin");
                wyswietlwynik(WynikBer);
                break;
            case 3:
                cout << "Test3\n";
                WynikBer = obliczenieBer("plik3.1.bin", "plik3.2.bin");
                wyswietlwynik(WynikBer);
                break;
            }
        } 
        while (wybor!=0);
    }
}
