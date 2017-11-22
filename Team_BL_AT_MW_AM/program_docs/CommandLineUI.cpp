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

CommandLineUI::CommandLineUI ()
{
}

void CommandLineUI::enterLoop ()
{
	WinHTTP::genreTableInit ();
	int menuOption;
	std::cout << "Welcome to the Movie Database, made by Branden Lee, Alex Morfin, Ann Truong, and Michael Wu";
	bool loopActive = true;
	while (loopActive)
	{
		std::cout << "Please enter the number representing the menu options below:" << std::endl
			<< "1. Push random integers to the integer type stack" << std::endl
			/*<< "2. Pop from the integer type stack" << std::endl
			<< "3. Clear the integer type stack" << std::endl
			<< "4. Push \"ExampleStrings.txt\" to the string type stack." << std::endl
			<< "5. Pop from the string type stack" << std::endl
			<< "6. Clear the string type stack" << std::endl
			<< "7. Push a random Currency to the currency type stack" << std::endl
			<< "8. Pop from the Currency type stack" << std::endl
			<< "9. Clear the Currency type stack" << std::endl*/
			<< "10. Exit Application" << std::endl << std::endl
			<< "Selection Number: ";
		// there is a bug that when you enter "test,2,3,hey" in the menu selection. 
		// The program gets stuck in an infinite loop
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
			if (menuOption == 1) WebSearch ();
			/*else if (menuOption == 2) intStackPop ();
			else if (menuOption == 3) intStackClear ();
			else if (menuOption == 4) stringStackPush ();
			else if (menuOption == 5) stringStackPop ();
			else if (menuOption == 6) stringStackClear ();
			else if (menuOption == 7) currencyStackPush ();
			else if (menuOption == 8) currencyStackPop ();
			else if (menuOption == 9) currencyStackClear ();*/
			else if (menuOption == 10) loopActive = false;
		}
	}
}

void CommandLineUI::WebSearch()
{
	std::string title;
	int year;
	std::cout << "Internet Movie Database Search" << std::endl
		<< "Enter the title: ";
	std::cin.ignore (999, '\n'); // discards "bad" characters
	std::getline(std::cin, title);
	std::cout << "Enter the year: ";
	std::cin >> year;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl
		<< "Year: " << year << std::endl << std::endl;
	List<MainStorageNode*>* resultNodesPtr = WinHTTP::find(title, year);
	for (int i = 0; i != resultNodesPtr->size(); i++)
	{
		std::cout << (*resultNodesPtr)[i] << std::endl;
	}
}

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