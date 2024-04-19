#include <bits/stdc++.h>

using namespace std;

const int UNIVERSITY_SEMESTER = 8;
const int UNIVERSITY_COURSE = 4;
const int UNIVERSITY_ASSIGNMENT = 3;
const int UNIVERSITY_TEST = 2;
const int UNIVERSITY_EXAM = 1;

const int COLLEGE_SEMESTER = 4;
const int COLLEGE_COURSE = 3;
const int COLLEGE_ASSIGNMENT = 1;
const int COLLEGE_TEST = 1;
const int COLLEGE_EXAM = 1;

const int MAX_SCORE = 10;
const int MAX_STUDENT = 20;

class Assignment {
private:
    int score;

public:
    Assignment() : score(0) {}
    Assignment(int score) : score(score) {}

    int getScore() const {
        return score;
    }

    void doAssignment() {
        score = rand() % (MAX_SCORE + 1);
    }
};

class Test {
private:
    int score;
    
public:
    Test() : score(0) {}
    Test(int score) : score(score) {}

    int getScore() const {
        return score;
    }

    void takeTest() {
        score = rand() % (MAX_SCORE + 1);
    }
};

class Exam {
private:
    int score;

public:
    Exam() : score(0) {}
    Exam(int score) : score(score) {}

    int getScore() const {
        return score;
    }

    void takeExam() {
        score = rand() % (MAX_SCORE + 1);
    }
};

class Course {
private:
    vector<Assignment> assignments;
    vector<Test> tests;
    vector<Exam> exams;

public:
    Course() {}
    Course(const int numberOfAssignments, const int numberOfTests, const int numberOfExams) {
        assignments = vector<Assignment>(numberOfAssignments);
        tests = vector<Test>(numberOfTests);
        exams = vector<Exam>(numberOfExams);
    }

    void doAssignment()  {
        for (auto &a : assignments) {
            a.doAssignment();
        }
    }

    void takeTest() {
        for (auto &t : tests) {
            t.takeTest();
        }
    }

    void takeExam() {
        for (auto &e : exams) {
            e.takeExam();
        }
    }

    float getAverageScore() {
        float sum = 0.0;
        for (auto a : assignments) {
            sum += 1.0 * a.getScore();
        }

        for (auto t : tests) {
            sum += 1.0 * t.getScore();
        }

        for (auto e : exams) {
            sum += 1.0 * e.getScore();
        }

        return 1.0 * sum / (assignments.size() + tests.size() + exams.size());
    }
};

class Semester {
protected:
    vector<Course> courses;
    Semester() {}

public:
    virtual void doAssignment() {
        for (auto &c : courses) {
            c.doAssignment();
        }
    }

    virtual void takeTest() {
        for (auto &c : courses) {
            c.takeTest();
        }
    }

    virtual void takeExam() {
        for (auto &c : courses) {
            c.takeExam();
        }
    }

    virtual float getAverageScore() const {
        float sum = 0.0;
        for (auto c : courses) {
            sum += 1.0 * c.getAverageScore();
        }
        return 1.0 * sum / courses.size();
    }
};

class UniversitySemester : public Semester {
public:
    UniversitySemester() {
        courses = vector<Course>(UNIVERSITY_COURSE, Course(UNIVERSITY_ASSIGNMENT, UNIVERSITY_TEST, UNIVERSITY_EXAM));
    }
};

class CollegeSemester : public Semester {
public:
    CollegeSemester() {
        courses = vector<Course>(COLLEGE_COURSE, Course(COLLEGE_ASSIGNMENT, COLLEGE_TEST, COLLEGE_EXAM));
    }
};

// product interface
class Student {
public:
    virtual ~Student() {}
    virtual void doAssignment() = 0;
    virtual void takeTest() = 0;
    virtual void takeExam() = 0;
    virtual float getAverageScore() const = 0;
};

// concrete product
class UniversityStudent : public Student {
private:
    vector<Semester> semesters;

public:
    UniversityStudent() {
        semesters = vector<Semester>(UNIVERSITY_SEMESTER, UniversitySemester());
    }

    void doAssignment() {
        for (auto &s : semesters) {
            s.doAssignment();
        }
    }
    
    void takeTest() {
        for (auto &s : semesters) {
            s.takeTest();
        }
    }

    void takeExam() {
        for (auto &s : semesters) {
            s.takeExam();
        }
    }

    float getAverageScore() const {
        float sum = 0.0;
        for (auto s : semesters) {
            sum += 1.0 * s.getAverageScore();
        }
        return 1.0 * sum / semesters.size();
    }
};

// concrete product
class CollegeStudent : public Student {
private:
    vector<Semester> semesters;

public:
    CollegeStudent() {
        semesters = vector<Semester>(COLLEGE_SEMESTER, CollegeSemester());
    }

    void doAssignment() {
        for (auto &s : semesters) {
            s.doAssignment();
        }
    }
    
    void takeTest() {
        for (auto &s : semesters) {
            s.takeTest();
        }
    }

    void takeExam() {
        for (auto &s : semesters) {
            s.takeExam();
        }
    }

    float getAverageScore() const {
        float sum = 0.0;
        for (auto s : semesters) {
            sum += 1.0 * s.getAverageScore();
        }
        return 1.0 * sum / semesters.size();
    }
};

// creator interface
class Institution {
public:
    virtual ~Institution() {}
    virtual Student* createStudent() const = 0;
};

// concrete creator
class University : public Institution {
public:
    Student* createStudent() const override {
        return new UniversityStudent();
    }
};

// concrete creator
class College : public Institution {
public:
    Student* createStudent() const override {
        return new CollegeStudent();
    }
};

class Client {
private:
    const Institution& institution;

public:
    Client(const Institution& institution) : institution(institution) {}

    void process() const {
        Student* students[MAX_STUDENT];
        for (int i = 0; i < MAX_STUDENT; ++i) {
            students[i] = institution.createStudent();
            students[i]->doAssignment();
            students[i]->takeTest();
            students[i]->takeExam();
            cout << "Average score of student number " << i + 1 << ": " << students[i]->getAverageScore() << endl;
        }
    }
};

int main() {
    srand(time(0));

    cout << fixed << setprecision(4);

    University university;
    College college;

    Client client1(university);
    Client client2(college);

    cout << "University students:" << endl;
    client1.process();
    cout << endl;

    cout << "College students:" << endl;
    client2.process();

    return 0;
}