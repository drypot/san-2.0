                                                                                                                        /*
--------------------------------------------------------------------------------
   win/strdlg.cpp
   copyright(c) kyuhyun park
   1996.05.13
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/dir.hpp>
#include <pub/init.hpp>
#include <pub/misc.hpp>
#include <vio/textbrd.hpp>
#include <key/mac.hpp>
#include <win/strdlg.hpp>

static bool exit_flg;
static int width;
static int height;

static HWND frame;
static HWND client;

static cls_mac_runner* mac_runner;
static cls_mac_bin* mac_bin;
static cls_text_brd* brd;

static cls_hnj_dlg* dlg;

static void pdf_left()
{
   iter.set_x_rel(-1);
}

static void pdf_right()
{
   iter.set_x_rel(1);
}

static void pdf_left_acc()
{
   iter.set_x_rel(-4);
}

static void pdf_right_acc()
{
   iter.set_x_rel(4);
}

static void pdf_up()
{
   iter.set_y_rel(-1);
}

static void pdf_down ()
{
   iter.set_y_rel(1);
}

static void pdf_home ()
{
   if (iter.is_x_first()) iter.set_first();
   else iter.set_x_first();
}

static void pdf_end()
{
   if (iter.is_x_last()) iter.set_last();
   else iter.set_x_last();
}

static void pdf_up_acc()
{
   iter.set_y_first();
}

static void pdf_home_acc()
{
   iter.set_y_first();
}

static void pdf_down_acc()
{
   iter.set_y_last();
}

static void pdf_end_acc()
{
   iter.set_y_last();
}

static void pdf_page_up()
{
   iter.set_first();
}

static void pdf_page_up_acc()
{
   iter.set_first();
}

static void pdf_page_down()
{
   iter.set_last();
}

static void pdf_page_down_acc()
{
   iter.set_last();
}

static void pdf_enter ()
{
   wchar->c16 = hanja_page.contents[iter.get_index()];
   exit_flg = def_yes;
}

static void pdf_cancel ()
{
   exit_flg  = def_yes;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void client_update()
{
   brd->set_xy(1 + iter.get_x()*2 , 3 + iter.get_y());
}

static void client_draw(HPS hps)
{
   brd->draw(hps);
}

static void client_draw()
{
   HPS hps = WinGetPS(client);
   client_draw(hps);
   WinReleasePS(hps);
}

static void client_key(cls_key_event* key_event)
{
   mac_assert(mac_runner);

   if (key_event->is_valid())
   {
      //int cnt = key_event->cnt;
      //while (cnt--)
      //{
         if (mac_runner->scan(key_event) == def_kb_scan_match)
         {
            mac_runner->execute();
            client_update();
            client_draw();
         }
      //}
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static MRESULT client_wm_char(MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event((MPARAM)mp1, (MPARAM)mp2);
   client_key(&key_event);
   return (MRESULT) TRUE; // processed
}

static MRESULT client_wm_create(HWND /*hwnd*/)
{
   int i;

   brd = new cls_text_brd(width, height);

   brd->set_fg(def_clr_black);
   brd->set_bg(def_clr_white);
   brd->erase();
   brd->set_wide_cursor(def_yes);
   brd->show_cursor(def_yes);

   brd->set_x(1);
   brd->set_y(1);
   brd->write(wchar->c16);

   forcnt(i, hanja_page.cnt)
   {
      if (i % def_horz_chars == 0 ) brd->set_xy(1, i/def_horz_chars+3);
      brd->write(hanja_page.contents[i]);
   }

   iter.set_index(0);

   client_update();

   return 0; // continue creation
}

static MRESULT client_wm_destroy()
{
   delete brd;

   return 0; // reserved
}

static MRESULT client_wm_paint(HPS hps)
{
   brd->invalidate();
   client_draw(hps);
   return 0; // reserved
}

static MRESULT EXPENTRY client_proc(HWND hwnd, ULONG mline, MPARAM mp1, MPARAM mp2)
{
   MRESULT rc;

   switch (mline)
   {
      case WM_CHAR :    return client_wm_char(mp1, mp2);
      case WM_CREATE :  return client_wm_create(hwnd);
      case WM_DESTROY : return client_wm_destroy();
      case WM_PAINT :
         {
            HPS hps = WinBeginPaint (hwnd, 0, 0);
            rc = client_wm_paint(hps);
            WinEndPaint(hps);
         }
         return rc;
   }

   return WinDefWindowProc(hwnd, mline, mp1, mp2);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void frame_create()
{
   static bool registered_flg;
   static char client_cname[] = "hnj_dlg_class";

   if (!registered_flg)
   {
      registered_flg = def_yes;
      WinRegisterClass (
         hab,
         client_cname,
         client_proc,
         CS_HITTEST,
         0
      );
   }

   ULONG flFrameFlags =
      //FCF_ICON |
      //FCF_MENU |
      FCF_SYSMODAL |
      FCF_NOBYTEALIGN |
      FCF_TITLEBAR |
      //FCF_SYSMENU |
      FCF_DLGBORDER
      //FCF_MINMAX |
      //FCF_HIDEBUTTON |
      //FCF_TASKLIST
      ;

   frame = WinCreateStdWindow (
      dlg->parent,
      /*WS_VISIBLE*/ 0,
      &flFrameFlags,
      client_cname,
      "Hanja Selector",
      WS_VISIBLE,
      0,
      0,
      &client
   );

   LONG cx_screen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
   //LONG cy_screen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

   RECTL rectl;

   rectl.xLeft   = 0;
   rectl.xRight  = width*8;
   rectl.yBottom = 0;
   rectl.yTop    = height*16;

   WinCalcFrameRect(frame, &rectl, FALSE);

   int frame_width  = rectl.xRight - rectl.xLeft;
   int frame_height = rectl.yTop - rectl.yBottom;

   int x = get_min(dlg->x + frame_width, cx_screen) - frame_width;
   int y = get_max(0, dlg->y - 1 - frame_height);

   WinSetWindowPos(
      frame,
      0,
      x, y,
      frame_width, frame_height,
      SWP_MOVE | SWP_SIZE
   );

   set_frame_activate(frame);
}

static void frame_destroy()
{
   WinDestroyWindow(frame);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_hnj_dlg::cls_hnj_dlg(HWND arg_parent, int arg_x, int arg_y, HWND arg_owner) :
   parent(arg_parent),
   x(arg_x),
   y(arg_y),
   owner(arg_owner)
{
}

void cls_hnj_dlg::execute (cls_wchar* arg_wchar)
{
   if (is_hanja (arg_wchar->c16))
   {
      arg_wchar->to_hangul();
   }
   else
   {
      wchar = arg_wchar;
      wchar->set_hanja_page(&hanja_page);

      if (!is_hnj_fnt_avail() || hanja_page.cnt == 0)
      {
         beep();
      }
      else
      {
         BOOL rc;

         dlg = this;
         exit_flg = def_no;
         width = 1 + def_horz_chars*2 + 1;
         height = 2 + get_seg_cnt(hanja_page.cnt, 8) + 1 + 1;
         iter.reset(def_horz_chars, hanja_page.cnt);

         rc = owner ? WinIsWindowEnabled(owner) : FALSE;
         if (rc) WinEnableWindow(owner, FALSE);

         frame_create();
         while (!exit_flg && WinGetMsg (hab, &qmsg, 0, 0, 0)) WinDispatchMsg (hab, &qmsg);
         frame_destroy();

         if (rc) WinEnableWindow(owner, TRUE);
      }
   }
}   

#include <macro/tmp/hnjdlg.def>
#include <macro/tmp/hnjdlg.map>

static void ctor()
{
   try
   {
      mac_bin = new cls_mac_bin(cls_fname("@bindir/../macro/hnjdlg.bin").get_path());
      mac_runner = new cls_mac_runner(mac_bin, mac_mapper);
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info("func: win/hnjdlg.cpp/ctor()\ninfo: macro loading error\n");
      throw;
   }
}

static cls_initer initer(ctor);
