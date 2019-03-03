/*
   1995.11.23
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#include <vio\textimg.hpp>

#define WIDTH 40
#define HEIGHT 20

TextImage* pImage;

MRESULT EXPENTRY WndProcClient(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HPS hps;
   BOOL bHandled = TRUE;
   MRESULT mReturn = 0;

   switch (msg)
   {
      case WM_CREATE:
         pImage = new TextImage(WIDTH, HEIGHT);
         break;

      case WM_PAINT :
         {
            hps = WinBeginPaint (hwnd, 0, 0);
            WinEndPaint(hps);
         }
         break;

      case WM_ERASEBACKGROUND:
         mReturn = (MRESULT) 1;
         break;

      case WM_CHAR :
         {
            USHORT fsflags = SHORT1FROMMP(mp1);
            //USHORT usch = SHORT1FROMMP(mp2);
            //USHORT usvk = SHORT2FROMMP(mp2);
            UCHAR ucscan = CHAR4FROMMP(mp1);
            LONG lTmp;
            char* p;
            char buf[128];

            mReturn = (MRESULT) TRUE;
            if (fsflags & KC_SCANCODE)
            {
               sprintf(buf,"%s 0x%02X  ", (fsflags & KC_KEYUP ? "UP  " : "DOWN"), (int)ucscan);
               p = buf + strlen(buf);

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x36);
               *p++ = lTmp & 0x8000 ? 'S' : 's';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x2A);
               *p++ = lTmp & 0x8000 ? 'S' : 's';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x5B);
               *p++ = lTmp & 0x8000 ? 'C' : 'c';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x1D);
               *p++ = lTmp & 0x8000 ? 'C' : 'c';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x5E);
               *p++ = lTmp & 0x8000 ? 'A' : 'a';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x38);
               *p++ = lTmp & 0x8000 ? 'A' : 'a';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x45);
               *p++ = lTmp & 0x8000 ? 'N' : 'n';

               lTmp = WinGetPhysKeyState(HWND_DESKTOP,0x3A);
               *p++ = lTmp & 0x8000 ? 'P' : 'p';

               *p++ = ' ';
               *p++ = ' ';

               lTmp = WinGetKeyState(HWND_DESKTOP,VK_SHIFT);
               *p++ = lTmp & 0x0001 ? 'S' : 's';

               lTmp = WinGetKeyState(HWND_DESKTOP,VK_CTRL);
               *p++ = lTmp & 0x0001 ? 'C' : 'c';

               lTmp = WinGetKeyState(HWND_DESKTOP,VK_ALT);
               *p++ = lTmp & 0x0001 ? 'A' : 'a';

               lTmp = WinGetKeyState(HWND_DESKTOP,VK_NUMLOCK);
               *p++ = lTmp & 0x0001 ? 'N' : 'n';

               lTmp = WinGetKeyState(HWND_DESKTOP,VK_CAPSLOCK);
               *p++ = lTmp & 0x0001 ? 'P' : 'p';

               *p = 0;



               pImage->TTYWrite(buf);
               pImage->TTYNewLine();

               int w = pImage->GetWidth()*8;
               int h = pImage->GetHeight()*16;
               SIZEL sizel = { w, h };
               POINTL pointl = {0, h-1};
               HPS hps;

               hps = WinGetPS(hwnd);
               GpiMove (hps, &pointl);
               GpiSetBackMix (hps, BM_OVERPAINT);
               //GpiSetColor (hps, CLR_WHITE);
               //GpiSetBackColor (hps, CLR_DARKBLUE);
               GpiImage (hps, 0, &sizel, w*h/8, (PBYTE)pImage->GetImageBase());
               WinReleasePS(hps);
            }
         }
         break;

      default :
         bHandled = FALSE;
         break;
   }

   return !bHandled ? WinDefWindowProc(hwnd, msg, mp1, mp2) : mReturn;
}

void Main()
{
   HWND  hwndFrame;
   HWND  hwndClient;
   ULONG flFrameFlags;
   static CHAR  clientClassName[]="CLIENT";

   flFrameFlags =
      //FCF_ICON |
      //FCF_SIZEBORDER |
      //FCF_MINMAX |
      //FCF_MENU |
      //FCF_SHELLPOSITION |
      FCF_TITLEBAR |
      FCF_SYSMENU |
      //FCF_BORDER |
      FCF_HIDEBUTTON |
      //FCF_MAXBUTTON |
      FCF_TASKLIST;

   WinRegisterClass
   (
      hab,
      clientClassName,
      WndProcClient,
      CS_SIZEREDRAW | CS_HITTEST,
      0
   );

   hwndFrame =
      WinCreateStdWindow
      (
         HWND_DESKTOP,
         0,
         &flFrameFlags,
         clientClassName,
         "Terminal Service  " __DATE__,
         WS_VISIBLE,
         0,
         0,
         &hwndClient
      );

   WinSetWindowPos(hwndFrame,0,0,2,80*8,26*16+18, SWP_MOVE | SWP_SIZE | SWP_ACTIVATE | SWP_SHOW);
   MessageBroker();
   WinDestroyWindow(hwndFrame);
}

