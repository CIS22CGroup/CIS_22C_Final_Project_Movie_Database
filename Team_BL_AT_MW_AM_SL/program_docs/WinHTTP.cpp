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

std::vector<MainStorageNode*>* WinHTTP::jsonStrToNodeArr (std::string html)
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
				title = it.value ().at("title").get<std::string> ();
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

std::vector<MainStorageNode*>* WinHTTP::find (std::string title, int year)
{
	std::string yearQuery = "";
	if (year > 0) yearQuery = "&year=" + std::to_string (year);
	std::string response;
	std::vector<MainStorageNode*>* nodeVector;
	std::string query;
	try
	{
		query = "/api/find/movie?title=" + title + yearQuery;
		//std::cout << "Query:" << query << std::endl;
		response = WinHTTP::getWebsite ("www.theimdbapi.org", query);
		//std::cout << response;
		response = WinHTTP::html (response);
		//std::cout << response;
		nodeVector = WinHTTP::jsonStrToNodeArr (response);
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