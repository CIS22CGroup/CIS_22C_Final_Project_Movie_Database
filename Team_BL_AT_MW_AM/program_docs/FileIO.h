/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
Use SDK Version: 10.0.15063.0 for De Anza Computers
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include "MainStorage.h"

/**
@class FileIO
contains file writing methods.
*/

class FileIO
{
public:
	/** serializes main storage into a file
	@pre file path exists
	@post writes to file
	@param mainStoragePtr main storage
	@param filePath file path
	@return true on success false on failure */
	static bool mainStorageToFile (MainStorage *mainStoragePtr, std::string filePath, std::function<void(MainStorageNode*)>* visit, unsigned int &operations);

	/** deserializes file to main storage
	@pre file path exists
	@post inserts data into main storage
	@param mainStoragePtr main storage
	@param filePath file path
	@return true on success false on failure */
	static bool fileToMainStorage (MainStorage *mainStoragePtr, std::string filePath, std::function<void(MainStorageNode*)>* visit, unsigned int &operations);
};
#endif