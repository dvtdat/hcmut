#include <bits/stdc++.h>

using namespace std;

// Target interface
class UniversityStudent {
public:
    virtual ~UniversityStudent() = default;
    virtual string RequestUniversityStudent() const = 0;
};

// Adaptee class
class HighSchoolStudent {
private:
    int id;
    string name;
    string schoolName;

public:
    HighSchoolStudent() : id(0), name(""), schoolName("") {}
    HighSchoolStudent(int id, string name, string schoolName) : id(id), name(name), schoolName(schoolName) {}
    ~HighSchoolStudent() = default;

    int GetID() const {
        return id;
    }

    string GetName() const {
        return name;
    }

    string GetSchoolName() const {
        return schoolName;
    }
};

// Adapter class
class HighSchoolStudentAdapter : public UniversityStudent, public HighSchoolStudent {
public:
    HighSchoolStudentAdapter() {}
    HighSchoolStudentAdapter(const HighSchoolStudent& highSchoolStudent) : HighSchoolStudent(highSchoolStudent) {}
    string RequestUniversityStudent() const override {
        int oldId = GetID();
        string oldName = GetName();
        string oldSchoolName = GetSchoolName();

        oldId += 100000;
        oldName = "Mr/Ms. " + oldName;
        oldSchoolName = "University of " + oldSchoolName;

        return "ID: " + to_string(oldId) + "\nName: " + oldName + "\nSchool Name: " + oldSchoolName;
    }
};

class Client {
public:
    // Client only accept UniersityStudent in its paramenter, HighSchoolStudent will not be able to be used
    static void RequestStudent(const UniversityStudent *universityStudent) {
        cout << universityStudent->RequestUniversityStudent() << endl;
    }
};

int main() {
    HighSchoolStudent* highSchoolStudent = new HighSchoolStudent(2252141, "Dat", "Ho Chi Minh City");
    // Client::RequestStudent(highSchoolStudent); // will not work
    
    HighSchoolStudentAdapter* highSchoolStudentAdapter = new HighSchoolStudentAdapter(*highSchoolStudent);
    Client::RequestStudent(highSchoolStudentAdapter);
}