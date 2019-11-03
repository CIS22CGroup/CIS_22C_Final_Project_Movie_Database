/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#include "MainStorageNode.h"

MainStorageNode::MainStorageNode ()
{
	title = "";
	titleListPtr = new List<std::string>;
	year = 0;
	theMovieDBId = 0;
	rating = 10;
	description = "";
	genreListPtr = new List<std::string>;
	actorListPtr = new List<std::string>;
}

MainStorageNode::MainStorageNode (std::string titleInit, int yearInit, double ratingInit, std::string descriptionInit)
{
	// strip out characters not in range
	title = StringHelper::sanitize255 (titleInit);
	// list will be lower-case. searches against it must also be lower case
	titleListPtr = StringHelper::split (StringHelper::toLower (StringHelper::sanitize (title, ' ')), " ");
	// remove entities under 3 characters long
	unsigned int i, n;
	n = titleListPtr->size ();
	for (i = 0; i < n; i++)
	{
		if ((*titleListPtr)[i].length () < 3)
		{
			titleListPtr->erase (i);
			i--;
			n--;
		}
	}
	theMovieDBId = 0;
	year = yearInit;
	rating = ratingInit;
	description = descriptionInit;
	genreListPtr = new List<std::string>;
	actorListPtr = new List<std::string>;
}

void MainStorageNode::setGenres (List<std::string>* genreListPtrInit)
{
	unsigned int i, n;
	n = genreListPtrInit->size ();
	for (i = 0; i < n; i++)
		if ((*genreListPtrInit)[i] != "")
			genreListPtr->push_back ((*genreListPtrInit)[i]);
}

void MainStorageNode::setTheMovieDBId (int idInit)
{
	theMovieDBId = idInit;
}
void MainStorageNode::setContentRating (std::string contentRatingInit)
{
	contentRating = contentRatingInit;
}

void MainStorageNode::setAdditional1 (int budgetInit, int revenueInit)
{
	budget = budgetInit;
	revenue = revenueInit;
}

void MainStorageNode::setActors (List<std::string>* actorListPtrInit)
{
	unsigned int i, n;
	n = actorListPtrInit->size ();
	for (i = 0; i < n; i++)
		if ((*actorListPtrInit)[i] != "")
			actorListPtr->push_back ((*actorListPtrInit)[i]);
}

int MainStorageNode::getGenreSize () { return genreSize; }
int MainStorageNode::getTitleIndexes () { return titleIndexes; }

std::string MainStorageNode::getTitle () { return title; }
List<std::string>* MainStorageNode::getTitleList () { return titleListPtr; }
std::string MainStorageNode::getTitleList (int index) { return (*titleListPtr)[index]; }
int MainStorageNode::getYear () { return year; }
int MainStorageNode::getTheMovieDBId () { return theMovieDBId; }
double MainStorageNode::getRating () { return rating; }
List<std::string>* MainStorageNode::getGenreList () { return genreListPtr; }
std::string MainStorageNode::getGenre (int index) { return (*genreListPtr)[index]; }
std::string MainStorageNode::getDescription() { return description; }

bool MainStorageNode::operator ==(MainStorageNode &other) const
{
	return theMovieDBId == other.getTheMovieDBId ();
}