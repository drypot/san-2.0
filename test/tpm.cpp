/*
   testpm.cpp

   1996.01.01
*/

#include <pub/config.hpp>
#include <pub/common.hpp>

HWND  hwndFrame;
HWND  hwndClient;

static CHAR ClientClassNamePnt[]="CLIENT";
static CHAR* TitleStrPnt;

MRESULT EvCreate(HWND /*hwnd*/)
{
   return 0;
}

MRESULT EvPaint(HWND hwnd)
{
   WinEndPaint(WinBeginPaint (hwnd, 0, 0));
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
      static FILEDLG filedlg;
      static int rerun;

      if (rerun == 0)
      {
         filedlg.cbSize = sizeof (FILEDLG);
         filedlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_OPEN_DIALOG; /* FDS_SAVEAS_DIALOG */
         strcpy (filedlg.szFullFile, GetExecDir());
         rerun = 1;
      }

      WinFileDlg(hwnd, hwnd, &filedlg);
      if (filedlg.lReturn == DID_OK) PutMessage (filedlg.szFullFile);
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
