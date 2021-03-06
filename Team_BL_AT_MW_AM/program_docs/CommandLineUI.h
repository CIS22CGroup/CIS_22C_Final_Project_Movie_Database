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
#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <string>
#include "List.h"
#include "FileIO.h"
#include "MainStorage.h"
#include "MovieWebDB.h"
#include "SearchResult.h"

/**
@class CommandLineUI
contains the presentational and interactive interface in the command line for the user.\n
KEEP ALL COUT<< AND CIN>> HERE
*/

class CommandLineUI
{
private:
	static const unsigned int resultsMax = 3;
	static unsigned int operationsTotal, operationsInsert, operationsFind, operationsDelete;
	static std::string initialFilePath;
	static MainStorage* mainStoragePtr;
public:
	/** entry point for the UI */
	static void enterLoop ();
	/** starts web search UI by title */
	static void WebSearchTitle ();
	/** starts web search UI by title and year */
	static void WebSearchTitleYear ();
	/** starts file import UI */
	static void StorageFileImport ();
	/** starts file import UI */
	static void StorageFileExport ();
	/** starts local search UI by title */
	static void LocalSearchTitle ();
	/** starts local search UI by year */
	static void LocalSearchYear ();
	/** starts local search UI by title and year */
	static void LocalSearchTitleYear ();
	/** starts local search UI by rating */
	static void LocalSearchRating ();
	/** starts local search UI by genre */
	static void LocalSearchGenre ();
	/** starts add movie UI 
	User may enter either the movie ID (an integer) or the 
	Hash Table Key (a string containing the title and year)
	for the identification of the movie. Both search criteria
	is unique, thus only a single movie will be found, if any.
	*/
	static void addMovie ();

	/** starts delete movie UI.\n
	User may enter either the movie ID (an integer) or the 
	Hash Table Key (a string containing the title and year)
	for the identification of the movie. Both search criteria
	is unique, thus only a single movie will be found, if any.
	*/
	static void deleteMovie ();

	static void updateMovie();
	/** starts find movie UI 
	User may enter either the movie ID (an integer) or the 
	Hash Table Key (a string containing the title and year)
	for the identification of the movie. Both search criteria
	is unique, thus only a single movie will be found, if any.
	*/
	static void findMovie ();

	/** prints the movie title BST */
	static void printMovieTitleBST ();
	/** starts file import UI */
	static void HashMapStats ();
	/** efficiency data */
	static void efficiencyStats();
	/** starts a hash map test */
	static void HashMapTest ();
	/** list all movies by title alphabetically */
	static void listTitle();

	/** formats search results */
	static void addResultHelper (SearchResult<List<MainStorageNode*>*>* searchResultPtr);
	static void searchResultHelper (SearchResult<List<MainStorageNode*>*>* searchResultPtr);
	static void deleteResultHelper(SearchResult<List<MainStorageNode*>*>* searchResultPtr);

	static void visitImport(MainStorageNode* movieNodePtr);
	static void visitImportDot(MainStorageNode* movieNodePtr);
	static void visitExport(MainStorageNode* movieNodePtr);
	static void visitExportDot(MainStorageNode* movieNodePtr);
	static std::string visitTitle(MainStorageNode* movieNodePtr);

	/** formats text */
	static std::string timeSecondFormat(unsigned int microSeconds);
};

#endif