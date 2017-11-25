/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef HASH_MAP_NODE_H
#define HASH_MAP_NODE_H

#include <string>

/**
@class HashMapNode
list node for the Hash Map. Keeps track of key and value pairs.
@param T data type
*/
template <class T>
class HashMapNode
{
private:
	std::string key;
	T value;
public:
	// CONSTRUCTORS/DESTRUCTORS
	HashMapNode ();
	HashMapNode (std::string keyInit, T val);
	~HashMapNode ();
	// GETTER/SETTER   
	std::string getKey ();
	T getValue ();
	void setKey (std::string keyInit);
	void setValue (T val);
};

//******************************************************
// HashMapNode CONSTRUCTORS/DESTRUCTORS    
//******************************************************
template <class T>
HashMapNode<T>::HashMapNode ()
{
	key = "";
	value = nullptr;
}

template <class T>
HashMapNode<T>::HashMapNode (std::string keyInit, T val)
{
	key = keyInit;
	value = val;
}

template <class T>
HashMapNode<T>::~HashMapNode () {}

//******************************************************
// HashMapNode GETTER/SETTER   
//******************************************************
template <class T>
std::string HashMapNode<T>::getKey () { return key; }

template <class T>
T HashMapNode<T>::getValue () { return value; }

template <class T>
void HashMapNode<T>::setKey (std::string keyInit) { key = keyInit; }

template <class T>
void HashMapNode<T>::setValue (T val) { value = val; }
#endif