/* set to true when debugging modules.
This will use the main for the command line
WinMain is the entry point for the windows GUI
set to false for the final product
*/
#define DEBUG_MODE true

#include "CommandLineUI.h"

int main ()
{
	CommandLineUI::enterLoop ();
	system ("pause");
	return 0;
}