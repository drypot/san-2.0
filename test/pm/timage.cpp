/*
   timage.cpp

   1996.01.16
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

MRESULT EXPENTRY WndProcClient(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HPS hps;
   BOOL bHandled = TRUE;
   MRESULT mReturn = 0;

   switch (msg)
   {
      case WM_PAINT :
         hps = WinBeginPaint (hwnd, 0, 0);
         WinEndPaint(hps);
         break;

      case WM_ERASEBACKGROUND :
         mReturn = MRFROMLONG(1L);
         break;

      default :
         bHandled = FALSE;
         break;
   }

   if (!bHandled) mReturn = WinDefWindowProc(hwnd, msg, mp1, mp2);

   return mReturn;
}

void Main()
{
   ULONG flFrameFlags =
      FCF_TITLEBAR |
      FCF_SYSMENU |
      FCF_SIZEBORDER |
      FCF_MINMAX |
      FCF_SHELLPOSITION |
      FCF_TASKLIST;

   WinRegisterClass(hab,
                    "TEST",
                    WndProcClient,
                    CS_SIZEREDRAW | CS_HITTEST ,
                    0);

   hwndFrame = WinCreateStdWindow(HWND_DESKTOP,
                                  WS_VISIBLE,
                                  &flFrameFlags,
                                  "TEST",
                                  "Test Window",
                                  WS_VISIBLE,
                                  0,
                                  0,
                                  &hwndClient);

   WinShowWindow(hwndFrame,TRUE);
   MessageBroker();
   WinDestroyWindow(hwndFrame);
}

