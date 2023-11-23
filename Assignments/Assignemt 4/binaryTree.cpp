#include "binaryTree.h"
#include<iostream>
using namespace std;

// Constructor
template<class elemType>
binaryTreeType<elemType>::binaryTreeType() 
{
    root = nullptr;
}

// Destructor
template<class elemType>
binaryTreeType<elemType>::~binaryTreeType() 
{
    clear(root);
}

// Check if the binary tree is empty
template<class elemType>
bool binaryTreeType<elemType>::isEmpty() const 
{
    return (root == nullptr);
}

// Perform an inorder traversal of the binary tree
template<class elemType>
void binaryTreeType<elemType>::inorderTraversal() const 
{
    inorder(root);
}

// Perform a preorder traversal of the binary tree
template<class elemType>
void binaryTreeType<elemType>::preorderTraversal() const 
{
    preorder(root);
}

// Perform a postorder traversal of the binary tree
template<class elemType>
void binaryTreeType<elemType>::postorderTraversal() const 
{
    postorder(root);
}

// Return the height of the binary tree
template<class elemType>
int binaryTreeType<elemType>::height() const 
{
    return height(root);
}

// Return the number of nodes in the binary tree
template<class elemType>
int binaryTreeType<elemType>::nodeCount() const 
{
    return nodeCount(root);
}

// Insert a node into the binary tree
template<class elemType>
void binaryTreeType<elemType>::insertNode(const elemType &item) 
{
    insert(root, item);
}

// Remove a node from the binary tree
template<class elemType>
void binaryTreeType<elemType>::deleteNode(const elemType &item) 
{
    deleteNode(root, item);
}

// Search for a node in the binary tree
template<class elemType>
bool binaryTreeType<elemType>::search(const elemType &item) const 
{
    return search(root, item);
}

// Clear the binary tree
template<class elemType>
void binaryTreeType<elemType>::clear() 
{
    clear(root);
    root = nullptr;
}

// Perform an inorder traversal (helper function)
template<class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType> *p) const 
{
    if (p != nullptr) 
    {
        inorder(p->lLink);
        std::cout << p->info << " ";
        inorder(p->rLink);
    }
}

// Perform a preorder traversal (helper function)
template<class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType> *p) const 
{
    if (p != nullptr) 
    {
        std::cout << p->info << " ";
        preorder(p->lLink);
        preorder(p->rLink);
    }
}

// Perform a postorder traversal (helper function)
template<class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType> *p) const 
{
    if (p != nullptr) 
    {
        postorder(p->lLink);
        postorder(p->rLink);
        std::cout << p->info << " ";
    }
}

// Return the height of a subtree (helper function)
template<class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType> *p) const 
{
    if (p == nullptr) 
    {

        return 0;
    } else 
    {
        int leftHeight = height(p->lLink);
        int rightHeight = height(p->rLink);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

// Return the number of nodes in a subtree (helper function)
template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType> *p) const {
    if (p == nullptr) 
    {
        return 0;
    } else 
    {
        return nodeCount(p->lLink) + nodeCount(p->rLink) + 1;
    }
}

// Insert a node into a subtree (helper function)
template<class elemType>
void binaryTreeType<elemType>::insert(nodeType<elemType>* &p, const elemType &item) 
{
    if (p == nullptr) 
    {
        p = new nodeType<elemType>;
        p->info = item;
        p->lLink = nullptr;
        p->rLink = nullptr;
    } else 
    {
        if (item < p->info) 
        {
            insert(p->lLink, item);
        } else 
        {
            insert(p->rLink, item);
        }
    }
}

// Remove a node from a subtree (helper function)
template<class elemType>
void binaryTreeType<elemType>::deleteNode(nodeType<elemType>* &p, const elemType &item) 
{
    if (p == nullptr) 
    {
        return;
    } else 
    {
        if (item < p->info) 
        {
            deleteNode(p->lLink, item);
        } else if (item > p->info) 
        {
            deleteNode(p->rLink, item);
        } else 
        {
            deleteFromTree(p);
        }
    }
}

// Search for a node in a subtree (helper function)
template<class elemType>
bool binaryTreeType<elemType>::search(nodeType<elemType> *p, const elemType &item) const 
{
    if (p == nullptr) 
    {
        return false;
    } else 
    {
        if (p->info == item) 
        {
            return true;
        } else if (item < p->info) 
        {
            return search(p->lLink, item);
        } else 
        {
            return search(p->rLink, item);
        }
    }
}

// Clear the binary tree (helper function)
template<class elemType>
void binaryTreeType<elemType>::clear(nodeType<elemType>* &p) 
{
    if (p != nullptr) 
    {
        clear(p->lLink);
        clear(p->rLink);
        delete p;
    }
}

// Delete a node from a subtree (helper function)
template<class elemType>
void binaryTreeType<elemType>::deleteFromTree(nodeType<elemType>* &p) 
{
    nodeType<elemType> *current;
    nodeType<elemType> *trailCurrent;
    nodeType<elemType> *temp;

    if (p == nullptr) 
    {
        std::cout << "Error: The node to be deleted does not exist." << std::endl;
    } else if (p->lLink == nullptr && p->rLink == nullptr) 
    {
        temp = p;
        p = nullptr;
        delete temp;
    } else if (p->lLink == nullptr) 
    {
        temp = p;
        p = temp->rLink;
        delete temp;
    } else if (p->rLink == nullptr) 
    {
        temp = p;
        p = temp->lLink;
        delete temp;
    } else 
    {
        current = p->lLink;
        trailCurrent = nullptr;

        while (current->rLink != nullptr) 
        {
            trailCurrent = current;
            current = current->rLink;
        }

        p->info = current->info;

        if (trailCurrent == nullptr) 
        {
            p->lLink = current->lLink;
        } else 
        {
            trailCurrent->rLink = current->lLink;
        }

        delete current;
    }
}
