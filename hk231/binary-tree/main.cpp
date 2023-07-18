#include <iostream>
#include "BST.cpp"

int main() {
    BST<int, std::string> myTree;

    // Inserting dummy data
    myTree.insert(5, "Apple");
    myTree.insert(3, "Banana");
    myTree.insert(7, "Orange");
    myTree.insert(2, "Grape");
    myTree.insert(4, "Mango");
    myTree.insert(6, "Pineapple");
    myTree.insert(8, "Strawberry");

    // Printing the BST
    myTree.print();

    // Searching for a node
    int searchKey = 4;
    std::string searchData = myTree.find(searchKey);
    if (searchData != "")
        std::cout << "Data found for key " << searchKey << ": " << searchData << std::endl;
    else
        std::cout << "Data not found for key " << searchKey << std::endl;

    // Removing a node
    int removeKey = 7;
    std::string removedData = myTree.remove(removeKey);
    if (removedData != "")
        std::cout << "Removed data for key " << removeKey << ": " << removedData << std::endl;
    else
        std::cout << "No data found for key " << removeKey << std::endl;

    std::string removeAnyData = myTree.removeAny();

    // Printing the BST after removal
    myTree.print();

    return 0;
}
