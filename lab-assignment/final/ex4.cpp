#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct Node 
{
    T data;
    Node* next;
    Node(T val): data(val), next(nullptr) {}
};

class Guest
{
protected:
    int ID;
    string name;
public:
    Guest(int ID, string name): ID(ID), name(name) {};
    void print()
    {   
        cout << "Guest number: " << ID << " Name: " << name << '\n';
    }
};

class Vip : public Guest
{
private:
    int level;
public:
    Vip(int ID, string name, int level): Guest(ID, name), level(level) {};
    void print()
    {   
        cout << "Vip number: " << ID << " Level: " << level << " Name: " << name << '\n';
    }
};

template<typename T>
class entranceList
{
private:
    Node<T>* head;
public:
    entranceList<T>(): head(nullptr) {}
    void add(T value)
    {
        if (head == nullptr)
        {
            head = new Node<T>(value);
            return;
        }

        Node<T>* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = new Node<T>(value);
    }

    int size()
    {
        if (head == nullptr) return 0;
        int cnt = 1;
        Node<T>* ptr = head;
        while (ptr->next) ptr = ptr->next, cnt++;
        return cnt;
    }

    void printList()
    {
        cout << "This list included " << size() << " guest(s):\n";
        Node<T>* ptr = head;
        while (ptr->next)
        {
            ptr->data.print();
            ptr = ptr->next;
        }
    }
};

void checkGuest(string name, entranceList<Guest>& GL, entranceList<Vip>& VL)
{
    
}

int main()
{
    entranceList<Guest> GL;
    entranceList<Vip> VL;

    int n; cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string input; cin >> input;
        
    }
    GL.printList();
    VL.printList();
}