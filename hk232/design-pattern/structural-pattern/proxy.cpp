#include <bits/stdc++.h>

using namespace std;

// Subject Interface
class AccountInterface {
public:
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
    virtual int getBalance() = 0;
};

// Real Subject
class CashAccount : public AccountInterface {
private:
    int balance;

public:
    CashAccount() {
        balance = 0;
    }

    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        balance -= amount;
    }

    int getBalance() {
        return balance;
    }
};

// Proxy Subject
class CreditAccount : public AccountInterface {
private:
    CashAccount* cashAccount;
    int creditLimit;
    string username;
    string password;

    bool authenticate() {
        return this->username == "admin" && this->password == "admin";
    }

public:
    CreditAccount(string username, string password) {
        cashAccount = new CashAccount();
        creditLimit = 1000;
        this->username = username;
        this->password = password;
    }

    void deposit(int amount) {
        if (!authenticate()) {
            cout << "Authentication failed" << endl;
            return;
        }
        
        cashAccount->deposit(amount);
    }

    void withdraw(int amount) {
        if (!authenticate()) {
            cout << "Authentication failed" << endl;
            return;
        }

        if (amount <= cashAccount->getBalance()) {
            cashAccount->withdraw(amount);
        } else if (amount <= cashAccount->getBalance() + creditLimit) {
            cout << "Credit limit reached" << endl;
        } else {
            cout << "Insufficient funds" << endl;
        }
    }

    int getBalance() {
        if (!authenticate()) {
            cout << "Authentication failed" << endl;
            return 0;
        }

        return cashAccount->getBalance();
    }
};

class Client {
public:
    static void operation() {
        AccountInterface* account = new CreditAccount("admin", "admin");
        account->deposit(100);
        account->withdraw(50);
        cout << account->getBalance() << '\n';
        
        account->withdraw(1000);
        account->withdraw(100);
        cout << account->getBalance() << '\n';

        account->deposit(1000);
        account->withdraw(100);
        cout << account->getBalance() << '\n';
    }
};

int main() {
    Client::operation();
}
