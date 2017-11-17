#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <cassert>
#include <iostream>
#include "MainStorage.h"
#include "UserStorage.h"

class FileIO
{
public:
	bool mainStorageToFile (MainStorage *mainStorageObj, std::string filePath);
	bool fileToMainStorage (MainStorage *mainStorageObj, std::string filePath);
	bool userStorageToFile (UserStorage *userStorageObj, std::string filePath);
	bool fileToUserStorage (UserStorage *userStorageObj, std::string filePath);
};
#endif