#include <iostream>
using namespace std;

float sumTriple(float num1, float num2, float num3) {
    return num1 + num2 + num3;
}

float mulTriple(float num1, float num2, float num3) {
    return num1 * num2 * num3;
}

float aveTriple(float num1, float num2, float num3) {
    return (num1 + num2 + num3) / 3.0;
}

int main() {
    float num1, num2, num3;

    while (true) {
        cout << "Enter three numbers (or -1 to exit): ";
        cin >> num1 >> num2 >> num3;

        if (num1 == -1 || num2 == -1 || num3 == -1) {
            cout << "Exiting program...\n";
            break;
        }

        float sum = sumTriple(num1, num2, num3);
        float product = mulTriple(num1, num2, num3);
        float average = aveTriple(num1, num2, num3);

        cout << "Sum: " << sum << endl;
        cout << "Product: " << product << endl;
        cout << "Average: " << average << endl;
    }

    return 0;
}

