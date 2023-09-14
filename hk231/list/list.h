#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
private:
    void operator =(const List&) {}
    List(const List&) {}
public:
    List() {}
    virtual ~List() {}

    virtual void clear() = 0;
    virtual void insert(const T& item) = 0;
    virtual void append(const T& item) = 0;
    virtual T remove() = 0;                     // remove and return current element

    virtual void moveToStart() = 0;
    virtual void moveToEnd() = 0;
    virtual void moveToPos(int pos) = 0;

    virtual void prev() = 0;
    virtual void next() = 0;

    virtual int length() const = 0;
    virtual int currentPos() const = 0;

    virtual const T& getValue() const = 0;

    /* Those have "const": their return value is un-modifiable */

    /* Comparision of different way to have "removeVal" prototype, which remove elements and return how many have its removed:
        - int removeVal(List<T> myList, T val) = 0;
            => parameter myList is redundant, we already determine that this method only happen in this object
        - void removeVal(const T& val) = 0;
            => corrent way, if we don't want to return anything
        - int removeVal(const T& val) const = 0;
            => wrong, as the remove method may change the data of the list, therefore it couldn't be suffixed with const
        - int removeVal(const T& val) = 0;
            => corrent way and suit our needs
    */
};

#endif // LIST_H
