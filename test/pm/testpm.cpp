
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

/*
static uint16 img_16x16[]=
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
*/

MRESULT EXPENTRY WndProcClient(HWND,ULONG,MPARAM,MPARAM);

int main()
{
   HAB   hab;
   HMQ   hmq;
   QMSG  qmsg;
   HWND  hwndFrame;
   HWND  hwndClient;
   ULONG flFrameFlags;

   CHAR  szClientClass[]="CLIENT";

   flFrameFlags =
      FCF_TITLEBAR |
      FCF_SYSMENU |
      FCF_ICON |
      FCF_SIZEBORDER |
      FCF_MINMAX |
      FCF_MENU |
      FCF_SHELLPOSITION |
      FCF_TASKLIST;

   hab = WinInitialize(0);
   hmq = WinCreateMsgQueue(hab,0);

   /*
   WinMessageBox
   (
      HWND_DESKTOP,
      NULL,
      "Hello",
      "Debugging information",
      0,
      MB_NOICON | MB_OK
   );
   */

   WinRegisterClass
   (
      hab,
      "TEST",
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
      "TEST",
      "Test Window",
      WS_VISIBLE,
      0,
      0,
      &hwndClient
   );

   WinShowWindow(hwndFrame,TRUE);
   while (WinGetMsg (hab, &qmsg, 0, 0, 0))
      WinDispatchMsg (hab, &qmsg);

   WinDestroyWindow(hwndFrame);
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);

   return 0;
}

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
