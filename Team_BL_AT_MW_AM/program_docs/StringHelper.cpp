/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "StringHelper.h"

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

List<std::string>* StringHelper::split (std::string target, std::string delim)
{
	List<std::string>* listPtr = new List<std::string> ();
	if (!target.empty ())
	{
		std::string::size_type start = 0;
		do
		{
			size_t x = target.find (delim, start);
			if (x == std::string::npos)
				break;

			listPtr->push_back (target.substr (start, x - start));
			start = x + delim.size ();
		} while (true);

		listPtr->push_back (target.substr (start));
	}
	return listPtr;
}

std::string StringHelper::toID (std::string title, int year)
{
	return sanitize (title, '_') + "_" + std::to_string (year);
}

std::string StringHelper::sanitize (std::string str, char replace)
{
	for (std::size_t i = 0; i < str.size (); ++i)
	{
		// we check by character code because std::isalnum crashes the program on characters out of range
		if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= '0' && str[i] <= '9') && str[i] != replace)
			str.replace (i, 1, std::string (1, replace));
	}
	return str;
}

std::string StringHelper::sanitize255 (std::string str)
{
	for (std::size_t i = 0; i < str.size (); ++i)
	{
		if (str[i] > 255 && str[i] < 0)
			str.erase (i, 1);
	}
	return str;
}

void StringHelper::replaceAll (std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty ())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find (from, start_pos)) != std::string::npos)
	{
		str.replace (start_pos, from.length (), to);
		start_pos += to.length (); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

std::string StringHelper::toLower (std::string str)
{
	std::locale loc;
	std::string result = "";
	for (std::string::size_type i = 0; i < str.length (); ++i)
		result += std::tolower (str[i], loc);
	return result;
}

unsigned int StringHelper::hashStr (std::string str, unsigned int size)
{
	const char * s = new char[str.length () + 1];
	s = str.c_str ();
	unsigned int h = FIRSTH;
	while (*s)
	{
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h % size; // or return h % C;
}