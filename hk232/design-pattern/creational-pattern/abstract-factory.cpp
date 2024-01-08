#include <iostream>
#include <string>

using namespace std;

// Abstract Product A
class Chocolate {
public:
    virtual string GetName() const = 0;
    virtual string GetTaste() const = 0;
};

// Concrete Product A - Dark Chocolate
class DarkChocolate : public Chocolate {
public:
    string GetName() const override {
        return "Dark Chocolate";
    }

    string GetTaste() const override {
        return "Bitter";
    }
};

// Concrete Product A - Milk Chocolate
class MilkChocolate : public Chocolate {
public:
    string GetName() const override {
        return "Milk Chocolate";
    }

    string GetTaste() const override {
        return "Sweet";
    }
};

// Abstract Product B
class Packaging {
public:
    virtual string GetMaterial() const = 0;
    virtual string GetColor() const = 0;
};

// Concrete Product B - Paper Packaging
class PaperPackaging : public Packaging {
public:
    string GetMaterial() const override {
        return "Paper";
    }

    string GetColor() const override {
        return "Brown";
    }
};

// Concrete Product B - Plastic Packaging
class PlasticPackaging : public Packaging {
public:
    string GetMaterial() const override {
        return "Plastic";
    }

    string GetColor() const override {
        return "Transparent";
    }
};

// Abstract Factory
class ChocolateFactory {
public:
    virtual Chocolate* CreateChocolate() const = 0;
    virtual Packaging* CreatePackaging() const = 0;
};

// Concrete Factory 1 - Dark Chocolate Factory
class DarkChocolateFactory : public ChocolateFactory {
public:
    Chocolate* CreateChocolate() const override {
        return new DarkChocolate();
    }

    Packaging* CreatePackaging() const override {
        return new PaperPackaging();
    }
};

// Concrete Factory 2 - Milk Chocolate Factory
class MilkChocolateFactory : public ChocolateFactory {
public:
    Chocolate* CreateChocolate() const override {
        return new MilkChocolate();
    }

    Packaging* CreatePackaging() const override {
        return new PlasticPackaging();
    }
};

// Client Code
void ClientCode(const ChocolateFactory& factory) {
    Chocolate* chocolate = factory.CreateChocolate();
    Packaging* packaging = factory.CreatePackaging();

    cout << "Chocolate: " << chocolate->GetName() << ", Taste: " << chocolate->GetTaste() << endl;
    cout << "Packaging: " << packaging->GetMaterial() << ", Color: " << packaging->GetColor() << endl;

    delete chocolate;
    delete packaging;
}

int main() {
    cout << "Client: Testing client code with the Dark Chocolate factory:\n";
    DarkChocolateFactory* darkFactory = new DarkChocolateFactory();
    ClientCode(*darkFactory);
    delete darkFactory;
    cout << endl;

    cout << "Client: Testing client code with the Milk Chocolate factory:\n";
    MilkChocolateFactory* milkFactory = new MilkChocolateFactory();
    ClientCode(*milkFactory);
    delete milkFactory;
    cout << endl;

    return 0;
}
