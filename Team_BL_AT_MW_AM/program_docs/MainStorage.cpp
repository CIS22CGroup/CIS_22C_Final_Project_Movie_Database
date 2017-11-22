/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "MainStorage.h"

MainStorage::MainStorage ()
{
	storageMap = new std::map <std::string, MainStorageNode*> ();
	titleBST = new BST<std::string, MainStorageNode> ();
	yearBST = new BST<int, MainStorageNode>;
	ratingBST = new BST<double, MainStorageNode>;
	genre1BST = new BST<std::string, MainStorageNode>;
	genre2BST = new BST<std::string, MainStorageNode>;
	/* nodes in the map */
	size = 0;
}

std::string MainStorage::insert (std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	return insert(new MainStorageNode (title, year, content_rating, rating, genre, description));
}

std::string MainStorage::insert (MainStorageNode* nodePtr)
{
	(*storageMap)[StringHelper::toID (nodePtr->getTitle(), nodePtr->getYear())] = nodePtr;
	//(*storageMap)[nodePtr->getTitle ()] = nodePtr;
	// add node to the BST
	titleBST->add (nodePtr, MainStorage::accessTitle);
	yearBST->add (nodePtr, MainStorage::accessYear);
	ratingBST->add (nodePtr, MainStorage::accessRating);
	genre1BST->add (nodePtr, MainStorage::accessGenre1);
	genre2BST->add (nodePtr, MainStorage::accessGenre2);
	//return nodePtr->getTitle ();
	return StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ());
}

bool MainStorage::update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	return false;
}
MainStorageNode* MainStorage::getNode (std::string ID)
{
	return (*storageMap)[ID];
}
bool MainStorage::remove (std::string ID)
{
	storageMap->erase (ID);
	return true;
}

//******************************************************
// FIND METHODS
//******************************************************
bool MainStorage::titleFind (std::string title, List<MainStorageNode*>* listPtr, int &operations)
{
	// case insensitive, but words must be exact
	return titleBST->find (StringHelper::toLower(title), listPtr, MainStorage::accessTitle, operations);
}
bool MainStorage::yearFind (int year, List<MainStorageNode*>* listPtr, int &operations)
{
	return yearBST->find (year, listPtr, MainStorage::accessYear, operations);
}
bool MainStorage::ratingFind (double rating, List<MainStorageNode*>* listPtr, int &operations)
{
	return ratingBST->find (rating, listPtr, MainStorage::accessRating, operations);
}
bool MainStorage::genre1Find (std::string genre, List<MainStorageNode*>* listPtr, int &operations)
{
	// case insensitive, but words must be exact
	return genre1BST->find (StringHelper::toLower (genre), listPtr, MainStorage::accessGenre1, operations);
}
bool MainStorage::genre2Find (std::string genre, List<MainStorageNode*>* listPtr, int &operations)
{
	// case insensitive, but words must be exact
	return genre2BST->find (StringHelper::toLower (genre), listPtr, MainStorage::accessGenre2, operations);
}

bool MainStorage::intersection (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult)
{
	return false;
}

//******************************************************
// VISIT AND ACCESS METHODS
//******************************************************
std::string MainStorage::visit (MainStorageNode* nodePtr)
{
	// string stream would also work for non-string data
	std::stringstream ss;
	ss << nodePtr->getTitle () << std::endl << nodePtr->getYear () << std::endl;
	return ss.str ();
}

std::string MainStorage::accessTitle (MainStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getTitle ());
}

int MainStorage::accessYear (MainStorageNode* nodePtr)
{
	return nodePtr->getYear ();
}

double MainStorage::accessRating (MainStorageNode* nodePtr)
{
	return nodePtr->getRating ();
}

std::string MainStorage::accessGenre1(MainStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getGenre1 ());
}
std::string MainStorage::accessGenre2 (MainStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getGenre2 ());
}
