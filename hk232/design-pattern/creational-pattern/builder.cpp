#include <bits/stdc++.h>

using namespace std;

// Product: School
class School {
public:
    vector<string> facilities;

    void ListFacilities() const {
        cout << "School facilities: ";
        for (size_t i = 0; i < facilities.size(); i++) {
            if (facilities[i] == facilities.back()) {
                cout << facilities[i];
            } else {
                cout << facilities[i] << ", ";
            }
        }
        cout << "\n\n";
    }
};

// Product: University
class University {
public:
    vector<string> facilities;

    void ListFacilities() const {
        cout << "University facilities: ";
        for (size_t i = 0; i < facilities.size(); i++) {
            if (facilities[i] == facilities.back()) {
                cout << facilities[i];
            } else {
                cout << facilities[i] << ", ";
            }
        }
        cout << "\n\n";
    }
};

class Builder {
public:
    virtual ~Builder() {}
    virtual void BuildClassrooms() const = 0;
    virtual void BuildAuditorium() const = 0;
    virtual void BuildSportArena() const = 0;
    virtual void BuildLibrary() const = 0;
    virtual void BuildDormitory() const = 0;
    virtual void BuildCanteen() const = 0;
};

class SchoolBuilder : public Builder {
private:
    School* school;

public:
    SchoolBuilder() : school(new School()) {}

    ~SchoolBuilder() {
        delete school;
    }

    void Reset() {
        delete school;
        school = new School();
    }

    void BuildClassrooms() const override {
        cout << "School - Add classrooms\n";
        school->facilities.push_back("Classrooms");
    }

    void BuildAuditorium() const override {
        cout << "School - Can't add auditorium\n";
    }

    void BuildSportArena() const override {
        cout << "School - Can't add sport arena\n";
    }

    void BuildLibrary() const override {
        cout << "School - Add library\n";
        school->facilities.push_back("Library");
    }

    void BuildDormitory() const override {
        cout << "School - Can't add dormitory\n";
    }

    void BuildCanteen() const override {
        cout << "School - Add canteen\n";
        school->facilities.push_back("Canteen");
    }

    School* GetSchool() {
        School* result = school;
        school = new School();
        return result;
    }
};

class UniversityBuilder : public Builder {
private:
    University* university;

public:
    UniversityBuilder() : university(new University()) {}

    ~UniversityBuilder() {
        delete university;
    }

    void Reset() {
        delete university;
        university = new University();
    }

    void BuildClassrooms() const override {
        cout << "University - Add classrooms\n";
        university->facilities.push_back("Classrooms");
    }

    void BuildAuditorium() const override {
        cout << "University - Add auditorium\n";
        university->facilities.push_back("Auditorium");
    }

    void BuildSportArena() const override {
        cout << "University - Add sport arena\n";
        university->facilities.push_back("Sport arena");
    }

    void BuildLibrary() const override {
        cout << "University - Add library\n";
        university->facilities.push_back("Library");
    }

    void BuildDormitory() const override {
        cout << "University - Add dormitory\n";
        university->facilities.push_back("Dormitory");
    }

    void BuildCanteen() const override {
        cout << "University - Add canteen\n";
        university->facilities.push_back("Canteen");
    }

    University* GetUniversity() {
        University* result = university;
        university = new University();
        return result;
    }
};

class Director {
private:
    Builder* builder;

public:
    void set_builder(Builder* new_builder) {
        builder = new_builder;
    }

    void BuildMinimalFacilites() {
        builder->BuildClassrooms();
        builder->BuildCanteen();
    }

    void BuildFullFeaturedFacilites() {
        builder->BuildClassrooms();
        builder->BuildAuditorium();
        builder->BuildSportArena();
        builder->BuildLibrary();
        builder->BuildDormitory();
        builder->BuildCanteen();
    }
};

void Client(Director& director) {
    SchoolBuilder* schoolBuilder = new SchoolBuilder();
    director.set_builder(schoolBuilder);

    cout << "Minimal facilities for School:\n";
    director.BuildMinimalFacilites();
    schoolBuilder->GetSchool()->ListFacilities();

    cout << "Full featured facilities for School:\n";
    director.BuildFullFeaturedFacilites();
    schoolBuilder->GetSchool()->ListFacilities();

    delete schoolBuilder;

    UniversityBuilder* universityBuilder = new UniversityBuilder();
    director.set_builder(universityBuilder);

    cout << "Minimal facilities for University:\n";
    director.BuildMinimalFacilites();
    universityBuilder->GetUniversity()->ListFacilities();

    cout << "Full featured facilities for University:\n";
    director.BuildFullFeaturedFacilites();
    universityBuilder->GetUniversity()->ListFacilities();

    delete universityBuilder;
}

int main() {
    Director* director = new Director();
    Client(*director);
    delete director;
}