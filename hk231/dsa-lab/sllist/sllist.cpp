#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class SLinkedList {
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    SLinkedList(const SLinkedList &list) {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin() {
        return Iterator(this, true);
    }
    Iterator end() {
        return Iterator(this, false);
    }
public:
    class Node {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index;
    public:
        Iterator() {};
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        Iterator &operator++();
        Iterator operator++(int);
        void remove();
    };
};

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin) {
    this->pList = pList;
    if (begin) {
        if (pList != nullptr && pList->head != nullptr) {
            current = pList->head;
            index = 0;
            return;
        }

        current = nullptr;
        index = -1;
        return;
    }

    if (pList != nullptr) {
        current = nullptr;
        index = pList->count;
        return;
    }

    current = nullptr;
    index = 0;
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator) {
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    if (current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (index == 0) {
        pList->head = current->next;
        index = -1;
        delete current;
        current = pList->head;
    } else {
        Node* prev = pList->head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        prev->next = current->next;
        delete current;
        current = prev;
        index--;
    }
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    if (current == nullptr) {
        throw out_of_range("Segmentation fault!");
    }
    current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    if (current == nullptr) {
        throw out_of_range("Segmentation fault!");
    }
    return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    return (current != iterator.current) || (index != iterator.index);
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    if (current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }

    current = current->next;
    index++;

    if (index == 0) {
        current = pList->head;
    } else if (current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }

    return *this;
}

template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

int main() {
    SLinkedList<int> list;

    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }

    SLinkedList<int>::Iterator it;
    int expvalue = 0;
    for(it = list.begin(); it != list.end(); it++){
        assert(*it == expvalue);
        expvalue += 1;
    }
}