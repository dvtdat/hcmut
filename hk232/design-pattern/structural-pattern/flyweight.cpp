#include <bits/stdc++.h>

using namespace std;

class PlaneType { // shared state, flyweight class
private:
    string name;
    string manufacturer;
    int passengerCapacity;
    int range;

public:
    PlaneType() = default;
    PlaneType(string name, string manufacturer, int passengerCapacity, int range) {
        this->name = name;
        this->manufacturer = manufacturer;
        this->passengerCapacity = passengerCapacity;
        this->range = range;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Passenger Capacity: " << passengerCapacity << endl;
        cout << "Range: " << range << endl;
    }

    string getName() {
        return name;
    }
};

class PlaneTypeFactory { // flyweight factory, manage existing flyweight objects
private:
    static unordered_map<string, PlaneType> planeTypes;

public:
    static PlaneType getPlaneType(string name, string manufacturer, int passengerCapacity, int range) {
        if (planeTypes.find(name) == planeTypes.end()) {
            planeTypes[name] = PlaneType(name, manufacturer, passengerCapacity, range);
        }
        return planeTypes[name];
    }
};

unordered_map<string, PlaneType> PlaneTypeFactory::planeTypes; // be careful with static declaring order

class Plane { // unique state
private:
    string livery;
    string locaction;
    PlaneType planeType;

public:
    Plane() = default;
    Plane(string livery, string locaction, PlaneType planeType) {
        this->livery = livery;
        this->locaction = locaction;
        this->planeType = planeType;
    }

    void print() {
        cout << "Livery: " << livery << endl;
        cout << "Location: " << locaction << endl;
        planeType.print();
    }

    PlaneType getPlaneType() {
        return planeType;
    }
};

class Airlines { // client
private:
    string name;
    string codeICAO;
    vector<Plane> planes;

public:
    Airlines() = default;
    Airlines(string name, string codeICAO) {
        this->name = name;
        this->codeICAO = codeICAO;
    }

    void printInfo() {
        cout << "Name: " << name << endl;
        cout << "ICAO: " << codeICAO << endl;
    }

    void addPlane(Plane plane, int amount = 1) {
        for (int i = 0; i < amount; i++) {
            planes.push_back(plane);
        }
    }

    void addPlane(string livery, string locaction, PlaneType planeType, int amount = 1) {
        for (int i = 0; i < amount; i++) {
            planes.push_back(Plane(livery, locaction, planeType));
        }
    }

    void addPlane(string livery, string locaction, string name, string manufacturer, int passengerCapacity, int range, int amount = 1) {
        for (int i = 0; i < amount; i++) {
            planes.push_back(Plane(livery, locaction, PlaneType(name, manufacturer, passengerCapacity, range)));
        }
    }

    void printAllFleet() {
        cout << "Current fleet size of " << name << ": " << planes.size() << endl; // "planes.size()" is the number of "Plane" objects, not the number of "PlaneType" objects
        cout << "Current fleet of " << name << ": " << endl;
        for (auto plane : planes) {
            plane.print();
        }
    }

    void printByType(string name) {
        for (auto plane : planes) {
            if (plane.getPlaneType().getName() == name) {
                plane.print();
            }
        }
    }
};


class Client {
public:
    static void createPlaneTypes() {
        PlaneTypeFactory::getPlaneType("Boeing 737-800", "Boeing", 189, 5200);
        PlaneTypeFactory::getPlaneType("Boeing 737-900ER", "Boeing", 215, 5750);
        PlaneTypeFactory::getPlaneType("Boeing 737 MAX 8", "Boeing", 210, 6300);
        PlaneTypeFactory::getPlaneType("Boeing 737 MAX 9", "Boeing", 220, 7050);
        PlaneTypeFactory::getPlaneType("Boeing 737 MAX 10", "Boeing", 230, 7050);
        PlaneTypeFactory::getPlaneType("Boeing 747-400", "Boeing", 416, 13430);
        PlaneTypeFactory::getPlaneType("Boeing 747-8", "Boeing", 467, 14815);
        PlaneTypeFactory::getPlaneType("Boeing 767-300ER", "Boeing", 218, 9700);
        PlaneTypeFactory::getPlaneType("Boeing 777-200ER", "Boeing", 280, 9700);
        PlaneTypeFactory::getPlaneType("Boeing 777-300ER", "Boeing", 396, 13600);
        PlaneTypeFactory::getPlaneType("Boeing 777-9", "Boeing", 426, 13500);
        PlaneTypeFactory::getPlaneType("Boeing 787-8", "Boeing", 242, 14140);
        PlaneTypeFactory::getPlaneType("Boeing 787-9", "Boeing", 290, 14140);
        PlaneTypeFactory::getPlaneType("Boeing 787-10", "Boeing", 330, 11950);
        PlaneTypeFactory::getPlaneType("Airbus A220-100", "Airbus", 108, 6100);
        PlaneTypeFactory::getPlaneType("Airbus A220-300", "Airbus", 141, 6100);
        PlaneTypeFactory::getPlaneType("Airbus A319neo", "Airbus", 160, 6850);
        PlaneTypeFactory::getPlaneType("Airbus A320neo", "Airbus", 195, 6850);
        PlaneTypeFactory::getPlaneType("Airbus A321neo", "Airbus", 240, 7400);
        PlaneTypeFactory::getPlaneType("Airbus A321-200", "Airbus", 220, 5950);
        PlaneTypeFactory::getPlaneType("Airbus A350-900", "Airbus", 325, 14800);
    }
    
    static void createAirlines() {
        Airlines VietnamAirlines("Vietnam Airlines", "HVN");
        VietnamAirlines.printInfo();
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Airbus A320neo", "Airbus", 195, 6850), 5);
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Airbus A321-200", "Airbus", 220, 5950), 47);
        VietnamAirlines.addPlane("Sky Team", "HAN", PlaneTypeFactory::getPlaneType("Airbus A321-200", "Airbus", 220, 5950), 1);
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Airbus A321neo", "Airbus", 240, 7400), 20);
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Airbus A350-900", "Airbus", 325, 14800), 1);
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Boeing 787-9", "Boeing", 290, 14140), 11);
        VietnamAirlines.addPlane("Standard Blue", "HAN", PlaneTypeFactory::getPlaneType("Boeing 787-10", "Boeing", 330, 11950), 4);
        VietnamAirlines.printAllFleet();
    }
};

int main() {
    Client::createAirlines();
}