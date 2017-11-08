#ifndef MAIN_STORAGE_H
#define MAIN_STORAGE_H

#include <map>
#include "MainStorageNode.h"

class MainStorage
{
private:
	std::map <int, MainStorageNode> storageMap;
};

#endif