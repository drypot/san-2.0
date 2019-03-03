                                                                                                                       /*
--------------------------------------------------------------------------------
   text/client.cpp
   copyright(c) kyuhyun park
   1991.
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>
#include <text/text.rc>

static ULONG timer_id;

void client_char()
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

void client_cmd_front_end()
{
   if (coder->is_incomplete())
   {
      coder->complete();
      client_char();
      coder_flushed_flg = def_yes;
   }
   else
   {
      coder_flushed_flg = def_no;
   }
   cdoc->log_new_group();
}

void client_cmd_back_end()
{
   if (cdoc->block_marking_flg) cdoc->block_continue_marking();
}

void client_key(cls_key_event* key_event)
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
                  client_cmd_back_end();
                  break;

               case def_kb_scan_failed :
                  cls_mc mc(key_event, mcp_list_iter->get_mcp());
                  coder->put (&mc);
                  client_char();
                  client_cmd_back_end();
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

void client_update()
{
   mline_update();

   if (cdoc)
   {
      sline_invalidate();
      view_invalidate();
      sline_update();
      view_update();
   }
   else
   {
      ebrd->set_fg(clr_normal_fg);
      ebrd->set_bg(clr_normal_bg);

      sline->erase_to_eol();
      ebrd->erase();
   }
}

void client_draw(HPS hps)
{
   view_draw(hps);
   sline_draw(hps);
   mline_draw(hps);
}

void client_draw()
{
   HPS hps = WinGetPS(client_hwnd);
   client_draw(hps);
   WinReleasePS(hps);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void client_cmd_new()
{
   pdf_doc_new();
}

void client_cmd_open()
{
   pdf_doc_open();
}

void client_cmd_open_johab()
{
   pdf_doc_open_johab();
}

void client_cmd_open_wansung()
{
   pdf_doc_open_wansung();
}

void client_cmd_save()
{
   pdf_doc_save();
}

void client_cmd_save_as()
{
   pdf_doc_save_as();
}

void client_cmd_save_all()
{
}

void client_cmd_save_and_close()
{
   if (pdf_doc_save())
   {
      pdf_doc_close();
   }
}

void client_cmd_close()
{
   pdf_doc_close();
}

void client_cmd_close_all()
{
}

void client_cmd_discard()
{
   pdf_doc_discard();
}

void client_cmd_discard_all()
{
}

void client_cmd_prev()
{
   pdf_doc_prev();
}

void client_cmd_next()
{
   pdf_doc_next();
}

void client_cmd_quit()
{
   if (pdf_doc_close_all())
   {
      pdf_quit();
   }
}

void client_cmd_undo()
{
   pdf_log_undo();
   pdf_cursor_adjust();
}

void client_cmd_redo()
{
   pdf_log_redo();
   pdf_cursor_adjust();
}

void client_cmd_copy()
{
}

void client_cmd_cut()
{
}

void client_cmd_paste()
{
}

void client_cmd_delete()
{
}

void client_cmd_keys_help()
{
   doc_open(cls_fname("@bindir/../etc/text.qh").get_path(), def_ct_auto);
}

void client_cmd_about()
{
   char buf[256];

   sprintf (buf, "%s\n\n%s\n\n", title_pch, copyright_eng_pch);
   WinMessageBox(
      HWND_DESKTOP,
      client_hwnd,
      buf,
      "About",
      0,
      MB_OK | MB_APPLMODAL | MB_MOVEABLE
   );
}
                                                                                                                              /*
--------------------------------------------------------------------------------                                        */

MRESULT client_wm_char(MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event((MPARAM)mp1, (MPARAM)mp2);
   client_key(&key_event);
   return (MRESULT) TRUE; // processed
}

MRESULT client_wm_close()
{
   client_cmd_quit();
   return 0; // reserved
}

MRESULT client_wm_command(int id)
{
   client_cmd_front_end();
   switch (id)
   {
      case def_idm_new              : client_cmd_new(); break;
      case def_idm_open             : client_cmd_open(); break;
      case def_idm_open_johab       : client_cmd_open_johab(); break;
      case def_idm_open_wansung     : client_cmd_open_wansung(); break;
      case def_idm_save             : client_cmd_save(); break;
      case def_idm_save_as          : client_cmd_save_as(); break;
      case def_idm_save_all         : client_cmd_save_all(); break;
      case def_idm_save_and_close   : client_cmd_save_and_close(); break;
      case def_idm_close            : client_cmd_close(); break;
      case def_idm_close_all        : client_cmd_close_all(); break;
      case def_idm_discard          : client_cmd_discard(); break;
      case def_idm_discard_all      : client_cmd_discard_all(); break;
      case def_idm_prev             : client_cmd_prev(); break;
      case def_idm_next             : client_cmd_next(); break;
      case def_idm_quit             : client_cmd_quit(); break;
      case def_idm_undo             : client_cmd_undo(); break;
      case def_idm_redo             : client_cmd_redo(); break;
      case def_idm_copy             : client_cmd_copy(); break;
      case def_idm_cut              : client_cmd_cut(); break;
      case def_idm_paste            : client_cmd_paste(); break;
      case def_idm_delete           : client_cmd_delete(); break;
      case def_idm_keys_help        : client_cmd_keys_help(); break;
      case def_idm_about            : client_cmd_about(); break;
   }
   client_cmd_back_end();

   sline_update();
   sline_draw();
   view_update();
   view_draw();

   return 0; // reserved
}

MRESULT client_wm_create(HWND hwnd)
{
   timer_id = WinStartTimer(hab, hwnd, 0, 1000);
   return 0; // continue creation
}

MRESULT client_wm_destroy()
{
   WinStopTimer(hab, client_hwnd, timer_id);
   return 0; // reserved
}

MRESULT client_wm_help()
{
   client_wm_command(def_idm_keys_help);
   return 0; // reserved;
}

MRESULT client_wm_min_max_frame(PSWP pswp)
{
   if (pswp->fl & SWP_MAXIMIZE)
   {
      RECTL rcl;

      rcl.xLeft   = 0;
      rcl.yBottom = 0;
      rcl.xRight  = pswp->cx;
      rcl.yTop    = pswp->cy;
                      
      WinCalcFrameRect(frame_hwnd, &rcl, TRUE);

      rcl.xRight -= rcl.xLeft;
      rcl.yTop -= rcl.yBottom;
      rcl.xLeft = 0;
      rcl.yBottom = 0;
      rcl.xRight -= rcl.xRight % 8;
      rcl.yTop -= rcl.yTop % 16;

      WinCalcFrameRect(frame_hwnd, &rcl, FALSE);

      rcl.xRight -= rcl.xLeft;
      rcl.yTop -= rcl.yBottom;
      pswp->cx = rcl.xRight;
      pswp->cy = rcl.yTop;
   }
   return 0;
}

MRESULT client_wm_paint(HPS hps)
{
   client_update();
   client_draw(hps);
   return 0; // reserved
}

MRESULT client_wm_size (int cx, int cy)
{
   if (cy % 16 == 0 && cx % 8 == 0)
   {
      cx /= 8;
      cy /= 16;

      delete ebrd;
      delete sline;
      delete mline;

      ebrd  = NULL;
      sline = NULL;
      mline = NULL;

      ebrd  = new cls_text_brd(cx, cy-2);
      sline = new cls_text_brd(cx, 1);
      mline = new cls_text_brd(cx, 1);

      sline->show_cursor(def_no);
      mline->show_cursor(def_no);

      sline->set_fg(clr_sline_fg);
      sline->set_bg(clr_sline_bg);
      mline->set_fg(clr_mline_fg);
      mline->set_bg(clr_mline_bg);

      if (cdoc) pdf_cursor_adjust();
   }

   return 0; // reserved
}

MRESULT client_wm_timer (USHORT)
{
   mline_wm_timer();
   return 0; // reserved
}

MRESULT EXPENTRY client_win_proc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   MRESULT rc;

   switch (msg)
   {
      case WM_CHAR :    return client_wm_char(mp1, mp2);
      case WM_CLOSE :   return client_wm_close();
      case WM_COMMAND : return client_wm_command(SHORT1FROMMP(mp1));
      case WM_CREATE :  return client_wm_create(hwnd);
      case WM_DESTROY : return client_wm_destroy();
      case WM_HELP :    return client_wm_help();
      case WM_MINMAXFRAME : return client_wm_min_max_frame((PSWP)mp1);
      case WM_PAINT :
         {
            /*
            HPS hps = WinBeginPaint (hwnd, 0, 0);
            rc = client_wm_paint(hps);
            WinEndPaint(hps);
            */
            HPS hps = WinBeginPaint (hwnd, 0, 0);
            WinEndPaint(hps);
            //client_update();
            ebrd->invalidate();
            sline->invalidate();
            mline->invalidate();
            client_draw();
         }
         return rc;
      case WM_SIZE : return client_wm_size(SHORT1FROMMP(mp2), SHORT2FROMMP(mp2));
      case WM_TIMER : return client_wm_timer(SHORT1FROMMP(mp1));
   }

   return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

