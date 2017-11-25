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
	title = titleInit;
	year = yearInit;
	theMovieDBId = theMovieDBIdInit;
	rating = ratingInit;
	genre = new std::string[genreSize];
	genreItems = 0;
	description = descriptionInit;
}

void MainStorageNode::setGenres (std::string genre1Init, std::string genre2Init)
{
	if(genre1Init != "") genre[genreItems++] = genre1Init;
	if (genre2Init != "") genre[genreItems++] = genre2Init;
}

int MainStorageNode::getGenreSize () { return genreSize; }
int MainStorageNode::getTitleIndexes () { return titleIndexes; }

std::string MainStorageNode::getTitle () { return title; }
int MainStorageNode::getYear () { return year; }
int MainStorageNode::getTheMovieDBId () { return theMovieDBId; }
double MainStorageNode::getRating () { return rating; }
std::string MainStorageNode::getGenre (int index){ return genre[index]; }

bool MainStorageNode::operator ==(MainStorageNode &other) const
{
	return theMovieDBId == other.getTheMovieDBId ();
}