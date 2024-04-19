#include <bits/stdc++.h>

using namespace std; 

class Student {
private:
    string name;
    int score;

public:
    Student(string name, int score) {
        this->name = name;
        this->score = score;
    }

    ~Student() {
        cout << "Student " << name << " deleted" << endl;
    }

    string getName() {
        return name;
    }

    int getScore() {
        return score;
    }

    void setName(string name) {
        this->name = name;
    }

    void setScore(int score) {
        this->score = score;
    }

    void print() {
        cout << "Name: " << name << ", score: " << score << endl;
    }
};

void addStudent(Student** students, string name, int score) {
    cout << "Adding student...\n";
    for (int i = 0; i < 100; i++) {
        if (students[i] == NULL) {
            students[i] = new Student(name, score);
            break;
        }
    }
}

void displayStudents(Student** students) {
    cout << "Displaying students...\n";
    for (int i = 0; i < 100 && students[i]; i++) {
        students[i]->print();
    }
}

void getHighestScore(Student** students) {
    cout << "Getting highest score...\n";
    int mx = 0;
    for (int i = 0; i < 100 && students[i]; i++) {
        if (students[i]->getScore() > mx) {
            mx = students[i]->getScore();
        }
    }

    for (int i = 0; i < 100 && students[i]; i++) {
        if (students[i]->getScore() == mx) {
            students[i]->print();
        }
    }

}

int main() {
    Student** students = new Student*[100];

    int input = -1;

    while (input != 0) {
        cout << "1. Add student" << '\n';
        cout << "2. Display students" << '\n';
        cout << "3. Get highest score" << '\n';
        cout << "0. Exit" << '\n';
        cout << "Enter your choice: ";
        cin >> input;

        switch (input) {
            case 1: {
                string name;
                int score;
                cout << "Enter student name: ";
                cin >> name;
                cout << "Enter student score: ";
                cin >> score;
                addStudent(students, name, score);
                break;
            }
            case 2: {
                displayStudents(students);
                break;
            }
            case 3: {
                getHighestScore(students);
                break;
            }
        }
    }

    delete[] students;
}