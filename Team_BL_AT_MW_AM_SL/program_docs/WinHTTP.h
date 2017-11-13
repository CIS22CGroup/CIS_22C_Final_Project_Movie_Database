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
private:
	static std::vector<std::string>* genreVector;
public:
	static std::string getWebsite (std::string host, std::string path);
	static std::string html (std::string response);
	static std::vector<MainStorageNode*>* jsonStrToNodeArrAPI1 (std::string html);
	static std::vector<MainStorageNode*>* jsonStrToNodeArrAPI2 (std::string html);
	static std::vector<MainStorageNode*>* find (std::string title, int year = 0);
	static std::vector<std::string> split (std::string target, std::string delim);
	static std::string MDBgenreIdToStr (int genreId);
	static void genreTableInit ();
};

#endif