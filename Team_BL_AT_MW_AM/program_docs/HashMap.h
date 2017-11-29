/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

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
	unsigned int itemCount;
	unsigned int bucketCount;
	unsigned int maxCount;
	unsigned int collisionCount;
	unsigned int replacementCount;
public:
	HashMap (unsigned int size);
	~HashMap ();

	/** Returns a reference to the mapped value
	of the element with key equivalent to key.
	@param key the key of the element to find
	@return reference to the mapped value
	*/
	T at (std::string key);

	/** Checks if the container has no elements
	@return true if the container is empty, false otherwise
	*/
	bool empty () const;

	/** Returns the number of elements in the container
	@return The number of elements in the container. */
	unsigned int size () const;
	unsigned int max_size () const;
	unsigned int bucketsUsed () const;
	unsigned int collisions () const;

	/** Removes all elements from the container.
	*/
	void clear ();

	/** Inserts element(s) into the container,
	if the container doesn't already contain an element
	with an equivalent key
	@pre None
	@post val is at the given key in the map
	@param key the key of the element to find
	@param val the element to insert
	@return true on success, false otherwise
	*/
	bool insert (std::string key, T val);

	bool erase (std::string key);
	bool remove (T val);

	/** Finds an element with key equivalent to key
	@param key the key of the element to find
	@return position in the bucket and
	-1 if bucket not initialized or key not found
	*/
	int find (std::string key);

	List<HashMapNode<T>*>* getHash (int hashId);
	bool existHash (int hashId);
	//T& operator[] (const std::string key); // write
	//const T& operator[](const std::string key) const // read
};

//******************************************************
// List class constructors/destructors
//******************************************************
template <class T>
HashMap<T>::HashMap (unsigned int size) // Default Constructor
{
	map = new List<HashMapNode<T>*>*[size];
	itemCount = 0;
	bucketCount = 0;
	maxCount = size;
	collisionCount = 0;
	replacementCount = 0;
	for (unsigned int i = 0; i < maxCount; i++)
		map[i] = nullptr;
}

template <class T>
HashMap<T>::~HashMap () { clear (); } // Destructor

//******************************************************
// List class implementation    
//******************************************************
template <class T>
T HashMap<T>::at (std::string key)
{
	unsigned int i, n;
	if (map[StringHelper::hashStr (key, maxCount)] == nullptr)
	{
		throw std::runtime_error ("Key " + key + " does not exist!");
	}
	else
	{
		n = map[StringHelper::hashStr (key, maxCount)]->size ();
		for (i = 0; i < n; i++)
		{
			if ((*map[StringHelper::hashStr (key, maxCount)])[i]->getKey () == key)
			{
				return (*map[StringHelper::hashStr (key, maxCount)])[i]->getValue ();
			}
		}
	}
	throw std::runtime_error ("Key " + key + " does not exist!");
}

template <class T>
bool HashMap<T>::empty () const
{
	if (itemCount == 0) return true;
	return false;
}

template <class T>
unsigned int HashMap<T>::size () const
{
	return itemCount;
}

template <class T>
unsigned int HashMap<T>::max_size () const
{
	return maxCount;
}

template <class T>
unsigned int HashMap<T>::bucketsUsed () const
{
	return bucketCount;
}

template <class T>
unsigned int HashMap<T>::collisions () const
{
	return collisionCount;
}

template <class T>
void HashMap<T>::clear ()
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
bool HashMap<T>::insert (std::string key, T val)
{
	/* this method will overwrite an existing key
	check if a key exists with the find method */
	bool flag = false;
	unsigned int n, i;
	n = 0;
	int hashId = StringHelper::hashStr (key, maxCount);
	if (map[hashId] == nullptr)
	{
		map[hashId] = new List<HashMapNode<T>*>;
		bucketCount++;
	}
	else
	{
		n = map[hashId]->size ();
	}
	/* push new node into linked list since the bucket
	was just created */
	if (n != 0)
	{
		collisionCount++;
		/* check if a node with the same key exists in the
		linked list and remove it */
		for (i = 0; i < n; i++)
		{
			if ((*map[hashId])[i]->getKey () == key)
			{
				replacementCount++;
				map[hashId]->erase (i);
			}
		}
	}
	itemCount++;
	return map[hashId]->push_back (new HashMapNode<T> (key, val));
}

template <class T>
bool HashMap<T>::erase (std::string key)
{
	bool flag = false;
	unsigned int i, n;
	if (map[StringHelper::hashStr (key, maxCount)] == nullptr)
	{
		throw std::runtime_error ("Key " + key + " does not exist!");
	}
	else
	{
		n = map[StringHelper::hashStr (key, maxCount)]->size ();
		for (i = 0; i < n; i++)
		{
			// erases all list nodes matching the key
			if ((*map[StringHelper::hashStr (key, maxCount)])[i]->getKey () == key)
			{
				map[StringHelper::hashStr (key, maxCount)]->erase (i);
				flag = true;
			}
		}
		if (flag)
			return flag;
		else
			throw std::runtime_error ("Key " + key + " does not exist!");
	}
}

template <class T>
bool HashMap<T>::remove (T val)
{
	bool flag = false;
	unsigned int i, j, n;
	/* We don't know the key so we have to check every single map node
	to see if any list node value matches */
	for (i = 0; i < maxCount; i++)
	{
		if (map[i] != nullptr)
		{
			n = map[i]->size ();
			for (j = 0; j < n; i++)
			{
				// erases all list nodes matching the value
				if ((*map[i])[j]->getValue () == val)
				{
					map[i]->erase (j);
					flag = true;
				}
			}
		}
	}
	if (flag)
		return flag;
	else
		throw std::runtime_error ("Value does not exist!");
}

template <class T>
int HashMap<T>::find (std::string key)
{
	/* this method will overwrite an existing key
	check if a key exists with the find method */
	bool flag = false;
	unsigned int n, i;
	n = 0;
	int pos = -1;
	int hashId = StringHelper::hashStr (key, maxCount);
	if (map[hashId] == nullptr)
	{
		pos = -1;
	}
	else
	{
		n = map[hashId]->size ();
	}
	if (n != 0)
	{
		/* check the first node with the same key exists in the
		linked list and return the position */
		for (i = 0; i < n; i++)
		{
			if ((*map[hashId])[i]->getKey () == key)
			{
				pos = i;
				break;
			}
		}
	}
	return pos;
}

template <class T>
List<HashMapNode<T>*>* HashMap<T>::getHash (int hashId)
{
	return map[hashId];
}

template <class T>
bool HashMap<T>::existHash (int hashId)
{
	return map[hashId] == nullptr ? false : true;
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