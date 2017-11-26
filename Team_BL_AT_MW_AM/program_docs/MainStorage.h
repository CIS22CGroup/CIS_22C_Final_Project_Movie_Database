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

#include <functional>
#include <string>
#include <sstream>
#include "StringHelper.h"
#include "MainStorageNode.h"
#include "List.h"
#include "BST.h"
#include "HashMap.h"

class MainStorage
{
private:
	static const int genreSize = 2;
	static const int titleIndexes = 10;
	static const int maxItems = 86969;
	HashMap <MainStorageNode*>* storageMap;
	unsigned int itemCount;
	BST<std::string, MainStorageNode> ** titleBST;
	BST<int, MainStorageNode> * yearBST;
	BST<double, MainStorageNode> * ratingBST;
	BST<std::string, MainStorageNode>** genreBST;
public:
	MainStorage ();

	/** inserts new movie into storage. 
	Adds searchable attributes to a BST.
	@pre None
	@post Movie node added to storage
	@param title Movie title
	@param content_rating Movie audience rating
	@param rating Movie critic rating score 1-10
	@param year Movie year made
	@param description Movie description
	@return ID of movie
	*/
	std::string insert (std::string title, int year, double rating, std::string description);

	/** inserts new movie node into storage. 
	Adds searchable attributes to a BST.
	@pre None
	@post Movie node added to storage
	@param nodePtr Movie node
	@return ID of movie
	*/
	std::string insert (MainStorageNode* nodePtr);
	bool update (MainStorageNode* nodePtr);
	MainStorageNode* getNode (std::string ID);
	bool remove(std::string ID);

	/* find methods
	These are the methods that should be used in the UI for searching
	*/
	bool titleFind (std::string title, List<MainStorageNode*>* listPtr, int &operations);
	bool yearFind (int year, List<MainStorageNode*>* listPtr, int &operations);
	bool ratingFind (double rating, List<MainStorageNode*>* listPtr, int &operations);
	bool genreFind (std::string genre, List<MainStorageNode*>* listPtr, int &operations);

	/** finds the intersection between two result lists
	@pre None
	@post data node pointers pushed into listPtrResult
	@param listPtr1 list #1
	@param listPtr2 list #2
	@param listPtrResult common nodes in listPtr1 and listPtr2
	@return true on success, false on failure or not found */
	static bool intersection (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult, int &operations);
	static bool mergeUnique (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtrResult, int &operations);

	/* visit and access methods
	We define methods on how to access certain data attributes inside the movie node
	this makes the BST more portable and reusable rather than hard coding attribute locations
	*/
	static std::string visit (MainStorageNode* nodePtr);
	static std::string visitTitleList (MainStorageNode* nodePtr);
	static std::string MainStorage::accessTitle (MainStorageNode* nodePtr);
	static std::function<std::string (MainStorageNode*)>* MainStorage::accessTitleList (int index);
	static std::string MainStorage::accessTitleListIndex (MainStorageNode* nodePtr, int index);
	static int MainStorage::accessYear (MainStorageNode* nodePtr);
	static double MainStorage::accessRating (MainStorageNode* nodePtr);
	static std::function<std::string (MainStorageNode*)>* MainStorage::accessGenre (int index);
	static std::string accessGenreIndex (MainStorageNode* nodePtr, int index);
};

#endif