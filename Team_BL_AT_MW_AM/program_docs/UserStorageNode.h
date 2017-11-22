#ifndef USER_STORAGE_NODE_H
#define USER_STORAGE_NODE_H

#include <string>

class UserStorageNode
{
private:
	std::string title; // Transformers
	int year; // 2007
public:
	UserStorageNode ();
	UserStorageNode (std::string titleInit, int yearInit);
};

#endif