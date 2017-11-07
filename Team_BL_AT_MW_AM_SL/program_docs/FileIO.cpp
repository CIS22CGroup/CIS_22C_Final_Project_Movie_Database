#include "FileIO.h"

void FileIO::test ()
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