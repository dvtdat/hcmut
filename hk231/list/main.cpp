#include <iostream>
#include <string>
#include <vector>

#include "llist.h"
#include "alist.h"

using namespace std;

int main() {
    vector<List<int>*> myVector;

    AList<int> myAList;
    LList<int> myLList;

    myVector.push_back(&myAList);
    myVector.push_back(&myLList);

    myVector[0]->append(1);
    myVector[0]->append(2);
    myVector[0]->append(3);

    myVector[1]->append(4);
    myVector[1]->append(5);
    myVector[1]->append(6);

    cout << "First List: \n";
    List<int>* L = myVector[0];
    for (L->moveToStart(); L->currentPos() < L->length(); L->next()) {
        cout << L->getValue() << ' ';
    }
    cout << '\n';

    cout << "Second List: \n";
    L = myVector[1];
    for (L->moveToStart(); L->currentPos() < L->length(); L->next()) {
        cout << L->getValue() << ' ';
    }
    cout << '\n';
}