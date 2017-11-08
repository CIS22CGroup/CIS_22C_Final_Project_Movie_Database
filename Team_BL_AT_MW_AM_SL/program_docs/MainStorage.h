#ifndef MAIN_STORAGE_H
#define MAIN_STORAGE_H

#include <map>
#include <algorithm>
#include <string>
#include <cctype>
#include "MainStorageNode.h"

class MainStorage
{
private:
	std::map <std::string, MainStorageNode*> storageMap;
	unsigned int size;
	MainStorageNode * titleBSTHead;
	MainStorageNode * yearBSTHead;
	MainStorageNode * contentRatingBSTHead;
	MainStorageNode * ratingBSTHead;
	MainStorageNode * genreBSTHead;
public:
	MainStorage ();
	std::string insert (std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description);
	bool update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description);
	MainStorageNode* getNode (std::string ID);
	bool remove(std::string ID);
	std::string toID (std::string title, int year);
};

#endif