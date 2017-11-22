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
	/* nodes in the map */
	size = 0;
}

std::string UserStorage::insert (std::string title, int year)
{
	(*bookmarkMapPtr)[StringHelper::toID (title, year)] = new UserStorageNode(title, year);
	return StringHelper::toID (title, year);
}

UserStorageNode* UserStorage::getNode (std::string ID)
{
	return (*bookmarkMapPtr)[ID];
}

bool UserStorage::remove (std::string ID)
{
	return false;
}