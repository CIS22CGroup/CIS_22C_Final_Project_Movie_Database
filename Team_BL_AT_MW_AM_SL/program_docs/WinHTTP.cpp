#include "WinHTTP.h"

std::string WinHTTP::getWebsite (std::string url, std::string path)
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent *host;
	std::string get_http;
	char *buffer = new char[1024];
	std::string website_HTML;
	char IPstring[100];

	struct addrinfo hints, *res;
	struct in_addr addr;
	int err;

	WSAData data;
	WSAStartup (MAKEWORD (2, 0), &data);

	memset (&hints, 0, sizeof (hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	if ((err = getaddrinfo (url.c_str (), NULL, &hints, &res)) != 0)
	{
		throw "error" + err;
	}

	addr.S_un = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.S_un;
	inet_ntop (AF_INET, &(addr.S_un), IPstring, INET_ADDRSTRLEN);

#if DEBUG_MODE
	std::cout << "ip address: " << IPstring;
#endif

	freeaddrinfo (res);

	WSACleanup ();

	get_http = "GET " + path + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	if (WSAStartup (MAKEWORD (2, 2), &wsaData) != 0)
	{
		throw "WSAStartup failed.";
		//return 1;
	}

	Socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SockAddr.sin_port = htons (80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)&(addr.S_un));

	if (connect (Socket, (SOCKADDR*)(&SockAddr), sizeof (SockAddr)) != 0)
	{
		throw "Could not connect.";
		//return 1;
	}
	send (Socket, get_http.c_str (), strlen (get_http.c_str ()), 0);

	int n;
	while ((errno = 0, (n = recv (Socket, buffer, sizeof (buffer), 0)) > 0) ||
		errno == EINTR)
	{
		if (n > 0)
			website_HTML.append (buffer, n);
	}

	if (n < 0)
	{
		throw "idk";
		/* handle error - for example throw an exception*/
	}

	closesocket (Socket);
	WSACleanup ();
	return website_HTML;
}

std::string WinHTTP::html (std::string response)
{
	return response.substr (response.find ("\r\n\r\n") + 4);
}

std::vector<MainStorageNode*>* WinHTTP::jsonStrToNodeArrAPI1 (std::string html)
{
	std::vector<MainStorageNode*>* nodeVector = new std::vector<MainStorageNode*> ();
	std::string title = "";
	int year = 0;
	std::string contentRating = "";
	double rating = 0.0;
	std::string genre = "";
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
				title = "";
			}
			try
			{
				year = stoi (it.value ().at ("year").get<std::string> ());
			}
			catch (const std::exception& e)
			{
				year = 0;
			}
			try
			{
				contentRating = it.value ().at ("content_rating").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				contentRating = "";
			}
			try
			{
				rating = stod (it.value ().at ("rating").get<std::string> ());
			}
			catch (const std::exception& e)
			{
				rating = 0.0;
			}
			try
			{
				genre = it.value ().at ("genre")[0].get<std::string> ();
			}
			catch (const std::exception& e)
			{
				genre = "";
			}
			try
			{
				description = it.value ().at ("description").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				description = "";
			}
			MainStorageNode* nodePtr = new MainStorageNode (title, year, contentRating, rating, genre, description);
			nodeVector->push_back (nodePtr);
		}
	}
	catch (const std::exception& e)
	{
		throw e.what ();
	}
	return nodeVector;
}

std::vector<MainStorageNode*>* WinHTTP::jsonStrToNodeArrAPI2 (std::string html)
{
	std::vector<MainStorageNode*>* nodeVector = new std::vector<MainStorageNode*> ();
	int theMovieDBId = 0;
	std::string title = "";
	int year = 0;
	std::string dateStr = "";
	std::vector<std::string> date;
	std::string contentRating = "";
	double rating = 0.0;
	std::string genre1 = "";
	std::string genre2 = "";
	int genre1Id = 0;
	int genre2Id = 0;
	std::string actors = "";
	std::string description = "";
	int budget = 0;
	int revenue = 0;
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
				theMovieDBId = stoi (it.value ().at ("id").get<std::string> ());
			}
			catch (const std::exception& e)
			{
				theMovieDBId = -1;
			}
			try
			{
				title = it.value ().at ("title").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				title = "";
			}
			try
			{
				dateStr = it.value ().at ("release_date").get<std::string> ();
				date = WinHTTP::split (dateStr, "-");
				if (date.size() == 3)
				{
					year = stoi (date[0]);
				}
				else
				{
					year = 0;
				}
			}
			catch (const std::exception& e)
			{
				year = 0;
			}
			try
			{
				rating = it.value ().at ("vote_average").get<double> ();
			}
			catch (const std::exception& e)
			{
				rating = 0.0;
			}
			try
			{
				description = it.value ().at ("overview").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				description = "";
			}
			try
			{
				genre1Id = it.value ().at ("genre_ids")[0].get<int> ();
			}
			catch (const std::exception& e)
			{
				genre1Id = 0;
			}
			/*
			try
			{
				genre2Id = it.value ().at ("genre_ids")[1].get<int> ();
			}
			catch (const std::exception& e)
			{
				genre2Id = 0;
			}*/
			/*
			std::string query1 = "/3/movie/" + std::to_string (theMovieDBId) + "?api_key=a677473afe79ffa4994be03e56665d28&query=";
			auto j2 = json::parse (WinHTTP::html (WinHTTP::getWebsite ("api.themoviedb.org", query1)));
			try
			{
				genre1 = j2.at ("genres")[0].at ("name").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				genre1 = "";
			}
			try
			{
				genre2 = j2.at ("genres")[1].at ("name").get<std::string> ();
			}
			catch (const std::exception& e)
			{
				genre2 = "";
			}
			try
			{
				budget = j2.at ("budget").get<int> ();
			}
			catch (const std::exception& e)
			{
				budget = 0;
			}
			try
			{
				revenue = j2.at ("revenue").get<int> ();
			}
			catch (const std::exception& e)
			{
				revenue = 0;
			}
			std::string query2 = "/3/movie/" + std::to_string (theMovieDBId) + "/credits?api_key=a677473afe79ffa4994be03e56665d28&query=";
			auto j3 = json::parse (WinHTTP::html (WinHTTP::getWebsite ("api.themoviedb.org", query2)));
			for (json::iterator it2 = j3["cast"].begin (); it2 != j3["cast"].end (); ++it2)
			{
				try
				{
					actors += it2.value ().at ("name").get<std::string> ();
					if (it2 != j3["cast"].end ()-1)
					{
						actors += ", ";
					}
				}
				catch (const std::exception& e)
				{

				}
			}
			std::cout << actors << std::endl;
			*/
			MainStorageNode* nodePtr = new MainStorageNode (title, year, contentRating, rating, MDBgenreIdToStr (genre1Id), description);
			nodeVector->push_back (nodePtr);
		}
	}
	catch (const std::exception& e)
	{
		throw e.what ();
	}
	return nodeVector;
}

std::vector<MainStorageNode*>* WinHTTP::find (std::string title, int year)
{
	std::string yearQuery = "";
	if (year > 0) yearQuery = "&year=" + std::to_string (year);
	std::string response;
	std::vector<MainStorageNode*>* nodeVector;
	std::string query;
	try
	{
		//query = "/api/find/movie?title=" + title + yearQuery;
		query = "/3/search/movie?api_key=a677473afe79ffa4994be03e56665d28&query=" + title + yearQuery;
		//std::cout << "Query:" << query << std::endl;
		//response = WinHTTP::getWebsite ("www.theimdbapi.org", query);
		response = WinHTTP::getWebsite ("api.themoviedb.org", query);
		//std::cout << response;
		response = WinHTTP::html (response);
		//std::cout << response;
		nodeVector = WinHTTP::jsonStrToNodeArrAPI2 (response);
#if DEBUG_MODE
		for (std::vector<int>::size_type i = 0; i != nodeVector->size (); i++)
		{
			std::cout << (*nodeVector)[i] << std::endl;
		}
#endif
	}
	catch (const std::exception& e)
	{
		throw e.what ();
	}
	return nodeVector;
}

std::vector<std::string> WinHTTP::split (std::string target, std::string delim)
{
	std::vector<std::string> v;
	if (!target.empty ())
	{
		std::string::size_type start = 0;
		do
		{
			size_t x = target.find (delim, start);
			if (x == std::string::npos)
				break;

			v.push_back (target.substr (start, x - start));
			start += delim.size ();
		} while (true);

		v.push_back (target.substr (start));
	}
	return v;
}
std::string WinHTTP::MDBgenreIdToStr (int genreId)
{
	if (genreId < 10000 && genreId >0)
	{
		return (*genreVector)[genreId];
	}
	else
	{
		return "";
	}
}

std::vector<std::string>* WinHTTP::genreVector = new std::vector<std::string> (10000);

void WinHTTP::genreTableInit ()
{
	for (int i = 0; i < 10000; i++)
		(*genreVector)[i] = "";
	(*genreVector)[12] = "Adventure";
	(*genreVector)[14] = "Fantasy";
	(*genreVector)[28] = "Action";
	(*genreVector)[35] = "Comedy";
	(*genreVector)[878] = "Science Fiction";
}