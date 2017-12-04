/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef LIST_H
#define LIST_H

#include "ListNode.h"

/**
@class List
A Singly Linked List ADT which will be composed of one or more nodes.
Implement the most common linked-list behaviors as explained in class -
new list, add anywhere, delete anywhere, find anywhere,
count of items in the list, empty the list, etc.
@param T list data type
*/
template <class T>
class List
{
private:
	ListNode<T> *head;
	ListNode<T> *tail;
	unsigned int itemCount;
public:
	// CONSTRUCTORS/DESTRUCTORS
	List ();
	List (unsigned int size);
	virtual ~List ();

	/** Sees whether this list is empty.
	@return True if the list is empty; otherwise returns false.
	*/
	bool empty ();

	/** Gets the current number of entries in this list.
	@return The integer number of entries currently in the list.
	*/
	int size () const;

	/** Removes all entries from this list.
	@post List contains no entries and the count of items is 0.
	*/
	void clear ();

	/** Inserts an entry into this list at a given position.
	@pre None.
	@post If 0 <= position <= size() and the insertion is
	successful, val is at the given position in the list,
	other entries are renumbered accordingly, and the returned
	value is true.
	@param position The list position at which to insert newEntry.
	@param val The entry to insert into the list.
	@return True if insertion is successful, or false if not.
	*/
	bool insert (unsigned int position, T val);

	/** get the value of the element from front of the list
	@pre None
	@post None
	@return The front value
	*/
	T front ();

	/** get the value of the element from back of the list
	@pre None
	@post None
	@return The back value
	*/
	T back ();

	/** pushes the the given element value to the back
	@pre None
	@post the entry is added to the back position in the list
	and the returned value is true.
	@return True if push is successful, or false if not.
	*/
	bool push_back (T newEntry);

	/** Prepends the given element value to the front
	@pre None
	@post the entry is added to the front position in the list
	and the returned value is true.
	@return True if push is successful, or false if not.
	*/
	bool push_front (T newEntry);

	/** Removes the entry at the front of the list
	@pre List is non-empty or returns false
	@post the entry at the front position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@return True if removal is successful, or false if not. */
	bool pop_front ();

	/** Removes the entry at the back of the list
	@pre List is non-empty or returns false
	@post the entry at the back position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@return True if removal is successful, or false if not. */
	bool pop_back ();

	/** Removes the entry at a given position from this list.
	@pre None.
	@post If 0 <= position <= size() and the removal is successful,
	the entry at the given position in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@param position The list position of the entry to remove.
	@return True if removal is successful, or false if not. */
	bool erase (unsigned int position);

	/** Removes the entry matching val from this list.
	@pre None.
	@post If val exists and the removal is successful,
	the entry matching the val in the list is removed, other
	items are renumbered accordingly, and the returned value is true.
	@param val The value of the entry to remove.
	@return True if removal is successful, or false if not. */
	bool remove (T anEntry);

	/** Tests whether this list contains a given value
	@pre None.
	@post None
	@param val The value of the entry to find.
	@return True if list contains val, or false otherwise. */
	bool find (T val);
	bool find (T val, unsigned int &operations);

	/** Gets the entry at the given position in this list.
	@pre 0 <= position < size().
	@post The desired entry has been returned.
	@param position The list position of the desired entry.
	@return The entry at the given position. */
	T getValue (unsigned int position);

	/** Gets the tail node
	@pre None
	@post None
	@return The tail node. */
	ListNode<T>* getTail ();

	/** pushes the target stack object elements to this stack
	@pre None
	@post Queue has target's elements pushed on
	@param target Queue to push from
	@return None */
	void copy (List<T> *target);

	/** pushes the target stack object elements to this stack in reverse
	@pre None
	@post Queue has target's elements pushed on
	@param target Queue to reverse from
	@return None */
	void reverse (List<T> *target);

	template <class T>
	friend std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr);
	// subscript access non-standard.
	T operator[] (const int index);
};

//******************************************************
// List class constructors/destructors  
//******************************************************
template <class T>
List<T>::List () // Default Constructor 
{
	head = nullptr;
	tail = nullptr;
	itemCount = 0;
}

template <class T>
List<T>::List (unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		push_back (T ());
}

template <class T>
List<T>::~List () { clear (); } // Destructor 

//******************************************************
// List class implementation    
//******************************************************
template <class T>
bool List<T>::empty ()
{
	if (itemCount == 0) return true;
	return false;
}

template <class T>
int List<T>::size () const
{
	return itemCount;
}

template <class T>
void List<T>::clear ()
{
	ListNode<T> *currentNode;
	ListNode<T> *nextNode;
	if (!empty ())
	{
		currentNode = tail;
		while (currentNode)
		{
			nextNode = currentNode->getNext ();
			delete currentNode;
			currentNode = nextNode;
		}
	}
	head = nullptr;
	tail = nullptr;
	itemCount = 0;
}

template <class T>
bool List<T>::insert (unsigned int position, T val)
{
	ListNode<T> *newNode;
	ListNode<T> *currentNode;
	ListNode<T> *prevNode;
	bool returnStatus = false;
	unsigned int i;

	newNode = nullptr;
	currentNode = tail;
	prevNode = nullptr;
	// position 0 = front
	// position size = back
	// position 1 = after first element
	if (position >= 0 && position <= itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position)
			{
				newNode = new ListNode<T> (val);
				returnStatus = true;
				if (i != 0) prevNode->setNext (newNode);
				else tail = newNode;
				if (i != itemCount) newNode->setNext (currentNode);
				else head = newNode;
				itemCount++;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->getNext ();
			}
		}
	}
	return returnStatus;
}

template <class T>
T List<T>::front ()
{
	return getValue (0);
}

template <class T>
T List<T>::back ()
{
	return getValue (size () - 1);
}

template <class T>
bool List<T>::push_back (T newEntry)
{
	bool returnStatus = insert (itemCount, newEntry);
	return returnStatus;
}

template <class T>
bool List<T>::push_front (T val)
{
	bool returnStatus = insert (0, val);
	return returnStatus;
}

template <class T>
bool List<T>::pop_front ()
{
	bool returnStatus = erase (0);
	return returnStatus;
}

template <class T>
bool List<T>::pop_back ()
{
	bool returnStatus = erase (itemCount - 1);
	return returnStatus;
}

template <class T>
bool List<T>::erase (unsigned int position)
{
	ListNode<T> *currentNode;
	ListNode<T> *prevNode;
	ListNode<T> *deletedNode;
	bool returnStatus = false;
	unsigned int i;

	currentNode = tail;
	prevNode = nullptr;
	deletedNode = nullptr;

	if (position >= 0 && position < itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position)
			{
				deletedNode = currentNode;
				if (i != 0 && i != itemCount) prevNode->setNext (currentNode->getNext ());
				if (i == 0 && i == itemCount) { head = nullptr; tail = nullptr; };
				if (i == 0 && i != itemCount) tail = currentNode->getNext ();
				if (i != 0 && i == itemCount) head = prevNode->getNext ();
				currentNode->setNext (nullptr);
				delete currentNode;
				itemCount--;
			}
			else
			{
				prevNode = currentNode;
				currentNode = currentNode->getNext ();
			}
		}
	}
	return returnStatus;
}

template <class T>
bool List<T>::remove (T val)
{
	ListNode<T> *currentNode;
	ListNode<T> *prevNode;

	currentNode = tail;
	prevNode = currentNode;
	bool returnStatus = true;

	if (currentNode->getValue () == val)
	{
		currentNode = currentNode->getNext ();
		delete tail;
		tail = currentNode;
	}
	else
	{

		while (currentNode != nullptr && currentNode->getValue () != val)
		{
			prevNode = currentNode;
			currentNode = currentNode->getNext ();
		}

		if (currentNode->getValue () == val && head->getValue () == val)
		{
			prevNode->getNext () = currentNode->getNext ();
			//delete currentNode;
			//delete head;
			head = prevNode;

		}
		else if (currentNode->getValue () == val)
		{
			prevNode->getNext () = currentNode->getNext ();
			delete currentNode;
		}
	}
	if (itemCount != 0)
	{
		itemCount--;
	}
	return returnStatus;
}

template <class T>
bool List<T>::find (T val)
{
	int operations = 0;
	return find (val, operations);
}

template <class T>
bool List<T>::find (T val, unsigned int &operations)
{
	ListNode<T> *currentNode;
	currentNode = tail;
	operations += 3;
	while (currentNode)
	{
		operations++;
		if (currentNode->getValue () == val) return true;
		else currentNode = currentNode->getNext ();
	}
	return false;
}

template <class T>
T List<T>::getValue (unsigned int position)
{
	ListNode<T> *currentNode;

	unsigned int i;
	currentNode = tail;

	if (position >= 0 && position < itemCount)
	{
		for (i = 0; i <= position; i++)
		{
			if (i == position) { return currentNode->getValue (); }
			else currentNode = currentNode->getNext ();
		}
	}
	throw std::runtime_error ("Position " + std::to_string (position) + " does not exist!");
}

template <class T>
ListNode<T>* List<T>::getTail ()
{
	return tail;
}

template <class T>
void List<T>::copy (List<T> *target)
{
	unsigned int n = target->size ();
	for (unsigned int i = 0; i < n; i++) push_back (target->getValue (i));
}

template <class T>
void List<T>::reverse (List<T> *target)
{
	unsigned int n = target->size ();
	for (unsigned int i = n; i > 0; i--) push_back (target->getValue (i - 1));
}

template <class T>
T List<T>::operator[] (const int index)
{
	return getValue (index);
}
#endif