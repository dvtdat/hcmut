#ifndef ALIST_H
#define ALIST_H

#include <assert.h>
#include "list.h"

template <typename T>
class AList : public List<T> {
private:
    int maxSize;
    int listSize;
    int curr;
    T* listArray;

public:
    AList(int size = defaultSize) {
        maxSize = size;
        listSize = curr = 0;
        listArray = new T[maxSize];
    }
    ~AList() { delete [] listArray; }

    void clear() {
        delete [] listArray;
        listSize = curr = 0;
        listArray = new T[maxSize];
    }
    void insert(const T& item) {                    // O(n)
        assert(listSize < maxSize);
        for (int i = listSize; i > curr; --i) {
            listArray[i] = listArray[i - 1];
        }
        listArray[curr] = item;
        listSize++;
    }
    void append(const T& item) {                    // O(1)
        assert(listSize < maxSize);
        listArray[listSize++] = item;
    }
    T remove() {                                    // O(n)
        assert(curr >= 0 && curr < listSize);
        T item = listArray[curr];
        for (int i = curr; i < listSize - 1; ++i) {
            listArray[i] = listArray[i + 1];
        }
        listSize--;
        return item;
    }

    void moveToStart() { curr = 0; }                // O(1)
    void moveToEnd() { curr = listSize; }           // O(1)
    void moveToPos(int pos) {                       // O(1)
        assert((pos >= 0) && (pos <= listSize));
        curr = pos;
    }

    void prev() { if (curr) curr--; }               // O(1)
    void next() { if (listSize - curr) curr++; }    // O(1)

    int length() const { return listSize; }
    int currentPos() const { return curr; }

    const T& getValue() const {                     // O(1)
        assert((curr >= 0 && curr < listSize));
        return listArray[curr];
    }
};

#endif // ALIST_H