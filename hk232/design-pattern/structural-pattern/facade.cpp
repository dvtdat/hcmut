#include <bits/stdc++.h>

using namespace std;

class OrderService {
private:
    string orderID;
    int amount;

public:
    void createOrder(const string& productId, int quantity) {
        cout << "Order created" << endl;
        orderID = productId;
        amount = quantity;
    }

    void updateAmount(int quantity) {
        cout << "Amount updated" << endl;
        amount = quantity;
    }

    string getOrderID() {
        return orderID;
    }

    int getAmount() {
        return amount;
    }
};

class PaymentService {
private:
    string paymentID;
    int totalCost;

public:
    void makePayment(const string& orderID, int amount) {
        cout << "Payment made" << endl;
        paymentID = orderID;
        totalCost = amount;
    }

    void updateTotalCost(int amount) {
        cout << "Total cost updated" << endl;
        totalCost = amount;
    }

    string getPaymentID() {
        return paymentID;
    }

    int getTotalCost() {
        return totalCost;
    }
};

class DeliveryService {
private:
    string deliveryID;
    string address;

public:
    void shipOrder(const string& orderID, const string& address) {
        cout << "Order shipped" << endl;
        deliveryID = orderID;
        this->address = address;
    }

    void updateAddress(const string& address) {
        cout << "Address updated" << endl;
        this->address = address;
    }

    string getDeliveryID() {
        return deliveryID;
    }

    string getAddress() {
        return address;
    }
};

class CustomerService {
private:
    string customerID;
    string name;

public:
    void addCustomer(const string& customerID, const string& name) {
        cout << "Customer added" << endl;
        this->customerID = customerID;
        this->name = name;
    }

    void updateName(const string& name) {
        cout << "Name updated" << endl;
        this->name = name;
    }

    string getCustomerID() {
        return customerID;
    }

    string getName() {
        return name;
    }
};

class Facade {
private:
    OrderService orderService;
    PaymentService paymentService;
    DeliveryService deliveryService;
    CustomerService customerService;

public:
    void placeOrder(const string& productId, int quantity, const string& address, const string& name) {
        orderService.createOrder(productId, quantity);
        paymentService.makePayment(orderService.getOrderID(), orderService.getAmount());
        deliveryService.shipOrder(orderService.getOrderID(), address);
        customerService.addCustomer(orderService.getOrderID(), name);
    }

    void cancelOrder(const string& orderID) {
        cout << "Order cancelled" << endl;
    }

    void updateOrder(const string& orderID, int quantity, const string& address, const string& name) {
        orderService.updateAmount(quantity);
        paymentService.updateTotalCost(orderService.getAmount());
        deliveryService.updateAddress(address);
        customerService.updateName(name);
        cout << "Order updated" << endl;
    }

    void printOrder() {
        cout << "Order ID: " << orderService.getOrderID() << endl;
        cout << "Amount: " << orderService.getAmount() << endl;
        cout << "Total cost: " << paymentService.getTotalCost() << endl;
        cout << "Address: " << deliveryService.getAddress() << endl;
        cout << "Customer ID: " << customerService.getCustomerID() << endl;
        cout << "Name: " << customerService.getName() << endl;
    }
};

class Client {
public:
    static void placeOrder() {
        Facade facade;
        facade.placeOrder("123", 10, "123 Street", "John");
        facade.printOrder();
        cout << endl;

        facade.updateOrder("123", 20, "456 Street", "John");
        facade.printOrder();
    }
};

int main() {
    Client::placeOrder();
    return 0;
}
