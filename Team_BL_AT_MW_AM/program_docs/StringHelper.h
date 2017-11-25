/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
#include <locale>
#include "List.h"

/**
@class StringHelper
A collection of static string manipulating methods
*/
class StringHelper
{
public:
	static List<std::string>* split (std::string target, std::string delim);

	/** converts a title and year to an alphanumeric ID with underscores\n
	spaces and non-alphanumeric characters become underscores
	@param title Movie title
	@param year Movie year made
	@return alphanumeric ID with underscores
	*/
	static std::string toID (std::string title, int year);

	/** replaces non-alphanumeric characters
	@param str unsanitized string
	@return sanitized string
	*/
	static std::string sanitize (std::string str, char replace);

	/** replaces all strings matching "from" with string "to"
	@pre str is not empty
	@post str is replaced
	@param str Original string
	@param from match string
	@param to replace string
	*/
	static void replaceAll (std::string& str, const std::string& from, const std::string& to);

	static std::string toLower (std::string str);
	static unsigned int hashStr (std::string str, unsigned int size);
};
#endif