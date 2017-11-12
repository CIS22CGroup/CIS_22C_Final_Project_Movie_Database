/* set to true when debugging modules. 
This will use the main for the command line 
WinMain is the entry point for the windows GUI
set to false for the final product
*/
#define COMMAND_LINE false
#define DEBUG_MODE true

#include <string>
#include "FileIO.h"
#include "MainStorage.h"
#include "MainStorageSearch.h"
#include "UserStorage.h"
#include "WinHTTP.h"
#include "windowUI.h"


#if COMMAND_LINE
int main ()
{
	std::string title;
	int year;
	std::cout << "Internet Movie Database Search" << std::endl
		<< "Enter the title: ";
	std::getline (std::cin, title);
	std::cout << "Enter the year: ";
	std::cin >> year;
	std::cout << "Searching for: " << std::endl
		<< "Title: " << title << std::endl
		<< "Year: " << year << std::endl;
	std::vector<MainStorageNode*>* nodeVector = WinHTTP::find(title,year);
	for (std::vector<int>::size_type i = 0; i != nodeVector->size (); i++)
	{
		std::cout << (*nodeVector)[i] << std::endl;
	}
	// parse XML
	//FileIO FileIOObj;
	//FileIOObj.XMLtest ();
	//FileIOObj.JSONtest ();
	system ("pause");
	return 0;
}
#endif

#if !COMMAND_LINE
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE, LPSTR pStr, int nCmd)
{
	return WindowUI::WinStart (hInst, NULL, pStr, nCmd);
};
#endif

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
