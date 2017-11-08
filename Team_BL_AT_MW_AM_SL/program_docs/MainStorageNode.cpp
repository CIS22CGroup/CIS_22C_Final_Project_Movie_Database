#include "MainStorageNode.h"

MainStorageNode::MainStorageNode ()
{
	title = "";
	year = 0;
	content_rating = ""; 
	rating = 10; 
	genre = "";
	description = "";
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