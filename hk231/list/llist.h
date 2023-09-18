#ifndef LLIST_H
#define LLIST_H

#include <assert.h>
#include "list.h"

template <typename T>
class LList : public List<T> {
private:
    template <typename U>
    class Link {
    public:
        U data;
        Link<U>* next;
        Link(): data(U()), next(nullptr) {}
        Link(const U& data, Link<U>* next): data(data), next(next) {}
    };

    Link<T>* head;
    Link<T>* tail;
    Link<T>* curr;
    int cnt;

    void init() {
        curr = head = tail = new Link<T>();
        cnt = 0;
    }
    void removeAll() {
        while (head != nullptr) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }
public:
    LList(int size = defaultSize) { init(); }
    ~LList() { removeAll(); }
    void clear() { removeAll(); init(); }

    void insert(const T& it) {
        curr->next = new Link<T>(it, curr->next);
        if (tail == curr) tail = curr->next;
        cnt++;
    }
    void append(const T& it) {
        tail->next = new Link<T>(it, nullptr);
        tail = tail->next;
        cnt++;
    }

    T remove() {
        assert(curr->next != nullptr);
        T it = curr->next->data;
        Link<T>* tmp = curr->next;
        if (tail == curr->next) tail = curr;
        curr->next = curr->next->next;

        delete tmp;
        cnt--;
        return it;
    }

    void moveToStart() { curr = head; }
    void moveToEnd() { curr = tail; }
    void prev() {
        if (curr == head) return;
        Link<T>* tmp = head;
        while (tmp->next != curr) tmp = tmp->next;
        curr = tmp;
    }
    void next() { if (curr != tail) curr = curr->next; }
    int length() const { return cnt; }
    int currentPos() const {
        Link<T>* tmp = head;
        int i;
        for (i = 0; curr != tmp; ++i) tmp = tmp->next;
        return i;
    }

    void moveToPos(int pos) {
        assert((pos >= 0) && (pos <= cnt));
        curr = head;
        for (int i = 0; i < pos; ++i) curr = curr->next;
    }
    const T& getValue() const {
        assert(curr->next != nullptr);
        return curr->next->data;
    }

    void reverse() {
        Link<T>* cur = head;
        Link<T>* tmp;
        Link<T>* newHead = new Link<T>();

        tail = cur->next;

        while (cur != nullptr) {
            tmp = cur;
            cur = cur->next;
            tmp->next = newHead->next;
            newHead->next = tmp;
        }

        head = newHead;
    }
};

#endif // LLIST_H