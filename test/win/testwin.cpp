#include <pub\stdhdr.hpp>
#pragma hdrstop

#include <pub\environ.hpp>
#include <pub\osmisc.hpp>
#include <hanpub\fnt.hpp>

/*
#include <pub\stdmain.inc>
{
	MessageBox(NULL,sys_dir(),"testwin",MB_OK);
}
*/

/*
#include <pub\stdmain.inc>
{
	beep();
	return 0;
}
*/

/*
char buf[512*1024];

#include <pub\stdmain.inc>
{
	char szBuffer[80];
	int i;

	memset(buf,1,sizeof(buf));

	for(i=0; i<sizeof(buf) ; i++) if (buf[i]!=1) return 1;

	sprintf(szBuffer, "%d %d", sizeof(buf), sizeof(int));
	MessageBox(NULL, szBuffer, "SOLOMEM", MB_OK);
	return NULL;
}
*/

LRESULT CALLBACK _export WndProcMain(HWND, UINT, WPARAM, LPARAM);

#include <pub\stdmain.inc>
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
	wndclass.hbrBackground	= GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName	= "WinMain";

	if (!RegisterClass(&wndclass)) return 1;

	hWnd =
	CreateWindow
	(
		"WinMain",
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

HDC hdcGlobal;
HDC hdcMem16x16;
HDC hdcMem8x16;
HBITMAP hbm16x16;
HBITMAP hbm8x16;

void DrawHan(int x, int y, char16 ch)
{
	SetBitmapBits(hbm16x16,32,han_fnt_pos(ch));
	SelectObject(hdcMem16x16, hbm16x16);
	BitBlt (hdcGlobal, x*16, y*16, 16, 16, hdcMem16x16, 0, 0, SRCCOPY);
}

#pragma argsused
BOOL WinMain_Create (HWND hWnd, LPCREATESTRUCT lpCreateStrct)
{
	hdcGlobal = GetDC(hWnd);
	//SetTextColor(hdcGlobal,RGB(200,200,200));
	//SetBkColor(hdcGlobal,RGB(0,0,0));

	hdcMem16x16 = CreateCompatibleDC(hdcGlobal);
	hdcMem8x16 = CreateCompatibleDC(hdcGlobal);

	hbm16x16 = CreateBitmap (16, 16, 1, 1, NULL);
	SelectObject(hdcMem16x16, hbm16x16);

	hbm8x16 = CreateBitmap (8, 16, 1, 1, NULL);
	SelectObject(hdcMem8x16, hbm8x16);

	return TRUE;
}

#pragma argsused
void WinMain_Destory (HWND hWnd)
{
	DeleteDC (hdcMem16x16);
	DeleteDC (hdcMem8x16);

	DeleteObject(hbm16x16);
	DeleteObject(hbm8x16);

	PostQuitMessage(0);
}

#pragma argsused
void WinMain_Key (HWND hWnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	/*
	static int y;
	char buf[80];
	RECT rc;


	GetClientRect(hWnd,&rc);
	sprintf(buf,"vk=%d fDown=%d scan=%d fExtended=%d",(int)vk,(int)fDown,(int)(byte)flags,(int)((flags >> 8)&1));
	if (y+20 > rc.bottom)
	{
		y=0;
		InvalidateRect(hWnd,&rc,TRUE);
		UpdateWindow(hWnd);
	}
	TextOut(hdcGlobal,5,y,buf,strlen(buf));
	y += 20;
	*/

	/*
	{
		RECT rc;
		int x,y,k;
		int cx,cy;

		GetClientRect(hWnd,&rc);
		cx = rc.right /16;
		cy = rc.bottom /16;
		forcnt (k,32)
			forcnt (y, cy+1)
				forcnt (x,cx+1)
				{
					DrawHan(x,y,hangul(k,k,k));
				}
	}
	*/

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

		HDC hdcMem = CreateCompatibleDC(hdcGlobal);
		HBITMAP hbm = CreateBitmap (cx*16, cy*16, 1, 1, textwin);

		SelectObject(hdcMem, hbm);
		BitBlt (hdcGlobal, 0, 0, cx*16, cy*16, hdcMem, 0, 0, SRCCOPY);

		DeleteObject (hbm);
		DeleteDC (hdcMem);
	}
	/*
	{
		static uint8 img[16] =
		{
			0x01,
			0x01,
			0x03,
			0x03,
			0x07,
			0x07,
			0x0F,
			0x0F,
			0x1F,
			0x1F,
			0x3F,
			0x3F,
			0x7F,
			0x7F,
			0xFF,
			0xFF
		};

		static uint8 textwin[80*480];
		static flag f;
		int x,y,i;
		RECT rc;
		int cx, cy, len;

		GetClientRect(hWnd,&rc);
		len = (rc.right+15)/16*2;
		cx = rc.right / 8;
		cy = rc.bottom / 16;

		forcnt (y,cy)
			forcnt (x,cx)
				forcnt (i,16)
					textwin[(y*16+i)*len + x] = img[i];

		HDC hdcMem = CreateCompatibleDC(hdcGlobal);
		HBITMAP hbm = CreateBitmap (cx*8, cy*16, 1, 1, textwin);

		SelectObject (hdcMem, hbm);
		BitBlt (hdcGlobal, 0, 0, cx*8, cy*16, hdcMem, 0, 0, f ? NOTSRCCOPY : SRCCOPY);
		turn(f);
		DeleteObject (hbm);
		DeleteDC (hdcMem);
	}
	*/
}

void WinMain_Paint(HWND hwnd)
{
	PAINTSTRUCT ps;

	BeginPaint(hwnd,&ps);
	/*
	TextOut(hdcGlobal,10,10,"Hello World",11);
	beep();
	*/
	{
		int i;
		static char *msg = "¥eëw–a≠A∂a";
		forcnt (i,5) DrawHan(i,0,char16_make(msg+i*2));
	}
	EndPaint(hwnd,&ps);
}

LRESULT CALLBACK __export WndProcMain (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_CREATE,	WinMain_Create);
		HANDLE_MSG(hWnd, WM_KEYDOWN,	WinMain_Key);
		//HANDLE_MSG(hWnd, WM_KEYUP, 	WinMain_Key);
		HANDLE_MSG(hWnd, WM_PAINT,    WinMain_Paint);
		HANDLE_MSG(hWnd, WM_DESTROY,	WinMain_Destory);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

