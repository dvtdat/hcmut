#include <bits/stdc++.h>

using namespace std;

class PrinterQueue
{
private:
    struct Node {
        string filename;
        int priority;
        Node* next;
        Node(): next(nullptr) {}
        Node(string name, int p): filename(name), priority(p), next(nullptr) {}
    };
    
    Node* front;
    
    void pop() {
        if (!front) return;
        Node* tmp = front;
        front = front->next;
        delete tmp;
    }
    
public:
    PrinterQueue(): front(nullptr) {}
    void addNewRequest(int priority, string filename)
    {
        Node* newNode = new Node(filename, priority);
        if (front == nullptr || priority > front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* tmp = front;
            while (tmp->next != nullptr && priority <= tmp->next->priority) {
                tmp = tmp->next;
            }
            
            newNode->next = tmp->next;
            tmp->next = newNode;
        }
    }

    void print()
    {
        if (!front) {
            cout << "No file to print\n";
            return;
        }
        
        cout << front->filename << '\n';
        pop();
    }
};

int main() {
    PrinterQueue* myPrinterQueue = new PrinterQueue();
    myPrinterQueue->addNewRequest(1, "hello.pdf");
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();
}