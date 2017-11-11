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

#include "WindowUI.h"

//=============================================================================
LRESULT CALLBACK WindowUI::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		return OnCreate(hwnd, reinterpret_cast<CREATESTRUCT*>(lParam));
	case WM_COMMAND:
	{
		switch (LOWORD (wParam))
		{
		case IDBC_DEFPUSHBUTTON:
		{
			//Step 5: User click on the button
			if (HIWORD (wParam) == BN_CLICKED)
			{
				UINT nButton = (UINT)LOWORD (wParam);
				HWND hButtonWnd = (HWND)lParam;

				// test
				char filename[MAX_PATH];

				OPENFILENAME ofn;
				ZeroMemory (&filename, sizeof (filename));
				ZeroMemory (&ofn, sizeof (ofn));
				ofn.lStructSize = sizeof (ofn);
				ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
				ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
				ofn.lpstrFile = filename;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrTitle = "Select a File, yo!";
				ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

				if (GetOpenFileNameA (&ofn))
				{
					MessageBox (hwnd, std::string ("You chose the file "+ std::string(filename)).c_str(), "File Chosen!", MB_OK);
				}
				else
				{
					// All this stuff below is to tell you exactly how you messed up above. 
					// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
					switch (CommDlgExtendedError ())
					{
						case CDERR_DIALOGFAILURE: MessageBox (hwnd, std::string ("CDERR_DIALOGFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_FINDRESFAILURE: MessageBox (hwnd, std::string ("CDERR_FINDRESFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_INITIALIZATION: MessageBox (hwnd, std::string ("CDERR_INITIALIZATION\n").c_str (), "Error", MB_OK); break;
						case CDERR_LOADRESFAILURE: MessageBox (hwnd, std::string ("CDERR_LOADRESFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_LOADSTRFAILURE: MessageBox (hwnd, std::string ("CDERR_LOADSTRFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_LOCKRESFAILURE: MessageBox (hwnd, std::string ("CDERR_LOCKRESFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_MEMALLOCFAILURE: MessageBox (hwnd, std::string ("CDERR_MEMALLOCFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_MEMLOCKFAILURE: MessageBox (hwnd, std::string ("CDERR_MEMLOCKFAILURE\n").c_str (), "Error", MB_OK); break;
						case CDERR_NOHINSTANCE: MessageBox (hwnd, std::string ("CDERR_NOHINSTANCE\n").c_str (), "Error", MB_OK); break;
						case CDERR_NOHOOK: MessageBox (hwnd, std::string ("CDERR_NOHOOK\n").c_str (), "Error", MB_OK); break;
						case CDERR_NOTEMPLATE: MessageBox (hwnd, std::string ("CDERR_NOTEMPLATE\n").c_str (), "Error", MB_OK); break;
						case CDERR_STRUCTSIZE: MessageBox (hwnd, std::string ("CDERR_STRUCTSIZE\n").c_str (), "Error", MB_OK); break;
						case FNERR_BUFFERTOOSMALL: MessageBox (hwnd, std::string ("FNERR_BUFFERTOOSMALL\n").c_str (), "Error", MB_OK); break;
						case FNERR_INVALIDFILENAME: MessageBox (hwnd, std::string ("FNERR_INVALIDFILENAME\n").c_str (), "Error", MB_OK); break;
						case FNERR_SUBCLASSFAILURE: MessageBox (hwnd, std::string ("FNERR_SUBCLASSFAILURE\n").c_str (), "Error", MB_OK); break;
						default: MessageBox (hwnd, std::string ("You cancelled.\n").c_str (), "Error", MB_OK);
					}
				}
				// test
			}
		}
		break;
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);    //signal end of application
		return 0;
	default:
		//let system deal with msg
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
//=============================================================================
int WindowUI::OnCreate(const HWND hwnd, CREATESTRUCT *cs) {
//handles the WM_CREATE message of the main, parent window; return -1 to fail
//window creation
	RECT rc = { 10, 10, 200, 40 };
//the various button types are created by simply varying the style bits
	HWND hwndButton = CreateButton(hwnd, cs->hInstance, BS_DEFPUSHBUTTON, rc, IDBC_DEFPUSHBUTTON,
			_T("OPEN FILE"));
	rc.top += 50;
	CreateButton(hwnd, cs->hInstance, BS_PUSHBUTTON, rc, IDBC_PUSHBUTTON,
			_T("PUSH BUTTON"));

	rc.top += 50;
	CreateButton(hwnd, cs->hInstance, BS_AUTOCHECKBOX, rc, IDBC_AUTOCHECKBOX,
			_T("CHECK BOX"));

	rc.top += 50;
	CreateButton(hwnd, cs->hInstance, BS_AUTORADIOBUTTON, rc, IDBC_AUTOCHECKBOX,
			_T("RADIO BUTTON"));

	rc = { 236, 10, 208, 200 };
	CreateButton(hwnd, cs->hInstance, BS_GROUPBOX, rc, IDBC_GROUPBOX,
			_T("GROUP BOX"));

	rc = { 240, 30, 200, 40 };
	HWND hIconBtn = CreateButton(hwnd, cs->hInstance, BS_ICON, rc, IDBC_ICON,
			_T("ICON BUTTON - NO TEXT"));
//get and assign the icon. Because LR_SHARED is used with a system 
//resource, there is no need to use DestroyIcon to free icon resources 
//when finshed with the icon.
	HICON hIcon = reinterpret_cast<HICON>(LoadImage(0, IDI_EXCLAMATION,
			IMAGE_ICON, 0, 0, LR_SHARED));
	SendMessage(hIconBtn, BM_SETIMAGE, IMAGE_ICON,
			reinterpret_cast<LPARAM>(hIcon));

	rc.top += 50;
	HWND hBmpBtn = CreateButton(hwnd, cs->hInstance, BS_BITMAP, rc, IDBC_BITMAP,
			_T("BITMAP BUTTON - NO TEXT"));

//get and assign the bitmap. Because LR_SHARED is used with a system 
//resource, there is no need to use DeleteObject to free bitmap
//resources when finshed with the bitmap.
	HBITMAP hBmp = reinterpret_cast<HBITMAP>(LoadImage(0,
			MAKEINTRESOURCE(OBM_CHECK), IMAGE_BITMAP, 0, 0, LR_SHARED));
	SendMessage(hBmpBtn, BM_SETIMAGE, IMAGE_BITMAP,
			reinterpret_cast<LPARAM>(hBmp));

	//handles the WM_CREATE message of the main, parent window; return -1 to fail
	//window creation
	rc = {10, 10, 200, 90};
	rc.left = 500;
	//the various combobox types are created by simply varying the style bits
	HWND hCombo = CreateCombobox(hwnd, cs->hInstance, CBS_SIMPLE, rc,
			IDCC_SIMPLE, _T(""));
	AddString(hCombo, _T("Simple Combobox"));

	rc.top += 90;
	hCombo = CreateCombobox(hwnd, cs->hInstance, CBS_DROPDOWN, rc,
			IDCC_DROPDOWN, _T(""));
	AddString(hCombo, _T("Drop Down Combobox"));

	rc.top += 40;
	hCombo = CreateCombobox(hwnd, cs->hInstance, CBS_DROPDOWNLIST, rc,
			IDCC_DROPDOWNLIST, _T(""));
	AddString(hCombo, _T("Drop Down List Combobox"));
	return 0;
}
//=============================================================================
inline int WindowUI::ErrMsg(const ustring& s) {
	return MessageBox(0, s.c_str(), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
}
//=============================================================================
HWND WindowUI::CreateButton(const HWND hParent, const HINSTANCE hInst, DWORD dwStyle,
		const RECT& rc, const int id, const ustring& caption) {
	dwStyle |= WS_CHILD | WS_VISIBLE;
	return CreateWindowEx(0,                            //extended styles
			_T("button"),                 //control 'class' name
			caption.c_str(),              //control caption
			dwStyle,                      //control style 
			rc.left,                      //position: left
			rc.top,                       //position: top
			rc.right,                     //width
			rc.bottom,                    //height
			hParent,                      //parent window handle
			//control's ID
			reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), hInst, //application instance
			0);                           //user defined info
}
//=============================================================================
//=============================================================================
HWND WindowUI::CreateCombobox(const HWND hParent, const HINSTANCE hInst, DWORD dwStyle,
		const RECT& rc, const int id, const ustring& caption) {
	dwStyle |= WS_CHILD | WS_VISIBLE;
	return CreateWindowEx(0,                            //extended styles
			_T("combobox"),               //control 'class' name
			caption.c_str(),              //control caption
			dwStyle,                      //control style 
			rc.left,                      //position: left
			rc.top,                       //position: top
			rc.right,                     //width
			rc.bottom,                    //height
			hParent,                      //parent window handle
			//control's ID
			reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), hInst, //application instance
			0);                           //user defined info
}
//=============================================================================
inline UINT WindowUI::AddString(const HWND hCombo, const ustring& s) {
	return static_cast<UINT>(SendMessage(hCombo, CB_ADDSTRING, 0,
			reinterpret_cast<LPARAM>(s.c_str())));
}
//=============================================================================
int WINAPI WindowUI::WinStart (HINSTANCE hInst, HINSTANCE, LPSTR pStr, int nCmd)
{
	ustring classname = _T ("SIMPLEWND");
	WNDCLASSEX wcx = { 0 };  //used for storing information about the wnd 'class'

	wcx.cbSize = sizeof (WNDCLASSEX);
	wcx.lpfnWndProc = WndProc;//wnd Procedure pointer
	wcx.hInstance = hInst;//app instance
						  //use 'LoadImage' to load wnd class icon and cursor as it supersedes the 
						  //obsolete functions 'LoadIcon' and 'LoadCursor', although these functions will 
						  //still work. Because the icon and cursor are loaded from system resources ie 
						  //they are shared, it is not necessary to free the image resources with either 
						  //'DestroyIcon' or 'DestroyCursor'.
	wcx.hIcon = reinterpret_cast<HICON>(LoadImage (0, IDI_APPLICATION,
		IMAGE_ICON, 0, 0, LR_SHARED));
	wcx.hCursor = reinterpret_cast<HCURSOR>(LoadImage (0, IDC_ARROW,
		IMAGE_CURSOR, 0, 0, LR_SHARED));
	wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
	wcx.lpszClassName = classname.c_str ();
	//the window 'class' (not c++ class) has to be registered with the system
	//before windows of that 'class' can be created
	if (!RegisterClassEx (&wcx))
	{
		ErrMsg (_T ("Failed to register wnd class"));
		return -1;
	}

	int desktopwidth = GetSystemMetrics (SM_CXSCREEN);
	int desktopheight = GetSystemMetrics (SM_CYSCREEN);

	HWND hwnd = CreateWindowEx (0,                     //extended styles
		classname.c_str (),//name: wnd 'class'
		_T ("Button Controls"),//wnd title
		WS_OVERLAPPEDWINDOW,//wnd style
		desktopwidth / 4,//position:left
		desktopheight / 4,//position: top
		desktopwidth / 2,//width
		desktopheight / 2,//height
		0,//parent wnd handle
		0,//menu handle/wnd id
		hInst,//app instance
		0);//user defined info
	if (!hwnd)
	{
		ErrMsg (_T ("Failed to create wnd"));
		return -1;
	}

	ShowWindow (hwnd, nCmd);
	UpdateWindow (hwnd);

	//start message loop - windows applications are 'event driven' waiting on user,
	//application or system signals to determine what action, if any, to take. Note 
	//that an error may cause GetMessage to return a negative value so, ideally,  
	//this result should be tested for and appropriate action taken to deal with 
	//it(the approach taken here is to simply quit the application).
	MSG msg;
	while (GetMessage (&msg, 0, 0, 0)>0)
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return static_cast<int>(msg.wParam);
}