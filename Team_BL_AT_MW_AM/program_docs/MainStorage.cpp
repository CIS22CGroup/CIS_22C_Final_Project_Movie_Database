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
	storageMap = new HashMap <MainStorageNode*> (86969);
	titleBST = new BST<std::string, MainStorageNode>;
	yearBST = new BST<int, MainStorageNode>;
	ratingBST = new BST<double, MainStorageNode>;
	genreBST = new BST<std::string, MainStorageNode>*[genreSize];
	for (int i = 0; i < genreSize; i++)
		genreBST[i] = new BST<std::string, MainStorageNode>;
	/* nodes in the map */
	size = 0;
}

std::string MainStorage::insert (std::string title, int year, std::string content_rating, double rating, std::string description)
{
	return insert (new MainStorageNode (title, year, 0, rating, description));
}

std::string MainStorage::insert (MainStorageNode* nodePtr)
{
	storageMap->insert (StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ()), nodePtr);
	//(*storageMap)[nodePtr->getTitle ()] = nodePtr;
	// add node to the BST
	titleBST->add (nodePtr, MainStorage::accessTitle);
	yearBST->add (nodePtr, MainStorage::accessYear);
	ratingBST->add (nodePtr, MainStorage::accessRating);
	for (int i = 0; i < genreSize; i++)
		genreBST[i]->add (nodePtr, MainStorage::accessGenre (i));
	//return nodePtr->getTitle ();
	return StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ());
}

bool MainStorage::update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	return false;
}
MainStorageNode* MainStorage::getNode (std::string ID)
{
	return storageMap->at (ID);
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
	return titleBST->find (StringHelper::toLower (title), listPtr, MainStorage::accessTitle, operations);
}
bool MainStorage::yearFind (int year, List<MainStorageNode*>* listPtr, int &operations)
{
	return yearBST->find (year, listPtr, MainStorage::accessYear, operations);
}
bool MainStorage::ratingFind (double rating, List<MainStorageNode*>* listPtr, int &operations)
{
	return ratingBST->find (rating, listPtr, MainStorage::accessRating, operations);
}
bool MainStorage::genreFind (std::string genre, List<MainStorageNode*>* listPtr, int &operations)
{
	bool flag = false;
	bool flagTemp = false;
	List<MainStorageNode*>* listPtrCurrent = new List<MainStorageNode*>;
	for (int i = 0; i < genreSize; i++)
	{
		/* We go through each sub result set of nodes
		case insensitive, but words must be exact */
		flagTemp = genreBST[i]->find (StringHelper::toLower (genre), listPtrCurrent, accessGenre (i), operations);
		// merge unique sub result movie nodes into the final result of movie nodes
		MainStorage::mergeUnique (listPtrCurrent, listPtr, operations);
		listPtrCurrent->clear ();
		if (flagTemp) flag = true;
	}
	return flag;
}

bool MainStorage::intersection (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult, int &operations)
{
	unsigned int i, n1;
	n1 = listPtr1->size ();
	operations += 3;
	for (i = 0; i < n1; i++)
	{
		operations++;
		// list2 contains value, but resultList does not
		if (listPtr2->find ((*listPtr1)[i], operations) && !listPtrResult->find ((*listPtr1)[i], operations))
		{
			listPtrResult->push_back ((*listPtr1)[i]);
		}
	}
	return false;
}

bool MainStorage::mergeUnique (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtrResult, int &operations)
{
	unsigned int i, n1;
	n1 = listPtr1->size ();
	operations += 3;
	for (i = 0; i < n1; i++)
	{
		operations++;
		// resultList does not contain
		if (!listPtrResult->find ((*listPtr1)[i], operations))
		{
			listPtrResult->push_back ((*listPtr1)[i]);
		}
	}
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

std::function<std::string (MainStorageNode*)>* MainStorage::accessGenre (int index)
{
	return new std::function<std::string (MainStorageNode*)>(std::bind (&accessGenreIndex, std::placeholders::_1, index));
}

std::string MainStorage::accessGenreIndex (MainStorageNode* nodePtr, int index)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getGenre (index));
}
