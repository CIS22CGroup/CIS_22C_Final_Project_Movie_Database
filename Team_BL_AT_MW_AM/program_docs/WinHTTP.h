/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef WIN_HTTP_H
#define WIN_HTTP_H

#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <locale>
#include <sstream>
#include "List.h" // List
#include "StringHelper.h" // split
#include "json.hpp" // JSON parser
#include "MainStorageNode.h"
#include "HashMap.h"

using json = nlohmann::json;

/**
@class WinHTTP
A collection of static web based methods
aimed at gathering movie data from the web
*/
class WinHTTP
{
private:
	static HashMap <std::string>* genreMap;
public:
	static std::string getWebsite (std::string host, std::string path);
	static std::string html (std::string response);
	static List<MainStorageNode*>* jsonStrToNodeArrAPI1 (std::string html);
	static List<MainStorageNode*>* jsonStrToNodeArrAPI2 (std::string html);
	static List<MainStorageNode*>* find (std::string title, int year = 0);

	/* Genre Table Methods
	The Movie Database API returns move genres as integer-based IDs
	that must be matched to the genre string. So far the table has been unsuccesful.
	Currently a genre ID to STR will return a genre of ""
	*/
	static std::string MDBgenreIdToStr (int genreId);
	static void genreTableInit ();
};

#endif