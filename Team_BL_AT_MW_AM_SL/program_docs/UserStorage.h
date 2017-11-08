#ifndef USER_STORAGE_H
#define USER_STORAGE_H

#include <map>
#include <algorithm>
#include <string>
#include <cctype>
#include "UserStorageNode.h"

class UserStorage
{
private:
	std::map <std::string, UserStorageNode*> bookmarkMap;
	unsigned int size;
public:
	UserStorage::UserStorage ();
	std::string insert (std::string title, int year);
	UserStorageNode* getNode (std::string ID);
	bool remove(std::string ID);
	std::string toID (std::string title, int year);
};

#endif