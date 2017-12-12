


#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "BinaryNode.h"

//***********************************************************************************************
//                              CLASS HEADER: BINARYSEARCHTREE                                  *
//***********************************************************************************************


template<class Type>
class BinarySearchTree
{
private:
	BinaryNode<Type>* rootPtr;

protected:
	BinaryNode<Type>* insertInOder(BinaryNode<Type>* subTreePtr, BinaryNode<Type> newNode);                     //DONE***
	BinaryNode<Type>* removeValue(BinaryNode<Type>* subTreePtr, const Type target, bool &success);      //BT    //DONE***
	BinaryNode<Type>* removeNode(BinaryNode<Type>* nodePtr);                                                        //DONE***
	BinaryNode<Type>* removeLeftmostNode(BinaryNode<Type>* subTreePtr, Type &inorderSuccessor);                 //DONE***
	BinaryNode<Type>* findNode(BinaryNode<Type>* treePtr, const Type &target) const;                    //BT    //DONE***
																										//Read Tree from File
	BinaryNode<Type>* readTree(int n);
	int getHeightHelper(BinaryNode<Type> *subTreePtr) const;            //BT        //DONE***
	int getNumberOfNodesHelper(BinaryNode<Type> *nodePtr) const;        //BT        //DONE***
	void destroyTree(BinaryNode<Type>* subTreePtr);						//BT		//DONE***

public:
	//Constructors and Destructor
	BinarySearchTree();                                                 //DONE***
	BinarySearchTree(const Type &root0);                                //DONE***
	virtual ~BinarySearchTree();                                        //DONE***

																		//Public Methods
	bool isEmpty() const;                                       //BT    //DONE***
	int getHeight() const;                                      //BT    //DONE***
	int getNumberOfNodes() const;                               //BT    //DONE***
	Type getRootData();											//BT
	Type setRootData(const Type &newData) const;                //BT


	bool add(const Type &newEntry);
	bool remove(const Type & anEntry);                                  //DONE***
	void clear();
	Type getEntry(const Type &anEntry) const;
	bool contain(const Type &anEntry) const;

	//Public Traversal
	void preoderTravere(void visit(Type &)) const;              //BT
	void inorderTraverse(void visit(Type &)) const;             //BT
	void postorderTraverse(void visist(Type &)) const;          //BT

	//Overloaded Operator Section
	//BinarySearchTree<Type> &operator=(const BinarySearchTree<Type> &rightHandSide);

};

#endif



//***********************************************************************************************
//                              CLASS IMPLEMENTATION: BINARYSEARCHTREE                          *
//***********************************************************************************************
template<class Type>
BinarySearchTree<Type>::BinarySearchTree() :rootPtr(nullptr) {}             //default constructor


template<class Type>
BinarySearchTree<Type>::BinarySearchTree(const Type& root0)
{
	root = new BinaryNode<Type>(root0, nullptr, nullptr);
}

/* Binary Tree Method
template<class Type>
BinarySearchTree<Type>::BinarySearchTree(const Type& root0, const BinaryNodeTree<Type> *leftPtr, const BinaryNodeTree<Type> *rightPtr)
{
rootPtr = new BinaryNode<Type>(root0, copyTree(leftPtr->rootPtr), copyTree(rightTreePtr->rootPtr));
//copyTree() return pointer to a root of a tree
}
*/

/*
//copyTree() use recursive preorder traversal to copy each node in the tree
template<class Type>
BinaryNode<Type> *BinaryTree<Type>::copyTree(const BinaryNode<Type> *treePtr) const
{
BinaryNode<Type> *newTreePtr = nullptr;

//copy nodes during preorder traversal
if(treePtr != nullptr)
{
newTreePtr = new BinaryNode<Type>(treePtr->getItem(), nullptr, nullptr);        //copy root node

newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));

}
return newTreePtr;
}
*/


// destroyTree() is called byt destructor. It uses a recursive postorder traversal to delete each node in the tree
template<class Type>
void BinarySearchTree<Type>::destroyTree(BinaryNode<Type>* subTreePtr)            //subTreePtr is pointer to a sub tree
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());                         //recursively calling leftChildPtr to reach the last to delete
		destroyTree(subTreePtr->getRightChildPtr());                        //recursively calling rightChildPtr to reach the last to delete

		delete subTreePtr;                                                  //delete the node
	}
}

template<class Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
	destroyTree(rootPtr);
}


//***************************************************************************
//                              add()                                       *
//***************************************************************************
template<class Type>
bool BinarySearchTree<Type>::add(const Type &newData)
{
	BinaryNode<Type> *newNodePtr = new BinaryNode<Type>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);

	return true;
}

//***************************************************************************
//                              insertInOrder                               *
//***************************************************************************
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::insertInOder(BinaryNode<Type>* subTreePtr, BinaryNode<Type> newNode)
{
	BinaryNode<Type>* tempPtr;

	if (subTreePtr == nullptr)
		return newNodePtr;
	else if (subTreePtr->getItem() > newNodePtr->getItem())
	{
		tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		tempPtr = insertInorder(subTreePtr->getRightChild(), newNodePtr);
		subTreePtr->setRihtChild(tempPtr);
	}
	return subTreePtr;
}

//***************************************************************************
//                              removeValue()                               *
// Remove the target value from the Binary Search Tree that the subTreePtr  *
// points to. Return a pointer to the node at the tree location after the   *
// value is removed. Success is true if removal is successful. False otherwise
//***************************************************************************
template<class Type>
BinaryNode<Type>* removeValue(BinaryNode<Type>* subTreePtr, const Type target, bool &success)
{
	if (subTreePtr == nullptr)            //tree is empty
	{
		success = false;
		return nullptr;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);     //reassign subTreePtr to the new tree after removing the item
		success = true;
		return subTreePtr;
	}
	else if (subTreePtr->getItem() > target)
	{
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr)
			return subTreePtr;
	}
	else
	{
		tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		return subTreePtr;
	}

}

//***************************************************************************
//                              removeNode()                                *
// Removes the item in the node that nodePtr points to                      *
// Return a pointer to the node at the location after the node is deleted   *
//***************************************************************************
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeNode(BinaryNode<Type>* nodePtr)
{
	BinaryNode<Type>* nodeToConnectPtr;

	if (nodePtr.isLeaf())        //if nodePtr is a leaf
	{
		delte nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}

	else if (nodePtr.getLeftChildPtr != nullptr || nodePtr.getRightChildPtr == nullptr)      //nodePtr has only left child
	{
		nodeToConnectPtr = nodePtr->getLeftChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}

	else if (nodePtr.getLeftChildPtr == nullptr || nodePtr.getRightChildPtr != nullptr)      //nodePtr has only left child
	{
		nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else //has 2 children
	{
		//find the inorder successor of nodePtr, it is in left subtree of nodePtr's rightChild
		tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(newNodeValue);                 //new value in nodePtr
		return nodePtr;
	}
}

//***************************************************************************
//                      removeLeftmostNode()                                *
// Remove the leftmost node in the left subtree of the node that nodePtr    *
// points to. Set inorderSuccessor to the value in this node.               *
// Returns a pointer to the revised subtree                                 *
//***************************************************************************
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeLeftmostNode(BinaryNode<Type>* subTreePtr, Type &inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
		return removeLeftmostNode(NodePtr->getLeftChildPtr(), inorderSuccessor);
}



//***************************************************************************
//                              remove()                                    *
// Remove a given data from the Binary Search Tree                          *
//***************************************************************************
template<class Type>
bool BinarySearchTree<Type>::remove(const Type & anEntry)
{
	bool success = false;

	rootPtr = removeValue(rootPtr, target, success);

	return success;
}


/*
//***************************************************************************
//                              readTree()                                  *
// Read input from a file and buil and Binary Search Tree                   *
// Returns a pointer to the tree's root                                     *
//***************************************************************************
template<class Type>
BinaryNde<Type>* readTree(int n)
{
if (n > 0)
{
BinaryNode<Type>* treePtr =
<Type> rootItem =
treePtr->setItem(rootItem);


}
}
*/

//***************************************************************************
//                              getHeightHelper()                           *
// Protected Helper function for Public Method GetHeight()                  *
//***************************************************************************
template<class Type>
int BinarySearchTree<Type>::getHeightHelper(BinaryNode<Type> *subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}

//***************************************************************************
//                              getHeight()                                 *
// Return the height of the tree by calling getHeightHelper()               *
//***************************************************************************
template<class Type>
int BinarySearchTree<Type>::getHeight() const
{
	return getHeightHelper(rootPtr);
}



//***************************************************************************
//                              isEmpty()                                   *
// Return true if the tree is empty                                         *
//***************************************************************************
template<class Type>
bool BinarySearchTree<Type>::isEmpty() const
{
	return rootPtr == nullptr
}


//***************************************************************************
//                              getNumberOfNodeHelper()                     *
// Helper function to return the number of nodes in the tree                *
//***************************************************************************
template<class Type>
int BinarySearchTree<Type>::getNumberOfNodesHelper(BinaryNode<Type> *nodePtr) const
{
	if (nodePtr == nullptr)
		return 0;
	else
		return getNumberOfNode(nodePtr->getLeftChildPtr) + getNumberOfNode(nodePtr->getRightChildPtr) + 1   //1 is the node itself
}

//***************************************************************************
//                              getNumberOfNode()                           *
// Return the number of nodes in the tree                                   *
//***************************************************************************
template<class Type>
int BinarySearchTree<Type>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

//***************************************************************************
//                             findNode()                                   *
// Find the node in the Binary Search Tree that subTreePtr points to        *
// that has the target value. Return a pointer to that node or nullptr      *
//***************************************************************************
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::findNode(BinaryNode<Type>* treePtr, const Type &target) const
{
	if (subTreePtr == nullptr)               //subTree is empty
		return nullptr;

	else if (subTreePtr->getItem() == target)    //found in subTreePtr
		return subTreePtr;

	else if (subTreePtr->getItem() > target)     //search left child
		return findNode(subTreePtr->getLeftChildPtr(), target);

	else    //search right Child
		return findNode(subTreePtr->getRightChildPtr(), target);
}

