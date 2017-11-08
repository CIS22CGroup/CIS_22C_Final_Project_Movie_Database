#include "FileIO.h"

using json = nlohmann::json;

void FileIO::XMLtest ()
{
	rapidxml::xml_document<> doc;
	try
	{
		char doc_text[] = "<movieDB><movie><key>1</key><title>test1</title></movie><movie><key>2</key><title>test2</title></movie></movieDB>";
		doc.parse<0> (doc_text);

		auto node = doc.first_node ();
		assert (std::string ("movieDB") == node->name ());
		auto child = node->first_node (0, "");
		assert (child);
		child = node->first_node ();
		assert (std::string ("movie") == child->name ());
		auto child1 = node->first_node (0, "");
		assert (child1);
		child1 = child->first_node ("key");
		doc.validate ();
	}
	catch (rapidxml::parse_error & e)
	{
		std::cout << "Parse error: " << e.what () << std::endl << "At: " << e.where<char> () << std::endl;
	}
	catch (rapidxml::validation_error & e)
	{
		std::cout << "Validation error: " << e.what () << std::endl;
	}
	std::cout << doc.first_node ()->name () << std::endl;
	std::cout << doc.first_node ()->first_node ()->name () << std::endl;
	std::cout << doc.first_node ()->first_node ()->first_node ("key")->value () << std::endl;
	auto child = doc.first_node ();
	//child->next_sibling ();
	//std::cout << child->next_sibling ("movie")->first_node ("key")->value () << std::endl;
}

void FileIO::JSONtest ()
{
	// deserialize
	std::string JSON_string = "{ \"happy\": true, \"pi\": 3.141 }";
	auto j = json::parse (JSON_string);
	try
	{
		std::cout << "j[\"happy\"]=" << j["happy"] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what () << std::endl;
	}
	// serialize
	json j2 = {
		{ "pi", 3.141 },
		{ "happy", true },
		{ "name", "Niels" },
		{ "nothing", nullptr },
		{ "answer",{
			{ "everything", 42 }
		} },
		{ "list",{ 1, 0, 2 } },
		{ "object",{
			{ "currency", "USD" },
			{ "value", 42.99 }
		} }
	};
	try
	{
		std::cout << "j2.dump ()=" << j2.dump () << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what () << std::endl;
	}
}

bool FileIO::mainStorageToFile (MainStorage *mainStorageObj, std::string filePath)
{
	return false;
}
bool FileIO::fileToMainStorage (MainStorage *mainStorageObj, std::string filePath)
{
	return false;
}
bool FileIO::userStorageToFile (UserStorage *userStorageObj, std::string filePath)
{
	return false;
}
bool FileIO::fileToUserStorage (UserStorage *userStorageObj, std::string filePath)
{
	return false;
}