#include "MainStorage.h"

MainStorage::MainStorage ()
{
	/* nodes in the map */
	size = 0;
}
/*
@pre None
@post Movie node added to
@param title Movie title
@param content_rating Movie audience rating
@param rating Movie critic rating score 1-10
@param year Movie year made
@param genre Movie IMDB first genre
@param description Movie description
@return Position of inserted movie node. -1 on failure
*/
std::string MainStorage::insert (std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	storageMap[toID (title, year)] = new MainStorageNode (title, year, content_rating, rating, genre, description);
	return toID (title, year);
}
bool MainStorage::update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	return false;
}
MainStorageNode* MainStorage::getNode (std::string ID)
{
	return storageMap[ID];
}
bool MainStorage::remove (std::string ID)
{
	storageMap.erase (ID);
	return true;
}

/*
@pre
@post
@param title Movie title
@param year Movie year made
@return
*/
std::string MainStorage::toID (std::string title, int year)
{
	std::replace (title.begin (), title.end (), ' ', '_');
	for (std::size_t i = 0; i < title.size (); ++i)
		while (!std::isalnum (title[i]) && i < title.size ()) title.erase (i, 1);
	return title + "_" + std::to_string(year);
}

std::string MainStorage::visit (MainStorageNode* nodePtr)
{
	// string stream would also work for non-string data
	std::stringstream ss;
	ss << nodePtr->getTitle () << std::endl << nodePtr->getYear () << std::endl;
	return ss.str ();
}

bool MainStorage::titleFind (std::string title, List<MainStorageNode*>* listPtr, int &operations)
{
	return titleBST->find (title, listPtr, MainStorage::accessTitle, operations);
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
	return genre1BST->find (genre, listPtr, MainStorage::accessGenre1, operations);
}
bool MainStorage::genre2Find (std::string genre, List<MainStorageNode*>* listPtr, int &operations)
{
	return genre2BST->find (genre, listPtr, MainStorage::accessGenre2, operations);
}

/** finds the intersection between two result lists
@pre None
@post data node pointers pushed into listPtrResult
@param listPtr1 list #1
@param listPtr2 list #2
@param listPtrResult common nodes in listPtr1 and listPtr2
@return true on success, false on failure or not found */
bool MainStorage::intersection (List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult)
{
	return false;
}

std::string MainStorage::accessTitle (MainStorageNode* nodePtr)
{
	return nodePtr->getTitle ();
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
	return nodePtr->getGenre1 ();
}
std::string MainStorage::accessGenre2 (MainStorageNode* nodePtr)
{
	return nodePtr->getGenre2 ();
}
