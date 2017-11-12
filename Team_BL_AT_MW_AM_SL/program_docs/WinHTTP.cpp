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

	/*int nDataLength;
	while ((nDataLength = recv (Socket, buffer, 10000, 0)) > 0)
	{
		std::cout << nDataLength << std::endl;
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
		{
			website_HTML += buffer[i];
			i += 1;
		}
	}*/

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
			MainStorageNode* nodePtr = new MainStorageNode (it.value ()["title"].get<std::string> (), stoi (it.value ()["year"].get<std::string> ()), it.value ()["content_rating"].get<std::string> (), stod (it.value ()["rating"].get<std::string> ()), it.value ()["genre"][0].get<std::string> (), it.value ()["description"].get<std::string> ());
			nodeVector->push_back (nodePtr);
		}
	}
	catch (const std::exception& e)
	{
		//std::cout << e.what () << std::endl;
		throw e.what ();
	}
	return nodeVector;
}