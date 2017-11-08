#include "UserStorage.h"

UserStorage::UserStorage ()
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
std::string UserStorage::insert (std::string title, int year)
{
	bookmarkMap[toID (title, year)] = new UserStorageNode(title, year);
	return toID (title, year);
}
/* NOTE: an update method is not included for bookmarks 
just delete and add a new one */

/*
@pre
@post
@param ID unique movie ID
@return
*/
UserStorageNode* UserStorage::getNode (std::string ID)
{
	return bookmarkMap[ID];
}

/*
@pre
@post
@param ID unique movie ID
@return
*/
bool UserStorage::remove (std::string ID)
{
	return false;
}

/*
@pre 
@post 
@param title Movie title
@param year Movie year made
@return 
*/
std::string UserStorage::toID (std::string title, int year)
{
	std::replace (title.begin (), title.end (), ' ', '_');
	for (std::size_t i = 0; i < title.size (); ++i)
		while (!std::isalnum (title[i]) && i < title.size ()) title.erase (i, 1);
	return title + "_" + std::to_string (year);
}