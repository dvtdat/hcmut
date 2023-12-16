#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();
    string toString();

public:
    class Node {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }
    public:
        Node() {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data) {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
        class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; 
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        
        Iterator &operator++();
        Iterator operator++(int);
    };
};

template <class T>
DLinkedList<T>::DLinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList() {
    
}

/*
    check head == nullptr
    else append to tail
*/
template <class T>
void DLinkedList<T>::add(const T &e) {
    Node* newNode = new Node(e);
    count++;

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    newNode->previous = tail;
    tail = newNode;
}

/*
    check for bound
    check for last index
    check for empty
    check for first index
    else
*/
template <class T>
void DLinkedList<T>::add(int index, const T &e) {
    if (index > count || index < 0) {
        throw std::out_of_range("Seg fault");
        return;
    }

    if (index == count && count != 0) {
        add(e);
        return;
    } 

    Node* newNode = new Node(e);

    if (count == 0) {
        head = tail = newNode;
        count++;
        return;
    }
    
    if (index == 0) {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        count++;
        return;
    }

    Node* tmp = head;
    for (int i = 0; i < index - 1; ++i) tmp = tmp->next;

    newNode->next = tmp->next;
    newNode->previous = tmp;
    tmp->next->previous = newNode;
    tmp->next = newNode;
    count++;
}

template <class T>
int DLinkedList<T>::size() {
    return count;
}

template <class T>
T DLinkedList<T>::get(int index) {
    Node* tmp = head;
    for (int i = 0; i < index; ++i, tmp = tmp->next);
    return tmp->data;  
}

template <class T>
void DLinkedList<T>::set(int index, const T &e) {
    Node* tmp = head;
    for (int i = 0; i < index; ++i, tmp = tmp->next);
    tmp->data = e;
}

template <class T>
bool DLinkedList<T>::empty() {
    return (count <= 0);
}

template <class T>
int DLinkedList<T>::indexOf(const T &item) {
    Node* tmp = head;
    int i;
    for (i = 0; i < count && tmp->data != item; ++i, tmp = tmp->next);
    return (count == i ? -1 : i);
}

template <class T>
bool DLinkedList<T>::contains(const T &item) {
    Node* tmp = head;
    int i;
    for (i = 0; i < count && tmp->data != item; ++i, tmp = tmp->next);
    return (count != i);
}

/*
    check for bound
    check for size 1
    check for last index
    check for first index
    else
*/
template <class T>
T DLinkedList<T>::removeAt(int index) {
    if (index >= count || index < 0) {
        return T();
    }

    if (count == 1) {
        T e = head->data;
        delete head;
        count--;
        head = tail = nullptr;
        return e;
    }

    if (index == count - 1) {
        Node* tmp = tail;
        T e = tmp->data;
        tail = tail->previous;
        tail->next = nullptr;
        tmp->next = tmp->previous = nullptr;
        delete tmp;
        count--;
        return e;
    }

    if (index == 0) {
        Node* tmp = head;
        T e = tmp->data;
        head = head->next;
        head->previous = nullptr;
        tmp->next = tmp->previous = nullptr;
        delete tmp;
        count--;
        return e;
    }

    Node* tmp = head;
    int i;
    for (i = 0; i < index; ++i, tmp = tmp->next);

    T e = tmp->data;
    tmp->next->previous = tmp->previous;
    tmp->previous->next = tmp->next;

    tmp->next = tmp->previous = nullptr;
    delete tmp;
    count--;
    return e;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item) {
    Node* tmp = head;
    int i;
    for (i = 0; i < count && tmp->data != item; ++i, tmp = tmp->next);
    if (count == i) return false;

    if (count == 1) {
        head = tail = nullptr;
        tmp->next = tmp->previous = nullptr;
        delete tmp;
        count--;
        return true;
    }

    if (tmp == head) {
        head = head->next;
        head->previous = nullptr;
        tmp->next = tmp->previous = nullptr;
        delete tmp;
        count--;
        return true;
    }

    if (tmp == tail) {
        tail = tail->previous;
        tail->next = nullptr;
        tmp->next = tmp->previous = nullptr;
        delete tmp;
        count--;
        return true;
    }
    
    tmp->previous->next = tmp->next;
    tmp->next->previous = tmp->previous;
    tmp->next = tmp->previous = nullptr;
    delete tmp;
    count--;
    return true;
}

template <class T>
void DLinkedList<T>::clear() {
    while (count) removeAt(0);
}

template <class T>
string DLinkedList<T>::toString() {
    stringstream ss;
    Node* tmp = head;
    for (; tmp != nullptr; tmp = tmp->next) {
        ss << tmp->data << ' ';
    }
    return ss.str();
}

/*
    if begin => check for pList
    else 
*/
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
    this->pList = pList;
    if (begin) {
        if (this->pList == nullptr) {
            this->current = nullptr;
            this->index = -1;
        } else {
            this->current = pList->head;
            this->index = 0;
        }
    } else {
        this->current = nullptr;
        this->index = 0;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator) {
    pList = iterator.pList;
    current = iterator.current;
    index = iterator.index;
    return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e) {
    if (current == nullptr) throw std::out_of_range("Seg fault");
    else pList->set(index, e);
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() {
    if (current == nullptr) throw std::out_of_range("Seg fault");
    else return current->data;
}

/*
    check for bound
    check for head
    else
*/
template<class T>
void DLinkedList<T>::Iterator::remove() {
    if (current == nullptr) {
        throw std::out_of_range("Seg fault");
        return;
    }

    if (current == pList->head) {
        current = nullptr;
        pList->removeAt(index);
        index = -1;
        return;
    }

    current = current->previous;
    pList->removeAt(index);
    --index;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator)  {
    return (pList != iterator.pList || current != iterator.current);
}

/*
    check for bound
    check for head
    else
*/
template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()  {
    if (current == nullptr && index == pList->size()) {
        throw std::out_of_range("Seg fault");
        return *this;
    }

    if (current == nullptr && index == -1) {
        current = pList->head;
        index = 0;
        return *this;
    }

    current = current->next;
    ++index;
    return *this;
}

/*
    create new iterator
    check for bound
    else
*/
template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)  {
    Iterator newIterator(pList, true);
    if (current == nullptr && index == pList->size()) {
        throw std::out_of_range("Seg fault");
        return *this;
    }

    newIterator = *this;
    ++*this;
    return newIterator;
}

int main() {
    DLinkedList<int> list;
    int size = 5;
    int value[] = {2, 3, 4, 5, 6};
    
    for(int idx = 0; idx < size; idx++) {
        list.add(value[idx]);
    }
    cout << list.toString() << '\n';
    list.clear();
    cout << list.toString() << '\n';
}