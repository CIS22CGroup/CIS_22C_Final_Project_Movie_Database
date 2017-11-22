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

#include <map>
#include <string>
#include "StringHelper.h"
#include "UserStorageNode.h"

class UserStorage
{
private:
	std::map <std::string, UserStorageNode*>* bookmarkMapPtr;
	unsigned int size;
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
};

#endif