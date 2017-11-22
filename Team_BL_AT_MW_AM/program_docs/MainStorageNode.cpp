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
	contentRating = ""; 
	rating = 10; 
	genre1 = "";
	genre2 = "";
	description = "";
}

MainStorageNode::MainStorageNode (std::string titleInit, int yearInit, std::string contentRatingInit, double ratingInit, std::string genreInit, std::string descriptionInit)
{
	title = titleInit;
	year = yearInit;
	contentRating = contentRatingInit;
	rating = ratingInit;
	genre1 = genreInit;
	description = descriptionInit;
}

std::string MainStorageNode::getTitle () { return title; }
int MainStorageNode::getYear () { return year; }
double MainStorageNode::getRating () { return rating; }
std::string MainStorageNode::getGenre1 (){ return genre1; }
std::string MainStorageNode::getGenre2 () { return genre2; }