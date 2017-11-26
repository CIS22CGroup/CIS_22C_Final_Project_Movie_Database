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

/**
@class UserStorageNode
The user storage node is also known as the bookmark node. This contains
all the bookmark data and should be pointed to in bookmark search and storage
methods. Only contains the minimum information about a movie. The data in the
bookmark node should be cross-referenced to the main storage for additional
information about a movie.
*/
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