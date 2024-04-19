#include <iostream>
using namespace std;

int main() {
    double amount;
    int choice;

    cout << "Enter the amount of money in VND: ";
    cin >> amount;

    cout << "Choose the currency conversion:\n";
    cout << "1. VND to AUD\n";
    cout << "2. VND to USD\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "VND to AUD conversion:\n";
            cout << "Amount in AUD: " << amount * 0.000057 << endl;
            break;
        case 2:
            cout << "VND to USD conversion:\n";
            cout << "Amount in USD: " << amount * 0.000043 << endl;
            break;
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}

