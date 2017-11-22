/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "UserStorageNode.h"

UserStorageNode::UserStorageNode ()
{
	title = "";
	year = 0;
}

UserStorageNode::UserStorageNode (std::string titleInit, int yearInit)
{
	title = titleInit;
	year = yearInit;
}