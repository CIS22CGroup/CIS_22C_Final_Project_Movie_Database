/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "UserStorage.h"

UserStorage::UserStorage ()
{
	storageMap = new HashMap <UserStorageNode*> (maxItems);
	titleBST = new BST<std::string, UserStorageNode>;
	yearBST = new BST<int, UserStorageNode>;
	/* nodes in the map */
	itemCount = 0;
}

std::string UserStorage::insert (std::string title, int year)
{
	return insert (new UserStorageNode (title, year));
}

std::string UserStorage::insert (UserStorageNode* nodePtr)
{
	storageMap->insert (StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ()), nodePtr);
	//(*storageMap)[nodePtr->getTitle ()] = nodePtr;
	// add node to the BST
	titleBST->add (nodePtr, UserStorage::accessTitle);
	yearBST->add (nodePtr, UserStorage::accessYear);
	//return nodePtr->getTitle ();
	return StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ());
}

UserStorageNode* UserStorage::getNode (std::string ID)
{
	return storageMap->at (ID);
}

bool UserStorage::remove (std::string ID)
{
	storageMap->erase (ID);
	return true;
}

//******************************************************
// VISIT AND ACCESS METHODS
//******************************************************

std::string UserStorage::accessTitle (UserStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getTitle ());
}

int UserStorage::accessYear (UserStorageNode* nodePtr)
{
	return nodePtr->getYear ();
}