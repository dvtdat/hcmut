#include <bits/stdc++.h>
#include "AVLTree.cpp"

int main()
{
    AVLTree<int, std::string> myTree;

    myTree.insert(1, "Node 1");
    myTree.print();

    myTree.insert(2, "Node 2");
    myTree.print();

    myTree.insert(5, "Node 5");
    myTree.print();

    myTree.insert(4, "Node 4");
    myTree.print();

    myTree.insert(7, "Node 7");
    myTree.print();

    myTree.insert(6, "Node 6");
    myTree.print();

    myTree.insert(3, "Node 3");
    myTree.print();

    myTree.insert(8, "Node 8");
    myTree.print();

    myTree.remove(8);
    myTree.print();

    myTree.remove(1);
    myTree.print();

    return 0;
}