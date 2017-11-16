/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 4

Used Microsoft Visual Studio 2017

CommandLineUI class
contains the presentational and interactive interface in the command line for the user.
KEEP ALL COUT<< AND CIN>> HERE
*/

#include "commandLineUI.h"

CommandLineUI::CommandLineUI ()
{
}

//******************************************************
// CommandLineUI::enterLoop  
//      
// the main menu UI loop
// Pre: None
// Post: None
// Purpose: Command Line to interact with the user
//******************************************************
void CommandLineUI::enterLoop ()
{
	bool test = true;
	if (test = true)
	{
		WebSearch();
	}
}

std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj)
{
	os << "Title: " << obj->title << std::endl;
	os << "Year: " << obj->year << std::endl;
	os << "Content Rating: " << obj->contentRating << std::endl;
	os << "Rating: " << obj->rating << std::endl;
	os << "Genre: " << obj->genre << std::endl;
	os << "Description: " << obj->description << std::endl;
	return os;
}

void CommandLineUI::WebSearch()
{
	WinHTTP::genreTableInit(); //Initializes the genre data hash table for the API
	std::string title;
	int year;
	std::cout << "Internet Movie Database Search" << std::endl
		<< "Enter the title: ";
	std::getline(std::cin, title);
	std::cout << "Enter the year: ";
	std::cin >> year;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl
		<< "Year: " << year << std::endl;
	std::vector<MainStorageNode*>* nodeVector = WinHTTP::find(title, year);
	for (std::vector<int>::size_type i = 0; i != nodeVector->size(); i++)
	{
		std::cout << (*nodeVector)[i] << std::endl;
	}
	// parse XML
	//FileIO FileIOObj;
	//FileIOObj.XMLtest ();
	//FileIOObj.JSONtest ();
}
