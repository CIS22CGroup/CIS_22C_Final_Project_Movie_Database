#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <cassert>
#include <iostream>
#include "rapidxml.hpp" // XML parser
#include "json.hpp" // JSON parser
#include "MainStorage.h"
#include "UserStorage.h"

class FileIO
{
public:
	void XMLtest ();
	void JSONtest ();
	bool mainStorageToFile (MainStorage *mainStorageObj, std::string filePath);
	bool fileToMainStorage (MainStorage *mainStorageObj, std::string filePath);
	bool userStorageToFile (UserStorage *userStorageObj, std::string filePath);
	bool fileToUserStorage (UserStorage *userStorageObj, std::string filePath);
};
#endif