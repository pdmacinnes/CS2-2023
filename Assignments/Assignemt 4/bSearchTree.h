#ifndef H_binarySearchTree
#define H_binarySearchTree

#include <iostream>
#include <cassert>
#include "binaryTree.h"

template<class elemType>
class bSearchTreeType : public binaryTreeType<elemType> 
{
public:
    // Function declarations without implementation in the header file
    void deleteNodeWithTwoChildren(nodeType<elemType>* &p);
    bool search(const elemType &searchItem) const;
    void insert(const elemType &insertItem);
    void deleteNode(const elemType &deleteItem);  // delete based on item value
    void deleteNode(nodeType<elemType>* &p);      // delete based on node pointer

private:
    bool searchHelper(nodeType<elemType> *p, const elemType &searchItem) const;
    void deleteHelper(nodeType<elemType> *&p, const elemType &deleteItem);
    void getPredecessor(nodeType<elemType> *p, nodeType<elemType> *&predecessor);
};

#endif
