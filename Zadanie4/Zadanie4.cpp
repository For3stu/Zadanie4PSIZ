#include <iostream>
#include <string>

using namespace std;

int choice;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        do {
            cout << "Kalkulator 0.1\n";
            cout << "1. Obliczenie BER" << endl << "2. Test 1" << endl << "3. Test 2" << endl << "4. Test 3" << endl << "0. Quit\n";
            
            cin >> choice;

            switch (choice)
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
                break;;
            }
        } 
        while (choice !=0);
    }
}

