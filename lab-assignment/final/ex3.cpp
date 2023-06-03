#include<iostream>

using namespace std;

struct Node 
{
    int data;
    Node* next;
    Node(int val = 0): data(val), next(nullptr) {}
};

class SLinkedList 
{
private:
    Node* head;
public:
    SLinkedList(): head(nullptr) {}
    
    SLinkedList operator+(const SLinkedList& lList) 
    {
        Node* tail = head;
        while (tail->next) tail = tail->next;
        tail->next = lList.head;
        return *this;
    }
    
    SLinkedList* mergeNode(int start, int end) 
    {
        if (start > end) return nullptr;
        if (start == end) return this;

        int cnt = 0;
        Node* first = head;
        while (cnt != start)
        {
            first = first->next;
            cnt++;
        }

        cnt = 0;
        Node* last = first->next;
        while (cnt + start != end)
        {
            first->data += last->data;
            cnt++;
            Node* tmp = last;
            last = last->next;
            delete tmp;
        }
        
        first->next = last->next;
        return this;
    }

    Node* operator[](const int index)
    {
        Node* temp = this -> head;
        for (int i = 0; i < index; i++)
        {
            if(temp == nullptr) return nullptr;
            temp = temp->next;
        }
        return temp;
    }
    
    void insert(int val)
    {
        Node* newNode = new Node(val);
        if (this->head == nullptr)
        {
            this->head = newNode;
        }
        else 
        {
            Node* temp = this->head;
            while(temp -> next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() 
    {
        Node* temp = this->head;
        while(temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{
    SLinkedList lList;
    lList.insert(0);
    lList.insert(5);
    lList.insert(7);
    lList.insert(11);

    SLinkedList lList2;
    lList2.insert(3);
    lList2.insert(6);
    lList2.insert(8);
    lList2.insert(9);

    lList = lList + lList2;
    lList.display();

    SLinkedList* newList = lList.mergeNode(1,2);
    newList -> display();
}