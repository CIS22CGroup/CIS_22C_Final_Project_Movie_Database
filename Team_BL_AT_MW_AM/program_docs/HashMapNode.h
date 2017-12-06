/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
Use SDK Version: 10.0.15063.0 for De Anza Computerss
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
	unsigned int hashId, listPos;
	bool flagCollision;
public:
	// CONSTRUCTORS/DESTRUCTORS
	HashMapNode ();
	HashMapNode (std::string keyInit, T val);
	HashMapNode(std::string keyInit, T val, unsigned int id, unsigned int pos);
	~HashMapNode ();
	// GETTER/SETTER   
	std::string getKey ();
	T getValue ();
	unsigned int getId();
	bool isCollision();
	unsigned int getListPos();
	HashMapNode<T>* getSelf();
	void setKey (std::string keyInit);
	void setValue (T val);
	void setId(unsigned int id);
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
HashMapNode<T>::HashMapNode(std::string keyInit, T val, unsigned int id, unsigned int pos)
{
	key = keyInit;
	value = val;
	hashId = id;
	flagCollision = (pos != 0);
	listPos = pos;
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
unsigned int HashMapNode<T>::getId() { return hashId; }

template <class T>
bool HashMapNode<T>::isCollision() { return flagCollision; }

template <class T>
unsigned int HashMapNode<T>::getListPos() { return listPos; }

template <class T>
HashMapNode<T>* HashMapNode<T>::getSelf() { return this; }

template <class T>
void HashMapNode<T>::setKey (std::string keyInit) { key = keyInit; }

template <class T>
void HashMapNode<T>::setValue (T val) { value = val; }

template <class T>
void HashMapNode<T>::setId(unsigned int id) { hashId = id; }
#endif