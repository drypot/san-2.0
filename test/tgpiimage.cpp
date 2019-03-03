/*
   tgpiimage.cpp

   1996.01.01
*/

#include <pub/config.hpp>
#include <pub/common.hpp>

uint16 Img16[]=
{
   0x0100,
   0x0300,
   0x0700,
   0x0F00,
   0x1F00,
   0x3F00,
   0x7F00,
   0xFF00,
   0xFF01,
   0xFF03,
   0xFF07,
   0xFF0F,
   0xFF1F,
   0xFF3F,
   0xFF7F,
   0xFFFF,
};

HWND  hwndFrame;
HWND  hwndClient;

static CHAR ClientClassNamePnt[]="CLIENT";
static CHAR* TitleStrPnt;

void Draw(HPS hps)
{
   static int flag;
   static SIZEL SizeL = { 16, 16 };
   static POINTL pointl = {0, 0};
   int x,y;

   flag = !flag;
   GpiSetBackMix (hps, BM_OVERPAINT);
   GpiSetColor (hps, flag ? CLR_BLUE : CLR_CYAN);
   forcnt (y,20)
   {
      pointl.y = y*16;
      forcnt (x,30)
      {
         pointl.x = x*16;
         GpiMove (hps, &pointl);
         GpiImage (hps, 0, &SizeL, 32, (PBYTE)(Img16));
      }
   }
}

MRESULT EvCreate(HWND /*hwnd*/)
{
   return 0;
}

MRESULT EvPaint(HWND hwnd)
{
   HPS hps = WinBeginPaint (hwnd, 0, 0);
   Draw(hps);
   WinEndPaint(hps);
   return 0;
}

MRESULT EvTimer()
{
   return 0;
}

MRESULT EvChar(HWND /*hwnd*/, MPARAM /*mp1*/, MPARAM /*mp2*/)
{
   return (MRESULT) TRUE;
}

MRESULT EvButtonDown(HWND hwnd)
{
   if (WinQueryWindow(hwnd, QW_PARENT) != WinQueryActiveWindow(HWND_DESKTOP))
   {
      WinSetFocus(HWND_DESKTOP, hwnd);
   }
   else
   {
      HPS hps = WinGetPS(hwnd);
      Draw(hps);
      WinReleasePS(hps);
   }
   return (MRESULT) TRUE;
}

MRESULT EXPENTRY WndProcClient(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   BOOL bHandled = TRUE;
   MRESULT mReturn = 0;

   switch (msg)
   {
      case WM_CREATE:   mReturn = EvCreate(hwnd);
                        break;

      case WM_PAINT :   mReturn = EvPaint(hwnd);
                        break;

      case WM_CHAR :    mReturn = EvChar(hwnd, mp1, mp2);
                        break;

      case WM_TIMER :   mReturn = EvTimer();
                        break;

      case WM_ERASEBACKGROUND :
                        mReturn = (MRESULT) TRUE;
                        break;

      case WM_BUTTON1DOWN:
      case WM_BUTTON2DOWN:
                        mReturn = EvButtonDown(hwnd);
                        break;

      default :
         bHandled = FALSE;
         break;
   }

   return !bHandled ? WinDefWindowProc(hwnd, msg, mp1, mp2) : mReturn;
}

void Main()
{
   TitleStrPnt = "Test Window";

   WinRegisterClass (hab,
                     ClientClassNamePnt,
                     WndProcClient,
                     CS_SIZEREDRAW | CS_HITTEST,
                     0);

   ULONG flFrameFlags =
      FCF_MINMAX |
      FCF_SHELLPOSITION |
      FCF_TITLEBAR |
      FCF_SYSMENU |
      FCF_SIZEBORDER |
      FCF_TASKLIST;

   hwndFrame = WinCreateStdWindow (HWND_DESKTOP,
                                   WS_VISIBLE,
                                   &flFrameFlags,
                                   ClientClassNamePnt,
                                   TitleStrPnt,
                                   WS_VISIBLE,
                                   0,
                                   0,
                                   &hwndClient);

   MessageBroker();
   WinDestroyWindow(hwndFrame);
}
