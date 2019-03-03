
#include <pub\config.hpp>
#include <pub\stdhdr.hpp>
#pragma hdrstop

#include <pub\osmisc.hpp>
#include <hanpub\fnt.hpp>

class win_han
{
	HWND hwnd;
	byte* textwin;
	int cx;
	int cy;
	flag inverse_f;
};

#pragma argsused
BOOL WinHan_Create (HWND hWnd, LPCREATESTRUCT lpCreateStrct)
{
	return TRUE;
}

#pragma argsused
void WinHan_Destory (HWND hWnd)
{
	PostQuitMessage(0);
}

#pragma argsused
void WinHan_Key (HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	{
		static uint8 textwin[80*480];
		static uint16 k;
		int x,y,i;
		RECT rc;
		int cx, cy;
		uint16* p;

		GetClientRect(hWnd,&rc);
		cx = rc.right / 16;
		cy = rc.bottom / 16;

		p = (uint16*)han_fnt_pos (hangul(k,k,k));
		forcnt (y,cy)
			forcnt (x,cx)
				forcnt (i,16)
				{
					*(uint16*)&(textwin[(y*16+i)*cx*2+x*2]) = p[i];
				}
		k++;
		if (k==32) k=0;

		HDC hdcGlobal = GetDC(hWnd);
		HDC hdcMem = CreateCompatibleDC(hdcGlobal);
		HBITMAP hbm = CreateBitmap (cx*16, cy*16, 1, 1, textwin);

		SelectObject(hdcMem, hbm);
		BitBlt (hdcGlobal, 0, 0, cx*16, cy*16, hdcMem, 0, 0, SRCCOPY);

		DeleteObject (hbm);
		DeleteDC (hdcMem);
		DeleteDC (hdcGlobal);
	}
}

void WinHan_Paint(HWND hwnd)
{
	PAINTSTRUCT ps;

	BeginPaint(hwnd,&ps);
	EndPaint(hwnd,&ps);
}

LRESULT CALLBACK __export WndProcMain (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE,	WinHan_Create);
		HANDLE_MSG(hWnd, WM_KEYDOWN,	WinHan_Key);
		//HANDLE_MSG(hWnd, WM_KEYUP, 	WinHan_Key);
		HANDLE_MSG(hWnd, WM_PAINT,    WinHan_Paint);
		HANDLE_MSG(hWnd, WM_DESTROY,	WinHan_Destory);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int main_core()
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	han_fnt_load("font\\sanigj.han");

	wndclass.style				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc		= WndProcMain;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszMenuName	= NULL;
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName	= "WinHan";

	if (!RegisterClass(&wndclass)) return 1;

	hWnd =
	CreateWindow
	(
		"WinHan",
		"Main Window",
		WS_OVERLAPPEDWINDOW,
		0, //CW_USEDEFAULT,
		0, //CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


