                                                                                                                        /*
--------------------------------------------------------------------------------
   text/frame.cpp
   copyright(c) kyuhyun park
   1991.
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/misc.hpp>
#include <text/glb.hpp>
#include <text/text.rc>

static PFNWP org_frame_win_proc;

MRESULT frame_ev_query_track_info(MPARAM mp1, MPARAM mp2)
{
   PTRACKINFO tinfo = (PTRACKINFO) mp2;
   MRESULT rc;

   rc = org_frame_win_proc(frame_hwnd, WM_QUERYTRACKINFO, mp1, mp2);
   tinfo->fs |= TF_GRID;
   tinfo->cxGrid = 8;
   tinfo->cyGrid = 16;
   tinfo->ptlMinTrackSize.x = 10*8;
   tinfo->ptlMinTrackSize.y = 5*16;
   return rc;
}

MRESULT EXPENTRY frame_win_proc(HWND hwnd, ULONG mline, MPARAM mp1, MPARAM mp2)
{
   switch (mline)
   {
      case WM_QUERYTRACKINFO: return frame_ev_query_track_info(mp1, mp2);
   }

   return org_frame_win_proc(hwnd, mline, mp1, mp2);
}

void frame_create()
{
   WinRegisterClass (
      hab,
      client_class_ach,
      client_win_proc,
      CS_SIZEREDRAW | CS_HITTEST,
      0
   );

   ULONG flFrameFlags =
      FCF_ICON |
      FCF_MENU |
      FCF_TITLEBAR |
      FCF_SYSMENU |
      FCF_SIZEBORDER |
      FCF_MINMAX |
      //FCF_HIDEBUTTON |
      FCF_TASKLIST;

   frame_hwnd = WinCreateStdWindow (
      HWND_DESKTOP,
      /*WS_VISIBLE*/ 0,
      &flFrameFlags,
      client_class_ach,
      title_pch,
      WS_VISIBLE,
      0,
      def_id_main_res,
      &client_hwnd
   );

   org_frame_win_proc = WinSubclassWindow(frame_hwnd, frame_win_proc);

   set_frame_size_from_client(frame_hwnd, init_width*8, init_height*16);
   set_frame_pos_center(frame_hwnd);
   set_frame_activate(frame_hwnd);
}

void frame_destroy()
{
   WinDestroyWindow(frame_hwnd);
}
