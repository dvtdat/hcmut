#include <iostream>
#include "BSTNode.h"
#include "BinaryNode.cpp"

int main() {
    // Create the nodes
    BSTNode<int, std::string>* node1 = new BSTNode<int, std::string>(5, "Node 5");
    BSTNode<int, std::string>* node2 = new BSTNode<int, std::string>(3, "Node 3");
    BSTNode<int, std::string>* node3 = new BSTNode<int, std::string>(7, "Node 7");
    BSTNode<int, std::string>* node4 = new BSTNode<int, std::string>(2, "Node 2");
    BSTNode<int, std::string>* node5 = new BSTNode<int, std::string>(4, "Node 4");
    BSTNode<int, std::string>* node6 = new BSTNode<int, std::string>(6, "Node 6");
    BSTNode<int, std::string>* node7 = new BSTNode<int, std::string>(8, "Node 8");

    // Set the children
    node1->setLeft(node2);
    node1->setRight(node3);
    node2->setLeft(node4);
    node2->setRight(node5);
    node3->setLeft(node6);
    node3->setRight(node7);



    
    std::cout << countNode(node1) << '\n';

    return 0;
}
