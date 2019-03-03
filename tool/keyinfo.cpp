/*
   keyinfo.cpp

   1995.08.18
*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#include <pub/misc.hpp>

LRESULT CALLBACK _export WndProcpcs_main(HWND, UINT, WPARAM, LPARAM);

void pcs_main()
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc		= WndProcpcs_main;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszMenuName	= NULL;
	wndclass.hbrBackground	= get_StockObject(BLACK_BRUSH);
	wndclass.lpszClassName	= "Winpcs_main";

	RegisterClass(&wndclass);

	hWnd =
	CreateWindow
	(
		"Winpcs_main",
		"Key Info",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);

	while (get_Message(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

HDC hdcGlobal;

#pragma argsused
BOOL Winpcs_main_Create (HWND hWnd, LPCREATESTRUCT lpCreateStrct)
{
	hdcGlobal = get_DC(hWnd);
	set_TextColor(hdcGlobal,RGB(200,200,200));
	set_BkColor(hdcGlobal,RGB(0,0,0));
	return def_true;
}

#pragma argsused
void Winpcs_main_Destory (HWND hWnd)
{
	PostQuitMessage(0);
}

#pragma argsused
void Winpcs_main_KeySub (HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags, char* type)
{
	static int y;
	char buf[80];
	RECT rc;

	if (fDown)
	{
		get_ClientRect(hWnd,&rc);
		if (y+20 > rc.bottom)
		{
			y=0;
			InvalidateRect(hWnd,&rc,def_true);
			UpdateWindow(hWnd);
		}
		TextOut(hdcGlobal,5,y,buf,sprintf(buf,"%s vk=%02x   scan=%02x  fExtended=%x",type,(int)vk,(int)(byte)flags,(int)((flags >> 8)&1)));
		y += 20;
	}
}

#pragma argsused
void Winpcs_main_Key (HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	Winpcs_main_KeySub(hWnd,vk,fDown,cRepeat,flags,"Normal");
}

#pragma argsused
void Winpcs_main_SysKey (HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	Winpcs_main_KeySub(hWnd,vk,fDown,cRepeat,flags,"System");
}

void Winpcs_main_Paint(HWND hwnd)
{
	PAINTSTRUCT ps;

	BeginPaint(hwnd,&ps);
	EndPaint(hwnd,&ps);
}

LRESULT CALLBACK __export WndProcpcs_main (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE,	Winpcs_main_Create);
		HANDLE_MSG(hWnd, WM_KEYDOWN,	Winpcs_main_Key);
		HANDLE_MSG(hWnd, WM_KEYUP, 	Winpcs_main_Key);
		HANDLE_MSG(hWnd, WM_SYSKEYDOWN,	Winpcs_main_SysKey);
		HANDLE_MSG(hWnd, WM_SYSKEYUP, 	Winpcs_main_SysKey);
		HANDLE_MSG(hWnd, WM_PAINT,    Winpcs_main_Paint);
		HANDLE_MSG(hWnd, WM_DESTROY,	Winpcs_main_Destory);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

