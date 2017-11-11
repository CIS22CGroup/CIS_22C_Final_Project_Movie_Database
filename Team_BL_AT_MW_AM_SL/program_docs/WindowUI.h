//=============================================================================
//BUTTON CONTROLS - Copyright © 2000,2005 Ken Fitlike
//=============================================================================
//API functions used: CreateWindowEx,DefWindowProc,DispatchMessage,GetMessage,
//GetSystemMetrics,LoadImage,MessageBox,PostQuitMessage,RegisterClassEx,
//SendMessage,ShowWindow,UpdateWindow,TranslateMessage,WinMain.
//=============================================================================
//This demonstrates the creation of the following button types: default push 
//button,push button,check box,radio button and groupbox. The image style of 
//'bitmap' buttons (BS_BITMAP) and 'icon' buttons (BS_ICON) can be used in 
//conjunction with other button styles to create image checkboxes, radio 
//buttons etc. The default is a push button.
//=============================================================================
#if defined _MSC_VER || defined __BORLANDC__
#define OEMRESOURCE
#endif

#ifndef WINDOW_UI_H
#define WINDOW_UI_H

#include <string>
#include <tchar.h>    //string and other mapping macros
#include <windows.h>  //include all the basics

class WindowUI
{
private:
	//define an unicode string type alias
	typedef std::basic_string<TCHAR> ustring;
	//=============================================================================
	//message processing function declarations
	static LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
	static int OnCreate (const HWND, CREATESTRUCT*);

	//non-message function declarations
	static HWND CreateButton (const HWND, const HINSTANCE, DWORD, const RECT&, const int,
		const ustring&);
	static inline UINT AddString (const HWND, const ustring&);
	static HWND CreateCombobox (const HWND, const HINSTANCE, DWORD, const RECT&, const int,
		const ustring&);
	static inline int ErrMsg (const ustring&);

	//setup some button id's
	static enum
	{
		IDBC_DEFPUSHBUTTON = 200,
		IDBC_PUSHBUTTON = 50,
		IDBC_AUTOCHECKBOX,
		IDBC_AUTORADIOBUTTON,
		IDBC_GROUPBOX,
		IDBC_ICON,
		IDBC_BITMAP,
		IDCC_SIMPLE = 200,
		IDCC_DROPDOWN,
		IDCC_DROPDOWNLIST
	};
public:
	static int WINAPI WinStart (HINSTANCE hInst, HINSTANCE, LPSTR pStr, int nCmd);
};

#endif