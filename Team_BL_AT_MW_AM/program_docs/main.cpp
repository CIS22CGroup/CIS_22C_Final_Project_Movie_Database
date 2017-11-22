/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

/**
@mainpage Movie Database
This program will allow the user to find more information about a movie.
*/
#define DEBUG_MODE true

#include "CommandLineUI.h"

int main ()
{
	CommandLineUI::enterLoop ();
	system ("pause");
	return 0;
}