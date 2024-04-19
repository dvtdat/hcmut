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

class University {
private:
    Student** students;

public:
    University() {
        students = new Student*[100];
    }

    ~University() {
        for (int i = 0; i < 100; i++) {
            if (students[i]) {
                delete students[i];
            }
        }
        delete[] students;
    }

    void addStudent(string name, int score) {
        cout << "Adding student...\n";
        for (int i = 0; i < 100; i++) {
            if (students[i] == NULL) {
                students[i] = new Student(name, score);
                break;
            }
        }
    }

    void displayStudents() {
        cout << "Displaying students...\n";
        for (int i = 0; i < 100 && students[i]; i++) {
            students[i]->print();
        }
    }

    void getHighestScore() {
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
};

int main() {
    int input = -1;
    University u;
    
    while (input != 0) {
        cout << "1. Add student\n2. Display students\n3. Get highest score\n0. Exit\n";
        cin >> input;

        if (input == 1) {
            string name;
            int score;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter score: ";
            cin >> score;
            u.addStudent(name, score);
        } else if (input == 2) {
            u.displayStudents();
        } else if (input == 3) {
            u.getHighestScore();
        }
    }    
}