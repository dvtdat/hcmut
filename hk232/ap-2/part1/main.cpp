#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;

string student[MAXN];
int N;

void addStudent(string newStudent) {
    cout << "Adding student: " << newStudent << '\n';
    student[N++] = newStudent;
}

void displayStudents() {
    cout << "Displaying students: ";
    for (int i = 0; i < N; i++) {
        cout << student[i] << ' ';
    }
    cout << "\n";
}

void removeStudentByName(string name) {
    cout << "Removing student with name: " << name << '\n';
    for (int i = 0; i < N; i++) {
        if (student[i] == name) {
            for (int j = i; j < N - 1; j++) {
                student[j] = student[j + 1];
            }
            N--;
            displayStudents();
            return;
        }
    }
    cout << "Student not found" << '\n';
}

int main() {
    int input;
    while (input != 0) {
        cout << "1. Add student" << '\n';
        cout << "2. Display students" << '\n';
        cout << "3. Remove student" << '\n';
        cout << "0. Exit" << '\n';
        cin >> input;
        
        if (input == 1) {
            string name;
            cin >> name;
            addStudent(name);
        } else if (input == 2) {
            displayStudents();
        } else if (input == 3) {
            string name;
            cin >> name;
            removeStudentByName(name);
        }
    }
    return 0;
}