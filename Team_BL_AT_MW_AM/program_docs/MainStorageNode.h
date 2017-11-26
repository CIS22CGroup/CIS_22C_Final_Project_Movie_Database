/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef MAIN_STORAGE_NODE_H
#define MAIN_STORAGE_NODE_H

#include <iostream>
#include <string>
#include "List.h"
#include "StringHelper.h"

/**
@class MainStorageNode
The main storage node is also known as the movie node. This contains
all the movie data and should be pointed to in search and storage
methods. 
*/
class MainStorageNode
{
private:
	static const int genreSize = 2;
	static const int titleIndexes = 10;

	/** movie title
	@brief Transformers
	*/
	std::string title;
	List<std::string>* titleList;
	/** movie year released
	@brief 2007
	*/
	int year;
	/** Move Database ID
	*/
	int theMovieDBId;
	/** movie rating on scale 1.0 to 10.0
	@brief 7.1
	*/
	double rating;
	/** movie genre array
	@brief Action
	*/
	std::string* genre;
	int genreItems;
	/** movie description
	@brief An ancient struggle between two Cybertronian races,
	the heroic Autobots and the evil Decepticons, comes to Earth,
	with a clue to the ultimate power held by a teenager.
	*/
	std::string description;
public:
	MainStorageNode ();
	MainStorageNode (std::string titleInit, int yearInit, int theMovieDBIdInit, double ratingInit, std::string descriptionInit);

	void setGenres (std::string genre1Init, std::string genre2Init);

	int MainStorageNode::getGenreSize ();
	int MainStorageNode::getTitleIndexes ();

	std::string getTitle ();
	List<std::string>* getTitleList ();
	std::string getTitleList (int index);
	int getYear ();
	int getTheMovieDBId ();
	double getRating ();
	std::string getGenre (int index);

	friend std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj);
	bool MainStorageNode::operator ==(MainStorageNode &b) const;
};
#endif