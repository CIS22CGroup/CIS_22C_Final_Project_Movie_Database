#include "MainStorage.h"

MainStorage::MainStorage ()
{
	/* nodes in the map */
	size = 0;
}
/*
@pre None
@post Movie node added to
@param title Movie title
@param content_rating Movie audience rating
@param rating Movie critic rating score 1-10
@param year Movie year made
@param genre Movie IMDB first genre
@param description Movie description
@return Position of inserted movie node. -1 on failure
*/
std::string MainStorage::insert (std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	storageMap[toID (title, year)] = new MainStorageNode (title, year, content_rating, rating, genre, description);
	return toID (title, year);
}
bool MainStorage::update (std::string ID, std::string title, int year, std::string content_rating, double rating, std::string genre, std::string description)
{
	return false;
}
MainStorageNode* MainStorage::getNode (std::string ID)
{
	return storageMap[ID];
}
bool MainStorage::remove (std::string ID)
{
	storageMap.erase (ID);
	return true;
}

/*
@pre
@post
@param title Movie title
@param year Movie year made
@return
*/
std::string MainStorage::toID (std::string title, int year)
{
	std::replace (title.begin (), title.end (), ' ', '_');
	for (std::size_t i = 0; i < title.size (); ++i)
		while (!std::isalnum (title[i]) && i < title.size ()) title.erase (i, 1);
	return title + "_" + std::to_string(year);
}