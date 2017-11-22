/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef MAIN_STORAGE_H
#define MAIN_STORAGE_H

#include <map>
#include <algorithm>
#include <string>
#include <cctype>
#include "MainStorageNode.h"
#include "BST.h"
#include "List.h"

class MainStorage
{
private:
	std::map <std::string, MainStorageNode*> storageMap;
	unsigned int size;
	BST<std::string, MainStorageNode> * titleBST;
	BST<int, MainStorageNode> * yearBST;
	BST<double, MainStorageNode> * ratingBST;
	BST<std::string, MainStorageNode> * genre1BST;
	BST<std::string, MainStorageNode> * genre2BST;
public:
	MainStorage ();
	std::string insert (std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description);
	bool update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description);
	MainStorageNode* getNode (std::string ID);
	bool remove(std::string ID);
	std::string toID (std::string title, int year);

	std::string visit (MainStorageNode* nodePtr);

	bool titleFind (std::string title, List<MainStorageNode*>* listPtr, int &operations);
	bool yearFind (int year, List<MainStorageNode*>* listPtr, int &operations);
	bool ratingFind (double rating, List<MainStorageNode*>* listPtr, int &operations);
	bool genre1Find (std::string genre, List<MainStorageNode*>* listPtr, int &operations);
	bool genre2Find (std::string genre, List<MainStorageNode*>* listPtr, int &operations);

	/** finds the intersection between two result lists
	@pre None
	@post data node pointers pushed into listPtrResult
	@param listPtr1 list #1
	@param listPtr2 list #2
	@param listPtrResult common nodes in listPtr1 and listPtr2
	@return true on success, false on failure or not found */
	static bool intersection (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult);

	static std::string MainStorage::accessTitle (MainStorageNode* nodePtr);
	static int MainStorage::accessYear (MainStorageNode* nodePtr);
	static double MainStorage::accessRating (MainStorageNode* nodePtr);
	static std::string MainStorage::accessGenre1 (MainStorageNode* nodePtr);
	static std::string MainStorage::accessGenre2 (MainStorageNode* nodePtr);

};

#endif