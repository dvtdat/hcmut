#include "linked-list.h"

int main()
{
    Node* list1 = nullptr;
    Node* list2 = nullptr;

    for (int i = 1; i < 3; ++i)
    {
        pushNode(list1, i * 10);
        pushNode(list2, i * 20);
    }

    Node* list3 = mergeListShallow(list1, list2);
    removeLastNode(list1);
    removeLastNode(list1);
    removeLastNode(list1);
    removeLastNode(list1);
    printList(list1);
} 