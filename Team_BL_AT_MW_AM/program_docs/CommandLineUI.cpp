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

#include "commandLineUI.h"

MainStorage* CommandLineUI::mainStoragePtr;
unsigned int CommandLineUI::operationsTotal = 0;
std::string CommandLineUI::initialFilePath = "mainStorage.txt";

void CommandLineUI::enterLoop()
{
	MovieWebDB::genreTableInit();
	mainStoragePtr = new MainStorage;
	int menuOption;
	unsigned int operations, n;
	bool flag;
	operations = 0;
	std::cout << "************************************" << std::endl;
	std::cout << "Welcome to the Movie Database!" << std::endl;
	std::cout << "Made by Branden Lee, Alex Morfin, Ann Truong, and Michael Wu" << std::endl;
	std::cout << "************************************" << std::endl << std::endl;
	// file import
	std::cout << "Importing Data";
	try
	{
		flag = FileIO::fileToMainStorage(mainStoragePtr, initialFilePath, new std::function<void(MainStorageNode*)>(&visitImportDot), operations);
		operationsTotal += operations;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	if (flag)
	{
		n = mainStoragePtr->size();
		std::cout << std::endl;
		std::cout << "Total Movies Cached: " << n << std::endl;
		std::cout << "Operations Performed: " << operations << " (" << ((n == 0) ? operations : (operations / n)) << " operations per movie)" << std::endl << std::endl;
	}
	// begin loop
	bool loopActive = true;
	while (loopActive)
	{
		std::cout << "Please enter the number representing the menu options below:" << std::endl
			<< "1. Add Movie" << std::endl
			<< "2. Delete Movie by movie ID or movie key" << std::endl
			<< "3. Find Movie by movie ID or movie key" << std::endl
			<< "4. Hash Table Statistics" << std::endl
			<< "5. Movie titles in alphabetical order" << std::endl
			<< "6. Display Movie Title BST" << std::endl
			<< "7. Efficiency" << std::endl
			<< "8. Import Movie Storage File" << std::endl
			<< "9. Export Movie Storage File" << std::endl
			<< "10. Search Movie Locally by title" << std::endl
			<< "11. Search Movie Locally by year" << std::endl
			// required to Find and display one data record using the primary key
			<< "12. Search Movie Locally by title and year" << std::endl
			//<< "17. Search Movie Locally by rating" << std::endl
			<< "13. Search Movie Locally by genre" << std::endl
			/* requires Complete demonstration of all options of the menu.
			The demonstration must include collision resolution
			and deletion of the root (it should have two children). */
			<< "14. Update Movie by movie ID or movie key" << std::endl
			// required to Find and display one data record using the primary key
			<< "15. Search movie from the web by title" << std::endl
			<< "16. Search movie from the web by title and year" << std::endl
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
			if (menuOption == 1) addMovie();
			else if (menuOption == 2) deleteMovie();
			else if (menuOption == 3) findMovie();
			else if (menuOption == 4) HashMapStats();
			else if (menuOption == 5) listTitle();
			else if (menuOption == 6) printMovieTitleBST();
			else if (menuOption == 7) efficiencyStats();
			else if (menuOption == 8) StorageFileImport();
			else if (menuOption == 9) StorageFileExport();
			else if (menuOption == 10) LocalSearchTitle();
			else if (menuOption == 11) LocalSearchYear();
			else if (menuOption == 12) LocalSearchTitleYear();
			else if (menuOption == 13) LocalSearchGenre();
			else if (menuOption == 14) updateMovie();
			else if (menuOption == 15) WebSearchTitle();
			else if (menuOption == 16) WebSearchTitleYear();
			//else if (menuOption == 17) LocalSearchRating ();
			//else if (menuOption == 18) HashMapTest ();
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
	unsigned int operations = 0;
	std::cout << std::endl << "Import Movie Database File" << std::endl
		<< "Enter the file path: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, filePath);
	std::cout << "Importing file...: " << std::endl
		<< "Path: " << filePath << std::endl << std::endl;
	// file import
	std::cout << "Importing Data";
	try
	{
		flag = FileIO::fileToMainStorage(mainStoragePtr, filePath, new std::function<void(MainStorageNode*)>(&visitImportDot), operations);
		operationsTotal += operations;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	if (flag)
	{
		std::cout << std::endl;
		std::cout << "Movies Imported Successfully!" << std::endl;
		std::cout << "Total Movies Cached: " << mainStoragePtr->size() << std::endl;
		std::cout << "Operations Performed: " << operations << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::StorageFileExport()
{
	std::string filePath;
	bool flag = false;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	unsigned int operations = 0;
	std::cout << std::endl << "Export Movie Database File" << std::endl
		<< "Enter the file path: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, filePath);
	std::cout << "Exporting file...: " << std::endl
		<< "Path: " << filePath << std::endl << std::endl;
	// file export
	std::cout << "Exporting Data";
	try
	{
		flag = FileIO::mainStorageToFile(mainStoragePtr, filePath, new std::function<void(MainStorageNode*)>(&visitExportDot), operations);
		operationsTotal += operations;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	if (flag)
	{
		std::cout << std::endl;
		std::cout << "Movies Exporteded Successfully!" << std::endl;
		std::cout << "Total Movies cached: " << mainStoragePtr->size() << std::endl;
		std::cout << "Operations Performed: " << operations << std::endl;
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
	unsigned int movieId, year, operations;
	double rating;
	MainStorageNode* movieNodePtr;
	List<std::string>* genreListPtr;
	std::string title, description, genreStr;
	movieId = 0;
	year = 0;
	rating = 0.0;
	operations = 0;
	bool movieIdValid, yearValid, ratingValid;
	movieIdValid = yearValid = ratingValid = false;
	std::cout << std::endl << "Add Movie" << std::endl;
	while (std::cin.fail() || !movieIdValid)
	{
		std::cout << "Enter the movie ID: ";
		std::cin >> movieId;
		movieIdValid = (movieId > 0 && mainStoragePtr->idFind(movieId)->getResults()->size() == 0);
		if (std::cin.fail()) {
			std::cout << "************************************" << std::endl;
			std::cout << "Invalid characters. Must be int. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
			std::cin.clear(); // clears failure state
			std::cin.ignore(999, '\n'); // discards "bad" characters
										//std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n'); // discards "bad" characters
			movieId = 0;
		}
		else if (movieIdValid) {
			std::cout << "************************************" << std::endl;
			std::cout << "That movie ID has already been taken. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
		}
	}
	std::cin.clear(); // clears failure state
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::cout << "Enter the title: ";
	std::getline(std::cin, title);
	while (std::cin.fail() || !yearValid)
	{
		std::cout << "Enter the year: ";
		std::cin >> year;
		yearValid = (year > 0 && year < 9999);
		if (std::cin.fail()) {
			std::cout << "************************************" << std::endl;
			std::cout << "Invalid characters. Must be int. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
			std::cin.clear(); // clears failure state
			std::cin.ignore(999, '\n'); // discards "bad" characters
			year = 0;
		}
	}
	while (std::cin.fail() || !ratingValid)
	{
		std::cout << "Enter the rating: ";
		std::cin >> rating;
		ratingValid = (rating >= 0 && rating <= 10);
		if (std::cin.fail()) {
			std::cout << "************************************" << std::endl;
			std::cout << "Invalid characters. Must be double. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
			std::cin.clear(); // clears failure state
			std::cin.ignore(999, '\n'); // discards "bad" characters
			rating = 0.0;
		}
	}
	std::cin.clear(); // clears failure state
	std::cin.ignore(999, '\n'); // discards "bad" characters
	// take user input for genre string and parse into a list
	std::cout << "Enter the genres separated by a comma ',': ";
	std::getline(std::cin, genreStr);
	genreListPtr = StringHelper::split(genreStr, ",");
	StringHelper::reduce(genreListPtr); // trim and remove excessive whitespace to each element
	std::cout << "Enter the description: ";
	std::getline(std::cin, description);
	std::cout << "Adding new movie: " << std::endl
		<< "Movie ID: " << movieId << std::endl
		<< "Title: " << title << std::endl << std::endl;
	// create the node
	movieNodePtr = new MainStorageNode(title, year, rating, description);
	movieNodePtr->setGenres(genreListPtr);
	genreListPtr->clear();
	movieNodePtr->setTheMovieDBId(movieId);
	// insert
	mainStoragePtr->insert(movieNodePtr, operations);
	operationsTotal += operations;
	std::cout << "Movie Insertion Done! " << std::endl;
	std::cout << "Operations Performed: " << operations << std::endl;
	std::cout << "Total Movies Cached: " << mainStoragePtr->size() << std::endl;
	std::cout << "______________________________________________" << std::endl;
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
	/* delete results */
	deleteResultHelper(searchResultPtr);
}

void CommandLineUI::updateMovie()
{
	/* This method will actally delete the old movie node
	and add a new one with user-defined replacements. This must be done
	since changing movie data requires it to be re-indexed. It easier just to to a full
	re-index rather than individual fields. */
	std::string searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	List<MainStorageNode*>* nodeListPtr;
	MainStorageNode *movieNodePtr, *targetNodePtr;
	unsigned int movieId, movieIdOrig, year, yearOrig, operations, executionTime, n;
	double rating, ratingOrig;
	List<std::string>* genreListPtr;
	std::string title, titleOrig, movieIdStr, yearStr, ratingStr, description, descriptionOrig, genreStr, genreStrOrig;
	bool movieIdValid, yearValid, ratingValid;
	movieIdValid = yearValid = ratingValid = false;
	std::cout << std::endl << "Update A Movie" << std::endl;
	// get by ID or hash key
	std::cout << "Enter the movie ID or Hash Table Key: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	if (searchTerm != "") {
		if (StringHelper::isNumeric(searchTerm)) {
			// search the term as the movie ID
			int targetID;
			targetID = std::stoi(searchTerm);
			std::cout << "Searching for: " << std::endl
				<< "Movie ID: " << targetID << std::endl << std::endl;
			searchResultPtr = mainStoragePtr->idFind(targetID);
		}
		else
		{
			// search the term as the hash table key
			std::cout << "Searching for: " << std::endl
				<< "Hash Table Key: " << searchTerm << std::endl << std::endl;
			searchResultPtr = mainStoragePtr->keyFind(searchTerm);
		}
		nodeListPtr = searchResultPtr->getResults();
		operations = searchResultPtr->getOperations();
		executionTime = (unsigned int)searchResultPtr->getExecutionTime();
		n = nodeListPtr->size();
		// movie to edit found. Only want one result.
		if (n == 1) {
			std::cout << "EDIT HAS BEGUN. ENTER A BLANK TO KEEP ORIGINAL VALUE. DO NOT TYPE A SPACE." << std::endl;
			targetNodePtr = (*nodeListPtr)[0];
			movieId = movieIdOrig = targetNodePtr->getId();
			title = titleOrig = targetNodePtr->getTitle();
			year = yearOrig = targetNodePtr->getYear();
			rating = ratingOrig = targetNodePtr->getRating();
			genreStr = genreStrOrig = targetNodePtr->getGenreStr();
			description = descriptionOrig = targetNodePtr->getDescription();
			// Auto fill variables with data from the searched movie node
			while (!movieIdValid)
			{
				std::cout << "Enter the movie new ID: ";
				std::getline(std::cin, movieIdStr);
				if (movieIdStr == "") {
					movieIdValid = true;
					movieId = movieIdOrig;
				}
				else if (StringHelper::isNumeric(movieIdStr)) {
					movieId = stoi(movieIdStr);
				}
				else {
					movieId = 0;
				}
				movieIdValid = (movieIdOrig == movieId || (movieId > 0 && mainStoragePtr->idFind(movieId)->getResults()->size() == 0));
				if (!movieIdValid) {
					std::cout << "************************************" << std::endl;
					std::cout << "That movie ID has already been taken. Please try again." << std::endl;
					std::cout << "************************************" << std::endl << std::endl;
				}
			}
			std::cout << "Enter the title: ";
			std::getline(std::cin, title);
			if (title == "") {
				title = titleOrig;
			}
			while (std::cin.fail() || !yearValid)
			{
				if (std::cin.fail()) {
					std::cout << "************************************" << std::endl;
					std::cout << "Invalid characters. Must be int. Please try again." << std::endl;
					std::cout << "************************************" << std::endl << std::endl;
					std::cin.clear(); // clears failure state
					std::cin.ignore(999, '\n'); // discards "bad" characters
				}
				std::cout << "Enter the new year: ";
				std::getline(std::cin, yearStr);
				if (yearStr == "") {
					yearValid = true;
					year = yearOrig;
				}
				else if (StringHelper::isNumeric(yearStr) && yearStr.length() <= 4) {
					year = stoi(yearStr);
				}
				else {
					year = 0;
				}
				yearValid = (year > 0);
			}
			while (std::cin.fail() || !ratingValid)
			{
				if (std::cin.fail()) {
					std::cout << "************************************" << std::endl;
					std::cout << "Invalid characters. Must be double. Please try again." << std::endl;
					std::cout << "************************************" << std::endl << std::endl;
					std::cin.clear(); // clears failure state
					std::cin.ignore(999, '\n'); // discards "bad" characters
				}
				std::cout << "Enter the rating: ";
				std::getline(std::cin, ratingStr);
				if (ratingStr == "") {
					ratingValid = true;
					rating = ratingOrig;
				}
				else if (StringHelper::isNumeric(ratingStr) && yearStr.length() <= 3) {
					rating = stod(ratingStr);
				}
				else {
					rating = 999;
				}
				ratingValid = (rating >= 0 && rating <= 10);
			}
			// take user input for genre string and parse into a list
			std::cout << "Enter the genres separated by a comma ',': ";
			std::getline(std::cin, genreStr);
			if (genreStr == "") {
				genreStr = genreStrOrig;
			}
			genreListPtr = StringHelper::split(genreStr, ",");
			StringHelper::reduce(genreListPtr); // trim and remove excessive whitespace to each element
			// description input. "" input will default to original value
			std::cout << "Enter the description: ";
			std::getline(std::cin, description);
			if (description == "") {
				description = descriptionOrig;
			}
			std::cout << "Editing movie: " << std::endl
				<< "Movie ID: " << movieId << std::endl
				<< "Title: " << title << std::endl << std::endl;
			// create the node
			movieNodePtr = new MainStorageNode(title, year, rating, description);
			movieNodePtr->setGenres(genreListPtr);
			genreListPtr->clear();
			movieNodePtr->setTheMovieDBId(movieId);
			// remove
			mainStoragePtr->remove(targetNodePtr, operations);
			// insert
			mainStoragePtr->insert(movieNodePtr, operations);
			operationsTotal += operations;
			std::cout << "Movie Update Done! " << std::endl;
			std::cout << "Operations Performed: " << operations << std::endl;
			std::cout << "Total Movies Cached: " << mainStoragePtr->size() << std::endl;
			std::cout << "______________________________________________" << std::endl;
		}
		else {
			std::cout << "Movie not found!" << std::endl;
			std::cout << "______________________________________________" << std::endl;
		}
	}
	else {
		std::cout << "Input may not be empty!" << std::endl;
		std::cout << "______________________________________________" << std::endl;
	}
}

void CommandLineUI::findMovie()
{
	std::string searchTerm;
	SearchResult<List<MainStorageNode*>*>* searchResultPtr;
	std::cout << std::endl << "Find Movie" << std::endl
		<< "Enter the movie ID or Hash Table Key: ";
	std::cin.ignore(999, '\n'); // discards "bad" characters
	std::getline(std::cin, searchTerm);
	if (StringHelper::isNumeric(searchTerm)) {
		// search the term as the movie ID
		int targetID;
		targetID = std::stoi(searchTerm);
		std::cout << "Searching for: " << std::endl
			<< "Movie ID: " << targetID << std::endl << std::endl;
		searchResultPtr = mainStoragePtr->idFind(targetID);
	}
	else
	{
		// search the term as the hash table key
		std::cout << "Searching for: " << std::endl
			<< "Hash Table Key: " << searchTerm << std::endl << std::endl;
		searchResultPtr = mainStoragePtr->keyFind(searchTerm);
	}
	/* display search statistics and results */
	searchResultHelper(searchResultPtr);
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
	unsigned int hashId;
	HashMap <MainStorageNode*>* movieHashMapPtr;
	HashMapNode<MainStorageNode*>* movieHashMapNodePtr;
	std::string movieKey;
	MainStorageNode* movieNodePtr;
	double loadFactor;
	bool flagCollision;
	// headers
	std::cout << std::left << std::setw(7) << "ID" << std::setw(17) << "Movie" << std::setw(5) << "Year" << std::setw(24) << "Key" << std::setw(5) << "Hash" << std::setw(9) << "Collision" << std::endl;
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
		std::cout << std::left << std::setw(7) << movieNodePtr->getTheMovieDBId() << std::setw(17) << movieNodePtr->getTitle().substr(0, 16) << std::setw(5) << movieNodePtr->getYear()
			<< std::setw(24) << movieKey.substr(0, 23) << std::setw(5) << hashId << std::setw(9) << (flagCollision ? "X" : "") << std::endl;
	}
	// hash map statistics
	loadFactor = ((double)movieHashMapPtr->bucketsUsed() / (double)movieHashMapPtr->max_size()) * 100.00;
	std::cout << std::endl << "Hash Table Stats" << std::endl;
	std::cout << "Max Size: " << movieHashMapPtr->max_size() << std::endl;
	std::cout << "Load Factor: " << std::fixed << std::setprecision(0) << loadFactor << "%" << std::endl;
	std::cout << "Collision Count: " << movieHashMapPtr->collisions() << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::efficiencyStats() {
	std::cout << std::endl << "Efficiency Stats:" << std::endl;
	std::cout << "Total Operations: " << operationsTotal << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::HashMapTest()
{
	unsigned int i, n, n1, operations;
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
		storageMap->insert(movieKey, titleArray[i], operations);
	}
	loadFactor = ((double)storageMap->bucketsUsed() / (double)storageMap->max_size()) * 100.00;
	std::cout << std::endl << "Hash Table Stats" << std::endl;
	std::cout << "Max Size: " << storageMap->max_size() << std::endl;
	std::cout << "Load Factor: " << std::fixed << std::setprecision(0) << loadFactor << "%" << std::endl;
	std::cout << "Collision Count: " << storageMap->collisions() << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::listTitle()
{
	std::string log;
	std::cout << std::endl << "Movie Titles in Alphabetical Order" << std::endl;
	std::cout << std::left << std::setw(7) << "ID" << std::setw(5) << "Year" << "Movie" << std::endl;
	std::cout << "______________________________________________" << std::endl;
	mainStoragePtr->listTitle(new std::function<std::string(MainStorageNode*)>(&visitTitle), log);
	std::cout << "______________________________________________" << std::endl << std::endl;
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
			mainStoragePtr->insert((*nodeListPtr)[i], searchResultPtr->getOperations());
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
		operationsTotal += operations;
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

void CommandLineUI::deleteResultHelper(SearchResult<List<MainStorageNode*>*>* searchResultPtr)
{
	bool flag = false;
	if (searchResultPtr)
	{
		unsigned int i, n1, operations, executionTime;
		List<MainStorageNode*>* nodeListPtr;
		nodeListPtr = searchResultPtr->getResults();
		operations = searchResultPtr->getOperations();
		executionTime = searchResultPtr->getExecutionTime();
		n1 = nodeListPtr->size();
		// begin deleting if any
		if (n1 > 0)
		{
			flag = true;
			for (i = 0; i < n1; i++)
			{
				mainStoragePtr->remove((*nodeListPtr)[i], operations);
				std::cout << "Movie Node Deleted!" << std::endl;
			}
		}
		operationsTotal += operations;
		std::cout << "Operations Performed: " << operations << " in " << executionTime << " micro-seconds" << std::endl;
		std::cout << "Total Movies Cached: " << mainStoragePtr->size() << std::endl;
		std::cout << "______________________________________________" << std::endl << std::endl;
	}
	// result error or no results
	if (!flag)
	{
		std::cout << "NO RESULTS FOUND. Nothing deleted." << std::endl;
		std::cout << "______________________________________________" << std::endl << std::endl;
	}
}

void CommandLineUI::visitImport(MainStorageNode* movieNodePtr)
{
	std::cout << "Imported: " << movieNodePtr->getTitle() << std::endl;
}

void CommandLineUI::visitImportDot(MainStorageNode* movieNodePtr)
{
	std::cout << ".";
}

void CommandLineUI::visitExport(MainStorageNode* movieNodePtr)
{
	std::cout << "Exported: " << movieNodePtr->getTitle() << std::endl;
}

void CommandLineUI::visitExportDot(MainStorageNode* movieNodePtr)
{
	std::cout << ".";
}

std::string CommandLineUI::visitTitle(MainStorageNode* movieNodePtr)
{
	std::stringstream ss;
	ss << std::left << std::setw(7) << movieNodePtr->getId() << std::setw(5) << movieNodePtr->getYear() << movieNodePtr->getTitle() << std::endl;
	std::cout << ss.str();
	return ss.str();
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