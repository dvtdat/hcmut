#include <bits/stdc++.h>

using namespace std;

// Singleton pattern
class Ministry {
private:
    string name;
    Ministry(const string& name) : name(name) {} // constructor at private
    
public:
    static Ministry& getInstance(const string& name) {
        static unordered_map<string, Ministry> ministries;
        auto it = ministries.find(name);
        if (it == ministries.end()) {
            it = ministries.emplace(name, Ministry(name)).first;
        }
        return it->second;
    }
    
    void performDuties() {
        cout << "Ministry of " << name << " is performing its duties." << endl;
    }
};

int main() {
    Ministry& ministry1 = Ministry::getInstance("Finance");
    Ministry& ministry2 = Ministry::getInstance("Education");
    Ministry& ministry3 = Ministry::getInstance("Health");
    
    ministry1.performDuties();
    ministry2.performDuties();
    ministry3.performDuties();
    
    return 0;
}
