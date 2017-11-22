/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef BST_NODE_H
#define BST_NODE_H

#include "list.h"

/**
@class BSTNode
Implement your BST as a link-based ADT - you may be able to reuse your Node classes from Labs 2 and 2b.
@param T The search tree data type
@param N The data node containing related data including data of type T
*/
template <class T, class N>
class BSTNode
{
private:
	N* value;
	BSTNode<T, N>* left;
	BSTNode<T, N>* right;
public:
	// CONSTRUCTORS/DESTRUCTORS
	BSTNode ();
	BSTNode (N* val);
	BSTNode (N* val, BSTNode<T, N> left, BSTNode<T, N> right);
	~BSTNode ();
	// GETTER/SETTER   
	N* getValue ();
	BSTNode<T, N>* getLeft ();
	BSTNode<T, N>* getRight ();
	void setLeft (BSTNode<T, N>* node);
	void setRight (BSTNode<T, N>* node);
	void setValue (N*);
};

//******************************************************
// BSTNode CONSTRUCTORS/DESTRUCTORS    
//******************************************************
template <class T, class N>
BSTNode<T, N>::BSTNode ()
{
	left = nullptr;
	right = nullptr;
}

template <class T, class N>
BSTNode<T, N>::BSTNode (N* val)
{
	value = val;
	left = nullptr;
	right = nullptr;
}

template <class T, class N>
BSTNode<T, N>::BSTNode (N* val, BSTNode<T, N> leftNode, BSTNode<T, N> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T, class N>
BSTNode<T, N>::~BSTNode () {}

//******************************************************
// BSTNode GETTER/SETTER   
//******************************************************
template <class T, class N>
N* BSTNode<T, N>::getValue () { return value; }

template <class T, class N>
BSTNode<T, N>* BSTNode<T, N>::getLeft () { return left; }

template <class T, class N>
BSTNode<T, N>* BSTNode<T, N>::getRight () { return right; }

template <class T, class N>
void BSTNode<T, N>::setLeft (BSTNode<T, N>* node) { left = node; }

template <class T, class N>
void BSTNode<T, N>::setRight (BSTNode<T, N>* node) { right = node; }

template <class T, class N>
void BSTNode<T, N>::setValue (N* val) { value = val; }
#endif