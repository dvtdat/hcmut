#include <iostream>
#include <string>

#include "alist.h"

int main() {
    AList<int> myList(10);

    myList.insert(11);
    myList.insert(12);
    myList.insert(13);
    myList.insert(14);
    myList.insert(15);

    std::cout << "Current position of the index pointer: " << myList.currentPos() << '\n' << '\n';
    std::cout << "Current lenght of the list: " << myList.length() << '\n' << '\n';

    myList.next();
    std::cout << "After moving, current value of the pointer is: " << myList.getValue() << '\n' << '\n';

    std::cout << "Printing the list: \n";

    for (myList.moveToStart(); myList.currentPos() < myList.length(); myList.next()) {
        int item = myList.getValue();
        std::cout << item << ' ';
    }
    std::cout << '\n';
}