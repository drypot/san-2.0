/*
   1995.11.08
*/

#include <pub\common.hpp>
#include <vio\textwin.hpp>
#include <fnt\engfont.hpp>

TextImage* pImage;

void DrawImage()
{
   int x,y,w,h;
   void* pFont;
   static char ch;

   ASSERT (pImage);

   w = pImage->GetWidth();
   h = pImage->GetHeight();

   forcnt (y,h)
   {
      pFont = EngFont(ch);
      ch = (ch + 1) % 128;
      forcnt (x,w)
         pImage->Put8(x, y, pFont);
   }
}

MRESULT EXPENTRY WndProcClient(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HPS hps;
   BOOL bHandled = TRUE;
   MRESULT mReturn = 0;

   switch (msg)
   {
      case WM_CREATE:
         pImage = new TextImage(40,20);
         DrawImage();
         break;

      case WM_PAINT :
         {

            int w = pImage->GetWidth()*8;
            int h = pImage->GetHeight()*16;
            SIZEL sizel = { w, h };
            POINTL pointl = {0, h-1};

            hps = WinBeginPaint (hwnd, 0, 0);
            GpiMove (hps, &pointl);
            GpiSetBackMix (hps, BM_OVERPAINT);
            //GpiSetColor (hps, CLR_WHITE);
            //GpiSetBackColor (hps, CLR_BLUE);
            GpiImage (hps, 0, &sizel, w*h/8, (PBYTE)pImage->GetImageBase());
            WinEndPaint(hps);
         }
         break;

      case WM_ERASEBACKGROUND :
         mReturn = MRFROMLONG(1L);
         break;

      case WM_CHAR :
         DrawImage();
         WinInvalidateRect(hwnd,0,TRUE);
         //sWinMessageBox(HWND_DESKTOP, hwnd, "KeyPressed", "MessageBox", 0, MB_OK);
         break;

      case WM_BUTTON1DOWN :
         HALT();

      default :
         bHandled = FALSE;
         break;
   }

   if (!bHandled) mReturn = WinDefWindowProc(hwnd, msg, mp1, mp2);

   return mReturn;
}

void Main()
{
   HWND  hwndFrame;
   HWND  hwndClient;
   ULONG flFrameFlags;

   CHAR  clientClassName[]="CLIENT";

   flFrameFlags =
      FCF_TITLEBAR |
      FCF_SYSMENU |
      //FCF_ICON |
      FCF_SIZEBORDER |
      FCF_MINMAX |
      //FCF_MENU |
      FCF_SHELLPOSITION |
      FCF_TASKLIST;

   WinRegisterClass
   (
      hab,
      clientClassName,
      WndProcClient,
      CS_SIZEREDRAW | CS_HITTEST ,
      0
   );

   hwndFrame =
      WinCreateStdWindow
      (
         HWND_DESKTOP,
         WS_VISIBLE,
         &flFrameFlags,
         clientClassName,
         "Test TextImage",
         WS_VISIBLE,
         0,
         0,
         &hwndClient
      );

   WinShowWindow(hwndFrame,TRUE);

   MessageBroker();

   WinDestroyWindow(hwndFrame);
}

