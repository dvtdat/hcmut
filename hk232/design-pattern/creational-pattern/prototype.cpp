#include <bits/stdc++.h>

using namespace std;

// Abstract base class for chocolate prototypes
class ChocolatePrototype {
public:
    ChocolatePrototype() {}
    virtual ~ChocolatePrototype() {}
    virtual ChocolatePrototype* clone() const = 0;
    virtual void info() const = 0;
};

// Concrete chocolate prototype
class Chocolate : public ChocolatePrototype {
private:
    string flavor;

public:
    Chocolate(const string& flavor) : flavor(flavor) {}

    ChocolatePrototype* clone() const override {
        return new Chocolate(*this);
    }

    void info() const override {
        cout << "Chocolate - Flavor: " << flavor << endl;
    }
};

// Chocolate factory that manages prototypes
class ChocolateFactory {
private:
    unordered_map<string, ChocolatePrototype*> prototypes;

public:
    void registerPrototype(const string& name, ChocolatePrototype* prototype) {
        prototypes[name] = prototype;
    }

    ChocolatePrototype* createChocolate(const string& name) {
        if (prototypes.find(name) != prototypes.end()) {
            return prototypes[name]->clone();
        }
        return nullptr;
    }
};

int main() {
    // Create a chocolate factory
    ChocolateFactory factory;

    // Register chocolate prototypes
    factory.registerPrototype("dark", new Chocolate("Bitter"));
    factory.registerPrototype("milk", new Chocolate("Sweet"));

    // Create new chocolates using the factory
    ChocolatePrototype* darkChocolate = factory.createChocolate("dark");
    ChocolatePrototype* milkChocolate = factory.createChocolate("milk");

    // Display chocolate information
    if (darkChocolate) {
        darkChocolate->info();
        delete darkChocolate;
    }

    if (milkChocolate) {
        milkChocolate->info();
        delete milkChocolate;
    }

    return 0;
}
