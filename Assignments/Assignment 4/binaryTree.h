#ifndef H_binaryTree
#define H_binaryTree

#include <iostream>
#include <cassert>

template <class elemType>
struct nodeType {
    elemType info;
    nodeType<elemType> *lLink;
    nodeType<elemType> *rLink;
};

template <class elemType>
class binaryTreeType {
public:
    // Constructor
    binaryTreeType();

    // Destructor
    ~binaryTreeType();

    // Function to check if the binary tree is empty
    bool isEmpty() const;

    // Function to perform an inorder traversal of the binary tree
    void inorderTraversal() const;

    // Function to perform a preorder traversal of the binary tree
    void preorderTraversal() const;

    // Function to perform a postorder traversal of the binary tree
    void postorderTraversal() const;

    // Function to return the height of the binary tree
    int height() const;

    // Function to return the number of nodes in the binary tree
    int nodeCount() const;

    // Function to insert a node into the binary tree
    void insertNode(const elemType &item);

    // Function to remove a node from the binary tree
    void deleteNode(const elemType &item);

    // Function to search for a node in the binary tree
    bool search(const elemType &item) const;

    // Function to clear the binary tree
    void clear();

protected:
    // Pointer to the root of the binary tree
    nodeType<elemType> *root;

    // Function to perform an inorder traversal (helper function)
    void inorder(nodeType<elemType> *p) const;

    // Function to perform a preorder traversal (helper function)
    void preorder(nodeType<elemType> *p) const;

    // Function to perform a postorder traversal (helper function)
    void postorder(nodeType<elemType> *p) const;

    // Function to return the height of a subtree (helper function)
    int height(nodeType<elemType> *p) const;

    // Function to count the nodes in a subtree (helper function)
    int nodeCount(nodeType<elemType> *p) const;

    // Function to delete a node from a subtree (helper function)
    void deleteFromTree(nodeType<elemType>* &p);

    // Function to find the minimum node in a subtree (helper function)
    nodeType<elemType>* minNode(nodeType<elemType>* p);
};

#include "binaryTree.cpp" // Include implementations

#endif
