#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "FileIO.h"
#include "MainStorage.h"
#include "MainStorageSearch.h"
#include "UserStorage.h"
#include "WinHTTP.h"

class CommandLineUI
{
private:
public:
	CommandLineUI ();
	static void enterLoop ();
};

#endif