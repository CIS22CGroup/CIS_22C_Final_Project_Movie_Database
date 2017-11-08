#ifndef MAIN_STORAGE_NODE_H
#define MAIN_STORAGE_NODE_H

#include <string>

class MainStorageNode
{
private:
	std::string title; // Transformers
	int year; // 2007
	std::string content_rating; // PG-13
	double rating; // 7.1
	std::string genre; // Action
	std::string description; 
	/*An ancient struggle between two Cybertronian races, 
	the heroic Autobots and the evil Decepticons, comes to Earth, 
	with a clue to the ultimate power held by a teenager.*/
public:
	MainStorageNode ();
	MainStorageNode (std::string titleInit, int yearInit, std::string content_ratingInit, double ratingInit, std::string genreInit, std::string descriptionInit);
};

#endif