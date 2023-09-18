#include <iostream>
#include <string>
#include <vector>

#include "llist.h"
#include "alist.h"

using namespace std;

#include <unordered_map>

template <typename T>
void DuplicationKiller(List<T>& L) {
    std::unordered_map<T, int> elementCount;

    L.moveToStart();
    for (int i = 0; i < L.length(); ++i) {
        T currentElement = L.getValue();
        if (elementCount.find(currentElement) == elementCount.end()) {
            elementCount[currentElement] = 1;
        } else {
            elementCount[currentElement]++;
        }
        L.next();
    }

    L.moveToStart();
    for (L.moveToStart(); L.currPos() < L.length();) {
        T currentElement = L.getValue();
        if (elementCount[currentElement] > 1) L.remove();
        else L.next();
    }
}

template <typename T>
List<T>* merge(List<T>* in1, List<T>* in2) {
    List<T>* res = new LList<T>();

    for (in1->moveToStart(), in2->moveToStart(); in1->currentPos() < in1->length() && in2->currentPos() < in2->length();) {
        if (in1->getValue() < in2->getValue()) {
            res->append(in1->getValue());
            in1->next();
        }
        else {
            res->append(in2->getValue());
            in2->next();
        }
    }

    for (; in1->currentPos() < in1->length(); in1->next()) res->append(in1->getValue());
    for (; in2->currentPos() < in2->length(); in2->next()) res->append(in2->getValue());

    return res;
}
 
int main() {
    {
        // vector<List<int>*> myVector;

        // AList<int> myAList;
        // LList<int> myLList;

        // myVector.push_back(&myAList);
        // myVector.push_back(&myLList);

        // myVector[0]->append(1);
        // myVector[0]->append(2);
        // myVector[0]->append(3);

        // myVector[1]->append(7);
        // myVector[1]->append(3);
        // myVector[1]->append(5);

        // // cout << "First List: \n";
        // // List<int>* L = myVector[0];
        // // for (L->moveToStart(); L->currentPos() < L->length(); L->next()) {
        // //     cout << L->getValue() << ' ';
        // // }
        // // cout << '\n';

        // myLList.reverse();

        // cout << "Second List: \n";
        // List<int>* L = myVector[1];
        // for (L->moveToStart(); L->currentPos() < L->length(); L->next()) {
        //     cout << L->getValue() << ' ';
        // }
        // cout << '\n';
    }


    LList<int> list1;
    list1.append(1);
    list1.append(3);
    list1.append(5);

    LList<int> list2;
    list2.append(2);
    list2.append(4);
    list2.append(6);

    // Merge the two lists
    List<int>* mergedList = merge(&list1, &list2);

    // Print the merged list
    mergedList->moveToStart();
    for (int i = 0; i < mergedList->length(); i++) {
        std::cout << mergedList->getValue() << " ";
        mergedList->next();
    }
}