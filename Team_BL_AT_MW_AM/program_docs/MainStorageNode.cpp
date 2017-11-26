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
	year = 0;
	theMovieDBId = 0;
	rating = 10; 
	genre = new std::string[genreSize];
	genreItems = 0;
	description = "";
}

MainStorageNode::MainStorageNode (std::string titleInit, int yearInit, int theMovieDBIdInit, double ratingInit, std::string descriptionInit)
{
	// strip out characters not in range
	title = StringHelper::sanitize255(titleInit);
	// list will be lower-case. searches against it must also be lower case
	titleList = StringHelper::split (StringHelper::toLower (StringHelper::sanitize(title,' ')), " ");
	// remove entities under 3 characters long
	unsigned int i, n;
	n = titleList->size ();
	for (i = 0; i < n; i++)
	{
		if ((*titleList)[i].length () < 3)
		{
			titleList->erase (i);
			i--;
			n--;
		}
	}
	year = yearInit;
	theMovieDBId = theMovieDBIdInit;
	rating = ratingInit;
	genre = new std::string[genreSize];
	genreItems = 0;
	description = descriptionInit;
}

void MainStorageNode::setGenres (std::string genre1Init, std::string genre2Init)
{
	if(genre1Init != "") genre[genreItems++] = StringHelper::sanitize255 (genre1Init);
	if (genre2Init != "") genre[genreItems++] = StringHelper::sanitize255 (genre2Init);
}

int MainStorageNode::getGenreSize () { return genreSize; }
int MainStorageNode::getTitleIndexes () { return titleIndexes; }

std::string MainStorageNode::getTitle () { return title; }
List<std::string>* MainStorageNode::getTitleList () { return titleList; }
std::string MainStorageNode::getTitleList (int index) { return (*titleList)[index]; }
int MainStorageNode::getYear () { return year; }
int MainStorageNode::getTheMovieDBId () { return theMovieDBId; }
double MainStorageNode::getRating () { return rating; }
std::string MainStorageNode::getGenre (int index){ return genre[index]; }

bool MainStorageNode::operator ==(MainStorageNode &other) const
{
	return theMovieDBId == other.getTheMovieDBId ();
}