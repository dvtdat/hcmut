#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() {
      this->head = nullptr;
      this->tail = nullptr;
      this->count = 0;
    }

    ~SLinkedList(){};

    void add(T e) {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }

    int size() {
        return this->count;
    }

    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort() {
    int n = size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        Node* tmp = head;
        bool isSwap = false;

        for (int j = 0; j < n - 1; ++j) {
            Node* ptr1 = tmp;
            Node* ptr2 = tmp->next;
            if (ptr1->data > ptr2->data) {
                swap(ptr1->data, ptr2->data);
                isSwap = true;
            }
            tmp = tmp->next;
        }

        if (isSwap) printList();
    }
}

int main() {
    int arr[] = {10, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    SLinkedList<int> list;
    for(int i = 0; i <int(sizeof(arr))/4;i++)
        list.add(arr[i]);
    list.bubbleSort();
    list.printList();
}