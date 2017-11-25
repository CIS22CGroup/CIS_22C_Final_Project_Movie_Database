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
HashMap <std::string, MainStorageNode*>* storageMap = new HashMap <std::string, MainStorageNode*>;
@param Key the map key type
@param T mapped type
*/
template <class T>
class HashMap
{
private:
	List<HashMapNode<T>*>** map;
	unsigned int itemCount;
	unsigned int maxCount;
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
	maxCount = size;
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
	if (map[StringHelper::hashStr (key, maxCount)] == nullptr)
	{
		map[StringHelper::hashStr (key, maxCount)] = new List<HashMapNode<T>*>;
	}
	itemCount++;
	return map[StringHelper::hashStr (key, maxCount)]->push_back (new HashMapNode<T> (key, val));
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
					map[i]->remove (j);
					flag = true;
				}
			}
		}
	}
	if (flag)
		return flag;
	else
		throw std::runtime_error ("Value " + val + "does not exist!");
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