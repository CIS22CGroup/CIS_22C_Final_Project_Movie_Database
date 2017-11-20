#ifndef BINARY_NODE
#define BINARY_NODE

template<class Type>
class BinaryNode
{
private:
	Type item;
	BinaryNode<Type> *leftChildPtr;
	BinaryNode<Type> *rightChildPtr;
	
public:
	BinaryNode();
	BinaryNode(const Type &anItem);
	BinaryNode(const Type &anItem, BinaryNode<Type> *leftPtr, BinaryNode<Type> *rightPtr);

	void setItem(const Type &anItem);
	Type getItem() const;

	bool isLeaf() const;

	BinaryNode<Type>* getLeftChildPtr() const;
	BinaryNode<Type>* getRightChildPtr() const;

	void setLeftChildPtr(BinaryNode<Type>* leftPtr);
	void setRightChildPtr(BinaryNode<Type>* rightPtr);

};
#endif



//********************************************************************************************
template<class Type>
BinaryNode<Type>::BinaryNode()
{
	leftChildPtr = nullptr;
	rightChildPtr = nullptr;
}

template<class Type>
BinaryNode<Type>::BinaryNode(const Type &item)
{
	item = anItem;
	leftChildPtr = nullptr;
	rightChildPtr = nullptr;
}

template<class Type>
BinaryNode<Type>::BinaryNode(const Type &anItem, BinaryNode<Type> *leftPtr, BinaryNode<Type> *rightPtr)
{
	item = anItem;
	leftChildPtr = leftPtr;
	rightChildPtr = rightPtr;
}

template<class Type>
void BinaryNode<Type>::setItem(const Type &anItem)
{
	item = anItem;
}

template<class Type>
Type BinaryNode<Type>::getItem() const
{
	return item;
}

template<class Type>
bool BinaryNode<Type>::isLeaf() const
{
	if (leftChildPtr == nullptr && rightChildPtr == nullptr)
		return true;
	else
		return false;
}



template<class Type>
BinaryNode<Type>* BinaryNode<Type>::getLeftChildPtr() const
{
	return leftChildPtr;
}

template<class Type>
BinaryNode<Type>* BinaryNode<Type>::getRightChildPtr() const
{
	return leftRightPtr;
}

template<class Type>
void BinaryNode<Type>::setLeftChildPtr(BinaryNode<Type> *leftPtr)
{
	leftChildPtr = leftPtr;
}

template<class Type>
void BinaryNode<Type>::setRightChildPtr(BinaryNode<Type> *rightPtr)
{
	rightChildPtr = rightPtr;
}


