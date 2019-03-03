                                                                                                                        /*
--------------------------------------------------------------------------------
   text/write.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <win/spcdlg.hpp>
#include <win/hnjdlg.hpp>

#include <text/glb.hpp>

static void make_space(char16 ch)
{
   if (insert_flg)
   {
      cdoc->paper_insert (cdoc->iter.get_x(), 1);
   }
   else
   {
      cdoc->paper_replace (cdoc->iter.get_x(), 1, cdoc->iter.get_width(ch));
   }
}

static void write_char(char16 ch)
{
   make_space(ch);
   cdoc->paper_write(ch);
   cdoc->focus_set_x_rel(1);
}

static void get_cursor_pos(int* x, int* y)
{
   POINTL pntl;

   pntl.x = cdoc->cursor.x * 8;
   pntl.y = (ebrd->get_height() - cdoc->cursor.y - 1 + 2) * 16;
   WinMapWindowPoints(client_hwnd, HWND_DESKTOP, &pntl, 1);
   *x = pntl.x;
   *y = pntl.y;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void ca_direct(char16 ch)
{
   cdoc->log_new_group();
   paper_line_edit_common();
   write_char(ch);
   cdoc->cursor_adjust_x();
}

void ca_open(char16 ch)
{
   cdoc->log_new_group();
   paper_line_edit_common();
   make_space(ch);
   cdoc->iter.put_val(ch);
   cdoc->cursor_adjust_x();
   view_invalidate_line();
}

void ca_replace(char16 ch)
{
   cdoc->iter.put_val (ch);
   view_invalidate_line();
}

void ca_close(char16 ch)
{
   cdoc->iter.put_val(' ');
   cdoc->paper_write(ch);
   cdoc->focus_set_x_rel(1);
   cdoc->cursor_adjust_x();
   view_invalidate_line();
}

void ca_cancel()
{
   if (insert_flg) cdoc->paper_remove(cdoc->iter.get_x(), 1);
   else cdoc->paper_replace(cdoc->iter.get_x(), cdoc->iter.get_width(), cdoc->iter.get_width());
   cdoc->cursor_adjust_x();
   view_invalidate_line();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_write_string()
{
   char* data_pnt = (char*) mac_runner->get_arg_pnt(0);

   paper_line_edit_common();
   while (*data_pnt) write_char(read_c16(&data_pnt));
}

void pdf_write_literal()
{
   /*
   mline_write(msg_literal);

   literal_f = def_yes;
   do
   {
      cursor_doc_win();
      Coder();
   } while (!CoderAvail());
   literal_f = def_no;

   Coderget_();
   line_edit_common();
   write_char(CoderCode());
   Coderreset();

   mline_clear();
   */
}

void pdf_write_hanja()
{
   int x;
   int y;

   get_cursor_pos(&x, &y);

   cls_hnj_dlg dlg(HWND_DESKTOP, x, y, client_hwnd);

   cls_wchar wchar(cdoc->iter.get_val());
   cls_wchar wchar_save = wchar;

   dlg.execute(&wchar);

   if (wchar.c16 != wchar_save.c16)
   {
      paper_line_edit_common();
      cdoc->paper_write(wchar.c16);
      cdoc->focus_set_x_rel(1);
   }
}

void pdf_write_special()
{
   int x;
   int y;

   get_cursor_pos(&x, &y);

   cls_spc_dlg dlg(HWND_DESKTOP, x, y, client_hwnd);

   dlg.execute();

   if (dlg.cnt)
   {
      char16* p = dlg.contents;
      char16* end = dlg.contents + dlg.cnt;

      paper_line_edit_common();
      while (p < end) write_char(*p++);
   }
}

void pdf_write_date()
{
}

void pdf_write_time()
{
}

void pdf_mcp_next()
{
   mcp_list_iter->next_mcp();
   sline_invalidate();
}

int32 pdf_coder_is_flushed()
{
   return coder_flushed_flg;
}

