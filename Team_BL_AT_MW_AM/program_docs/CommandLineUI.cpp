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
#define HTTP_TEST false

MainStorage* CommandLineUI::mainStoragePtr;

void CommandLineUI::enterLoop ()
{
	WinHTTP::genreTableInit ();
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
			else if (menuOption == 10) loopActive = false;
		}
	}
}

void CommandLineUI::WebSearchTitle()
{
	std::string title;
	std::cout << std::endl << "All search results are added to the local database!" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline(std::cin, title);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl << std::endl;
	List<MainStorageNode*>* resultNodesPtr = WinHTTP::find(title, 0);
	for (int i = 0; i != resultNodesPtr->size(); i++)
	{
		mainStoragePtr->insert ((*resultNodesPtr)[i]);
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::WebSearchTitleYear ()
{
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
	List<MainStorageNode*>* resultNodesPtr = WinHTTP::find (title, year);
	for (int i = 0; i != resultNodesPtr->size (); i++)
	{
		mainStoragePtr->insert ((*resultNodesPtr)[i]);
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

void CommandLineUI::LocalSearchTitle ()
{
	std::string title;
	List<MainStorageNode*>* resultNodesPtr = new List<MainStorageNode*>;
	int operations;
	std::cout << std::endl <<  "Local Movie Database search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline (std::cin, title);
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl << std::endl;
	mainStoragePtr->titleFind (title, resultNodesPtr, operations);
	std::cout << "Operations Performed: " << operations << std::endl
		<< "Search Results: " << resultNodesPtr->size () << std::endl << std::endl;
	for (int i = 0; i != resultNodesPtr->size(); i++)
	{
		mainStoragePtr->insert ((*resultNodesPtr)[i]);
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
	std::cout << "______________________________________________" << std::endl;
}

//******************************************************
// operator<<        
//******************************************************
std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj)
{
	os << "Title: " << obj->title << std::endl;
	os << "Year: " << obj->year << std::endl;
	os << "Content Rating: " << obj->contentRating << std::endl;
	os << "Rating: " << obj->rating << std::endl;
	os << "Genre: " << obj->genre1 << std::endl;
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