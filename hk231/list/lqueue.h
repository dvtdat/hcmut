#ifndef LQUEUE_H
#define LQUEUE_H

#include <assert.h>
#include "queue.h"

template <typename E>
class LQueue : public Queue<E> {
private:
    template <typename U>
    class Link {
    public:
        U data;
        Link<U>* next;
        Link(): data(U()), next(nullptr) {}
        Link(const U& data, Link<U>* next): data(data), next(next) {}
    };

    Link<E>* front;
    Link<E>* rear;
    int size;
public:
    LQueue(int sz = defaultSize) {
        front = rear = new Link<E>();
        size = 0;
    }

    ~LQueue() {
        clear();
    }

    void clear() {
        while (front->next != nullptr) {
            Link<E>* temp = front->next;
            front->next = temp->next;
            delete temp;
        }
        
        rear = front;
        size = 0;
    }

    void enqueue(const E& it) {
        rear->next = new Link<E>(it, nullptr);
        rear = rear->next;
        size++;
    }

    E dequeue() {
        assert(size != 0);

        E it = front->next->data;
        Link<E>* tmp = front->next;
        front->next = tmp->next;

        if (rear == tmp) rear = front;
        delete tmp;
        size--;

        return it;
    }

    const E& frontValue() const {
        assert(size != 0);
        return front->next->data;
    }

    virtual int length() const { return size; }
};

#endif // LQUEUE_H