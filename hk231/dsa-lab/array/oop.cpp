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

int main() {
    ArrayList<int> arr;
    int size = 20;

    for(int index = 0; index < size; index++){
        arr.add(0, index);
    }

    cout << arr.size() << '\n';
    arr.ensureCapacity(5);
}