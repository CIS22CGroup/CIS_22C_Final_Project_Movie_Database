#include "UserStorageNode.h"

UserStorageNode::UserStorageNode ()
{
	title = "";
	year = 0;
}

UserStorageNode::UserStorageNode (std::string titleInit, int yearInit)
{
	title = titleInit;
	year = yearInit;
}