/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
Use SDK Version: 10.0.15063.0 for De Anza Computers
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef MAIN_STORAGE_H
#define MAIN_STORAGE_H

#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include "StringHelper.h"
#include "MainStorageNode.h"
#include "List.h"
#include "BST.h"
#include "HashMap.h"
#include "SearchResult.h"

class MainStorage
{
private:
	static const int genreSize = 2;
	static const int titleIndexes = 10;
	static const int maxItems = 100;
	HashMap <MainStorageNode*>* storageMap;
	unsigned int itemCount;
	BST<int, MainStorageNode> * idBST;
	BST<std::string, MainStorageNode> * titleBriefBST;
	BST<std::string, MainStorageNode> * titleFullBST;
	BST<std::string, MainStorageNode> ** titleBST;
	BST<int, MainStorageNode> * yearBST;
	BST<double, MainStorageNode> * ratingBST;
	BST<std::string, MainStorageNode>** genreBST;
public:
	MainStorage();

	unsigned int size() const;

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
	std::string insert(std::string title, int year, double rating, std::string description, unsigned int &operations);

	/** inserts new movie node into storage.
	Adds searchable attributes to a BST.
	@pre None
	@post Movie node added to storage
	@param nodePtr Movie node
	@return ID of movie
	*/
	std::string insert(MainStorageNode* nodePtr, unsigned int &operations);

	/** removes movie node from storage.
	romoves searchable attributes from all BST.
	@pre None
	@post Movie node removed from storage
	@param movieKey movie key
	@return true on success, false on failure or not found
	*/
	bool remove(std::string movieKey, unsigned int &operations);
	bool remove(MainStorageNode* nodePtr, unsigned int &operations);

	bool update(MainStorageNode* nodePtr);
	MainStorageNode* getNode(std::string ID);
	HashMap <MainStorageNode*>* getTable();
	BST<std::string, MainStorageNode>* getMovieTitleBST();

	/* find methods
	These are the methods that should be used in the UI for searching
	*/
	/** searches for movie nodes by the hash table key (should only return one) */
	SearchResult<List<MainStorageNode*>*>* keyFind(std::string searchStr);
	/** searches for movie nodes matching the theMovieDBId (should only return one) */
	SearchResult<List<MainStorageNode*>*>* idFind(int searchInt);
	SearchResult<List<MainStorageNode*>*>* titleFind(std::string title);
	SearchResult<List<MainStorageNode*>*>* yearFind(int searchInt);
	SearchResult<List<MainStorageNode*>*>* titleYearFind(std::string title, int year);
	SearchResult<List<MainStorageNode*>*>* ratingFind(double rating);
	SearchResult<List<MainStorageNode*>*>* genreFind(std::string genre);

	/** finds the intersection between two result lists
	@pre None
	@post data node pointers pushed into listPtrResult
	@param listPtr1 list #1
	@param listPtr2 list #2
	@param listPtrResult common nodes in listPtr1 and listPtr2
	@return true on success, false on failure or not found */
	static bool intersection(List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult, unsigned int &operations);
	static bool mergeUnique(List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtrResult, unsigned int &operations);

	// list methods
	void listTitle(std::function<std::string(MainStorageNode*)>* visit, std::string &log);

	/* visit and access methods
	We define methods on how to access certain data attributes inside the movie node
	this makes the BST more portable and reusable rather than hard coding attribute locations
	*/
	static std::string visit(MainStorageNode* nodePtr);
	static std::string visitTitleList(MainStorageNode* nodePtr);
	static int MainStorage::accessId(MainStorageNode* nodePtr);
	static std::string MainStorage::accessTitle(MainStorageNode* nodePtr);
	static std::string MainStorage::accessTitleBrief(MainStorageNode* nodePtr);
	static std::string MainStorage::accessTitleFull(MainStorageNode* nodePtr);
	static std::function<std::string(MainStorageNode*)>* MainStorage::accessTitleList(int index);
	static std::string MainStorage::accessTitleListIndex(MainStorageNode* nodePtr, int index);
	static int MainStorage::accessYear(MainStorageNode* nodePtr);
	static double MainStorage::accessRating(MainStorageNode* nodePtr);
	static std::function<std::string(MainStorageNode*)>* MainStorage::accessGenre(int index);
	static std::string accessGenreIndex(MainStorageNode* nodePtr, int index);
};

#endif