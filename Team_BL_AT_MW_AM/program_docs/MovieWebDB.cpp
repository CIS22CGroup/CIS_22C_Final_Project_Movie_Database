/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "MovieWebDB.h"

std::string MovieWebDB::theMovieDB_API_Key = "a677473afe79ffa4994be03e56665d28";
HashMap <std::string>* MovieWebDB::genreMap = new HashMap <std::string> (MovieWebDB::genreMapSize);

List<MainStorageNode*>* MovieWebDB::jsonStrToNodeArrAPI1 (std::string html)
{
	List<MainStorageNode*>* resultListPtr = new List<MainStorageNode*> ();
	std::string title = "";
	int year = 0;
	std::string contentRating = "";
	double rating = 0.0;
	List<std::string>* genreListPtr = new List<std::string> ();
	std::string description = "";
	try
	{
#if DEBUG_MODE
		std::cout << std::endl;
#endif
		auto j = json::parse (html);
		for (json::iterator it = j.begin (); it != j.end (); ++it)
		{
#if DEBUG_MODE
			std::cout << it.value ()["title"].get<std::string> () << std::endl;
			std::cout << it.value ()["year"].get<std::string> () << std::endl;
			std::cout << it.value ()["content_rating"].get<std::string> () << std::endl;
			std::cout << it.value ()["rating"].get<std::string> () << std::endl;
			std::cout << it.value ()["genre"][0].get<std::string> () << std::endl;
			std::cout << it.value ()["description"].get<std::string> () << std::endl << "------------------------------";
#endif
			try
			{
				title = it.value ().at ("title").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				title = "";
			}
			try
			{
				year = stoi (it.value ().at ("year").get<std::string> ());
			}
			catch (const std::exception& e)
			{
				e.what ();
				year = 0;
			}
			try
			{
				contentRating = it.value ().at ("content_rating").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				contentRating = "";
			}
			try
			{
				rating = stod (it.value ().at ("rating").get<std::string> ());
			}
			catch (const std::exception& e)
			{
				e.what ();
				rating = 0.0;
			}
			try
			{
				int i;
				int n = (int)it.value ().at ("genre").size ();
				for (i = 0; i < n; i++)
				{
					genreListPtr->push_back (it.value ().at ("genre")[0].get<std::string> ());
				}
			}
			catch (const std::exception& e)
			{
				e.what ();
			}
			try
			{
				description = it.value ().at ("description").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				description = "";
			}
			MainStorageNode* nodePtr = new MainStorageNode (title, year, rating, description);
			nodePtr->setGenres (genreListPtr);
			genreListPtr->clear ();
			nodePtr->setContentRating (contentRating);
			resultListPtr->push_back (nodePtr);
		}
	}
	catch (const std::exception& e)
	{
		throw e.what ();
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::jsonStrToNodeArrAPI2 (std::string html)
{
	List<MainStorageNode*>* resultListPtr = new List<MainStorageNode*>;
	int theMovieDBId = 0;
	std::string title = "";
	int year = 0;
	std::string dateStr = "";
	List<std::string>* date;
	double rating = 0.0;
	List<std::string>* genreListPtr = new List<std::string> ();
	std::string description = "";
	/* this following try and catch is the biggest
	point of failure in the program.
	*/
	try
	{
#if DEBUG_MODE
		std::cout << std::endl;
#endif
		auto j = json::parse (html);
		for (json::iterator it = j["results"].begin (); it != j["results"].end (); ++it)
		{
			try
			{
				theMovieDBId = it.value ().at ("id").get<int> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				theMovieDBId = -1;
			}
			try
			{
				title = it.value ().at ("title").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				title = "";
			}
			try
			{
				dateStr = it.value ().at ("release_date").get<std::string> ();
				date = StringHelper::split (dateStr, "-");
				if (date->size () == 3)
				{
					year = stoi ((*date)[0]);
				}
				else
				{
					year = 0;
				}
			}
			catch (const std::exception& e)
			{
				e.what ();
				year = 0;
			}
			try
			{
				rating = it.value ().at ("vote_average").get<double> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				rating = 0.0;
			}
			try
			{
				description = it.value ().at ("overview").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				e.what ();
				description = "";
			}
			try
			{
				int i;
				int n = (int)it.value ().at ("genre_ids").size ();
				for (i = 0; i < n; i++)
				{
					genreListPtr->push_back (MDBgenreIdToStr (it.value ().at ("genre_ids")[i].get<int> ()));
				}
			}
			catch (const std::exception& e)
			{
				e.what ();
			}
			MainStorageNode* nodePtr = new MainStorageNode (title, year, rating, description);
			nodePtr->setGenres (genreListPtr);
			genreListPtr->clear ();
			nodePtr->setTheMovieDBId (theMovieDBId);
			resultListPtr->push_back (nodePtr);
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::jsonStrToNodeArrAPI3 (std::string html)
{
	List<MainStorageNode*>* resultListPtr = new List<MainStorageNode*>;
	int budget = 0;
	int revenue = 0;
	/* this following try and catch is the biggest
	point of failure in the program.
	*/
	try
	{
#if DEBUG_MODE
		std::cout << std::endl;
#endif
		auto j = json::parse (html);
		try
		{
			budget = j.at ("budget").get<int> ();
		}
		catch (const std::exception& e)
		{
			e.what ();
			budget = 0;
		}
		try
		{
			revenue = j.at ("revenue").get<int> ();
		}
		catch (const std::exception& e)
		{
			e.what ();
			revenue = 0;
		}
		MainStorageNode* nodePtr = new MainStorageNode ();
		nodePtr->setAdditional1 (budget, revenue);
		resultListPtr->push_back (nodePtr);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::jsonStrToNodeArrAPI4 (std::string html)
{
	List<MainStorageNode*>* resultListPtr = new List<MainStorageNode*>;
	List<std::string>* actorListPtr = new List<std::string> ();
	/* this following try and catch is the biggest
	point of failure in the program.
	*/
	try
	{
#if DEBUG_MODE
		std::cout << std::endl;
#endif
		auto j = json::parse (html);
		try
		{
			for (json::iterator it = j["cast"].begin (); it != j["cast"].end (); ++it)
			{
				actorListPtr->push_back (it.value ().at ("name").get<std::string> ());
			}
		}
		catch (const std::exception& e)
		{
			e.what ();
		}
		MainStorageNode* nodePtr = new MainStorageNode ();
		nodePtr->setActors (actorListPtr);
		resultListPtr->push_back (nodePtr);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::find1 (std::string title, int year)
{
	std::string yearQuery = "";
	if (year > 0) yearQuery = "&year=" + std::to_string (year);
	std::string response;
	List<MainStorageNode*>* resultListPtr;
	std::string query;
	try
	{
		query = "/api/find/movie?title=" + title + yearQuery;
		response = WinHTTP::getWebsite ("www.theimdbapi.org", query);
		response = WinHTTP::html (response);
		resultListPtr = MovieWebDB::jsonStrToNodeArrAPI1 (response);
#if DEBUG_MODE
		for (List<int>::size_type i = 0; i != resultListPtr->size (); i++)
		{
			std::cout << (*resultListPtr)[i] << std::endl;
		}
#endif
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::find2 (std::string title, int year)
{
	std::string yearQuery = "";
	if (year > 0) yearQuery = "&year=" + std::to_string (year);
	std::string response;
	List<MainStorageNode*>* resultListPtr;
	std::string query;
	try
	{
		query = "/3/search/movie?api_key=" + theMovieDB_API_Key + "&query=" + title + yearQuery;
		//std::cout << "Query:" << query << std::endl;
		response = WinHTTP::getWebsite ("api.themoviedb.org", query);
		//std::cout << response;
		response = WinHTTP::html (response);
		//std::cout << response;
		resultListPtr = MovieWebDB::jsonStrToNodeArrAPI2 (response);
#if DEBUG_MODE
		for (List<int>::size_type i = 0; i != resultListPtr->size (); i++)
		{
			std::cout << (*resultListPtr)[i] << std::endl;
		}
#endif
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::find3 (int movieId)
{
	std::string response;
	List<MainStorageNode*>* resultListPtr;
	std::string query;
	try
	{
		query = "/3/movie/" + std::to_string (movieId) + "?api_key=" + theMovieDB_API_Key;
		//std::cout << "Query:" << query << std::endl;
		response = WinHTTP::getWebsite ("api.themoviedb.org", query);
		//std::cout << response;
		response = WinHTTP::html (response);
		//std::cout << response;
		resultListPtr = MovieWebDB::jsonStrToNodeArrAPI3 (response);
#if DEBUG_MODE
		for (List<int>::size_type i = 0; i != resultListPtr->size (); i++)
		{
			std::cout << (*resultListPtr)[i] << std::endl;
		}
#endif
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

List<MainStorageNode*>* MovieWebDB::find4 (int movieId)
{
	std::string response;
	List<MainStorageNode*>* resultListPtr;
	std::string query;
	try
	{
		query = "/3/movie/" + std::to_string (movieId) + "/credits?api_key=" + theMovieDB_API_Key;
		//std::cout << "Query:" << query << std::endl;
		response = WinHTTP::getWebsite ("api.themoviedb.org", query);
		//std::cout << response;
		response = WinHTTP::html (response);
		//std::cout << response;
		resultListPtr = MovieWebDB::jsonStrToNodeArrAPI4 (response);
#if DEBUG_MODE
		for (List<int>::size_type i = 0; i != resultListPtr->size (); i++)
		{
			std::cout << (*resultListPtr)[i] << std::endl;
		}
#endif
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error (e.what ());
	}
	return resultListPtr;
}

std::string MovieWebDB::MDBgenreIdToStr (int genreId)
{
	std::string genre = "";
	if (genreId < 100000 && genreId > 0)
	{
		try
		{
			genre = genreMap->at (std::to_string (genreId));
		}
		catch (std::exception& e)
		{
			e.what ();
			//std::cout << "NOT FOUND: " << e.what () << std::endl;
		}
	}
	return genre;
}

void MovieWebDB::genreTableInit ()
{
	genreMap->insert (std::to_string (12), "Adventure");
	genreMap->insert (std::to_string (14), "Fantasy");
	genreMap->insert (std::to_string (18), "Drama");
	genreMap->insert (std::to_string (28), "Action");
	genreMap->insert (std::to_string (35), "Comedy");
	genreMap->insert (std::to_string (878), "Science Fiction");
	genreMap->insert (std::to_string (10749), "Romance");
}