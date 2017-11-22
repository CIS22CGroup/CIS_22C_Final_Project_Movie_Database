/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include "list.h"

/**
@class BST
constructor example:\n
BST<std::string, MyDataNode> *nameBST = new BST<std::string, MyDataNode> ();
@param T The search tree data type
@param N The data node containing related data including data of type T
*/
template <class T, class N>
class BST
{

private:
	BSTNode<T, N> *root;
	void addHelper (BSTNode<T, N> *root, N* val, T (*access)(N*));
	void visitLogPostorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogInorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogPreorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogLevelHelper (BSTNode<T, N> *root, int level, std::string (*visit)(N*), std::string &log);
	int nodesCountHelper (BSTNode<T, N> *root);
	int heightHelper (BSTNode<T, N> *root);
	void MaxPathNodesHelper (BSTNode<T, N> *root, List<N*>* listPtr);
	bool removeHelper (BSTNode<T, N>* parent, BSTNode<T, N>* current, T value, T (*access)(N*));
	void findHelper (BSTNode<T, N>* current, T value, List<N*>* listPtr, T (*access)(N*), int &operations);

public:
	// CONSTRUCTORS/DESTRUCTORS
	BST ();
	BST (List<N*>* listPtr, T (*access)(N* node));
	~BST ();

	/** adds data node N to the tree
	@pre None
	@post places data node N into the tree
	@param val the data node
	@param access the data node accessor method
	@return None */
	void add (N* val, T (*access)(N*));

	/** accesses data using a post-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogPostorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a in-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogInorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a pre-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogPreorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a breadth-first traversal mechanism
	or level-order traversal
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogBreadthFirst (std::string (*visit)(N*), std::string &log);

	/** returns the nodes in the tree
	@pre root node exists
	@post None
	@return number of nodes in tree */
	int nodesCount ();

	/** returns the max height of the tree
	@pre root node exists
	@post None
	@return height of longest branch */
	int height ();

	/** inserts the data nodes of the longest branch
	into the list
	@pre root node exists
	@post None
	@param listPtr the list of result data nodes
	@return None
	*/
	void MaxPathNodes (List<N*>* listPtr);

	/** deletes the matching data node attribute
	@pre root node exists
	@post node removed from tree
	@param value the data node attribute of type T
	@param access the data node accessor method
	@return true on success, false on failure or not found */
	bool remove (T value, T (*access)(N*));

	/** inserts a list into the BST
	@pre list is not empty
	@post list nodes added to BST
	@param listPtr the list of data nodes
	@param access the data node accessor method
	@return true on success, false on failure or not found */
	bool insert (List<N*>* listPtr, T (*access)(N* node));

	/** finds the matching data node attribute
	and pushes the data node into the list
	@pre root node exists
	@post data nodes pushed into list
	@param value the data node attribute of type T
	@param listPtr the list of result data nodes
	@param access the data node accessor method
	@return true on success, false on failure or not found */
	bool find (T value, List<N*>* listPtr, T (*access)(N*));

	/** finds the matching data node attribute
	and pushes the data node into the list. exposes operations done.
	@pre root node exists
	@post data nodes pushed into list
	@param value the data node attribute of type T
	@param listPtr the list of result data nodes
	@param access the data node accessor method
	@param operations number of operations
	@return true on success, false on failure or not found */
	bool find (T value, List<N*>* listPtr, T (*access)(N*), int &operations);
};

//******************************************************
// BST class implementation    
// PRIVATE METHODS
//******************************************************

template <class T, class N>
void BST<T, N>::addHelper (BSTNode<T, N> *root, N* val, T (*access)(N*))
{
	if ((*access)(root->getValue ()) > (*access)(val))
	{
		// val less than root to the left
		if (!root->getLeft ()) root->setLeft (new BSTNode<T, N> (val));
		else addHelper (root->getLeft (), val, access);
	}
	else
	{
		// val greater or equal to root to the right
		if (!root->getRight ()) root->setRight (new BSTNode<T, N> (val));
		else addHelper (root->getRight (), val, access);
	}
}
template <class T, class N>
void BST<T, N>::visitLogPostorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogPostorderHelper (root->getLeft (), visit, log);
	visitLogPostorderHelper (root->getRight (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
}

template <class T, class N>
void BST<T, N>::visitLogInorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogInorderHelper (root->getLeft (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogInorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogPreorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogPreorderHelper (root->getLeft (), visit, log);
	visitLogPreorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogLevelHelper (BSTNode<T, N> *root, int level, std::string (*visit)(N*), std::string &log)
{
	std::stringstream ss;
	if (!root)
		return;
	if (level == 1)
	{
		ss << (*visit)(root->getValue ());
		log += ss.str ();
	}
	else if (level > 1)
	{
		visitLogLevelHelper (root->getLeft (), level - 1, visit, log);
		visitLogLevelHelper (root->getRight (), level - 1, visit, log);
	}
}

template <class T, class N>
int BST<T, N>::nodesCountHelper (BSTNode<T, N> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T, class N>
int BST<T, N>::heightHelper (BSTNode<T, N> *root)
{
	if (!root) return 0;
	// removed max() method to remove <algorithm> dependency
	else return 1 + ((heightHelper (root->getLeft ()) > heightHelper (root->getRight ())) ? heightHelper (root->getLeft ()) : heightHelper (root->getRight ()));
}

template <class T, class N>
void BST<T, N>::MaxPathNodesHelper (BSTNode<T, N> *root, List<N*>* listPtr)
{
	if (!root) return;
	listPtr->push_back (root->getValue ());
	if (heightHelper (root->getLeft ()) > heightHelper (root->getRight ()))
		MaxPathNodesHelper (root->getLeft (), listPtr);
	else
		MaxPathNodesHelper (root->getRight (), listPtr);
}
template <class T, class N>
bool BST<T, N>::removeHelper (BSTNode<T, N>* parent, BSTNode<T, N>* current, T value, T (*access)(N*))
{
	if (!current) return false;
	if ((*access)(current->getValue ()) == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			BSTNode<T, N>* temp = current->getLeft ();
			if (current->getRight ()) temp = current->getRight ();
			if (parent)
			{
				if (parent->getLeft () == current)
				{
					parent->setLeft (temp);
				}
				else
				{
					parent->setRight (temp);
				}
			}
			else
			{
				this->root = temp;
			}
		}
		else
		{
			BSTNode<T, N>* validSubs = current->getRight ();
			while (validSubs->getLeft ())
			{
				validSubs = validSubs->getLeft ();
			}
			N* temp = current->getValue ();
			current->setValue (validSubs->getValue ());
			validSubs->setValue (temp);
			return removeHelper (current, current->getRight (), (*access)(temp), access);
		}
		delete current;
		return true;
	}
	return removeHelper (current, current->getLeft (), value, access) ||
		removeHelper (current, current->getRight (), value, access);
}

template <class T, class N>
void BST<T, N>::findHelper (BSTNode<T, N>* current, T value, List<N*>* listPtr, T (*access)(N*), int &operations)
{
	/*
	searches the normal add path to find matching values
	list will be empty if no matches found assuming list was
	empty in the beginning
	*/
	if (!current) return;
	if ((*access)(current->getValue ()) == value)
		listPtr->push_back (current->getValue ());
	if ((*access)(current->getValue ()) > value)
	{
		// val less than root to the left
		operations++;
		findHelper (current->getLeft (), value, listPtr, access, operations);
	}
	else
	{
		// val greater or equal to root to the right
		operations++;
		findHelper (current->getRight (), value, listPtr, access, operations);
	}
}

//******************************************************
// BST class implementation 
// PUBLIC METHODS
//******************************************************

template <class T, class N>
BST<T, N>::BST ()
{
}

template <class T, class N>
BST<T, N>::BST (List<N*>* listPtr, T (*access)(N* node))
{
	insert (listPtr, access);
}

template <class T, class N>
BST<T, N>::~BST ()
{
}

template <class T, class N>
void BST<T, N>::add (N* val, T (*access)(N*))
{
	if (root) this->addHelper (root, val, access);
	else root = new BSTNode<T, N> (val);
}

template <class T, class N>
void BST<T, N>::visitLogPostorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPostorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogInorder (std::string (*visit)(N*), std::string &log)
{
	visitLogInorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogPreorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPreorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogBreadthFirst (std::string (*visit)(N*), std::string &log)
{
	int h = heightHelper (this->root);
	int i;
	for (i = 1; i <= h; i++)
		visitLogLevelHelper (this->root, i, visit, log);
}

template <class T, class N>
int BST<T, N>::nodesCount ()
{
	return nodesCountHelper (root);
}
template <class T, class N>
int BST<T, N>::height ()
{
	return heightHelper (this->root);
}
template <class T, class N>
void BST<T, N>::MaxPathNodes (List<N*>* listPtr)
{
	MaxPathNodesHelper (this->root, listPtr);
}

template <class T, class N>
bool BST<T, N>::remove (T value, T (*access)(N*))
{
	return this->removeHelper (NULL, this->root, value, access);
}

template <class T, class N>
bool BST<T, N>::insert (List<N*>* listPtr, T (*access)(N* node))
{
	bool flag = false;
	int n = listPtr->size ();
	for (int i = 0; i < n; i++)
	{
		add ((*listPtr)[i], access);
	}
	return flag;
}

template <class T, class N>
bool BST<T, N>::find (T value, List<N*>* listPtr, T (*access)(N*))
{
	int operations = 0;
	bool flag = false;
	this->findHelper (this->root, value, listPtr, access, operations);
	operations = 2 + operations;
	if (!listPtr->empty ()) flag = true;
	return flag;
}

template <class T, class N>
bool BST<T, N>::find (T value, List<N*>* listPtr, T (*access)(N*), int &operations)
{
	operations = 0;
	bool flag = false;
	this->findHelper (this->root, value, listPtr, access, operations);
	operations = 2 + operations;
	if (!listPtr->empty ()) flag = true;
	return flag;
}
#endif