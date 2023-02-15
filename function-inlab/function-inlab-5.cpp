#include <iostream>

using namespace std;

long int decimalToBinary(int decimal_number)
{
	if (decimal_number == 0) return 0;
    return (decimal_number % 2) + decimalToBinary(decimal_number / 2) * 10;
}

int main()
{
    cout << decimalToBinary(20);
}