/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
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

	std::string getTitle ();
	int getYear ();
};

#endif