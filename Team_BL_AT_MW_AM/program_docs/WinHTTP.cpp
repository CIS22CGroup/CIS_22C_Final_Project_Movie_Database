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
#include "WinHTTP.h"

std::string WinHTTP::getWebsite (std::string url, std::string path)
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	std::string get_http;
	char *buffer = new char[1024];
	std::string website_HTML, errMsg;
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
		errMsg = "";
		if (err == 11001)
		{
			errMsg = "Host not found";
		}
		throw std::runtime_error ("Error Code " + std::to_string (err) + (errMsg.length () > 0 ? ": " + errMsg : ""));
	}

	try
	{
		addr.S_un = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.S_un;
		inet_ntop (AF_INET, &(addr.S_un), IPstring, INET_ADDRSTRLEN);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error ("Could not connect to the internet." + std::string(e.what ()));
	}

#if DEBUG_MODE
	std::cout << "ip address: " << IPstring;
#endif

	freeaddrinfo (res);

	WSACleanup ();

	get_http = "GET " + path + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	if (WSAStartup (MAKEWORD (2, 2), &wsaData) != 0)
	{
		throw std::runtime_error ("WSAStartup failed.");
		//return 1;
	}

	Socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SockAddr.sin_port = htons (80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)&(addr.S_un));

	if (connect (Socket, (SOCKADDR*)(&SockAddr), sizeof (SockAddr)) != 0)
	{
		throw std::runtime_error ("Could not connect.");
		//return 1;
	}
	send (Socket, get_http.c_str (), (int)strlen (get_http.c_str ()), 0);

	int n;
	while ((errno = 0, (n = recv (Socket, buffer, sizeof (buffer), 0)) > 0) ||
		errno == EINTR)
	{
		if (n > 0)
			website_HTML.append (buffer, n);
	}

	if (n < 0)
	{
		/* handle error - for example throw an exception*/
		throw std::runtime_error ("Not sure what happened.");
	}

	closesocket (Socket);
	WSACleanup ();
	return website_HTML;
	}

std::string WinHTTP::html (std::string response)
{
	return response.substr (response.find ("\r\n\r\n") + 4);
}