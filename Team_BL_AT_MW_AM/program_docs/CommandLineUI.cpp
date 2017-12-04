/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#include "commandLineUI.h"

MainStorage* CommandLineUI::mainStoragePtr;

void CommandLineUI::enterLoop()
{
	MovieWebDB::genreTableInit();
	mainStoragePtr = new MainStorage;
	int menuOption;
	std::cout << "Welcome to the Movie Database, made by Branden Lee, Alex Morfin, Ann Truong, and Michael Wu";
	bool loopActive = true;
	while (loopActive)
	{
		std::cout << "Please enter the number representing the menu options below:" << std::endl
			<< "1. Search movie from the web by title" << std::endl
			<< "2. Search movie from the web by title and year" << std::endl
			<< "3. Import Movie Storage File" << std::endl
			<< "4. Export Movie Storage File" << std::endl
			<< "5. Search Movie Locally by title" << std::endl
			<< "6. Search Movie Locally by year" << std::endl
			// required to Find and display one data record using the primary key
			<< "7. Search Movie Locally by title and year" << std::endl
			//<< "6. Search Movie Locally by rating" << std::endl
			<< "8. Search Movie Locally by genre" << std::endl
			<< "9. Add Movie" << std::endl
			/* requires Complete demonstration of all options of the menu.
			The demonstration must include collision resolution
			and deletion of the root (it should have two children). */
			<< "10. Delete Movie by movie ID or movie key" << std::endl
			// required to Find and display one data record using the primary key
			<< "11. Find Movie by movie ID or movie key" << std::endl
			<< "12. Print Movie Title BST" << std::endl
			<< "13. Hash Table Statistics" << std::endl
			<< "20. Exit Program" << std::endl << std::endl
			<< "Selection Number: ";
		std::cin >> menuOption;
		if (std::cin.fail())
		{
			std::cin.clear(); // clears failure state
			std::cin.ignore(999, '\n'); // discards "bad" characters
			//std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n'); // discards "bad" characters
			menuOption = 0;
		}
		std::cout << std::endl;
		if (menuOption < 1 || menuOption > 20)
		{
			std::cout << "************************************" << std::endl;
			std::cout << "Your selection was not valid. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
		}
		else
		{
			/* please keep each sub-menu in a separate function to increase readability and prevent
			a huge blob of unorganized code. */
			if (menuOption == 1) WebSearchTitle();
			else if (menuOption == 2) WebSearchTitleYear();
			else if (menuOption == 3) StorageFileImport();
			else if (menuOption == 4) StorageFileExport();
			else if (menuOption == 5) LocalSearchTitle();
			else if (menuOption == 6) LocalSearchYear();
			else if (menuOption == 7) LocalSearchTitleYear();
			//else if (menuOption == 6) LocalSearchRating ();
			else if (menuOption == 8) LocalSearchGenre();
			else if (menuOption == 9) addMovie();
			else if (menuOption == 10) deleteMovie();
			else if (menuOption == 11) findMovie();
			else if (menuOption == 12) printMovieTitleBST();
			else if (menuOption == 13) HashMapStats();
			//else if (menuOption == 12) HashMapTest ();
			else if (menuOption == 20) loopActive = false;
		}
	}
}

void CommandLineUI::WebSearchTitle()
{
	std::string title;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	searchResultPtr = nullptr;
	std::cout << std::endl << "All search results are added to the local database!" << std::endl
		<< "Enter the title: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, title);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl << std::endl;
	/* Web searches may create many exceptions due to the unpredictability
	of the return data */
	try
	{
		searchResultPtr = MovieWebDB::find2(title, 0);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	// add results
	addResultHelper(searchResultPtr);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::WebSearchTitleYear()
{
	std::string title;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	int year;
	searchResultPtr = nullptr;
	std::cout << std::endl << "All search results are added to the local database!" << std::endl
		<< "Enter the title: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, title);
	std::cout << "Enter the year: ";
	std::cin >> year;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl
		<< "Year: " << year << std::endl << std::endl;
	/* Web searches may create many exceptions due to the unpredictability
	of the return data */
	try
	{
		searchResultPtr = MovieWebDB::find2(title, year);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	// add results
	addResultHelper(searchResultPtr);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::LocalSearchTitle()
{
	std::string searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << searchTerm << std::endl << std::endl;
	searchResultPtr = mainStoragePtr->titleFind(searchTerm);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::StorageFileImport()
{
	std::string filePath;
	bool flag = false;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Import Movie Database File" << std::endl
		<< "Enter the file path: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, filePath);
	std::cout << "Importing file...: " << std::endl
		<< "Path: " << filePath << std::endl << std::endl;
	// file import
	try
	{
		flag = FileIO::fileToMainStorage(mainStoragePtr, filePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	if (flag)
	{
		std::cout << "Movies Imported Successfully!" << std::endl;
		std::cout << "Total Movies cached: " << mainStoragePtr->size() << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::StorageFileExport()
{
	std::string filePath;
	bool flag = false;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Export Movie Database File" << std::endl
		<< "Enter the file path: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, filePath);
	std::cout << "Exporting file...: " << std::endl
		<< "Path: " << filePath << std::endl << std::endl;
	// file export
	try
	{
		flag = FileIO::mainStorageToFile(mainStoragePtr, filePath);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	if (flag)
	{
		std::cout << "Movies Exporteded Successfully!" << std::endl;
		std::cout << "Total Movies cached: " << mainStoragePtr->size() << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchYear()
{
	int searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the year: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::cin >> searchTerm;
	std::cout << "Searching for: " << std::endl
		<< "Year: " << std::to_string(searchTerm) << std::endl << std::endl;
	searchResultPtr = mainStoragePtr->yearFind(searchTerm);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::LocalSearchTitleYear()
{
	std::string searchTerm;
	int searchTerm2;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	std::cout << "Enter the year: ";
	std::cin >> searchTerm2;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << searchTerm << ", Year: " << searchTerm2 << std::endl << std::endl;
	searchResultPtr = mainStoragePtr->titleYearFind(searchTerm, searchTerm2);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::LocalSearchRating()
{
	double searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the rating: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::cin >> searchTerm;
	std::cout << "Searching for: " << std::endl
		<< "Rating: " << std::to_string(searchTerm) << std::endl << std::endl;
	searchResultPtr = mainStoragePtr->ratingFind(searchTerm);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::LocalSearchGenre()
{
	std::string searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the genre: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	std::cout << "Searching for: " << std::endl
		<< "Genre: " << searchTerm << std::endl << std::endl;
	searchResultPtr = mainStoragePtr->genreFind(searchTerm);
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
}

void CommandLineUI::addMovie()
{

}

void CommandLineUI::deleteMovie()
{
	std::string searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Delete Movie" << std::endl
		<< "Enter the movie ID or Hash Table Key: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	if (StringHelper::isNumeric(searchTerm)) {
		// search the term as the movie ID
		int targetID;
		targetID = std::stoi(searchTerm);
		std::cout << "Searching for and Deleteing: " << std::endl
			<< "Movie ID: " << targetID << std::endl << std::endl;
		searchResultPtr = mainStoragePtr->idFind(targetID);
	}
	else
	{
		// search the term as the hash table key
		std::cout << "Searching for and Deleteing: " << std::endl
			<< "Hash Table Key: " << searchTerm << std::endl << std::endl;
		searchResultPtr = mainStoragePtr->keyFind(searchTerm);
	}
}

void CommandLineUI::findMovie()
{

}

void CommandLineUI::printMovieTitleBST()
{
	BST<std::string, MainStorageNode>* titleBriefBST = mainStoragePtr->getMovieTitleBST();
	std::string log = "";
	titleBriefBST->logLevel(new std::function<std::string(MainStorageNode*)>(MainStorage::accessTitleBrief), log);
	std::cout << std::endl << "Title Name BST:" << std::endl;
	std::cout << log;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::HashMapStats()
{
	// variable declarations
	unsigned int i, n, hashId;
	HashMap <MainStorageNode*>* movieHashMapPtr;
	HashMapNode<MainStorageNode*>* movieHashMapNodePtr;
	List<std::string>* genreListPtr;
	std::string movieKey;
	MainStorageNode* movieNodePtr;
	double loadFactor;
	bool flagCollision;
	// headers
	std::cout << std::left << std::setw(17) << "Movie" << std::setw(5) << "Year" << std::setw(24) << "Key" << std::setw(5) << "Hash" << std::setw(9) << "Collision" << std::endl;
	// get the entire movie hash table
	movieHashMapPtr = mainStoragePtr->getTable();
	// custom iterator saves lots of nested loops
	HashMap <MainStorageNode*>::iterator it;
	HashMap <MainStorageNode*>::iterator itend = movieHashMapPtr->end();
	for (it = movieHashMapPtr->begin(); it != itend; it++)
	{
		// get the hash table nodes from the list
		movieHashMapNodePtr = it->getSelf();
		hashId = movieHashMapNodePtr->getId();
		flagCollision = movieHashMapNodePtr->isCollision();
		movieKey = movieHashMapNodePtr->getKey();
		movieNodePtr = movieHashMapNodePtr->getValue();
		std::cout << std::left << std::setw(17) << movieNodePtr->getTitle().substr(0, 16) << std::setw(5) << movieNodePtr->getYear()
			<< std::setw(24) << movieKey.substr(0, 23) << std::setw(5) << hashId << std::setw(9) << (flagCollision?"X":"") << std::endl;
	}
	// hash map statistics
	loadFactor = ((double)movieHashMapPtr->bucketsUsed() / (double)movieHashMapPtr->max_size()) * 100.00;
	std::cout << std::endl << "Hash Table Stats" << std::endl;
	std::cout << "Max Size: " << movieHashMapPtr->max_size() << std::endl;
	std::cout << "Load Factor: " << std::fixed << std::setprecision(0) << loadFactor << "%" << std::endl;
	std::cout << "Collision Count: " << movieHashMapPtr->collisions() << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::HashMapTest()
{
	unsigned int i, n, n1;
	n = 5;
	n1 = 6;
	std::string movieKey;
	int hash;
	double loadFactor;
	HashMap <std::string>* storageMap;
	storageMap = new HashMap <std::string>(n);
	std::string titleArray[] = { "SUPERMAN II","IRON MAN 3","SKY HIGH", "BATMAN","KICK-ASS", "X-MEN" };
	int yearArray[] = { 1981,2013,2005,1989,2010,2000 };
	std::cout << std::left << std::setw(14) << "Movie" << std::setw(5) << "Year" << std::setw(20) << "Key" << std::setw(5) << "Hash" << std::endl;
	for (i = 0; i < n1; i++)
	{
		movieKey = StringHelper::toID(titleArray[i], yearArray[i]);
		hash = StringHelper::hashStr(movieKey, n);
		std::cout << std::left << std::setw(14) << titleArray[i] << std::setw(5) << yearArray[i] << std::setw(20) << movieKey << std::setw(5) << hash << std::endl;
		storageMap->insert(movieKey, titleArray[i]);
	}
	loadFactor = ((double)storageMap->bucketsUsed() / (double)storageMap->max_size()) * 100.00;
	std::cout << std::endl << "Hash Table Stats" << std::endl;
	std::cout << "Max Size: " << storageMap->max_size() << std::endl;
	std::cout << "Load Factor: " << std::fixed << std::setprecision(0) << loadFactor << "%" << std::endl;
	std::cout << "Collision Count: " << storageMap->collisions() << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::addResultHelper(SearchResult<List<MainStorageNode*>*>* searchResultPtr)
{
	if (searchResultPtr)
	{
		unsigned int i, n1;
		List<MainStorageNode*>* nodeListPtr;
		nodeListPtr = searchResultPtr->getResults();
		n1 = nodeListPtr->size();
		for (i = 0; i < n1; i++)
		{
			mainStoragePtr->insert((*nodeListPtr)[i]);
		}
	}
}

void CommandLineUI::searchResultHelper(SearchResult<List<MainStorageNode*>*>* searchResultPtr)
{
	bool flag = false;
	if (searchResultPtr)
	{
		unsigned int i, n, n1, operations, executionTime;
		List<MainStorageNode*>* nodeListPtr;
		nodeListPtr = searchResultPtr->getResults();
		operations = searchResultPtr->getOperations();
		executionTime = searchResultPtr->getExecutionTime();
		n1 = nodeListPtr->size();
		n = resultsMax <= n1 ? resultsMax : n1;
		std::cout << "Operations Performed: " << operations << " in " << executionTime << " micro-seconds" << std::endl
			<< "Displaying Results: " << n << " of " << n1 << std::endl;
		std::cout << "Total Movies Cached: " << mainStoragePtr->size() << std::endl;
		if (n1 > 0)
		{
			flag = true;
			std::cout << "______________________________________________" << std::endl;
			for (i = 0; i < n; i++)
			{
				std::cout << (*nodeListPtr)[i];
				if (i != n - 1) std::cout << std::endl;
			}
			std::cout << "______________________________________________" << std::endl << std::endl;
		}
	}
	// result error or no results
	if (!flag)
	{
		std::cout << "______________________________________________" << std::endl;
		std::cout << "NO RESULTS FOUND" << std::endl;
		std::cout << "______________________________________________" << std::endl << std::endl;
	}
}

//******************************************************
// operator<<        
//******************************************************
std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj)
{
	os << "#" << obj->theMovieDBId << " Title: " << obj->title;
	if (obj->year > 0)
		os << ", Year: " << obj->year;
	if (obj->rating > 0)
		os << ", Rating: " << obj->rating;
	os << std::endl;
	int n = obj->genreListPtr->size();
	if (n > 0)
	{
		os << "Genre: ";
		for (int i = 0; i < n; i++)
		{
			os << obj->genreListPtr->getValue(i);
			if (i != n - 1) os << ", ";
		}
		os << std::endl;
	}
	// Trim Description length to 200 characters
	if (obj->description.length() > 200)
		os << "Description: " << obj->description.substr(0, 197) << "..." << std::endl;
	else if (obj->description.length() > 0)
		os << "Description: " << obj->description << std::endl;
	return os;
}

template <class T>
std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr)
{
	int n = ListPtr->size();
	for (int i = 0; i < n; i++)
	{
		foo << (*ListPtr)[i] << std::endl;
	}
	return foo;
}