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
	storageMap = new HashMap <MainStorageNode*> (maxItems);
	titleBriefBST = new BST<std::string, MainStorageNode>;
	titleBST = new BST<std::string, MainStorageNode>*[titleIndexes];
	for (int i = 0; i < titleIndexes; i++)
		titleBST[i] = new BST<std::string, MainStorageNode>;
	yearBST = new BST<int, MainStorageNode>;
	ratingBST = new BST<double, MainStorageNode>;
	genreBST = new BST<std::string, MainStorageNode>*[genreSize];
	for (int i = 0; i < genreSize; i++)
		genreBST[i] = new BST<std::string, MainStorageNode>;
	/* nodes in the map */
	itemCount = 0;
}

unsigned int MainStorage::size () const
{
	return storageMap->size();
}

std::string MainStorage::insert (std::string title, int year, double rating, std::string description)
{
	return insert (new MainStorageNode (title, year, rating, description));
}

std::string MainStorage::insert (MainStorageNode* nodePtr)
{
	int i, n, pos;
	std::string movieKey = StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ());
	/* first, check if the movie already exists
	-1 means the key is not present */
	pos = storageMap->find (movieKey);
	if (pos < 0)
	{
		storageMap->insert (movieKey, nodePtr);
		// stores a shortened title for testing purposes
		titleBriefBST->add (nodePtr, MainStorage::accessTitleBrief);
		/* In the future it would be more convenient and elegant
		to use the subscript operator to make the assignment
		(*storageMap)[StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ())] = nodePtr;
		*/
		/* title is split by spaces for a full text search
		entities must be at least 3 characters long and
		must be alphanumeric */
		List<std::string>* titleListPtr = nodePtr->getTitleList ();
		n = (titleIndexes < titleListPtr->size () ? titleIndexes : titleListPtr->size ());
		for (i = 0; i < n; i++)
		{
			titleBST[i]->add (nodePtr, MainStorage::accessTitleList (i));
			//std::cout << "i=" << i << " VALUE: " << (*accessTitleList (i))(nodePtr) << std::endl;
		}
		yearBST->add (nodePtr, MainStorage::accessYear);
		ratingBST->add (nodePtr, MainStorage::accessRating);
		List<std::string>* genreListPtr = nodePtr->getGenreList ();
		n = (genreSize < genreListPtr->size () ? genreSize : genreListPtr->size ());
		for (i = 0; i < n; i++)
			genreBST[i]->add (nodePtr, MainStorage::accessGenre (i));
	}
	return movieKey;
}

bool MainStorage::remove (std::string movieKey)
{
	MainStorageNode* nodePtr = storageMap->at (movieKey);
	return remove(nodePtr);
}

bool MainStorage::remove (MainStorageNode* nodePtr)
{
	bool flag = false;
	int i, n, pos;
	std::string movieKey = StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ());
	/* first, check if the movie already exists
	-1 means the key is not present */
	pos = storageMap->find (movieKey);
	if (pos >= 0)
	{
		storageMap->remove (nodePtr);
		titleBriefBST->remove (nodePtr, MainStorage::accessTitleBrief);
		// title indexes removal
		List<std::string>* titleListPtr = nodePtr->getTitleList ();
		n = (titleIndexes < titleListPtr->size () ? titleIndexes : titleListPtr->size ());
		for (i = 0; i < n; i++)
		{
			titleBST[i]->remove (nodePtr, MainStorage::accessTitleList (i));
		}
		// year and rating index removval
		yearBST->remove (nodePtr, MainStorage::accessYear);
		ratingBST->remove (nodePtr, MainStorage::accessRating);
		// genre indexes removal
		List<std::string>* genreListPtr = nodePtr->getGenreList ();
		n = (genreSize < genreListPtr->size () ? genreSize : genreListPtr->size ());
		for (i = 0; i < n; i++)
			genreBST[i]->remove (nodePtr, MainStorage::accessGenre (i));
		flag = true;
	}
	return flag;
}

bool MainStorage::update (MainStorageNode* nodePtr)
{
	return false;
}
MainStorageNode* MainStorage::getNode (std::string ID)
{
	return storageMap->at (ID);
}
HashMap <MainStorageNode*>* MainStorage::getTable ()
{
	return storageMap;
}

BST<std::string, MainStorageNode>* MainStorage::getMovieTitleBST ()
{
	return titleBriefBST;
}

//******************************************************
// FIND METHODS
//******************************************************
bool MainStorage::titleFind (std::string title, List<MainStorageNode*>* listPtr, int &operations)
{
	std::string log = "";
	bool flag = false;
	bool flagTemp = false;
	List<MainStorageNode*>* listPtrCurrent = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrIntersectPrev = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrIntersectCurrent = new List<MainStorageNode*>;
	/* each title term is searched and intersected.
	This leads to quite an operationally expensive search, but is comprehensive */
	List<std::string>* titleList = StringHelper::split (StringHelper::toLower (StringHelper::sanitize255 (title)), " ");
	unsigned int i, j, n;
	n = titleList->size ();
	for (i = 0; i < n; i++)
	{
		if ((*titleList)[i].length () >= 3)
		{
			listPtr->clear ();
			for (j = 0; j < titleIndexes; j++)
			{
				//std::cout << "j=" << j << std::endl;
				/* We go through each sub result set of nodes
				case insensitive, but words must be exact */
				//titleBST[j]->visitLogInorder (visitTitleList, log);
				flagTemp = titleBST[j]->find ((*titleList)[i], listPtrCurrent, accessTitleList (j), operations);
				// merge unique sub result movie nodes into the final result of movie nodes
				MainStorage::mergeUnique (listPtrCurrent, listPtr, operations);
				listPtrCurrent->clear ();
				if (flagTemp) flag = true;
			}
			// intersects result nodes of current and previous title term searches 
			if (!listPtrIntersectPrev->empty ())
			{
				MainStorage::intersection (listPtrIntersectPrev, listPtr, listPtrIntersectCurrent, operations);
				listPtr->clear ();
				listPtr->copy (listPtrIntersectCurrent);
				listPtrIntersectCurrent->clear ();
			}
			listPtrIntersectPrev->copy (listPtr);
		}
	}
	return flag;
}
bool MainStorage::yearFind (int year, List<MainStorageNode*>* listPtr, int &operations)
{
	return yearBST->find (year, listPtr, MainStorage::accessYear, operations);
}

bool MainStorage::titleYearFind (std::string title, int year, List<MainStorageNode*>* listPtr, int &operations)
{
	bool flag = false;
	List<MainStorageNode*>* listPtr1 = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtr2 = new List<MainStorageNode*>;
	if (titleFind (title, listPtr1, operations) && yearFind (year, listPtr2, operations))
	{
		flag = true;
	}
	intersection (listPtr1, listPtr2, listPtr, operations);
	delete listPtr1;
	delete listPtr2;
	return flag;
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
		unsigned int n = listPtrResult->size ();
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

std::string MainStorage::visitTitleList (MainStorageNode* nodePtr)
{
	std::stringstream ss;
	List<std::string>* titleList = nodePtr->getTitleList ();
	int n = titleList->size ();
	ss << "Title Terms: ";
	for (int i = 0; i < n; i++)
	{
		ss << (*accessTitleList (i))(nodePtr) << " ";
	}
	ss << "\n";
	//std::cout << ss.str ();
	return ss.str ();
}

std::string MainStorage::accessTitle (MainStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getTitle ());
}

std::string MainStorage::accessTitleBrief (MainStorageNode* nodePtr)
{
	// don't lower case. already lower cased and "safe"
	return nodePtr->getTitleList (0).substr(0,5);
}

std::function<std::string (MainStorageNode*)>* MainStorage::accessTitleList (int index)
{
	return new std::function<std::string (MainStorageNode*)> (std::bind (&accessTitleListIndex, std::placeholders::_1, index));
}

std::string MainStorage::accessTitleListIndex (MainStorageNode* nodePtr, int index)
{
	// don't lower case. already indexed as lower case
	return nodePtr->getTitleList (index);
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
	return new std::function<std::string (MainStorageNode*)> (std::bind (&accessGenreIndex, std::placeholders::_1, index));
}

std::string MainStorage::accessGenreIndex (MainStorageNode* nodePtr, int index)
{
	// case insensitive
	return StringHelper::toLower (nodePtr->getGenre (index));
}
