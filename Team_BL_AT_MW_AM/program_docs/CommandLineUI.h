/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "List.h"
#include "FileIO.h"
#include "MainStorage.h"
#include "UserStorage.h"
#include "WinHTTP.h"

/**
@class CommandLineUI
contains the presentational and interactive interface in the command line for the user.\n
KEEP ALL COUT<< AND CIN>> HERE
*/

class CommandLineUI
{
private:
	static MainStorage* mainStoragePtr;
public:
	/** entry point for the UI */
	static void enterLoop ();
	/** starts web search UI by title */
	static void WebSearchTitle ();
	/** starts web search UI by title and year */
	static void WebSearchTitleYear ();
	/** starts local search UI by title */
	static void LocalSearchTitle ();
};

#endif