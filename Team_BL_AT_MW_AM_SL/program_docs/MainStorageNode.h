#ifndef MAIN_STORAGE_NODE_H
#define MAIN_STORAGE_NODE_H

#include <string>

class MainStorageNode
{
private:
	std::string title; // Transformers
	int year; // 2007
	std::string contentRating; // PG-13
	double rating; // 7.1
	std::string genre; // Action
	std::string description; 
	/*An ancient struggle between two Cybertronian races, 
	the heroic Autobots and the evil Decepticons, comes to Earth, 
	with a clue to the ultimate power held by a teenager.*/
	/* two leaf pointers for each searchable criterion */
	// title Binary Search Tree
	MainStorageNode* titleLeafLeft;
	MainStorageNode* titleLeafRight;
	// year Binary Search Tree
	MainStorageNode* yearLeafLeft;
	MainStorageNode* yearLeafRight;
	// contentRating Binary Search Tree
	MainStorageNode* contentRatingLeafLeft;
	MainStorageNode* contentRatingLeafRight;
	// rating Binary Search Tree
	MainStorageNode* ratingLeafLeft;
	MainStorageNode* ratingLeafRight;
	// genre Binary Search Tree
	MainStorageNode* genreLeafLeft;
	MainStorageNode* genreLeafRight;
public:
	MainStorageNode ();
	MainStorageNode (std::string titleInit, int yearInit, std::string contentRatingInit, double ratingInit, std::string genreInit, std::string descriptionInit);

	friend std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj);
};
#endif