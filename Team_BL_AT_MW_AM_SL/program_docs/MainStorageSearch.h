#ifndef MAIN_STORAGE_SEARCH_H
#define MAIN_STORAGE_SEARCH_H

#include <string>
#include "MainStorageNode.h"

class MainStorageSearch
{
private:
public:
	bool titleFind (std::string title, MainStorageNode* headNode, MainStorageNode** resultNodes);
};

#endif