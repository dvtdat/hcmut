#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;

int main() {
    string names[MAX_STUDENTS];
    int scores[MAX_STUDENTS];
    string status[MAX_STUDENTS];
    
    int numStudents = 0;
    
    while (numStudents < MAX_STUDENTS) {
        cout << "Enter student's name and score (separated by space), or enter -1 to stop: ";
        cin >> names[numStudents];
        
        if (names[numStudents] == "-1") {
            break;
        }
        
        cin >> scores[numStudents];
        
        if (scores[numStudents] >= 50) {
            status[numStudents] = "Passed";
        } else {
            status[numStudents] = "Failed";
        }
        
        numStudents++;
    }
    
    cout << "\nStudents\tScores\tStatus" << endl;
    for (int i = 0; i < numStudents; ++i) {
        cout << names[i] << "\t\t" << scores[i] << "\t" << status[i] << endl;
    }
    
    return 0;
}

