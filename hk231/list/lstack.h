#ifndef LSTACK_H
#define LSTACK_H

#include <assert.h>
#include "stack.h"

template <typename E>
class LStack : public Stack<E> {
private:
    template <typename U>
    class Link {
    public:
        U data;
        Link<U>* next;
        Link(): data(U()), next(nullptr) {}
        Link(const U& data, Link<U>* next): data(data), next(next) {}
    };

    Link<E>* top;
    int size;
public:
    LStack(int sz = defaultSize): top(nullptr), size(0) {};
    ~LStack() { clear(); }

    void clear() {
        while (top != nullptr) {
            Link<E>* tmp = top;
            top = top->next;
            delete tmp;
        }
        size = 0;
    }

    void push(const E& it) {
        top = new Link<E>(it, top);
        size++;
    }

    E pop() {
        assert(top != nullptr);
        E it = top->data;
        Link<E>* tmp = top->next;

        delete top;
        top = tmp;
        size--;
        return it;
    }

    const E& topValue() const {
        assert(top != 0);
        return top->data;
    }

    int length() const { return size; }
};

#endif // LSTACK_H