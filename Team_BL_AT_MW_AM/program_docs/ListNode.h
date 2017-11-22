/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef LIST_NODE_H
#define LIST_NODE_H

/**
@class ListNode
A Node ADT which will have two attributes
- a data attribute
- pointer attribute
.
Remember the Node has to be an ADT, so that it can hold any kind of data.
You can choose to use this node as both a data and a head-pointing node
or as a simple data node in which case you will need a new head pointing node.
@param T list data type
*/
template <class T>
class ListNode
{
private:
	T value;
	ListNode<T> *next;
public:
	// CONSTRUCTORS/DESTRUCTORS
	ListNode (T nodeValue);
	~ListNode ();
	// GETTER/SETTER   
	T getValue ();
	ListNode<T>* getNext ();
	void setValue (T val);
	void setNext (ListNode<T>* nodePtr);
};

//******************************************************
// ListNode class implementation    
//******************************************************
template <class T> 
ListNode<T>::ListNode (T nodeValue) // Default Constructor     
{
	value = nodeValue;
	next = nullptr;
}

template <class T>
ListNode<T>::~ListNode () // Destructor  
{
	next = nullptr;
}

template <class T>
T ListNode<T>::getValue () { return value; }

template <class T>
ListNode<T>* ListNode<T>::getNext () { return next; }

template <class T>
void ListNode<T>::setValue (T val) { value = val; }

template <class T>
void ListNode<T>::setNext (ListNode<T>* nodePtr) { next = nodePtr; }
#endif