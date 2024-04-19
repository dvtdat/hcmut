#include <bits/stdc++.h>

using namespace std;

class School;
class Semester;
class Assignment;
class Test;
class Exam;
class Course;
class Student;
class UniversityStudent;
class CollegeStudent;
class University;
class College;

class Student {
protected:
    string name;
    string DOB;
    School* school;
    Semester* Semesters[100];

    void addSemester(Semester* semester) {
        for (int i = 0; i < 100; i++) {
            if (Semesters[i] == NULL) {
                Semesters[i] = semester;
                break;
            }
        }
    }

public:
    Student(string name, string DOB) {
        this->name = name;
        this->DOB = DOB;
    }

    virtual void print() = 0;
};

class UniversityStudent : public Student {
public:
    UniversityStudent(string name, string DOB, Semester** semesters, School* school) : Student(name, DOB) {
        this->school = school;
        for (int i = 0; i < 100; i++) {
            if (semesters[i] == NULL) {
                break;
            }
            addSemester(semesters[i]);
        }
    };

    void print() {
        cout << "University student: " << name << ", DOB: " << DOB << endl;
    }
};

class CollegeStudent : public Student {
public:
    CollegeStudent(string name, string DOB, Semester** semesters, School* school) : Student(name, DOB) {
        this->school = school;
        for (int i = 0; i < 100; i++) {
            if (semesters[i] == NULL) {
                break;
            }
            addSemester(semesters[i]);
        }
    };

    void print() {
        cout << "College student: " << name << ", DOB: " << DOB << endl;
    }
};

class Assignment {
private:
    string names;
    int marks;
    string dueDate;

public:
    Assignment(string names, int marks, string dueDate) {
        this->names = names;
        this->marks = marks;
        this->dueDate = dueDate;
    }

    void print() {
        cout << "Name: " << names << ", marks: " << marks << ", due date: " << dueDate << endl;
    }
};

class Test {
private:
    string names;
    int marks;
    string date;

public:
    Test(string names, int marks, string date) {
        this->names = names;
        this->marks = marks;
        this->date = date;
    }

    void print() {
        cout << "Name: " << names << ", marks: " << marks << ", date: " << date << endl;
    }
};

class Exam {
private:
    string names;
    int marks;
    string date;

public:
    Exam(string names, int marks, string date) {
        this->names = names;
        this->marks = marks;
        this->date = date;
    }

    void print() {
        cout << "Name: " << names << ", marks: " << marks << ", date: " << date << endl;
    }
};

class Course {
private:
    string name;
    string code;
    int credits;
    Assignment* assignments[100];
    Test* tests[100];
    Exam* exams[100];

public:
    Course() {
        for (int i = 0; i < 100; i++) {
            assignments[i] = NULL;
            tests[i] = NULL;
            exams[i] = NULL;
        }
    }

    Course(string name, string code, int credits) {
        this->name = name;
        this->code = code;
        this->credits = credits;
        for (int i = 0; i < 100; i++) {
            assignments[i] = NULL;
            tests[i] = NULL;
            exams[i] = NULL;
        }
    }

    Course(string name, string code, int credits, Assignment** assignments, Test** tests, Exam** exams) {
        this->name = name;
        this->code = code;
        this->credits = credits;
        for (int i = 0; i < 100; i++) {
            this->assignments[i] = assignments[i];
            this->tests[i] = tests[i];
            this->exams[i] = exams[i];
        }
    }

    void print() {
        cout << "Course: " << name << ", code: " << code << ", credits: " << credits << endl;
    }

    void setName(string name) {
        this->name = name;
    }

    void setCode(string code) {
        this->code = code;
    }

    void setCredits(int credits) {
        this->credits = credits;
    }

    void addAssignment(Assignment* assignment) {
        for (int i = 0; i < 100; i++) {
            if (assignments[i] == NULL) {
                assignments[i] = assignment;
                break;
            }
        }
    }

    void addTest(Test* test) {
        for (int i = 0; i < 100; i++) {
            if (tests[i] == NULL) {
                tests[i] = test;
                break;
            }
        }
    }

    void addExam(Exam* exam) {
        for (int i = 0; i < 100; i++) {
            if (exams[i] == NULL) {
                exams[i] = exam;
                break;
            }
        }
    }
};

class Semester {
private:
    Course* courses[100];
public:
    Semester() {
        for (int i = 0; i < 100; i++) {
            courses[i] = NULL;
        }
    }

    Semester(Course** courses) {
        for (int i = 0; i < 100; i++) {
            if (courses[i] == NULL) {
                break;
            }
            this->courses[i] = courses[i];
        }
    }

    void print() {
        for (int i = 0; i < 100; i++) {
            if (courses[i] == NULL) {
                break;
            }
            courses[i]->print();
        }
    
    }
};

class School {
protected:
    string name;
    string address;
    int capacity;

public:
    virtual void print() = 0;

    School(string name, string address, int capacity) {
        this->name = name;
        this->address = address;
        this->capacity = capacity;
    }
    
    void setName(string name) {
        this->name = name;
    }

    void setAddress(string address) {
        this->address = address;
    }

    void setCapacity(int capacity) {
        this->capacity = capacity;
    }
};

class University : public School {
private:
public:
    University(string name, string address, int capacity) : School(name, address, capacity) {}

    void print() {
        cout << "University: " << name << ", address: " << address << ", capacity: " << capacity << endl;
    }
};

class College : public School {
private:
public:
    College(string name, string address, int capacity) : School(name, address, capacity) {}

    void print() {
        cout << "College: " << name << ", address: " << address << ", capacity: " << capacity << endl;
    }
};

int main() {
    Assignment* firstAssignment(new Assignment("First assignment", 10, "01/01/2022"));
    Assignment* secondAssignment(new Assignment("Second assignment", 20, "01/02/2022"));
    Assignment* thirdAssignment(new Assignment("Third assignment", 30, "01/03/2022"));

    Test* firstTest(new Test("First test", 10, "01/01/2022"));
    Test* secondTest(new Test("Second test", 20, "01/02/2022"));

    Exam* firstExam(new Exam("First exam", 10, "01/01/2022"));
    Exam* secondExam(new Exam("Second exam", 20, "01/02/2022"));

    Course* UniversityCourse(new Course("First Course", "CS101", 3, new Assignment*[100]{firstAssignment, secondAssignment, thirdAssignment}, new Test*[100]{firstTest, secondTest}, new Exam*[100]{firstExam}));
    Course* CollegeCourse(new Course("First Course", "CS101", 3, new Assignment*[100]{firstAssignment, secondAssignment, thirdAssignment}, new Test*[100]{firstTest}, new Exam*[100]{firstExam}));

    Semester* UniversitySemester(new Semester(new Course*[100]{UniversityCourse, UniversityCourse, UniversityCourse, UniversityCourse, UniversityCourse, UniversityCourse, UniversityCourse, UniversityCourse}));
    Semester* CollegeSemester(new Semester(new Course*[100]{CollegeCourse, CollegeCourse, CollegeCourse, CollegeCourse}));

    University* HCMUT(new University("HCMC University of Technology", "268 Ly Thuong Kiet", 25000));
    College* HCMCT(new College("HCMC College of Technology", "1 Vo Van Ngan", 15000));

    UniversityStudent("Nguyen Van A", "01/01/2000", new Semester*[100]{UniversitySemester, UniversitySemester, UniversitySemester, UniversitySemester, UniversitySemester, UniversitySemester, UniversitySemester, UniversitySemester}, HCMUT);
    CollegeStudent("Nguyen Van B", "01/01/2000", new Semester*[100]{CollegeSemester, CollegeSemester, CollegeSemester, CollegeSemester}, HCMCT);
}