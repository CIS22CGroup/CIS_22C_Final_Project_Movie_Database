#include "MainStorageNode.h"

MainStorageNode::MainStorageNode ()
{
	title = "";
	year = 0;
	content_rating = ""; 
	rating = 10; 
	genre = "";
	description = "";
	/* two leaf pointers for each searchable criterion */
	// title Binary Search Tree
	MainStorageNode* titleLeafLeft = nullptr;
	MainStorageNode* titleLeafRight = nullptr;
	// year Binary Search Tree
	MainStorageNode* yearLeafLeft = nullptr;
	MainStorageNode* yearLeafRight = nullptr;
	// contentRating Binary Search Tree
	MainStorageNode* contentRatingLeafLeft = nullptr;
	MainStorageNode* contentRatingLeafRight = nullptr;
	// rating Binary Search Tree
	MainStorageNode* ratingLeafLeft = nullptr;
	MainStorageNode* ratingLeafRight = nullptr;
	// genre Binary Search Tree
	MainStorageNode* genreLeafLeft = nullptr;
	MainStorageNode* genreLeafRight = nullptr;
}

MainStorageNode::MainStorageNode (std::string titleInit, int yearInit, std::string content_ratingInit, double ratingInit, std::string genreInit, std::string descriptionInit)
{
	title = titleInit;
	year = yearInit;
	content_rating = content_ratingInit;
	rating = ratingInit;
	genre = genreInit;
	description = descriptionInit;
}