/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef BST_H
#define BST_H

#include <sstream>
#include <iomanip>
#include <functional>
#include "BSTNode.h"
#include "list.h"
#include "MathHelper.h"

/**
@class BST
constructor example:\n
BST<std::string, MyDataNode> *nameBST = new BST<std::string, MyDataNode>;
@param T The search tree data type
@param N The data node containing related data including data of type T
*/
template <class T, class N>
class BST
{

private:
	BSTNode<T, N> *root;
	int heightCount;

	// Private Methods
	BSTNode<T, N>* addHelper (BSTNode<T, N> *root, N* val, std::function<T (N*)>* access);
	void visitLogPostorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogInorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogPreorderHelper (BSTNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogLevelHelper (BSTNode<T, N> *root, int level, std::string (*visit)(N*), std::string &log);
	void levelHelper (BSTNode<T, N> *currentNode, List<BSTNode<T, N>*>** levelNodePtr, int level, int levelMax);
	int nodesCountHelper (BSTNode<T, N> *root);
	int heightHelper (BSTNode<T, N> *root);
	unsigned int widthHelper (List<BSTNode<T, N>*>** levelNodePtrArr, unsigned int levelMax);
	unsigned int widthHelper (List<BSTNode<T, N>*>* levelNodeListPtr);
	void MaxPathNodesHelper (BSTNode<T, N> *root, List<N*>* listPtr);
	bool removeHelper (BSTNode<T, N>* parent, BSTNode<T, N>* current, T value, std::function<T (N*)>* access);
	void findHelper (BSTNode<T, N>* current, T value, List<N*>* listPtr, std::function<T (N*)>* access, int &operations);

	// AVL (By Ahn)
	void makeEmpty (BSTNode<T, N>* t);
	BSTNode<T, N>* addAVLHelper (N* x, BSTNode<T, N>* t, std::function<T (N*)>* access);
	BSTNode<T, N>* singleRightRotate (BSTNode<T, N>* t);
	BSTNode<T, N>* singleLeftRotate (BSTNode<T, N>* t);
	BSTNode<T, N>* doubleLeftRotate (BSTNode<T, N>* t);
	BSTNode<T, N>* doubleRightRotate (BSTNode<T, N>* t);
	BSTNode<T, N>* findMin (BSTNode<T, N>* t);
	BSTNode<T, N>* findMax (BSTNode<T, N>* t);
	BSTNode<T, N>* removeAVLHelper (N* x, BSTNode<T, N>* t, std::function<T (N*)>* access);
	//int heightAVLHelper(BSTNode<T, N>* t);
	int getBalance (BSTNode<T, N>* t);
	void setHeight (int num);
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
	void add (N* val, std::function<T (N*)>* access);

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

	void logLevel (std::function<std::string (N*)>* visit, std::string &log);

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
	bool remove (T val, T (*access)(N*));
	bool remove (T val, std::function<T (N*)>* access);
	bool remove (N* val, T (*access)(N*));
	bool remove (N* val, std::function<T (N*)>* access);

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
	bool find (T value, List<N*>* listPtr, std::function<T (N*)>* access, int &operations);
};

//******************************************************
// BST class implementation    
// PRIVATE METHODS
//******************************************************

template <class T, class N>
BSTNode<T, N>* BST<T, N>::addHelper (BSTNode<T, N> *currentNode, N* val, std::function<T (N*)>* access)
{
	//***PRINTING OUT
	if (currentNode == nullptr)
	{
		currentNode = new BSTNode<T, N>;
		currentNode->setValue(val);
		currentNode->setHeight(0);
		currentNode->setLeft(nullptr);
		currentNode->setRight(nullptr);
	}
	
	else if ((*access)(currentNode->getValue ()) <= (*access)(val))
	{
		// val greater or equal than root to the left
	//*	if (!currentNode->getLeft ())
		{
			//currentNode->setLeft (new BSTNode<T, N> (val));
			currentNode->setRight(addHelper(currentNode->getRight(), val, access));
			//******************************************************
			// AVL TREE (By Ahn)
			//******************************************************
			if (heightHelper (currentNode->getRight ()) - heightHelper (currentNode->getLeft ()) == 2)
			{
				if ((*access)(val) >= (*access)(currentNode->getRight ()->getValue ()))
					currentNode = singleLeftRotate (currentNode);
				else
					currentNode = doubleLeftRotate (currentNode);
			}
		}
		//else addHelper (currentNode->getLeft (), val, access);
	}
	else
	{
		// val smaller to root to the right
		//**if (!currentNode->getRight ())
		{
			//currentNode->setRight (new BSTNode<T, N> (val));
			currentNode->setLeft(addHelper(currentNode->getLeft(), val, access));
			//******************************************************
			// AVL TREE (By Ahn)
			//******************************************************
			if (heightHelper (currentNode->getLeft ()) - heightHelper (currentNode->getRight ()) == 2)
			{
				if ((*access)(val) < (*access)(currentNode->getLeft ()->getValue ()))
					currentNode = singleRightRotate (currentNode);
				else
					currentNode = doubleRightRotate (currentNode);
			}
		}
		//else addHelper (currentNode->getRight (), val, access);
	}
	setHeight (MathHelper::max (heightHelper (currentNode->getLeft ()), heightHelper (currentNode->getRight ())) + 1);
	return currentNode;
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
	int nodeWidth = 6;
	int spaceWidth = 3;
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
void BST<T, N>::levelHelper (BSTNode<T, N> *currentNode, List<BSTNode<T, N>*>** levelNodePtr, int level, int levelMax)
{
	if (level > 0 && level < levelMax)
	{
		if (currentNode)
		{
			if (currentNode->getLeft ())
			{
				levelNodePtr[level]->push_back (currentNode->getLeft ());
				levelHelper (currentNode->getLeft (), levelNodePtr, level + 1, levelMax);
			}
			else
			{
				levelNodePtr[level]->push_back (nullptr);
				levelHelper (nullptr, levelNodePtr, level + 1, levelMax);
			}
			if (currentNode->getRight ())
			{
				levelNodePtr[level]->push_back (currentNode->getRight ());
				levelHelper (currentNode->getRight (), levelNodePtr, level + 1, levelMax);
			}
			else
			{
				levelNodePtr[level]->push_back (nullptr);
				levelHelper (nullptr, levelNodePtr, level + 1, levelMax);
			}
		}
		else
		{
			levelNodePtr[level]->push_back (nullptr);
			levelNodePtr[level]->push_back (nullptr);
			levelHelper (nullptr, levelNodePtr, level + 1, levelMax);
			levelHelper (nullptr, levelNodePtr, level + 1, levelMax);
		}
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
unsigned int BST<T, N>::widthHelper (List<BSTNode<T, N>*>** levelNodePtrArr, unsigned int levelMax)
{
	unsigned int i, j, n, n1, width;
	width = 0;
	for (i = 0; i < levelMax; i++)
	{
		n1 = 0;
		n = levelNodePtrArr[i]->size ();
		for (j = 0; j < n; j++)
		{
			// only count non-null elements in list
			if ((*levelNodePtrArr[i])[j])
				n1++;
		}
		width = n1 > width ? n1 : width;
	}
	return width;
}

template <class T, class N>
unsigned int BST<T, N>::widthHelper (List<BSTNode<T, N>*>* levelNodeListPtr)
{
	unsigned int i, n, width;
	width = 0;
	n = levelNodeListPtr->size ();
	for (i = 0; i < n; i++)
	{
		// only count non-null elements in list
		if ((*levelNodeListPtr)[i])
			width++;
	}
	return width;
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
bool BST<T, N>::removeHelper (BSTNode<T, N>* parent, BSTNode<T, N>* current, T value, std::function<T (N*)>* access)
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
void BST<T, N>::findHelper (BSTNode<T, N>* current, T value, List<N*>* listPtr, std::function<T (N*)>* access, int &operations)
{
	/*
	searches the normal add path to find matching values
	list will be empty if no matches found assuming list was
	empty in the beginning
	*/
	T tmp;
	if (!current) return;
	/* sometimes the access function may try to access an index or value out of range
	the BST was probably constructed wrong or a value changed
	*/
	try
	{
		tmp = (*access)(current->getValue ());
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	if (tmp == value)
		listPtr->push_back (current->getValue ());
	if (tmp > value)
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

//************************************************************
//		AVL Private Implementation
//************************************************************
template <class T, class N>
void BST<T, N>::makeEmpty (BSTNode<T, N>* t)
{
	if (t == nullptr)
		return;
	makeEmpty (t->getLeft);
	makeEmpty (t->getRight);
	delete t;
}

template <class T, class N>
void BST<T, N>::setHeight (int num)
{
	heightCount = num;
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::addAVLHelper (N* x, BSTNode<T, N>* t, std::function<T (N*)>* access)
{
	if (t == nullptr)
	{
		t = new BSTNode<T, N>;
		t->setValue (x);
		t->setHeight(0);
		t->setLeft (nullptr);
		t->setRight (nullptr);
	}
	else if ((*access)(x) < (*access)(t->getValue ()))
	{
		t->setLeft (addAVLHelper (x, t->getLeft (), access));
		if (heightHelper (t->getLeft ()) - heightHelper (t->getRight ()) == 2)
		{
			if ((*access)(x) < (*access)(t->getLeft ()->getValue ()))
				t = singleRightRotate (t);
			else
				t = doubleRightRotate (t);
		}
	}
	else if ((*access)(x) >= (*access)(t->getValue ()))
	{
		t->setRight (addAVLHelper (x, t->getRight (), access));
		if (heightHelper (t->getRight ()) - heightHelper (t->getLeft ()) == 2)
		{
			if ((*access)(x) > (*access)(t->getRight ()->getValue ()))
				t = singleLeftRotate (t);
			else
				t = doubleLeftRotate (t);
		}
	}

	setHeight (MathHelper::max (heightHelper (t->getLeft ()), heightHelper (t->getRight ())) + 1);
	return t;
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::singleRightRotate (BSTNode<T, N>* t)
{
	BSTNode<T, N>* u = t->getLeft ();
	t->setLeft (u->getRight ());
	u->setRight (t);
	t->setHeight (MathHelper::max (heightHelper (t->getLeft ()), heightHelper (t->getRight ())) + 1);
	u->setHeight (MathHelper::max (heightHelper (u->getLeft ()), t->getHeight ()) + 1);
	return u;
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::singleLeftRotate (BSTNode<T, N>* t)
{
	BSTNode<T, N>* u = t->getRight ();
	t->setRight (u->getLeft ());
	u->setLeft (t);
	t->setHeight (MathHelper::max (heightHelper (t->getLeft ()), heightHelper (t->getRight ())) + 1);
	u->setHeight (MathHelper::max (heightHelper (t->getRight ()), t->getHeight ()) + 1);
	return u;
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::doubleLeftRotate (BSTNode<T, N>* t)
{
	t->setRight(singleRightRotate (t->getRight()));
	return singleLeftRotate (t);
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::doubleRightRotate (BSTNode<T, N>* t)
{
	t->setLeft (singleLeftRotate (t->getLeft ()));
	return singleRightRotate (t);
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::findMin (BSTNode<T, N>* t)
{
	if (t == nullptr)
		return nullptr;
	else if (t->getLeft () == nullptr)
		return t;
	else
		return findMin (t->getLeft ());
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::findMax (BSTNode<T, N>* t)
{
	if (t == nullptr)
		return nullptr;
	else if (t->getRight () == nullptr)
		return t;
	else
		return findMax (t->getRight ());
}

template <class T, class N>
BSTNode<T, N>* BST<T, N>::removeAVLHelper (N* x, BSTNode<T, N>* t, std::function<T (N*)>* access)
{
	BSTNode<T, N>* temp;

	// Element not found
	if (t == nullptr)
		return nullptr;

	// Searching for element
	else if ((*access)(x) < (*access)t->getValue ())
		t->setLeft (removeAVLHelper (x, t->getLeft (), access));
	else if (x > t->getValue ())
		t->setRight (removeAVLHelper (x, t->getRight (), access));

	// Element found
	// With 2 children
	else if (t->getLeft () && t->getRight ())
	{
		temp = findMin (t->getRight ());
		t->setValue (temp->getValue ());
		t->getRight (removeAVLHelper (t->getValue (), t->getRight (), access));
	}
	// With one or zero child
	else
	{
		temp = t;
		if (t->getLeft () == nullptr)
			t = t->getRight ();
		else if (t->getRight () == nullptr)
			t = t->getLeft ();
		delete temp;
	}

	if (t == nullptr)
		return t;

	setHeight (MathHelper::max (heightHelper (t->getLeft ()), heightHelper (t->getRight ()) + 1));

	// If node is unbalanced
	// If left node is deleted, right case
	if (heightHelper (t->getLeft ()) - heightHelper (t->getRight ()) == 2)
	{
		// right right case
		if (heightHelper (t->getLeft ()->getLeft ()) - heightHelper (t->getLeft ()->getRight ()) == 1)
			return singleLeftRotate (t);
		// right left case
		else
			return doubleLeftRotate (t);
	}
	// If right node is deleted, left case
	else (heightHelper (t->getRight ()) - heightHelper (t->getLeft ()) == 2)
	{
		// left left case
		if (heightHelper (t->getRight ()->getRight ()) - heightHelper (t->getRight ()->getLeft ()) == 1)
			return singleRightRotate (t);
		// left right case
		else
			return doubleRightRotate (t);
	}
	return t;
}

/*
template <class T, class N>
int BST<T, N>::height(BSTNode<T, N>* t)
{
return (t == nullptr ? -1 : t->height);
}

*/

template <class T, class N>
int BST<T, N>::getBalance (BSTNode<T, N>* t)
{
	if (t == nullptr)
		return 0;
	else
		return heightHelper (t->getLeft ()) - heightHelper (t->getRight ());
}

//******************************************************
// BST class implementation 
// PUBLIC METHODS
//******************************************************

template <class T, class N>
BST<T, N>::BST ()
{
	root = nullptr;
	heightCount = 0;
}

template <class T, class N>
BST<T, N>::BST (List<N*>* listPtr, T (*access)(N* node))
{
	root = nullptr;
	heightCount = 0;
	insert (listPtr, access);
}

template <class T, class N>
BST<T, N>::~BST ()
{
}

template <class T, class N>
void BST<T, N>::add (N* val, T (*access)(N*))
{
	add (val, new std::function<T (N*)> ((*access)));
}

template <class T, class N>
void BST<T, N>::add (N* val, std::function<T (N*)>* access)
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
void BST<T, N>::logLevel (std::function<std::string (N*)>* visit, std::string &log)
{
	int titleWidth = 5;
	int spaceWidth = 1;
	int maxDepth = 10;
	if (this->root)
	{
		int i, h, levelMax;
		unsigned int j, n, maxNodeWidth, maxWidth, lineNodes, lineWidth;
		h = heightHelper (this->root);
		levelMax = (maxDepth < h) ? maxDepth : h;
		std::stringstream ss;
		// a list of BST nodes for each level
		List<BSTNode<T, N>*>** levelNodePtrArr = new List<BSTNode<T, N>*>*[levelMax];
		for (i = 0; i < levelMax; i++)
			levelNodePtrArr[i] = new List<BSTNode<T, N>*>;
		BSTNode<T, N>* BST_NodePtr1;
		BSTNode<T, N>* BST_NodePtr2;
		// root is level 0
		(*levelNodePtrArr)[0].push_back (this->root);
		/* traverse tree and fill up array of lists
		list levels will always contain predictable amount of elements 2^i
		may contain nullptr. they are used to maintain a predictable structure */
		levelHelper (this->root, levelNodePtrArr, 1, levelMax);
		// log the BST node lists level by level
		maxNodeWidth = widthHelper (levelNodePtrArr, levelMax);
		maxWidth = maxNodeWidth*titleWidth + (maxNodeWidth - 1)*spaceWidth;
		for (i = 0; i < levelMax; i++)
		{
			lineNodes = widthHelper (levelNodePtrArr[i]);
			lineWidth = (lineNodes == 0) ? maxWidth : maxWidth / lineNodes;
			//std::cout << "maxNodeWidth: " << maxNodeWidth << " maxWidth: " << maxWidth << " lineNodes: " << lineNodes << " lineWidth: " << lineWidth << std::endl;
			ss.str ("");
			n = levelNodePtrArr[i]->size ();
			// we are only going to check pairs of leaves so we can format them correctly
			for (j = 0; j < n; j += 2)
			{
				if (i > 0)
				{
					BST_NodePtr1 = (*levelNodePtrArr[i])[j];
					BST_NodePtr2 = (*levelNodePtrArr[i])[j + 1];
					if (BST_NodePtr1)
					{
						ss << std::left << std::setw (lineWidth);
						ss << StringHelper::center ((*visit) (BST_NodePtr1->getValue ()), lineWidth);
						ss << " ";
					}
					if (BST_NodePtr2)
					{
						ss << std::left << std::setw (lineWidth);
						ss << StringHelper::center ((*visit) (BST_NodePtr2->getValue ()), lineWidth);
						ss << " ";
					}
				}
				else
				{
					BST_NodePtr1 = (*levelNodePtrArr[i])[j];
					if (BST_NodePtr1)
					{
						ss << std::left << std::setw (lineWidth);
						ss << StringHelper::center ((*visit) (BST_NodePtr1->getValue ()), lineWidth);
						ss << " ";
					}
				}
			}
			log += ss.str () + "\n";
		}
	}
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
bool BST<T, N>::remove (T val, T (*access)(N*))
{
	return remove (val, new std::function<T (N*)> ((*access)));
}

template <class T, class N>
bool BST<T, N>::remove (T val, std::function<T (N*)>* access)
{
	return this->removeHelper (NULL, this->root, val, access);
}

template <class T, class N>
bool BST<T, N>::remove (N* val, T (*access)(N*))
{
	return remove (val, new std::function<T (N*)> ((*access)));
}

template <class T, class N>
bool BST<T, N>::remove (N* val, std::function<T (N*)>* access)
{
	return this->removeHelper (NULL, this->root, (*access)(val), access);
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
	bool flag = false;
	this->findHelper (this->root, value, listPtr, access, operations);
	operations += 2;
	if (!listPtr->empty ()) flag = true;
	return flag;
}

template <class T, class N>
bool BST<T, N>::find (T value, List<N*>* listPtr, T (*access)(N*), int &operations)
{
	return find (value, listPtr, new std::function<T (N*)> ((*access)), operations);
}

template <class T, class N>
bool BST<T, N>::find (T value, List<N*>* listPtr, std::function<T (N*)>* access, int &operations)
{
	bool flag = false;
	operations += 1;
	if (root)
	{
		findHelper (root, value, listPtr, access, operations);
		operations += 2;
		if (!listPtr->empty ()) flag = true;
	}
	return flag;
}
#endif