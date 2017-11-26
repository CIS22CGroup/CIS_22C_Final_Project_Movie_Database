/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef USER_STORAGE_H
#define USER_STORAGE_H

#include <string>
#include "StringHelper.h"
#include "UserStorageNode.h"
#include "List.h"
#include "BST.h"
#include "HashMap.h"

class UserStorage
{
private:
	static const int maxItems = 86969;

	HashMap <UserStorageNode*>* storageMap;
	BST<std::string, UserStorageNode> * titleBST;
	BST<int, UserStorageNode> * yearBST;
	/* nodes in the map */
	unsigned int itemCount;
public:
	UserStorage::UserStorage ();

	/*
	@pre None
	@post Bookmark node added to bookmark storage
	@param title Movie title
	@param year Movie year released
	@return ID of the movie
	*/
	std::string insert (std::string title, int year);
	std::string insert (UserStorageNode* nodePtr);

	/* NOTE: an update method is not included for bookmarks
	an "update" should involve deleting the bookmark node and adding a new one
	editing bookmark node data attributes may corrupt the BST */

	/*
	@pre
	@post
	@param ID unique movie ID
	@return
	*/
	UserStorageNode* getNode (std::string ID);

	/*
	@pre
	@post
	@param title Movie title
	@param year Movie year made
	@return
	*/
	bool remove(std::string ID);

	/* visit and access methods
	We define methods on how to access certain data attributes inside the movie node
	this makes the BST more portable and reusable rather than hard coding attribute locations
	*/
	static std::string UserStorage::accessTitle (UserStorageNode* nodePtr);
	static int UserStorage::accessYear (UserStorageNode* nodePtr);
};

#endif