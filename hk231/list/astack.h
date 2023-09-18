#ifndef ASTACK_H
#define ASTACK_H

#include <assert.h>
#include "stack.h"

template <typename E>
class AStack : public Stack<E>{
private:
    int maxSize;
    int top;
    E* listArray;
public:
    AStack(int size = defaultSize): maxSize(size), top(0), listArray(new E[size]) {}
    ~AStack() {delete [] listArray; }
    
    void clear() override { top = 0; }
    void push(const E& it) {
        assert(top != maxSize);
        listArray[top++] = it;
    }

    E pop() {
        assert(top != 0);
        return listArray[--top];
    }

    const E& topValue() const {
        assert(top != 0);
        return listArray[top - 1];
    }

    int length() const { return top; }
};


#endif // ASTACK_H