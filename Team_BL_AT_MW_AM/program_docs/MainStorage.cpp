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
#include "MainStorage.h"

MainStorage::MainStorage()
{
	storageMap = new HashMap <MainStorageNode*>(maxItems);
	idBST = new BST<int, MainStorageNode>;
	titleBriefBST = new BST<std::string, MainStorageNode>;
	titleFullBST = new BST<std::string, MainStorageNode>;
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
	operationsTotal = operationsInsert = operationsFind = operationsDelete = 0;
}

unsigned int MainStorage::size() const
{
	return storageMap->size();
}

std::string MainStorage::insert(std::string title, int year, double rating, std::string description, unsigned int &operations)
{
	return insert(new MainStorageNode(title, year, rating, description), operations);
}

std::string MainStorage::insert(MainStorageNode* nodePtr, unsigned int &operations)
{
	unsigned int i, n, n1, n2;
	int pos; // may be -1 for not found
	std::string movieKey = StringHelper::toID(nodePtr->getTitle(), nodePtr->getYear());
	/* first, check if the movie already exists
	-1 means the key is not present */
	pos = storageMap->find(movieKey, operations);
	if (pos < 0)
	{
		storageMap->insert(movieKey, nodePtr, operations);
		idBST->add(nodePtr, MainStorage::accessId, operations);
		titleFullBST->add(nodePtr, MainStorage::accessTitleFull, operations);
		/* In the future it would be more convenient and elegant
		to use the subscript operator to make the assignment
		(*storageMap)[StringHelper::toID (nodePtr->getTitle (), nodePtr->getYear ())] = nodePtr;
		*/
		/* title is split by spaces for a full text search
		entities must be at least 3 characters long and
		must be alphanumeric */
		List<std::string>* titleListPtr = nodePtr->getTitleList();
		n1 = titleListPtr->size();
		n = (titleIndexes < n1 ? titleIndexes : n1);
		/* stores a shortened title for testing purposes
		sometimes short movie titles will be reduced for nothing after sanitization*/
		if (n1 > 0) {
			titleBriefBST->add(nodePtr, MainStorage::accessTitleBrief, operations);
		}
		for (i = 0; i < n; i++)
		{
			titleBST[i]->add(nodePtr, MainStorage::accessTitleList(i), operations);
			//std::cout << "i=" << i << " VALUE: " << (*accessTitleList (i))(nodePtr) << std::endl;
		}
		yearBST->add(nodePtr, MainStorage::accessYear, operations);
		ratingBST->add(nodePtr, MainStorage::accessRating, operations);
		List<std::string>* genreListPtr = nodePtr->getGenreList();
		n2 = genreListPtr->size();
		n = (genreSize < n2 ? genreSize : n2);
		for (i = 0; i < n; i++)
			genreBST[i]->add(nodePtr, MainStorage::accessGenre(i), operations);
	}
	// operations stats
	operationsTotal += operations;
	operationsInsert += operations;
	return movieKey;
}

bool MainStorage::remove(std::string movieKey, unsigned int &operations)
{
	MainStorageNode* nodePtr = storageMap->at(movieKey);
	return remove(nodePtr, operations);
}

bool MainStorage::remove(MainStorageNode* nodePtr, unsigned int &operations)
{
	bool flag = false;
	unsigned int i, n, n1, n2;
	int pos;
	std::string movieKey = StringHelper::toID(nodePtr->getTitle(), nodePtr->getYear());
	/* first, check if the movie already exists
	-1 means the key is not present */
	pos = storageMap->find(movieKey, operations);
	if (pos >= 0)
	{
		idBST->remove(nodePtr);
		titleFullBST->remove(nodePtr);
		// title indexes removal
		List<std::string>* titleListPtr = nodePtr->getTitleList();
		n1 = titleListPtr->size();
		n = (titleIndexes < n1 ? titleIndexes : n1);
		for (i = 0; i < n; i++)
		{
			titleBST[i]->remove(nodePtr);
		}
		// year and rating index removal
		yearBST->remove(nodePtr);
		ratingBST->remove(nodePtr);
		// genre indexes removal
		List<std::string>* genreListPtr = nodePtr->getGenreList();
		n2 = genreListPtr->size();
		n = (genreSize < n2 ? genreSize : n2);
		titleBriefBST->remove(nodePtr);
		for (i = 0; i < n; i++)
			genreBST[i]->remove(nodePtr);
		// done last because removing from BST still requires movie node to exist
		storageMap->remove(nodePtr, operations);
		delete nodePtr;
		flag = true;
	}
	// operations stats
	operationsTotal += operations;
	operationsDelete += operations;
	return flag;
}

bool MainStorage::update(MainStorageNode* nodePtr)
{
	return false;
}
MainStorageNode* MainStorage::getNode(std::string ID)
{
	return storageMap->at(ID);
}
HashMap <MainStorageNode*>* MainStorage::getTable()
{
	return storageMap;
}

BST<std::string, MainStorageNode>* MainStorage::getMovieTitleBST()
{
	return titleBriefBST;
}

//******************************************************
// FIND METHODS
//******************************************************
SearchResult<List<MainStorageNode*>*>* MainStorage::keyFind(std::string searchStr)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	int operations, executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	MainStorageNode* nodePtr;
	operations = 0;
	executionTime = 0;
	/* search for the node matching the key
	made some weird design choice that throws an exception
	if the key is not found. */
	try {
		nodePtr = storageMap->at(searchStr);
		listPtr->push_back(nodePtr);
	}
	catch (const std::exception& e)
	{
		e.what();
	}
	operations++;
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}


SearchResult<List<MainStorageNode*>*>* MainStorage::idFind(int searchInt)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	operations = 0;
	executionTime = 0;
	// search
	idBST->find(searchInt, listPtr, MainStorage::accessId, operations);
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}

SearchResult<List<MainStorageNode*>*>* MainStorage::titleFind(std::string title)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrCurrent = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrIntersectPrev = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrIntersectCurrent = new List<MainStorageNode*>;
	operations = 0;
	executionTime = 0;
	/* each title term is searched and intersected.
	This leads to quite an operationally expensive search, but is comprehensive */
	List<std::string>* titleList = StringHelper::split(StringHelper::toLower(StringHelper::sanitize255(title)), " ");
	unsigned int i, j, n;
	n = titleList->size();
	for (i = 0; i < n; i++)
	{
		if ((*titleList)[i].length() >= 3)
		{
			listPtr->clear();
			for (j = 0; j < titleIndexes; j++)
			{
				//std::cout << "j=" << j << std::endl;
				/* We go through each sub result set of nodes
				case insensitive, but words must be exact */
				//titleBST[j]->visitLogInorder (visitTitleList, log);
				titleBST[j]->find((*titleList)[i], listPtrCurrent, accessTitleList(j), operations);
				// merge unique sub result movie nodes into the final result of movie nodes
				MainStorage::mergeUnique(listPtrCurrent, listPtr, operations);
				listPtrCurrent->clear();
			}
			// intersects result nodes of current and previous title term searches 
			if (!listPtrIntersectPrev->empty())
			{
				MainStorage::intersection(listPtrIntersectPrev, listPtr, listPtrIntersectCurrent, operations);
				listPtr->clear();
				listPtr->copy(listPtrIntersectCurrent);
				listPtrIntersectCurrent->clear();
			}
			listPtrIntersectPrev->copy(listPtr);
		}
	}
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}
SearchResult<List<MainStorageNode*>*>* MainStorage::yearFind(int searchInt)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	operations = 0;
	executionTime = 0;
	// search
	yearBST->find(searchInt, listPtr, MainStorage::accessYear, operations);
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}

SearchResult<List<MainStorageNode*>*>* MainStorage::titleYearFind(std::string title, int year)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtr1;
	List<MainStorageNode*>* listPtr2;
	SearchResult<List<MainStorageNode*>*>* titleSearchResultPtr;
	SearchResult<List<MainStorageNode*>*>* yearSearchResultPtr;
	operations = 0;
	executionTime = 0;
	// searches
	titleSearchResultPtr = titleFind(title);
	yearSearchResultPtr = yearFind(year);
	// search results
	listPtr1 = titleSearchResultPtr->getResults();
	operations += titleSearchResultPtr->getOperations();
	executionTime += titleSearchResultPtr->getExecutionTime();
	listPtr2 = yearSearchResultPtr->getResults();
	operations += yearSearchResultPtr->getOperations();
	executionTime += yearSearchResultPtr->getExecutionTime();
	// intersect results
	intersection(listPtr1, listPtr2, listPtr, operations);
	delete listPtr1;
	delete listPtr2;
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// clock, clean-up, and return
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	delete titleSearchResultPtr;
	delete yearSearchResultPtr;
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}
SearchResult<List<MainStorageNode*>*>* MainStorage::ratingFind(double rating)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	operations = 0;
	executionTime = 0;
	// search
	ratingBST->find(rating, listPtr, MainStorage::accessRating, operations);
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}
SearchResult<List<MainStorageNode*>*>* MainStorage::genreFind(std::string genre)
{
	// init vars
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned int operations;
	int executionTime;
	List<MainStorageNode*>* listPtr = new List<MainStorageNode*>;
	List<MainStorageNode*>* listPtrCurrent = new List<MainStorageNode*>;
	operations = 0;
	executionTime = 0;
	// search
	for (int i = 0; i < genreSize; i++)
	{
		/* We go through each sub result set of nodes
		case insensitive, but words must be exact */
		genreBST[i]->find(StringHelper::toLower(genre), listPtrCurrent, accessGenre(i), operations);
		// merge unique sub result movie nodes into the final result of movie nodes
		MainStorage::mergeUnique(listPtrCurrent, listPtr, operations);
		listPtrCurrent->clear();
	}
	// operations stats
	operationsTotal += operations;
	operationsFind += operations;
	// search results
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	executionTime = (int)std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	return new SearchResult<List<MainStorageNode*>*>(listPtr, operations, executionTime);
}

bool MainStorage::intersection(List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtr2, List<MainStorageNode*>* listPtrResult, unsigned int &operations)
{
	unsigned int i, n1;
	n1 = listPtr1->size();
	operations += 3;
	for (i = 0; i < n1; i++)
	{
		operations++;
		// list2 contains value, but resultList does not
		if (listPtr2->find((*listPtr1)[i], operations) && !listPtrResult->find((*listPtr1)[i], operations))
		{
			listPtrResult->push_back((*listPtr1)[i]);
		}
	}
	return false;
}

bool MainStorage::mergeUnique(List<MainStorageNode*>* listPtr1, List<MainStorageNode*>* listPtrResult, unsigned int &operations)
{
	unsigned int i, n1;
	n1 = listPtr1->size();
	operations += 3;
	for (i = 0; i < n1; i++)
	{
		operations++;
		// resultList does not contain
		unsigned int n = listPtrResult->size();
		if (!listPtrResult->find((*listPtr1)[i], operations))
		{
			listPtrResult->push_back((*listPtr1)[i]);
		}
	}
	return false;
}

//******************************************************
// LIST METHODS
//******************************************************
void MainStorage::listTitle(std::function<std::string(MainStorageNode*)>* visit, std::string &log) {
	titleFullBST->visitLogInorder(visit, log);
}

//******************************************************
// VISIT AND ACCESS METHODS
//******************************************************
std::string MainStorage::visit(MainStorageNode* nodePtr)
{
	// string stream would also work for non-string data
	std::stringstream ss;
	ss << nodePtr->getTitle() << std::endl << nodePtr->getYear() << std::endl;
	return ss.str();
}

std::string MainStorage::visitTitleList(MainStorageNode* nodePtr)
{
	std::stringstream ss;
	List<std::string>* titleList = nodePtr->getTitleList();
	int n = titleList->size();
	ss << "Title Terms: ";
	for (int i = 0; i < n; i++)
	{
		ss << (*accessTitleList(i))(nodePtr) << " ";
	}
	ss << "\n";
	//std::cout << ss.str ();
	return ss.str();
}

int MainStorage::accessId(MainStorageNode* nodePtr)
{
	return nodePtr->getTheMovieDBId();
}

std::string MainStorage::accessTitle(MainStorageNode* nodePtr)
{
	// case insensitive
	return StringHelper::toLower(nodePtr->getTitle());
}

std::string MainStorage::accessTitleBrief(MainStorageNode* nodePtr)
{
	// don't lower case. already lower cased and "safe"
	return nodePtr->getTitleList(0).substr(0, 5);
}

std::string MainStorage::accessTitleFull(MainStorageNode* nodePtr)
{
	return nodePtr->getTitle();
}

std::function<std::string(MainStorageNode*)>* MainStorage::accessTitleList(unsigned int index)
{
	return new std::function<std::string(MainStorageNode*)>(std::bind(&accessTitleListIndex, std::placeholders::_1, index));
}

std::string MainStorage::accessTitleListIndex(MainStorageNode* nodePtr, unsigned int index)
{
	// don't lower case. already indexed as lower case
	return nodePtr->getTitleList(index);
}

int MainStorage::accessYear(MainStorageNode* nodePtr)
{
	return nodePtr->getYear();
}

double MainStorage::accessRating(MainStorageNode* nodePtr)
{
	return nodePtr->getRating();
}

std::function<std::string(MainStorageNode*)>* MainStorage::accessGenre(unsigned int index)
{
	return new std::function<std::string(MainStorageNode*)>(std::bind(&accessGenreIndex, std::placeholders::_1, index));
}

std::string MainStorage::accessGenreIndex(MainStorageNode* nodePtr, unsigned int index)
{
	// case insensitive
	return StringHelper::toLower(nodePtr->getGenre(index));
}
