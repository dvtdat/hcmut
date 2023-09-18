#include <iostream>

using namespace std;

template <class T>
class ArrayList {
protected:
    T* data;        // dynamic array to store the list's items
    int capacity;   // size of the dynamic array
    int count;      // number of items stored in the array

public:
    ArrayList() {capacity = 5; count = 0; data = new T[5];}
   ~ArrayList() { delete[] data; }    
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item);
    bool    contains(T item);
    T       removeAt(int index);
    bool    removeItem(T item);
    void    ensureCapacity(int index);
};

template <class T>
void ArrayList<T>::add(T e) {
    ensureCapacity(count);
    if (count == capacity) return;
    data[count++] = e;
}

template <class T>
void ArrayList<T>::add(int index, T e) {
    if (index > count) {
        throw std::out_of_range("the input index is out of range!");
    }

    ensureCapacity(count);

    if (count == capacity) return;
    count++;
    
    for (int i = count; i > index; --i) data[i] = data[i - 1];
    data[index] = e;
}

template <class T>
int ArrayList<T>::size() {
    return count;
}

template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if (cap == capacity) {
        int nCap = (int)(1.5 * cap);
        T* tmp = new T[nCap];
        for (int i = 0; i < count; ++i) tmp[i] = data[i];
        capacity = nCap;
    } else return;
}

template <class T>
bool ArrayList<T>::empty() {
}

template <class T>
void ArrayList<T>::clear() {
    delete data;
    capacity = 5; count = 0; data = new T[5];
}

template <class T>
T ArrayList<T>::get(int index) {

}

template <class T>
void ArrayList<T>::set(int index, T e) {

}

template <class T>
int ArrayList<T>::indexOf(T item) {

}

template <class T>
bool ArrayList<T>::contains(T item) {

}

template <class T>
T ArrayList<T>::removeAt(int index) {
    if (index > count) {
        throw std::out_of_range("the input index is out of range!");
    }

    for (int i = index; i < count - 1; ++i) {
        data[i] = data[i + 1];
    }
    count--;
}

template <class T>
bool ArrayList<T>::removeItem(T item) {
    for (int i = 0; i < count; ++i) {
        if (data[i] == item) {
            removeAt(i);
            return true;
        }
    }
    return false;
}

int main() {
    ArrayList<int> arr;

    for (int i = 0; i < 10; ++i) {
        arr.add(i);
    }
    arr.removeItem(9);
    cout << arr.size();
}