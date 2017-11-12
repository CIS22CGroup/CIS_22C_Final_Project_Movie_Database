#ifndef MAIN_STORAGE_SEARCH_H
#define MAIN_STORAGE_SEARCH_H

#include <string>
#include <vector>
#include "MainStorageNode.h"

class MainStorageSearch
{
private:
public:
	static std::vector<MainStorageNode*>* titleFind (std::string title, MainStorageNode* headNode);
	static std::vector<MainStorageNode*>* yearFind (int year, MainStorageNode* headNode);
	static std::vector<MainStorageNode*>* contentRatingFind (std::string contentRating, MainStorageNode* headNode);
	static std::vector<MainStorageNode*>* ratingFind (double rating, MainStorageNode* headNode);
	static std::vector<MainStorageNode*>* genreFind (std::string genre, MainStorageNode* headNode);
	/* finds the intersection between two result sets */
	static std::vector<MainStorageNode*>* intersection (std::vector<MainStorageNode*>* nodeVector1, std::vector<MainStorageNode*>* nodeVector2);
};

#endif