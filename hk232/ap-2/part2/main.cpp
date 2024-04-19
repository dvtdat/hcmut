#include <bits/stdc++.h>

using namespace std;

void addStudent(string name, int score, string*& names, int*& scores, int& N) {
    string* newNames = new string[N + 1];
    int* newScores = new int[N + 1];
    for (int i = 0; i < N; i++) {
        newNames[i] = names[i];
        newScores[i] = scores[i];
    }
    newNames[N] = name;
    newScores[N] = score;
    N++;
    delete[] names;
    delete[] scores;
    names = newNames;
    scores = newScores;
}

void displayStudent(string* names, int* scores, int N) {
    cout << "Displaying students\n";
    for (int i = 0; i < N; i++) {
        cout << names[i] << ' ' << scores[i] << '\n';
    }
    cout << "\n";
}

void displayHighestScore(string* names, int* scores, int N) {
    int maxScore = 0;
    string* highestScoreStudents = nullptr;
    int highestScoreStudentsCount = 0;

    for (int i = 0; i < N; ++i) {
        maxScore = max(maxScore, scores[i]);
    }

    for (int i = 0; i < N; ++i) {
        if (scores[i] == maxScore) {
            string* newHighestScoreStudents = new string[highestScoreStudentsCount + 1];
            for (int j = 0; j < highestScoreStudentsCount; ++j) {
                newHighestScoreStudents[j] = highestScoreStudents[j];
            }
            newHighestScoreStudents[highestScoreStudentsCount] = names[i];
            highestScoreStudentsCount++;
            delete[] highestScoreStudents;
            highestScoreStudents = newHighestScoreStudents;
        }
    }

    cout << "Displaying students with highest score\n";
    for (int i = 0; i < highestScoreStudentsCount; ++i) {
        cout << highestScoreStudents[i] << ' ' << maxScore << '\n';
    }
    cout << "\n";
}

int main() {
    string* names = nullptr;
    int* scores = nullptr;  
    int N = 0;

    int input = -1;
    while (input != 0) {
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Display students with highest score\n";
        cout << "0. Exit\n";
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
                addStudent(name, score, names, scores, N);
                break;
            }
            case 2: {
                displayStudent(names, scores, N);
                break;
            }
            case 3: {
                displayHighestScore(names, scores, N);
                break;
            }
            case 0: {
                cout << "Exiting\n";
                break;
            }
            default: {
                cout << "Invalid choice\n";
                break;
            }
        }
    }

    delete[] names;
    delete[] scores;
}