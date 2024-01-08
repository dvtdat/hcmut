#include <iostream>
#include <vector>

using namespace std;

// Product interface
class Chocolate {
public:
    virtual ~Chocolate() {}
    virtual void produce() const = 0;
};

// Concrete products
class DarkChocolate : public Chocolate {
public:
    void produce() const override {
        cout << "Producing Dark Chocolate." << endl;
    }
};

class MilkChocolate : public Chocolate {
public:
    void produce() const override {
        cout << "Producing Milk Chocolate." << endl;
    }
};

// Creator interface
class ChocolateFactory {
public:
    virtual ~ChocolateFactory() {}
    virtual Chocolate* createChocolate() const = 0;
};

// Concrete creators
class DarkChocolateFactory : public ChocolateFactory {
public:
    Chocolate* createChocolate() const override {
        return new DarkChocolate();
    }
};

class MilkChocolateFactory : public ChocolateFactory {
public:
    Chocolate* createChocolate() const override {
        return new MilkChocolate();
    }
};

// Client class
class Client {
private:
    const ChocolateFactory& factory;
    
public:
    Client(const ChocolateFactory& factory) : factory(factory) {}

    void orderChocolate() const {
        Chocolate* chocolate = factory.createChocolate();
        chocolate->produce();
        delete chocolate;
    }
};

int main() {
    // Create factories
    DarkChocolateFactory darkFactory;
    MilkChocolateFactory milkFactory;

    // Create clients
    Client client1(darkFactory);
    Client client2(milkFactory);

    // Order chocolates
    cout << "Client 1 orders chocolate:" << endl;
    client1.orderChocolate();
    cout << endl;

    cout << "Client 2 orders chocolate:" << endl;
    client2.orderChocolate();
    cout << endl;

    return 0;
}
