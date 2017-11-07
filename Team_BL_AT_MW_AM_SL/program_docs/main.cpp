/* set to true when debugging modules. 
This will use the main for the command line 
WinMain is the entry point for the windows GUI
set to false for the final product
*/
#define COMMAND_LINE false

#include <string>
#include "FileIO.h"
#include "MainStorage.h"
#include "windowUI.h"


#if COMMAND_LINE
int main ()
{
	FileIO FileIOObj;
	FileIOObj.test ();
	system ("pause");
	return 0;
}
#endif

#if !COMMAND_LINE
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE, LPSTR pStr, int nCmd)
{
	return WindowUI::WinStart (hInst, NULL, pStr, nCmd);
};
#endif