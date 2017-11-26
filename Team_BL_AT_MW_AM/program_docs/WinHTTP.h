/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef WIN_HTTP_H
#define WIN_HTTP_H

#pragma comment(lib, "Ws2_32.lib")

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h> // getaddrinfo
#include <iostream>
#include <locale>

/**
@class WinHTTP
Uses libraries for a basic winsock application.
A collection of HTTP methods.
*/
class WinHTTP
{
public:
	static std::string getWebsite (std::string host, std::string path);
	static std::string html (std::string response);
};

#endif