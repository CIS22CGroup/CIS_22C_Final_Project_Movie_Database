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

#include <string>

class MainStorageNode
{
private:
	/** movie title
	@brief Transformers
	*/
	std::string title;
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
	/** movie genre #1
	@brief Action
	*/
	std::string genre1;
	/** movie genre #2
	@brief Science-Fiction
	*/
	std::string genre2;
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

	std::string getTitle ();
	int getYear ();
	double getRating ();
	std::string getGenre1 ();
	std::string getGenre2 ();

	friend std::ostream& operator<<(std::ostream& os, const MainStorageNode* obj);
};
#endif