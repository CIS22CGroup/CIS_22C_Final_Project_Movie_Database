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
#include "json.hpp" // JSON parser
#include "MainStorageNode.h"

using json = nlohmann::json;

class WinHTTP
{
public:
	static std::string getWebsite (std::string host, std::string path);
	static std::string html (std::string response);
	static std::vector<MainStorageNode*>* jsonStrToNodeArr (std::string html);
};

#endif