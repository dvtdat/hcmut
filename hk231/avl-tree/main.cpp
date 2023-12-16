#include <bits/stdc++.h>
#include "AVLTree.cpp"

int main()
{
    AVLTree<int, std::string> myTree;

    myTree.insert(20, "Node");
    myTree.insert(10, "Node");
    myTree.insert(40, "Node");
    myTree.insert(5, "Node");
    myTree.insert(7, "Node");
    myTree.insert(42, "Node");
    myTree.insert(2, "Node");
    myTree.print();

    myTree.remove(20);
    myTree.print();

    return 0;
}