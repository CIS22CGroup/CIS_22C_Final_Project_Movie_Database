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
	genre1 = "";
	genre2 = "";
	description = "";
}

MainStorageNode::MainStorageNode (std::string titleInit, int yearInit, int theMovieDBIdInit, double ratingInit, std::string descriptionInit)
{
	title = titleInit;
	year = yearInit;
	theMovieDBId = theMovieDBIdInit;
	rating = ratingInit;
	description = descriptionInit;
}

void MainStorageNode::setGenres (std::string genre1Init, std::string genre2Init)
{
	genre1 = genre1Init;
	genre2 = genre2Init;
}

std::string MainStorageNode::getTitle () { return title; }
int MainStorageNode::getYear () { return year; }
double MainStorageNode::getRating () { return rating; }
std::string MainStorageNode::getGenre1 (){ return genre1; }
std::string MainStorageNode::getGenre2 () { return genre2; }