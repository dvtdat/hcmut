#include "linked-list.h"

int main()
{
    Node* list1 = nullptr;
    Node* list2 = nullptr;
    printList(list1);

    for (int i = 0; i < 5; ++i)
    {
        pushNode(list1, i * 10);
        pushNode(list2, i * 20);
    }

    Node* list3 = mergeListShallow(list1, list2);
    
} 