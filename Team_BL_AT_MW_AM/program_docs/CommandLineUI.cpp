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

void CommandLineUI::enterLoop ()
{
	MovieWebDB::genreTableInit ();
	mainStoragePtr = new MainStorage;
	int menuOption;
	std::cout << "Welcome to the Movie Database, made by Branden Lee, Alex Morfin, Ann Truong, and Michael Wu";
	bool loopActive = true;
	while (loopActive)
	{
		std::cout << "Please enter the number representing the menu options below:" << std::endl
			<< "1. Search movie from the web by title" << std::endl
			<< "2. Search movie from the web by title and year" << std::endl
			<< "3. Search Movie Locally by title" << std::endl
			<< "4. Search Movie Locally by year" << std::endl
			//<< "5. Search Movie Locally by title and year" << std::endl
			//<< "6. Search Movie Locally by rating" << std::endl
			<< "5. Search Movie Locally by genre" << std::endl
			<< "9. Hash Table Test" << std::endl
			<< "10. Exit Program" << std::endl << std::endl
			<< "Selection Number: ";
		std::cin >> menuOption;
		if (std::cin.fail ())
		{
			std::cin.clear (); // clears failure state
			std::cin.ignore (999, '\n'); // discards "bad" characters
			//std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n'); // discards "bad" characters
			menuOption = 0;
		}
		std::cout << std::endl;
		if (menuOption < 1 || menuOption > 10)
		{
			std::cout << "************************************" << std::endl;
			std::cout << "Your selection was not valid. Please try again." << std::endl;
			std::cout << "************************************" << std::endl << std::endl;
		}
		else
		{
			/* please keep each sub-menu in a separate function to increase readability and prevent
			a huge blob of unorganized code. */
			if (menuOption == 1) WebSearchTitle ();
			else if (menuOption == 2) WebSearchTitleYear ();
			else if (menuOption == 3) LocalSearchTitle ();
			else if (menuOption == 4) LocalSearchYear ();
			//else if (menuOption == 5) LocalSearchTitleYear ();
			//else if (menuOption == 6) LocalSearchRating ();
			else if (menuOption == 5) LocalSearchGenre ();
			else if (menuOption == 9) HashMapTest ();
			else if (menuOption == 10) loopActive = false;
		}
	}
}

void CommandLineUI::WebSearchTitle ()
{
	unsigned int i, n, n1;
	std::string title;
	std::cout << std::endl << "All search results are added to the local database!" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, title);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl << std::endl;
	/* Web searches may create many exceptions due to the unpredictability
	of the return data */
	try
	{
		List<MainStorageNode*>* resultNodesPtr = MovieWebDB::find2 (title, 0);
		/* display search statistics and results */
		n1 = resultNodesPtr->size ();
		n = resultsMax <= n1 ? resultsMax : n1;
		std::cout << "Displaying Results: " << n << " of " << n1 << std::endl;
		std::cout << "______________________________________________" << std::endl;
		for (i = 0; i < n1; i++)
		{
			mainStoragePtr->insert ((*resultNodesPtr)[i]);
			if (i < resultsMax)
			{
				std::cout << (*resultNodesPtr)[i] << std::endl;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what () << std::endl;
	}
	std::cout << std::endl << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::WebSearchTitleYear ()
{
	unsigned int i, n, n1;
	std::string title;
	int year;
	std::cout << std::endl << "All search results are added to the local database!" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, title);
	std::cout << "Enter the year: ";
	std::cin >> year;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl
		<< "Year: " << year << std::endl << std::endl;
	/* Web searches may create many exceptions due to the unpredictability
	of the return data */
	try
	{
		List<MainStorageNode*>* resultNodesPtr = MovieWebDB::find2 (title, year);
		/* display search statistics and results */
		n1 = resultNodesPtr->size ();
		n = resultsMax <= n1 ? resultsMax : n1;
		std::cout << "Displaying Results: " << n << " of " << n1 << std::endl;
		std::cout << "______________________________________________" << std::endl;
		for (i = 0; i < n1; i++)
		{
			mainStoragePtr->insert ((*resultNodesPtr)[i]);
			if (i < resultsMax)
			{
				std::cout << (*resultNodesPtr)[i] << std::endl;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what () << std::endl;
	}
	std::cout << std::endl << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchTitle ()
{
	unsigned int i, n, n1;
	std::string searchTerm;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, searchTerm);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << searchTerm << std::endl << std::endl;
	mainStoragePtr->titleFind (searchTerm, resultNodesPtr, operations);
	/* display search statistics and results */
	n1 = resultNodesPtr->size ();
	n = resultsMax <= n1 ? resultsMax : n1;
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Displaying Results: " << n << " of " << n1 << std::endl;
	std::cout << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchYear ()
{
	unsigned int i, n, n1;
	int searchTerm;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the year: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::cin >> searchTerm;
	std::cout << "Searching for: " << std::endl
		<< "Year: " << std::to_string (searchTerm) << std::endl << std::endl;
	mainStoragePtr->yearFind (searchTerm, resultNodesPtr, operations);
	/* display search statistics and results */
	n1 = resultNodesPtr->size ();
	n = resultsMax <= n1 ? resultsMax : n1;
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Displaying Results: " << n << " of " << n1 << std::endl;
	std::cout << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchTitleYear ()
{
	unsigned int i, n, n1;
	std::string searchTerm;
	int searchTerm2;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, searchTerm);
	std::cout << "Enter the year: ";
	std::cin >> searchTerm2;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << searchTerm << " Year: " << searchTerm2 << std::endl << std::endl;
	mainStoragePtr->titleYearFind (searchTerm, searchTerm2, resultNodesPtr, operations);
	/* display search statistics and results */
	n1 = resultNodesPtr->size ();
	n = resultsMax <= n1 ? resultsMax : n1;
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Displaying Results: " << n << " of " << n1 << std::endl;
	std::cout << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchRating ()
{
	unsigned int i, n, n1;
	double searchTerm;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the rating: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::cin >> searchTerm;
	std::cout << "Searching for: " << std::endl
		<< "Rating: " << std::to_string (searchTerm) << std::endl << std::endl;
	mainStoragePtr->ratingFind (searchTerm, resultNodesPtr, operations);
	/* display search statistics and results */
	n1 = resultNodesPtr->size ();
	n = resultsMax <= n1 ? resultsMax : n1;
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Displaying Results: " << n << " of " << n1 << std::endl;
	std::cout << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchGenre ()
{
	unsigned int i, n, n1;
	std::string searchTerm;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations = 0;
	std::cout << std::endl << "Local Movie Database search" << std::endl
		<< "Enter the genre: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, searchTerm);
	std::cout << "Searching for: " << std::endl
		<< "Genre: " << searchTerm << std::endl << std::endl;
	mainStoragePtr->genreFind (searchTerm, resultNodesPtr, operations);
	/* display search statistics and results */
	n1 = resultNodesPtr->size ();
	n = resultsMax <= n1 ? resultsMax : n1;
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Displaying Results: " << n << " of " << n1 << std::endl;
	std::cout << "Total Movies cached: " << mainStoragePtr->size () << std::endl;
	std::cout << "______________________________________________" << std::endl;
	for (i = 0; i < n; i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::HashMapTest ()
{
	unsigned int i, n;
	n = 5;
	std::string movieKey;
	int hash;
	double loadFactor;
	HashMap <std::string>* storageMap;
	storageMap = new HashMap <std::string> (n);
	std::string titleArray[] = { "Thor","Batman","Spiderman", "Superman","The Flash" };
	int yearArray[] = { 2007,2008,2009,1995,1996 };
	std::cout << std::left << std::setw (14) << "Movie" << std::setw (5) << "Year" << std::setw (20) << "Key" << std::setw (5) << "Hash" << std::endl;
	for (i = 0; i < n; i++)
	{
		movieKey = StringHelper::toID (titleArray[i], yearArray[i]);
		hash = StringHelper::hashStr (movieKey, n);
		std::cout << std::left << std::setw (14) << titleArray[i] << std::setw (5) << yearArray[i] << std::setw (20) << movieKey << std::setw (5) << hash << std::endl;
		storageMap->insert (movieKey, titleArray[i]);
	}
	loadFactor = ((double)storageMap->bucketsUsed () / (double)storageMap->max_size ()) * 100.00;
	std::cout << std::endl << "Hash Table Stats" << std::endl;
	std::cout << "Load Factor: " << std::fixed << std::setprecision (0) << loadFactor << "%" << std::endl;
	std::cout << "Collision Count: " << storageMap->collisions () << std::endl;
	std::cout << "______________________________________________" << std::endl;
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
	int n = obj->genreListPtr->size ();
	if (n > 0)
	{
		os << "Genre: ";
		for (int i = 0; i < n; i++)
		{
			os << obj->genreListPtr->getValue (i);
			if (i != n - 1) os << ", ";
		}
		os << std::endl;
	}
	// Trim Description length to 200 characters
	if (obj->description.length () > 200)
		os << "Description: " << obj->description.substr (0, 197) << "..." << std::endl;
	else if (obj->description.length () > 0)
		os << "Description: " << obj->description << std::endl;
	return os;
}

template <class T>
std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr)
{
	int n = ListPtr->size ();
	for (int i = 0; i < n; i++)
	{
		foo << (*ListPtr)[i] << std::endl;
	}
	return foo;
}