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
#ifndef MOVIE_WEB_DB_H
#define MOVIE_WEB_DB_H

#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include "List.h" // List
#include "StringHelper.h" // split
/* THIS IS THE ONLY CLASS THAT USES AN EXTERNAL LIBRARY.
THIS LIBRARY WAS APPROVED BY MR. GOEL AS INQUIRED IN CLASS
ON 11/22/2017 at 5:20pm.
It would be far too tedious to write a JSON parsing 
implementation so json.hpp is needed to save time
*/
#include "json.hpp" // JSON parser
#include "MainStorageNode.h"
#include "HashMap.h"
#include "WinHTTP.h"
#include "SearchResult.h"

using json = nlohmann::json;

/**
@class MovieWebDB
Static methods working as a driver between the main storage database
and the internet movie database. Uses the WebHTTP library to make 
HTTP GET calls to the internet.
*/
class MovieWebDB
{
private:
	static std::string theMovieDB_API_Key;
	static const int genreMapSize = 1000;
	static HashMap <std::string>* genreMap;
public:
	static List<MainStorageNode*>* jsonStrToNodeArrAPI1 (std::string html, int &operations);
	static List<MainStorageNode*>* jsonStrToNodeArrAPI2 (std::string html, int &operations);
	static List<MainStorageNode*>* jsonStrToNodeArrAPI3 (std::string html, int &operations);
	static List<MainStorageNode*>* jsonStrToNodeArrAPI4 (std::string html, int &operations);
	/** Uses theimdbapi.org API to return comprehensive information
	about each movie matching a search query.\n
	Sample:\n
	http://www.theimdbapi.org/api/find/movie?title=transformers&year=2007
	response is in JSON. This is a very slow service because it is public and
	does not require an API key. This method may be good for a threaded query
	that won't stall the program.
	*/
	static SearchResult<List<MainStorageNode*>*>* find1 (std::string title, int year = 0);

	/** Uses themoviedb.org API to return simple information
	about each movie matching a search query.\n
	Sample:\n
	http://api.themoviedb.org/3/search/movie?api_key=a677473afe79ffa4994be03e56665d28&query=thor
	response is in JSON. This is a very quick and free API service. DO NOT SPAM QUERIES
	OR THEY WILL BAN THE API KEY.
	*/
	static SearchResult<List<MainStorageNode*>*>* find2 (std::string title, int year = 0);

	/** Uses themoviedb.org API to return extra information
	about a single movie matching the movie ID.\n
	Sample:\n
	http://api.themoviedb.org/3/movie/44434?api_key=a677473afe79ffa4994be03e56665d28
	response is in JSON. This is a very quick and free API service. DO NOT SPAM QUERIES
	OR THEY WILL BAN THE API KEY.
	*/
	static SearchResult<List<MainStorageNode*>*>* find3 (int movieId);

	/** Uses themoviedb.org API to return actor information
	about a single movie matching the movie ID.\n
	Sample:\n
	http://api.themoviedb.org/3/movie/44434/credits?api_key=a677473afe79ffa4994be03e56665d28
	response is in JSON. This is a very quick and free API service. DO NOT SPAM QUERIES
	OR THEY WILL BAN THE API KEY.
	*/
	static SearchResult<List<MainStorageNode*>*>* find4 (int movieId);

	/* Genre Table Methods
	The Movie Database API returns move genres as integer-based IDs
	that must be matched to the genre string. So far the table has been unsuccesful.
	Currently a genre ID to STR will return a genre of ""
	*/
	static std::string MDBgenreIdToStr (int genreId);
	static void genreTableInit ();
};

#endif