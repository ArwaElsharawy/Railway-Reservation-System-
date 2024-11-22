#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;

int main() {
    User u1;
    int choose;
    cout << "\n-------Welcome to our  railway reservation system-------\n ";
again:

    cout << " To Create An Account Press (1) \n  To Login Press (2) \n";
    cin >> choose;
    switch (choose)
    {
    case 1:
        u1.Create();
        u1.BookTicket();
        break;
    case 2:
        u1.SignIn();
        break;
    default:
        cout << " UnValid Choice Please Try Again...! \n";
        goto again;
        break;
    }
    return 0;
}