#include <bits/stdc++.h>

using namespace std;

class Command {
public:
    virtual void execute() = 0;
    virtual int getTableNumber() = 0;
    virtual string getName() = 0;
};

// Receiver
class Kitchen {
private:
    vector<Command*> commands;

public:
    void addCommand(Command* command) {
        commands.push_back(command);
    }

    void printAllCommand() {
        cout << "All current commands: " << endl;
        for (int i = 0; i < commands.size(); i++) {
            cout << "Request " << commands[i]->getName() << " at table: " << commands[i]->getTableNumber() << endl;
        }
    }

    void removeCommandByTableNumber(int tableNumber) {
        for (int i = 0; i < commands.size(); i++) {
            if (commands[i]->getTableNumber() == tableNumber) {
                commands.erase(commands.begin() + i);
            }
        }
    }

    void prepareFirstCommand() {
        cout << "Prepare     " << commands[0]->getName() << " for table: " << commands[0]->getTableNumber() << endl;
        commands.erase(commands.begin());
    }
};

class OrderFoodCommand : public Command {
private:
    Kitchen* kitchen;
    string foodName;
    int tableNumber;
    int quantity;

public:
    OrderFoodCommand(Kitchen* kitchen): kitchen(kitchen) {}
    OrderFoodCommand(Kitchen* kitchen, string foodName, int tableNumber, int quantity): kitchen(kitchen), foodName(foodName), tableNumber(tableNumber), quantity(quantity) {}

    void execute() {
        kitchen->addCommand(this);
    }

    int getTableNumber() {
        return tableNumber;
    }

    string getName() {
        return foodName;
    }
};

class OrderDrinkCommand : public Command {
private:
    Kitchen* kitchen;
    string drinkName;
    int tableNumber;
    int size;
    int quantity;

public:
    OrderDrinkCommand(Kitchen* kitchen): kitchen(kitchen) {}
    OrderDrinkCommand(Kitchen* kitchen, string drinkName, int tableNumber, int size, int quantity): kitchen(kitchen), drinkName(drinkName), tableNumber(tableNumber), size(size), quantity(quantity) {}

    void execute() {
        kitchen->addCommand(this);
    }

    int getTableNumber() {
        return tableNumber;
    }

    string getName() {
        return drinkName;
    }
};

class CancelAllOrderCommand : public Command {
private:
    Kitchen* kitchen;
    int tableNumber;

public:
    CancelAllOrderCommand(Kitchen* kitchen): kitchen(kitchen) {}
    CancelAllOrderCommand(Kitchen* kitchen, int tableNumber): kitchen(kitchen), tableNumber(tableNumber) {
        kitchen->removeCommandByTableNumber(tableNumber);
    }

    void execute() {
        kitchen->removeCommandByTableNumber(tableNumber);
    }

    int getTableNumber() {
        return tableNumber;
    }

    string getName() {
        return "";
    }
};

// Invoker
class Waiter {
private:
    Kitchen* kitchen;

public:
    Waiter() = default;
    Waiter(Kitchen* kitchen): kitchen(kitchen) {}

    void addCommand(Command* command) {
        command->execute();
    }
};


class Client {
public:
    static void Operation() {
        Kitchen* kitchen = new Kitchen();
        Waiter* waiter = new Waiter();

        waiter->addCommand(new OrderFoodCommand(kitchen, "Pizza", 1, 2));
        waiter->addCommand(new OrderDrinkCommand(kitchen, "Coke", 1, 1, 2));
        waiter->addCommand(new OrderFoodCommand(kitchen, "Burger", 2, 1));
        waiter->addCommand(new OrderDrinkCommand(kitchen, "Pepsi", 2, 1, 1));
        kitchen->printAllCommand();
        cout << "\n";

        cout << "Cancel all order at table 1" << endl;
        waiter->addCommand(new CancelAllOrderCommand(kitchen, 1));
        kitchen->printAllCommand();
        cout << "\n";

        cout << "Prepare first order" << endl;
        kitchen->prepareFirstCommand();
        cout << "\n";
    }
};

int main() {
    Client::Operation();
}