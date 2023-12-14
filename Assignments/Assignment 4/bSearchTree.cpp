#include "bSearchTree.h"
#include<iostream>
using namespace std;

// Implementation of member functions for bSearchTreeType

template<class elemType>
bool bSearchTreeType<elemType>::searchHelper(nodeType<elemType> *p, const elemType &searchItem) const 
{
    if (p == nullptr) 
    {
        return false;
    }

    if (p->info == searchItem) 
    {
        return true;
    } else if (searchItem < p->info) 
    {
        return searchHelper(p->lLink, searchItem);
    } else 
    {
        return searchHelper(p->rLink, searchItem);
    }
}


template<class elemType>
bool bSearchTreeType<elemType>::search(const elemType &searchItem) const 
{
    return searchHelper(this->root, searchItem);
}

template<class elemType>
void bSearchTreeType<elemType>::insert(const elemType &insertItem) 
{
    insertHelper(this->root, insertItem);
}

template<class elemType>
void insertHelper(nodeType<elemType> *&p, const elemType &insertItem) 
{
    if (p == nullptr) 
    {
        p = new nodeType<elemType>;
        p->info = insertItem;
        p->lLink = nullptr;
        p->rLink = nullptr;
    } else if (insertItem < p->info) 
    {
        insertHelper(p->lLink, insertItem);
    } else 
    {
        insertHelper(p->rLink, insertItem);
    }
}

template<class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType &deleteItem) 
{
    deleteHelper(this->root, deleteItem);
}

template<class elemType>
void bSearchTreeType<elemType>::deleteNode(nodeType<elemType>* &p) 
{
    if (p == nullptr) {
        cout << "Error: Node to be deleted is nullptr." << endl;
        return;
    } else if (p->rLink == nullptr) 
    {
        nodeType<elemType> *temp = p;
        p = p->lLink;
        delete temp;
    } else if (p->lLink == nullptr) 
    {
        nodeType<elemType> *temp = p;
        p = p->rLink;
        delete temp;
    } else 
    {
        deleteNodeWithTwoChildren(p);
    }
}

template<class elemType>
void bSearchTreeType<elemType>::deleteNodeWithTwoChildren(nodeType<elemType>* &p) 
{
    nodeType<elemType> *temp = p->lLink;
    nodeType<elemType> *parent = p;

    while (temp->rLink != nullptr) 
    {
        parent = temp;
        temp = temp->rLink;
    }

    p->info = temp->i
    {
        parent->lLink = temp->lLink;
    } else 
    {
        parent->rLink = temp->lLink;
    }

    delete temp;
}


template<class elemType>
void getPredecessor(nodeType<elemType> *p, nodeType<elemType> *&predecessor) 
{
    while (p->rLink != nullptr) 
    {
        p = p->rLink;
    }
    predecessor = p;
}

template<class elemType>
void bSearchTreeType<elemType>::deleteHelper(nodeType<elemType> *&p, const elemType &deleteItem) 
{
    if (p == nullptr) 
    {
        cout << "Item to be deleted is not in the tree." << endl;
    } else if (deleteItem < p->info) 
    {
        deleteHelper(p->lLink, deleteItem);
    } else if (deleteItem > p->info) 
    {
        deleteHelper(p->rLink, deleteItem);
    } else 
    {
        deleteNode(p);
    }
}

template class bSearchTreeType<int>;
