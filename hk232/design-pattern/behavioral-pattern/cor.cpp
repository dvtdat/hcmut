#include <bits/stdc++.h>

using namespace std;

class Handler {
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual string handle(string request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler* nextHandler;

public:
    AbstractHandler() : nextHandler(nullptr) {}

    Handler* setNext(Handler* handler) override {
        this->nextHandler = handler;
        return handler;
    }

    string handle(string request) override {
        if (this->nextHandler) {
            return this->nextHandler->handle(request);
        }
        return "No car maker found!";
    }
};

class FordHandler : public AbstractHandler {
public:
    string handle(string request) override {
        if (request == "Ford") {
            return "Ford Mustang GT500 is the best car in the world!";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class ToyotaHandler : public AbstractHandler {
public:
    string handle(string request) override {
        if (request == "Toyota") {
            return "Toyota Camry is the most beautiful car in the world!";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class HondaHandler : public AbstractHandler {
public:
    string handle(string request) override {
        if (request == "Honda") {
            return "Honda Civic is the perfect car!";
        } else {
            return AbstractHandler::handle(request);
        }
    }
};

class Client {
public:
    static void Operation() {
        vector<string> requests = {"Ford", "Toyota", "Honda", "BMW", "Mercedes"};
        for (auto request : requests) {
            cout << "Client: Who is the best car maker?" << endl;
            Handler* handler = new FordHandler();
            handler->setNext(new ToyotaHandler())->setNext(new HondaHandler());
            cout << "    " << handler->handle(request) << endl;
            delete handler;
        }
    }
};

int main() {
    Client::Operation();
}