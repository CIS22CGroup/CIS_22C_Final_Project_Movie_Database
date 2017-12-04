/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

/**
@class SearchResult
A wrapper to structure search results
@param RL The result list type
*/
template <class RL>
class SearchResult
{
private:
	unsigned int operations;
	int executionTime;
	RL searchResults;
public:
	SearchResult ();
	SearchResult (RL searchResultsInit, unsigned int operationsInit, int executionTimeInit);
	unsigned int& getOperations ();
	int getExecutionTime ();
	RL getResults ();
};

//******************************************************
// SearchResult class implementation 
// PUBLIC METHODS
//******************************************************

template <class RL>
SearchResult<RL>::SearchResult ()
{
	operations = 0;
	executionTime = 0;
	searchResults = nullptr;
}

template <class RL>
SearchResult<RL>::SearchResult (RL searchResultsInit, unsigned int operationsInit, int executionTimeInit)
{
	operations = operationsInit;
	executionTime = executionTimeInit;
	searchResults = searchResultsInit;
}

template <class RL>
unsigned int& SearchResult<RL>::getOperations (){return operations;}

template <class RL>
int SearchResult<RL>::getExecutionTime () { return executionTime; }

template <class RL>
RL SearchResult<RL>::getResults () { return searchResults; }
#endif