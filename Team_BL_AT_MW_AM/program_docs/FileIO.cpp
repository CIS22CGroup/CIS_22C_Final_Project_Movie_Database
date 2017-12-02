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
	double rating;

	List<std::string>* genreListPtr;

	// open file for writing
	std::ofstream myFile;
	myFile.open (filePath);
	if (myFile)
	{
		myFile << filePath << "\n";
		///////serializedData = filePath+"\n";

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
				for (j = 0; j < n1; j++)
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
					serializedData = "\n*****";
					serializedData += "\n***ID: " + std::to_string(movieNodePtr->getTheMovieDBId());
					serializedData += "\n***TT: " + movieNodePtr->getTitle();
					serializedData += "\n***YR: " + std::to_string(movieNodePtr->getYear());
					rating = floor(movieNodePtr->getRating() * 100.00 + 0.5) / 100;
					serializedData += "\n***RT: " + std::to_string(rating);
					serializedData += "\n***GG:";
					genreListPtr = movieNodePtr->getGenreList();
					for (unsigned int i=0; i < movieNodePtr->getGenreSize(); i++)
					{
						//serializedData += " " + std::to_string(i) + ": " + genreListPtr->getValue(i);
						serializedData += " *" + genreListPtr->getValue(i);
					}
					serializedData += "\n***DC: " + movieNodePtr->getDescription() + "\n";
					myFile << serializedData;
				}
			}
		}
		myFile << "\n**********";
		flag = true;
		myFile.close();
		// Done serializing data. Write it to file.
		/*
		if (serializedData.length () > 0)
		{
			flag = true;
			myFile << serializedData;
			myFile.close ();
		}
		*/
	}
	return flag;
}
bool FileIO::fileToMainStorage (MainStorage *mainStoragePtr, std::string filePath)
{
	std::string key, title, description, genre, path, readIn, word;
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
		myFile >> path;
		std::getline(myFile, readIn);
		while (myFile.good ())
		{
			
			std::getline(myFile, readIn);
			if (readIn == "**********")
			{
				myFile.close();
				return flag;
			}
			if(readIn != "*****")
				throw std::runtime_error ("The database file is invalid");

			// Movie ID
			std::getline(myFile, readIn);
			std::istringstream iss(readIn);
			iss >> word;
			if(word != "***ID:")
				throw std::runtime_error("The database file is invalid");
			iss >> readIn;
			theMovieDBId = std::stoi(readIn);

			// Movie Title
			std::getline(myFile, readIn);
			std::istringstream iss2(readIn);
			iss2 >> word;
			if(word != "***TT:")
				throw std::runtime_error("The database file is invalid");
			iss2 >> title;

			// Movie Year
			std::getline(myFile, readIn);
			std::istringstream iss6(readIn);
			iss6 >> word;
			if (word != "***YR:")
				throw std::runtime_error("The database file is invalid");
			iss6 >> readIn;
			year = std::stoi(readIn);

			// Movie Rating
			std::getline(myFile, readIn);
			std::istringstream iss3(readIn);
			iss3 >> word;
			if (word != "***RT:")
				throw std::runtime_error("The database file is invalid");
			iss3 >> readIn;
			rating = std::stod(readIn);

			// Movie Genre
			std::getline(myFile, readIn);
			std::istringstream iss4(readIn);
			if(word != "***GG:")
				throw std::runtime_error("The database file is invalid");
			// hard coded # of genres for now, 2
			while (iss4 >> readIn)
			{
				if (readIn.at(0) == '*')
				{
					genre = readIn.substr(1, std::string::npos);
				}
				else
				{
					genre += " " + readIn;
					genreListPtr->push_back(genre);
				}
			}

			// Movie Description
			std::getline(myFile, readIn);
			std::istringstream iss5(readIn);
			iss5 >> word;
			if (word != "***DC:")
				throw std::runtime_error("The database file is invalid");
			description = iss5.str();

			year = 0;
			/*
			while (myFile >> genre)
			{
				myFile >> genre;
				genreListPtr->push_back (genre);
			}
			*/
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