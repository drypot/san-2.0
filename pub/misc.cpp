																																								/*
--------------------------------------------------------------------------------
   pub/misc.cpp
   copyright(c) kyuhyun park
   1990
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/misc.hpp>

void beep ()
{
   #if defined def_dos
		sound (5000);
		delay (50);
		nosound();
   #elif defined def_os2
      DosBeep(5000,50);
   #elif defined def_windows
		MessageBeep(-1);
	#else

	#endif
}

#if defined def_pm
   void set_frame_size_from_client(HWND hwnd, int cx, int cy)
   {
      RECTL rectl;

      rectl.xLeft   = 0;
      rectl.xRight  = cx;
      rectl.yBottom = 0;
      rectl.yTop    = cy;

      WinCalcFrameRect(hwnd, &rectl, def_false);

      int int_frame_width  = rectl.xRight - rectl.xLeft;
      int int_frame_height = rectl.yTop - rectl.yBottom;

      WinSetWindowPos(hwnd,
                      0,
                      0, 0,
                      int_frame_width,
                      int_frame_height,
                      SWP_SIZE);
   }

   void set_frame_pos_center(HWND hwnd)
   {
      LONG cxScreen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
      LONG cyScreen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

      RECTL rectl;

      WinQueryWindowRect(hwnd, &rectl);

      int int_frame_width  = rectl.xRight;
      int int_frame_height = rectl.yTop;

      WinSetWindowPos(hwnd,
                      0,
                      (cxScreen - int_frame_width)/2,
                      (cyScreen - int_frame_height)/2,
                      0,
                      0,
                      SWP_MOVE);
   }

   void set_frame_activate(HWND hwnd)
   {
      WinSetWindowPos(hwnd,
                      HWND_TOP,
                      0, 0,
                      0, 0,
                      SWP_ACTIVATE | SWP_SHOW);
   }
#endif
