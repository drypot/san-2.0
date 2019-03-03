                                                                                                                        /*
--------------------------------------------------------------------------------
   term/main.cpp
   copyright(C) kyuhyun park
   1995.11.14
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/time.hpp>
#include <pub/misc.hpp>
#include <pub/ipc.hpp>

#include <term/glb.hpp>

#include <term/term.rc>

static CHAR  client_class_ach[]="term_service_client";
static CHAR* title_pch;
static CHAR* copyright_eng_pch = "Copyright(C) Kyuhyun Park";
static CHAR* copyright_han_pch = "Copyright(C) ¤b ‹A Ñe";

static cls_mutex_sem scn_sem;
static volatile bool end_read_thred_flg;
static volatile bool read_thred_ended_flg;

void port_read_thread(void*)
{
   int cnt = 0;

   while (!end_read_thred_flg)
   {
      if (cnt++ == 4)
      {
         if (port_check_state())
         {
            scn_sem.request();
            draw_state_brd();
            draw_state();
            scn_sem.release();
         }
         cnt = 0;
      }

      if (port_is_readable())
      {
         scn_sem.request();
         while (port_is_readable()) term_write(port_read());
         draw_term();
         scn_sem.release();
      }
      else DosSleep(128);
   }
   read_thred_ended_flg = def_yes;
}

void about()
{
   char buf[256];

   sprintf (buf, "%s\n\n%s\n\n", title_pch, copyright_eng_pch);
   WinMessageBox(HWND_DESKTOP,
                 client_hwnd,
                 buf,
                 "About",
                 0,
                 MB_OK | MB_APPLMODAL | MB_MOVEABLE
   );
}

void ev_create(HWND /*hwnd*/)
{
   term_brd_pnt  = new cls_text_brd(def_client_width, term_height_int);
   char_brd_pnt  = new cls_text_brd(def_client_width, 1);
   stat_brd_pnt  = new cls_text_brd(def_client_width, 1);

   term_brd_pnt->set_xy(0,0); term_brd_pnt->write("---------------------------");
   term_brd_pnt->set_xy(0,1); term_brd_pnt->write(title_pch);
   term_brd_pnt->set_xy(0,3); term_brd_pnt->write(copyright_han_pch);
   term_brd_pnt->set_xy(0,4); term_brd_pnt->write("---------------------------");
   term_brd_pnt->set_xy(0,6);

   char_brd_pnt->show_cursor(def_no);

   stat_brd_pnt->set_bg(def_clr_dark_gray);
   stat_brd_pnt->show_cursor(def_no);
   stat_brd_pnt->erase_to_eol();
   draw_state_brd();

   scn_sem.create();
   begin_thread(port_read_thread, 16384, NULL);
}

void ev_destroy(HWND /*hwnd*/)
{
   end_read_thred_flg = def_yes;
   while (!read_thred_ended_flg) DosSleep(64);
   scn_sem.close();
}

MRESULT ev_paint(HWND hwnd)
{
   scn_sem.request();
   HPS hps = WinBeginPaint (hwnd, 0, 0);
   invalidate_client();
   draw_client(hps);
   WinEndPaint(hps);
   scn_sem.release();
   return 0;
}

MRESULT ev_char(HWND /*hwnd*/, MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event(mp1, mp2);
   pcs_key_event (&key_event);
   return (MRESULT) def_true;
}

MRESULT ev_command(HWND hwnd, MPARAM mp1, MPARAM /*mp2*/)
{
   switch (SHORT1FROMMP(mp1))
   {
      case def_idm_quit :
         WinPostMsg(hwnd , WM_CLOSE, 0, 0);
         break;

      case def_idm_snd_txt :
         snd_txt();
         break;

      case def_idm_snd_bin :
         break;

      case def_idm_snd_zmd :
         WinMessageBox(HWND_DESKTOP,
                       client_hwnd,
                       "Not supported yet... sorry~",
                       "He He...",
                       0,
                       MB_OK | MB_APPLMODAL | MB_MOVEABLE);
         break;

      case def_idm_rcv_txt :
         rcv_txt();
         break;

      case def_idm_rcv_bin :
         rcv_bin();
         break;

      case def_idm_rcv_zmd :
         WinMessageBox(HWND_DESKTOP,
                       client_hwnd,
                       "Not supported yet... sorry~",
                       "He He...",
                       0,
                       MB_OK | MB_APPLMODAL | MB_MOVEABLE);
         break;

      case def_idm_about :
         about();
         break;
   }

   return 0;
}

MRESULT ev_button_down(HWND hwnd)
{
   if (WinQueryWindow(hwnd, QW_PARENT) != WinQueryActiveWindow(HWND_DESKTOP))
      WinSetFocus(HWND_DESKTOP, hwnd);
   return (MRESULT) def_true;
}

MRESULT EXPENTRY WndProcClient(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   switch (msg)
   {
      case WM_CREATE:      ev_create(hwnd);
                           break;

      case WM_PAINT :      return ev_paint(hwnd);

      case WM_CHAR :       return ev_char(hwnd, mp1, mp2);

      case WM_COMMAND :    return ev_command(hwnd, mp1, mp2);

      /*
      case WM_BUTTON1DOWN:
      case WM_BUTTON2DOWN: return ev_button_down(hwnd);
      */
      case WM_DESTROY :    ev_destroy(hwnd);
                           break;
   }

   return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

void create_main_frame()
{
   WinRegisterClass (hab,
                     client_class_ach,
                     WndProcClient,
                     CS_SIZEREDRAW | CS_HITTEST,
                     0);

   ULONG flFrameFlags =
      FCF_ICON |
      FCF_MENU |
      FCF_TITLEBAR |
      FCF_SYSMENU |
      FCF_BORDER |
      //FCF_SIZEBORDER |
      FCF_HIDEBUTTON |
      FCF_TASKLIST;

   frame_hwnd = WinCreateStdWindow (HWND_DESKTOP,
                                   /*WS_VISIBLE*/ 0,
                                   &flFrameFlags,
                                   client_class_ach,
                                   title_pch,
                                   WS_VISIBLE,
                                   0,
                                   def_id_main_res,
                                   &client_hwnd);

   set_frame_size_from_client(frame_hwnd, 80*8, def_client_height*16);
   set_frame_pos_center(frame_hwnd);
   set_frame_activate(frame_hwnd);

}

void destroy_main_frame()
{
   WinDestroyWindow(frame_hwnd);
}

int pcs_main()
{
   title_pch = dup_msg("TerminalService %s",get_converted_date(__DATE__));

   port_open();

   create_main_frame();
   msg_broker();
   destroy_main_frame();
   return 0;
}
