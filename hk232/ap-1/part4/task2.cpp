#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int user;
    
    while (true) {
        cout << "Guess the secret number (between 0 and 20): ";
        cin >> user;
        
        if (user < n) {
            cout << "The secret number is greater." << endl;
        } else if (user > n) {
            cout << "The secret number is smaller." << endl;
        } else {
            cout << "Congratulations! You guessed the secret number correctly." << endl;
            break;
        }
    }
    
    return 0;
}

