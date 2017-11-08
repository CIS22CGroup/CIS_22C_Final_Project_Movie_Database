#ifndef WIN_HTTP_H
#define WIN_HTTP_H

#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>

class WinHTTP
{
public:
	static void getWebsite (std::string host, std::string path);
};

#endif