#include <iostream>
#include <string>

using namespace std;

int findMax(int* arr, int n) {
    if (n == 1) return arr[0];
    int mx = findMax(arr + 1, n - 1);
    return (arr[0] > mx) ? arr[0] : mx;
}

void printArray(int n) {
    if (n == 0) {
        std::cout << "0"; return;
    }
    printArray(n - 1);
    std::cout << ", " << n;
}

void printPattern(int n) {
    if (n <= 0) {
        std::cout << n;
        return;
    }
    std::cout << n << ' ';
    printPattern(n - 5);
    std::cout << ' ' << n;
}

string process(string str, int idx) {
    if (idx == str.length()) return "";
    if (str[idx] != ' ') return str[idx] + process(str, idx + 1);
    return process(str, idx + 1);
}

bool isPalindrome(string str) {
    str = process(str, 0);
    if (str.length() <= 1) return true;
    if (str[0] == str[str.length() - 1]) {
        return isPalindrome(str.substr(1, str.length() - 2));
    }
    return false;
}

int findGCD(int a, int b) {
    if (b == 0) return a;
    return findGCD(b, a % b);
}

int findLCM(int a, int b) {
    return a * b / findGCD(a, b);
}

void printHailstone(int n) {
    if (n == 1) {
        cout << 1; return;
    }

    cout << n << ' ';
    return printHailstone(n & 1 ? n * 3 + 1 : n / 2);
}

char* reverse(char* str, int n) {
    if (n <= 1) return str;
    swap(str[0], str[n - 1]);
    reverse(str + 1, n - 2);
    return str;
}

int myArrayToIntNew(char *str, int n) {
    if (n == 0) return str[0];
    return myArrayToIntNew(str + 1, n - 1) * 10 + (str[0] - '0');
}

int myArrayToInt(char *str, int n) {
    reverse(str, n);
    return myArrayToIntNew(str, n);
}

int strLen(char* str)     
{
    if (*str == '\0') return 0;
    return 1 + strLen(str + 1);
} 

int main() {
    char str[] = "1234";
    printf("%d", strLen(str));
    return 0;
}
