#include <iostream>
#include <string>

using namespace std;

/* Implementation of Diamond Inheritance*/

class Animal // abstract class
{
private:
    int id;
public:
    static int idIdx;

    Animal() : id(idIdx++) {}
    virtual ~Animal() {}
    int getID() {return id;}
    virtual void eat() = 0; //pure virtual function
    //void play() {}
    virtual void play() = 0; //switch to the above declaration to see the differences
};

int Animal::idIdx = 0;

class Insect : virtual public Animal
{
    int nLegs;
public:
    Insect(int nL = 8) : nLegs(nL) {}
    void eat()
    {
        cout << "Insect " << getID() << " is eating\n";
    }
    void play()
    {
        cout << "Insect " << getID() << " is playing\n";
    }
};

//class Ant : public Insect
class Ant : virtual public Insect
{
private:
    int power;
public:
    Ant(int nL = 6, int pw = 1000) :  Insect(nL), power(pw) {}
    ~Ant() {}

    void eat()
    {
        cout << "Ant " << getID() << "[power: " << power <<"] is eating\n";
    }
    void play()
    {
        cout << "Ant " << getID() << "[power: " << power <<"] is playing\n";
    }
};

class Mammal : virtual public Animal
{
public:
    virtual void giveBirth() = 0;
};

//class Human : public Mammal
class Human : virtual public Mammal
{
protected:
    string name;
    int age;
public:
    Human(const string & strName = "NoOne", int a = 0) : name(strName), age(a) {} 
    //before entering the curly bracket of the constructor, everything must be created
    //every attribute of the parent class must be defined before entering the curly bracket of the child's constructor

    ~Human() {} //currently doing nothing

    
    void giveBirth() {} //even though there's nothing, the function must be here for everything to work finely
    void eat()
    {
        cout << "Human " << getID() << "[name: " << name << ", age: " << age << "] is eating\n";
    }
    void play()
    {
        cout << "Human " << getID() << "[name: " << name << ", age: " << age << "] is playing\n";
    }
};


class AntMan : public Ant, public Human //order of declaration is important, try changing the order to see the differences
{
public:
    /* void eat() { cout << "Human " << getID() << "[name: " << name << ", age: " << age << "] is eating\n"; }*/
    /* getID(), name and age could not be used if the corresponding attribute were set on private */
    /* btw, getID() get conflicted */

    AntMan(const string & strName, int a, int pw) : Human(strName, a), Ant(2, 999) {}
    /* everything must be initialize before doing any thing */
    /* Ant, Human and AntMan is not an Animal, beware that */
    
    void eat()
    {
        cout << "Antman " << getID() << "[name: " << name << ", age: " << age << "] is eating\n";
    }
    void play()
    {
        cout << "Antman " << getID() << "[name: " << name << ", age: " << age << "] is playing\n";
    }
};