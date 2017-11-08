#include "WinHTTP.h"

void WinHTTP::getWebsite (std::string url, std::string path)
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent *host;
	std::string get_http;
	char *buffer = new char[10000];
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
		printf ("error %d\n", err);
	}

	addr.S_un = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.S_un;
	inet_ntop (AF_INET, &(addr.S_un), IPstring, INET_ADDRSTRLEN);

	printf ("ip address : %s\n", IPstring);

	freeaddrinfo (res);

	WSACleanup ();

	get_http = "GET " + path + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	if (WSAStartup (MAKEWORD (2, 2), &wsaData) != 0)
	{
		std::cout << "WSAStartup failed.\n";
		system ("pause");
		//return 1;
	}

	Socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SockAddr.sin_port = htons (80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)&(addr.S_un));

	if (connect (Socket, (SOCKADDR*)(&SockAddr), sizeof (SockAddr)) != 0)
	{
		std::cout << "Could not connect";
		system ("pause");
		//return 1;
	}
	send (Socket, get_http.c_str (), strlen (get_http.c_str ()), 0);

	int nDataLength;
	while ((nDataLength = recv (Socket, buffer, 10000, 0)) > 0)
	{
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
		{

			website_HTML += buffer[i];
			i += 1;
		}
	}

	std::cout << website_HTML;

	closesocket (Socket);
	WSACleanup ();

}