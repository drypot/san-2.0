/*
   1995.11.26
*/

#include <pub\common.hpp>
#include <win\textimg.hpp>
#include <key\keyevent.hpp>

#define WIDTH 65
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
            KeyEvent keyev;

            keyev.Set(mp1,mp2);
            if (keyev.IsValid())
            {
               char buf[128];

               pImage->Printf ("%04X ", keyev.GetKeyCode());
               pImage->Printf (keyev.IsKeyDownEvent() ? "down  " : "up    ");
               pImage->Printf ("%04X %02X ", keyev.GetKeyCodeType(), keyev.GetKeyCodeOffset());

               pImage->Write (keyev.IsRShiftPressed()   ? "rS" : "  ");
               pImage->Write (keyev.IsLShiftPressed()   ? "lS" : "  ");
               pImage->Write (keyev.IsRCtrlPressed()    ? "rC" : "  ");
               pImage->Write (keyev.IsLCtrlPressed()    ? "lC" : "  ");
               pImage->Write (keyev.IsRAltPressed()     ? "rA" : "  ");
               pImage->Write (keyev.IsLAltPressed()     ? "lA" : "  ");
               pImage->Write (keyev.IsRMachinePressed() ? "rM" : "  ");
               pImage->Write (keyev.IsLMachinePressed() ? "lM" : "  ");
               pImage->Write (keyev.IsNumLockPressed()  ? "NL" : "  ");
               pImage->Write (keyev.IsCapsLockPressed() ? "CL" : "  ");

               pImage->Write ("| ");

               pImage->Write (keyev.IsRShiftToggledOn()   ? "rS" : "  ");
               pImage->Write (keyev.IsLShiftToggledOn()   ? "lS" : "  ");
               pImage->Write (keyev.IsRCtrlToggledOn()    ? "rC" : "  ");
               pImage->Write (keyev.IsLCtrlToggledOn()    ? "lC" : "  ");
               pImage->Write (keyev.IsRAltToggledOn()     ? "rA" : "  ");
               pImage->Write (keyev.IsLAltToggledOn()     ? "lA" : "  ");
               pImage->Write (keyev.IsRMachineToggledOn() ? "rM" : "  ");
               pImage->Write (keyev.IsLMachineToggledOn() ? "lM" : "  ");
               pImage->Write (keyev.IsNumLockToggledOn()  ? "NL" : "  ");
               pImage->Write (keyev.IsCapsLockToggledOn() ? "CL" : "  ");

               pImage->NewLine();

               int w = pImage->GetWidth()*8;
               int h = pImage->GetHeight()*16;
               SIZEL sizel = { w, h };
               POINTL pointl = {0, h-1};
               HPS hps;

               hps = WinGetPS(hwnd);
               GpiMove (hps, &pointl);
               GpiSetBackMix (hps, BM_OVERPAINT);
               GpiImage (hps, 0, &sizel, w*h/8, (PBYTE)pImage->GetImageBase());
               WinReleasePS(hps);
            }
         }
         mReturn = (MRESULT) TRUE;
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

