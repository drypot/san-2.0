                                                                                                                        /*
--------------------------------------------------------------------------------
   win/strdlg.hpp
   copyright(c) kyuhyun park
   1996
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <vio/textbrd.hpp>
#include <key/keyevent.hpp>
#include <key/coder.hpp>
#include <key/mac.hpp>

cls_str_dlg
{
   public: // !!!
      HWND parent_hwnd,
      HWND owner_hwnd,
      int x,
      int y,
      char16* buf;
      int buf_size;
      char* title;

   public:
      cls_str_dlg(HWND parent_hwnd, int x, int y, HWND owner_hwnd, char16* arg_buf, int arg_buf_size, char* title);

      int excute();
};


static cls_str_dlg* str_dlg;
static HWND frame_hwnd;
static HWND client_hwnd;
static bool exit_flg;

extern cls_mac_runner*    mac_runner;
extern cls_mcp_list_iter* mcp_list_iter;
extern cls_coder*         coder;

static bool    chat_flg;
static char16  char_buf_c16_ary[def_size_chat_buf];
static int     chat_x;
static int     chat_xvis_base;
static int     chat_len;
static bool    chat_insert_flg = def_yes;



static void frame_create();
static void frame_destroy();

cls_str_dlg::cls_str_dlg(HWND arg_parent_hwnd, int arg_x, int arg_y, HWND arg_owner_hwnd, char16* arg_buf, int arg_buf_size, char* title)
   parent_hwnd(parent_hwnd),
   owner_hwnd(owner_hwnd),
   x(x),
   y(y),
   buf(buf),
   buf_size(buf_size),
   title(arg_title)
{
}

int cls_str_dlg::excute()
{
   str_dlg = this;
   exit_flg = def_no;

   frame_create();
   while (!exit_flg && WinGetMsg (hab, &qmsg, 0, 0, 0)) WinDispatchMsg (hab, &qmsg);
   frame_destroy();
}

                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void client_char()
{
   while (coder->is_holding())
   {
      coder->get();
      char16 code = coder->get_code();
      switch (coder->get_action())
      {
         case def_ca_direct :
            ca_direct(code);
            break;

         case def_ca_open :
            ca_open(code);
            break;

         case def_ca_replace :
            ca_replace(code);
            break;

         case def_ca_close:
            ca_close(code);
            break;

         case def_ca_cancel:
            ca_cancel();
            break;
      }
   }
}

static void client_cmd_front_end()
{
   if (coder->is_incomplete())
   {
      coder->complete();
      client_char();
   }
   cdoc->log_new_group();
}

static void client_key(cls_key_event* key_event)
{
   mac_assert(mac_runner);
   mac_assert(coder);
   mac_assert(mcp_list_iter);

   if (key_event->is_valid())
   {
      int cnt = key_event->cnt;
      while (cnt--)
      {
         if (key_event->get_code() == def_key_backspace && key_event->get_shifted() == 0 && key_event->is_make_event() && coder->is_incomplete())
         {
            coder->discard();
            client_char();
         }
         else
         {
            switch (mac_runner->scan(key_event))
            {
               case def_kb_scan_match :
                  client_cmd_front_end();
                  mac_runner->execute();
                  break;

               case def_kb_scan_failed :
                  cls_mc mc(key_event, mcp_list_iter->get_mcp());
                  coder->put (&mc);
                  client_char();
                  break;
            }
         }
      }
   }

   sline_update();
   sline_draw();

   if (WinPeekMsg(hab, &qmsg, client_hwnd, WM_CHAR, WM_CHAR, PM_NOREMOVE) == FALSE)
   {
      view_update();
      view_draw();
   }
}

static void client_update()
{
}

static void client_draw(HPS hps)
{
   brd->draw(hps);
}

static void client_draw()
{
   HPS hps = WinGetPS(client_hwnd);
   client_draw(hps);
   WinReleasePS(hps);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static MRESULT client_wm_char(MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event((MPARAM)mp1, (MPARAM)mp2);
   client_key(&key_event);
   return (MRESULT) TRUE; // processed
}

static MRESULT client_wm_close()
{
   return 0; // reserved
}

static MRESULT client_wm_create(HWND hwnd)
{
   return 0; // continue creation
}

static MRESULT client_wm_destroy()
{
   return 0; // reserved
}

static MRESULT client_wm_paint(HPS hps)
{
   client_update();
   client_draw(hps);
   return 0; // reserved
}

static MRESULT EXPENTRY client_win_proc(HWND hwnd, ULONG mline, MPARAM mp1, MPARAM mp2)
{
   MRESULT rc;

   switch (mline)
   {
      case WM_CHAR :    return client_wm_char(mp1, mp2);
      case WM_CLOSE :   return client_wm_close();
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
   static char client_class_name[] = "str_dlg_class";

   if (!registered_flg)
   {
      WinRegisterClass (
         hab,
         client_class_name,
         client_win_proc,
         CS_HITTEST,
         0
      );
   }

   ULONG flFrameFlags =
      //FCF_ICON |
      //FCF_MENU |
      FCF_TITLEBAR |
      //FCF_SYSMENU |
      FCF_BORDER |
      //FCF_MINMAX |
      //FCF_HIDEBUTTON |
      //FCF_TASKLIST
      ;

   frame_hwnd = WinCreateStdWindow (
      str_dlg->parent_hwnd,
      WS_VISIBLE /* 0*/,
      &flFrameFlags,
      client_class_name,
      str_dlg->title,
      WS_VISIBLE,
      0,
      0,
      &client_hwnd
   );

   set_frame_activate(frame_hwnd);
}

static void frame_destroy()
{
   WinDestroyWindow(frame_hwnd);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

int pcs_main()
{
   char16 buf[16];
   cls_str_dlg str_dlg(HWND_DESKTOP, 50, 200, NULL, buf, sizeof(buf)/2);

   str_dlg.excute();
   return 0;
}

