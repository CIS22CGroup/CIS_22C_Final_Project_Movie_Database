/*
Branden Lee, Anh Truong, Alexander Morfin, and Michael Wu
CIS 22C
Fall 2017
Final Project

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#include "FileIO.h"

bool FileIO::mainStorageToFile (MainStorage *mainStoragePtr, std::string filePath)
{
	// variable declarations
	HashMap <MainStorageNode*>* movieHashMapPtr;
	List<HashMapNode<MainStorageNode*>*>* movieHashMapListPtr;
	HashMapNode<MainStorageNode*>* movieHashMapNodePtr;
	std::string key, serializedData;
	MainStorageNode* movieNodePtr;
	unsigned int i, n, j, n1;
	bool flag = false;
	// open file for writing
	std::ofstream myFile;
	myFile.open (filePath);
	if (myFile)
	{
		// get the entire movie hash table
		movieHashMapPtr = mainStoragePtr->getTable ();
		n = movieHashMapPtr->max_size ();
		// loop through the entire hash table and look at the "buckets"
		for (i = 0; i < n; i++)
		{
			// hash table "buckets" might be null. check if they exist.
			if (movieHashMapPtr->existHash (i))
			{
				movieHashMapListPtr = movieHashMapPtr->getHash (i);
				// loop through every linked-list in the bucket
				n1 = movieHashMapListPtr->size ();
				for (j = 0; i < n1; i++)
				{
					// get the hash table nodes from the list
					movieHashMapNodePtr = (*movieHashMapListPtr)[j];
					key = movieHashMapNodePtr->getKey ();
					movieNodePtr = movieHashMapNodePtr->getValue ();
					//--------------------------------
					// YOUR CODE HERE
					//--------------------------------
					// grab data from the movie node
					// movieNodePtr->getTitle ();
					// movieNodePtr->getYear ();
					// do some serialization here
					// serializedData += "";
				}
			}
		}
		// Done serializing data. Write it to file.
		if (serializedData.length () > 0)
		{
			flag = true;
			myFile << serializedData;
			myFile.close ();
		}
	}
	return flag;
}
bool FileIO::fileToMainStorage (MainStorage *mainStoragePtr, std::string filePath)
{
	std::string key, title, description, genre;
	int year, theMovieDBId;
	double rating;
	bool flag = false;
	std::ifstream myFile;
	MainStorageNode* movieNodePtr;
	List<std::string>* genreListPtr = new List<std::string> ();
	// open file
	myFile.open (filePath);
	if (myFile.is_open ())
	{
		flag = true;
		// While the file is good
		while (myFile.good ())
		{
			//--------------------------------
			// YOUR CODE HERE
			//--------------------------------
			// do some data validation here
			throw std::runtime_error ("The database file is invalid");
			// sample data deserialization
			myFile >> key >> theMovieDBId >> title >> year >> rating >> description;
			// REMEMBER: you must also get the genre list
			while (myFile >> genre)
			{
				myFile >> genre;
				genreListPtr->push_back (genre);
			}
			// create the movie node
			movieNodePtr = new MainStorageNode (title, year, rating, description);
			movieNodePtr->setGenres (genreListPtr);
			genreListPtr->clear ();
			movieNodePtr->setTheMovieDBId (theMovieDBId);
			// insert into the movie database
			mainStoragePtr->insert (movieNodePtr);
		}
		myFile.close ();
	}
	return flag;
}