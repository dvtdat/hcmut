#include <bits/stdc++.h>

using namespace std;

class Delivery {
public:
    virtual ~Delivery() = default;
    virtual int calculateCost() = 0;
    virtual void add(Delivery* delivery) {}
    virtual void remove(Delivery* delivery) {}
    virtual bool isComposite() = 0;
};

class Item : public Delivery {
private:
    int weight;
    int cost;

public:
    Item() : weight(0), cost(0) {}
    Item(int weight, int cost) : weight(weight), cost(cost) {}
    
    int calculateCost() override {
        return cost;
    }

    bool isComposite() override {
        return false;
    }
};

class Receipt : public Item {
private:
    string manufacturer;
    string date;

public:
    Receipt() : Item() {}
    Receipt(string manufacturer, string date) : Item(), manufacturer(manufacturer), date(date) {}

    int calculateCost() {
        return Item::calculateCost();
    }

    void print() {
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Date: " << date << endl;
    }
};

class Box : public Delivery {
private:
    vector<Delivery*> items;

public:
    Box() {}
    
    Box(vector<Delivery*> items, string manufacturer, string date) : items(items) {
        items.push_back(new Receipt(manufacturer, date));
    }
    
    int calculateCost() override {
        int totalCost = 0;
        for (auto item : items) {
            totalCost += item->calculateCost();
        }
        return totalCost;
    }

    bool isComposite() override {
        return true;
    }

    void add(Delivery* delivery) override {
        items.push_back(delivery);
    }

    void remove(Delivery* delivery) override {
        items.erase(find(items.begin(), items.end(), delivery));
    }
};

class Client {
public:
    static void printCost(Delivery* delivery) {
        cout << "Total cost: " << delivery->calculateCost() << endl;
    }

    static void printReceipt(Delivery* delivery) {
        if (delivery->isComposite()) {
            dynamic_cast<Box*>(delivery)->add(new Receipt());
        }
    }
};

int main() {
    vector<Delivery*> greenItems;
    for (int i = 1; i <= 10; ++i) {
        greenItems.push_back(new Item(i, i * 10));
    }
    Box* greenBox = new Box(greenItems, "Green Manufacturer", "2020-01-01");

    vector<Delivery*> redItems;
    for (int i = 1; i <= 10; ++i) {
        redItems.push_back(new Item(i, i * 20));
    }
    Box* redBox = new Box(redItems, "Red Manufacturer", "2022-02-01");

    vector<Delivery*> blueItems;
    for (int i = 1; i <= 10; ++i) {
        blueItems.push_back(new Item(i, i * 30));
    }
    Box* blueBox = new Box(blueItems, "Blue Manufacturer", "2023-03-01");

    vector<Delivery*> boxes;
    boxes.push_back(greenBox);
    boxes.push_back(redBox);
    boxes.push_back(blueBox);
    boxes.push_back(new Item(100, 1000));

    Box* bigBox = new Box(boxes, "Manufacturer", "2023-03-01");

    Client::printCost(bigBox);

    bigBox->remove(greenBox);

    Client::printCost(bigBox);
}