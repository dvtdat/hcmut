#include <iostream>
#include "BST.cpp"

int main() {
    BST<int, std::string> myTree;

    // Inserting dummy data
    myTree.insert(5, "Node 5");
    myTree.insert(3, "Node 3");
    myTree.insert(7, "Node 7");
    myTree.insert(2, "Node 2");
    myTree.insert(4, "Node 4");
    myTree.insert(6, "Node 6");
    myTree.insert(8, "Node 8");
    myTree.insert(9, "Node 9");
    myTree.insert(10, "Node 10");
    myTree.insert(1, "Node 1");
    myTree.insert(12, "Node 12");
    myTree.print();

    int removeKey = 7;
    std::string removedData = myTree.remove(removeKey);
    if (removedData != "") std::cout << "Removed data for key " << removeKey << ": " << removedData << '\n';
    else std::cout << "No data found for key " << removeKey << '\n';

    myTree.print();

    return 0;
}
