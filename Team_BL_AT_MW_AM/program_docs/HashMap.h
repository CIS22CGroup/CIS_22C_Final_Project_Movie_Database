/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
Use SDK Version: 10.0.15063.0 for De Anza Computers
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <iostream>
#include <string>
#include <sstream>
#include "StringHelper.h"
#include "List.h"
#include "HashMapNode.h"

/**
@class HashMap
constructor example:\n
HashMap <std::string, MainStorageNode*>* storageMap = new HashMap <std::string, MainStorageNode*>;\n
Only takes keys of type std::string. Implemented as separate chaining with linked lists meaning
each bucket has an overflow linked list for key collisions.
@param T mapped type
*/
template <class T>
class HashMap
{
private:
	List<HashMapNode<T>*>** map;
	List<HashMapNode<T>*>* mapNodes;
	unsigned int itemCount;
	unsigned int bucketCount;
	unsigned int maxCount;
	unsigned int collisionCount;
	unsigned int replacementCount;
public:
	HashMap(unsigned int size);
	~HashMap();

	class iterator
	{
	private:
		List<HashMapNode<T>*>* mapNodes;
		int position;
		unsigned int operations;
	public:
		iterator() {
			mapNodes = nullptr;
			position = 0;
		}
		iterator(List<HashMapNode<T>*>* ptr, int pos) {
			mapNodes = ptr;
			position = pos;
		}
		iterator operator++() { iterator i = *this; position++; return i; }
		iterator operator++(int junk) { position++; return *this; }
		HashMapNode<T>& operator*() { return *((*mapNodes)[position]); }
		HashMapNode<T>* operator->() { return (*mapNodes)[position]; }
		bool operator==(const iterator& rhs) { return position == rhs.position; }
		bool operator!=(const iterator& rhs) { return position != rhs.position; }
	};

	//typedef HashMapNode<T>* iterator;
	//typedef const HashMapNode<T>* const_iterator;

	/** Returns a reference to the mapped value
	of the element with key equivalent to key.
	@param key the key of the element to find
	@return reference to the mapped value
	*/
	T at(std::string key);

	/** Checks if the container has no elements
	@return true if the container is empty, false otherwise
	*/
	bool empty() const;

	/** Returns the number of elements in the container
	@return The number of elements in the container. */
	unsigned int size() const;
	unsigned int max_size() const;
	unsigned int bucketsUsed() const;
	unsigned int collisions() const;

	/** Removes all elements from the container.
	*/
	void clear();

	/** Inserts element(s) into the container,
	if the container doesn't already contain an element
	with an equivalent key
	@pre None
	@post val is at the given key in the map
	@param key the key of the element to find
	@param val the element to insert
	@return true on success, false otherwise
	*/
	bool insert(std::string key, T val, unsigned int &operations);

	bool erase(std::string key, unsigned int &operations);
	bool erase(List<HashMapNode<T>*>* &bucketPtr, unsigned int pos, unsigned int &operations);
	bool remove(T val, unsigned int &operations);

	/** Finds an element with key equivalent to key
	@param key the key of the element to find
	@return position in the bucket and
	-1 if bucket not initialized or key not found
	*/
	int find(std::string key, unsigned int &operations);

	List<HashMapNode<T>*>* getHash(int hashId);
	bool existHash(int hashId);
	/** turns the linked list array into a linear
	linked list. this allows the hash table to be
	read with an iterator */
	void linearize(unsigned int &operations);

	iterator begin()
	{
		unsigned int operations = 0;
		linearize(operations);
		return iterator(mapNodes, 0);
	}
	iterator end()
	{
		unsigned int operations = 0;
		linearize(operations);
		return iterator(mapNodes, mapNodes->size());
	}

	//T& operator[] (const std::string key); // write
	//const T& operator[](const std::string key) const // read
};

//******************************************************
// List class constructors/destructors
//******************************************************
template <class T>
HashMap<T>::HashMap(unsigned int size) // Default Constructor
{
	map = new List<HashMapNode<T>*>*[size];
	mapNodes = new List<HashMapNode<T>*>;
	itemCount = 0;
	bucketCount = 0;
	maxCount = size;
	collisionCount = 0;
	replacementCount = 0;
	for (unsigned int i = 0; i < maxCount; i++)
		map[i] = nullptr;
}

template <class T>
HashMap<T>::~HashMap() { clear(); } // Destructor

//******************************************************
// List class implementation    
//******************************************************
template <class T>
T HashMap<T>::at(std::string key)
{
	unsigned int i, n;
	if (map[StringHelper::hashStr(key, maxCount)] == nullptr)
	{
		throw std::runtime_error("Key " + key + " does not exist!");
	}
	else
	{
		n = map[StringHelper::hashStr(key, maxCount)]->size();
		for (i = 0; i < n; i++)
		{
			if ((*map[StringHelper::hashStr(key, maxCount)])[i]->getKey() == key)
			{
				return (*map[StringHelper::hashStr(key, maxCount)])[i]->getValue();
			}
		}
	}
	throw std::runtime_error("Key " + key + " does not exist!");
}

template <class T>
bool HashMap<T>::empty() const
{
	if (itemCount == 0) return true;
	return false;
}

template <class T>
unsigned int HashMap<T>::size() const
{
	return itemCount;
}

template <class T>
unsigned int HashMap<T>::max_size() const
{
	return maxCount;
}

template <class T>
unsigned int HashMap<T>::bucketsUsed() const
{
	return bucketCount;
}

template <class T>
unsigned int HashMap<T>::collisions() const
{
	return collisionCount;
}

template <class T>
void HashMap<T>::clear()
{
	unsigned int i;
	for (i = 0; i < maxCount; i++)
	{
		if (map[i])
			delete map[i];
	}
	itemCount = 0;
}

template <class T>
bool HashMap<T>::insert(std::string key, T val, unsigned int &operations)
{
	operations += 10;
	/* this method will overwrite an existing key
	check if a key exists with the find method */
	bool flag = false;
	unsigned int n, i;
	n = 0;
	unsigned int hashId = (unsigned int)StringHelper::hashStr(key, maxCount);
	// init a new bucket if necessary
	if (map[hashId] == nullptr)
	{
		map[hashId] = new List<HashMapNode<T>*>;
		bucketCount++;
	}
	else
	{
		n = map[hashId]->size();
	}
	// collision occurs
	if (n != 0)
	{
		collisionCount++;
		/* check if a node with the same key exists in the
		linked list and remove it */
		for (i = 0; i < n; i++)
		{
			operations++;
			if ((*map[hashId])[i]->getKey() == key)
			{
				replacementCount++;
				map[hashId]->erase(i);
			}
		}
	}
	itemCount++;
	flag = map[hashId]->push_back(new HashMapNode<T>(key, val, hashId, n));
	return flag;
}

template <class T>
bool HashMap<T>::erase(std::string key, unsigned int &operations)
{
	bool flag = false;
	unsigned int i, n, hashId;
	hashId = (unsigned int)StringHelper::hashStr(key, maxCount);
	if (map[hashId] == nullptr)
	{
		throw std::runtime_error("Key " + key + " does not exist!");
	}
	else
	{
		n = map[hashId]->size();
		for (i = 0; i < n; i++)
		{
			// erases all list nodes matching the key
			if ((*map[hashId])[i]->getKey() == key)
			{
				flag = erase(map[hashId], i, operations);
				n--;
			}
		}
		if (flag)
			return flag;
		else
			throw std::runtime_error("Key " + key + " does not exist!");
	}
}

template <class T>
bool HashMap<T>::erase(List<HashMapNode<T>*>* &bucketPtr, unsigned int pos, unsigned int &operations) {
	bool flag = false;
	HashMapNode<T>* hashMapNodePtr;
	if (bucketPtr && pos < (unsigned int)bucketPtr->size()) {
		hashMapNodePtr = (*bucketPtr)[pos];
		// linearize clear
		mapNodes->clear();
		// collisions reduced
		if ((*bucketPtr)[pos]->isCollision()) {
			collisionCount--;
		}
		// remove hash node from bucket
		bucketPtr->erase(pos);
		itemCount--;
		// delete bucket if empty
		if (bucketPtr->empty()) {
			delete bucketPtr;
			bucketPtr = nullptr;
			bucketCount--;
		}
		delete hashMapNodePtr;
		flag = true;
	}
	return flag;
}

template <class T>
bool HashMap<T>::remove(T val, unsigned int &operations)
{
	bool flag = false;
	unsigned int i, j, n;
	/* We don't know the key so we have to check every single map node
	to see if any list node value matches */
	for (i = 0; i < maxCount; i++)
	{
		if (map[i] != nullptr)
		{
			n = map[i]->size();
			for (j = 0; j < n; j++)
			{
				// erases all list nodes matching the value
				if ((*map[i])[j]->getValue() == val)
				{
					flag = erase(map[i], j, operations);
					n--;
				}
			}
		}
	}
	return flag;
}

template <class T>
int HashMap<T>::find(std::string key, unsigned int &operations)
{
	/* this method will overwrite an existing key
	check if a key exists with the find method */
	bool flag = false;
	unsigned int n, i;
	n = 0;
	int pos = -1;
	int hashId = StringHelper::hashStr(key, maxCount);
	if (map[hashId] == nullptr)
	{
		pos = -1;
	}
	else
	{
		n = map[hashId]->size();
	}
	operations += 6;
	if (n != 0)
	{
		/* check the first node with the same key exists in the
		linked list and return the position */
		for (i = 0; i < n; i++)
		{
			operations++;
			if ((*map[hashId])[i]->getKey() == key)
			{
				pos = i;
				break;
			}
		}
	}
	return pos;
}

template <class T>
List<HashMapNode<T>*>* HashMap<T>::getHash(int hashId)
{
	return map[hashId];
}

template <class T>
bool HashMap<T>::existHash(int hashId)
{
	return map[hashId] == nullptr ? false : true;
}

template <class T>
void HashMap<T>::linearize(unsigned int &operations) {
	List<HashMapNode<T>*>* movieHashMapListPtr;
	HashMapNode<T>* movieHashMapNodePtr;
	unsigned int i, n, j, n1;

	n = max_size();
	mapNodes->clear();
	operations += 2;
	// loop through the entire hash table and look at the "buckets"
	for (i = 0; i < n; i++)
	{
		operations++;
		// hash table "buckets" might be null. check if they exist.
		if (existHash(i))
		{
			operations++;
			movieHashMapListPtr = getHash(i);
			// loop through every linked-list in the bucket
			n1 = movieHashMapListPtr->size();
			for (j = 0; j < n1; j++)
			{
				operations += 2;
				// get the hash table nodes from the list
				movieHashMapNodePtr = (*movieHashMapListPtr)[j];
				mapNodes->push_back(movieHashMapNodePtr);
			}
		}
	}
}

/*
template <class T>
T& HashMap<T>::operator[] (const std::string key)
{
	//write
	try
	{
		erase (std::string key)
	}
	catch (const std::exception& e)
	{

	}
	return at (std::string key);
}

template <class T>
const T& HashMap<T>::operator[](const std::string key) const
{
	//read
	return at (std::string key);
}*/
#endif