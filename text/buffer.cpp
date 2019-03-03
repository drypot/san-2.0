                                                                                                                        /*
--------------------------------------------------------------------------------
   text/buffer.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <text/glb.hpp>

void cls_doc::buffer_reset()
{
   buffer.reset();
   buffer_type = 0;
}

bool cls_doc::buffer_read_char_block ()
{
   bool rc = def_error;

   if (block_mark_is_ok(&block_begin, &block_end, def_block_type_char))
   {
      int32 src_begin_y = block_begin.y;
      int32 src_end_y = block_end.y;
      int32 src_y = src_begin_y;
      int32 tar_y = 0;
      int32 sx, ex;

      while (src_y <= src_end_y)
      {
         paper.locate(src_y);
         buffer.locate(tar_y);
         sx = src_y == src_begin_y ? block_begin.x : 0;
         ex = src_y == src_end_y ? block_end.x : paper.get_line_len();
         ex = get_max(ex,sx);
         buffer.put_paper(0, &paper, sx, ex - sx);
         buffer.insert_line_below();
         src_y++;
         tar_y++;
      }
      buffer.remove_line_below();
      iter.locate();
      rc = def_ok;
   }
   return rc;
}

bool cls_doc::buffer_read_line_block ()
{
   bool rc = def_error;

   if (block_mark_is_ok(&block_begin, &block_end, def_block_type_line))
   {
      int32 src_y = block_begin.y;
      int32 src_end_y = block_end.y;
      int32 tar_y = 0;

      while (src_y <= src_end_y)
      {
         paper.locate(src_y++);
         buffer.locate(tar_y++);
         buffer.put_paper(0, &paper, 0, paper.get_line_len());
         buffer.insert_line_below();
      }
      buffer.remove_line_below();
      iter.locate();
      rc = def_ok;
   }

   return rc;
}

bool cls_doc::buffer_read_block ()
{
   bool rc = def_error;

   buffer_reset();
   switch(block_type)
   {
      case def_block_type_char : rc = buffer_read_char_block(); break;
      case def_block_type_line : rc = buffer_read_line_block(); break;
      case def_block_type_column: break;
   }
   if (rc)
   {
      buffer_type = block_type;
   }
   return rc;
}

bool cls_doc::buffer_read_block_arranging ()
{
   bool rc = def_error;

   if (block_type == def_block_type_line && block_mark_is_ok(&block_begin, &block_end, def_block_type_line))
   {
      cls_paper_quick_iter src_iter(&paper);
      cls_paper_iter tar_iter(&buffer);

      int32 src_end_y = block_end.y;
      int32 src_prev_x;

      int32 tar_prev_x;

      int32 len;
      int32 cnt;
      bool new_line_flg;

      buffer.reset();
      buffer_type = def_block_type_line;

      src_iter.set_y(block_begin.y);
      tar_iter.set_x(para_end_i32);

      while (src_iter.get_y() <= src_end_y)
      {
         src_iter.locate();
         len = paper.get_line_len();

         while (src_iter.get_x() < len)
         {
            while (is_space(src_iter.get_val()) && src_iter.get_x() < len) src_iter.set_x_rel(1);
            if (src_iter.get_x() < len)
            {
               src_prev_x = src_iter.get_x();
               while (!is_space(src_iter.get_val()) && src_iter.get_x() < len) src_iter.set_x_rel(1);
               cnt = src_iter.get_x() - src_prev_x;

               new_line_flg = def_no;
               if (tar_iter.get_vx() + 1 < para_end_i32)
               {
                  tar_prev_x = tar_iter.get_x();
                  buffer.insert(tar_prev_x, 1);
                  buffer.put_paper(tar_prev_x+1, &paper, src_prev_x, cnt);
                  tar_iter.set_x_rel(cnt+1);
                  if (tar_iter.get_vx() > para_end_i32)
                  {
                     buffer.remove(tar_prev_x, cnt + 1);
                     new_line_flg = def_yes;
                  }
               }
               else
               {
                  new_line_flg = def_yes;
               }

               if (new_line_flg)
               {
                  buffer.insert_line_below();
                  tar_iter.set_y_rel(1);
                  tar_iter.locate();

                  buffer.insert(0,para_begin_i32);
                  buffer.put_paper(para_begin_i32, &paper, src_prev_x, cnt);
                  tar_iter.set_x(para_begin_i32 + cnt);
               }
            }
         }
         src_iter.set_y_rel(1);
      }
      buffer.locate(0);
      buffer.remove_line();
      iter.locate();
      rc = def_ok;
   }

   return rc;
}

bool cls_doc::buffer_write_char_block ()
{
   int32 cnt = buffer.get_line_cnt();

   log_mark(&block_end);
   block_end = block_get_mark();
   forever
   {
      buffer.locate(--cnt);
      paper_insert(iter.get_x(), &buffer, 0, buffer.get_line_len());
      if (cnt) paper_separate();
      else break;
   }
   log_block_begin();
   block_begin = block_get_mark();

   return def_ok;
}

bool cls_doc::buffer_write_line_block ()
{
   int32 cnt = buffer.get_line_cnt();
   int32 inx = 0;

   block_save_focus();
   focus_set_x(0);
   while (inx < cnt)
   {
      paper_insert_line_below();
      focus_set_y_rel(1);
      buffer.locate(inx);
      paper_insert(iter.get_x(), &buffer, 0, buffer.get_line_len());
      inx++;
   }
   block_restore_focus();
   log_block_begin();
   log_mark(&block_end);
   block_begin = cls_mark(0, iter.get_y() + 1, def_yes);
   block_end = cls_mark(0, iter.get_y() + cnt, def_yes);

   return def_ok;
}

bool cls_doc::buffer_write_block ()
{
   bool rc = def_error;

   switch(buffer_type)
   {
      case def_block_type_char : rc = buffer_write_char_block(); break;
      case def_block_type_line : rc = buffer_write_line_block(); break;
      case def_block_type_column: break;
   }
   if (rc)
   {
      block_type = buffer_type;
      log_view_invalidate();
      view_invalidate();
   }
   return rc;
}

void cls_doc::buffer_read_file(char* fname_pch)
{
   buffer_reset();
   code_type = detect_hangul_code_type(fname_pch);
   switch (code_type)
   {
      case def_ct_johab :
         buffer.read_file_johab(fname_pch);
         break;
      case def_ct_wansung :
         buffer.read_file_wansung(fname_pch);
         break;
   }
}

void cls_doc::buffer_write_file(char* fname_pch)
{
   switch (code_type)
   {
      case def_ct_johab :
         buffer.write_file_johab(fname_pch);
         break;
      case def_ct_wansung :
         buffer.write_file_wansung(fname_pch);
         break;
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_buffer_reset()
{
   cdoc->buffer_reset();
}

int32 pdf_buffer_read_block()
{
   return bdoc->buffer_read_block();
}

int32 pdf_buffer_read_block_arranging()
{
   return bdoc->buffer_read_block_arranging();
}

int32 pdf_buffer_write_block()
{
   return cdoc->buffer_write_block();
}

int32 pdf_buffer_read_file()
{
   static FILEDLG fdlg;
   char* name = fdlg.szFullFile;
   bool rc = def_error;

   fdlg.cbSize = sizeof (FILEDLG);
   fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_OPEN_DIALOG;
   fdlg.pszTitle = "Import";

   WinFileDlg(HWND_DESKTOP, client_hwnd, &fdlg);

   if (fdlg.lReturn == DID_OK)
   {
      if (access(name,0) == 0)
      {
         try
         {
            mline_write(msg_xlator->xlate("loading block"));
            cdoc->buffer_read_file(name);
            mline_clear();
            rc = def_ok;
         }
         catch (...)
         {
            mline_write_error();
            cdoc->buffer_reset();
         }
      }
      else
      {
         mline_write_error();
      }
   }
   return rc;
}

int32 pdf_buffer_write_file()
{
   static FILEDLG fdlg;
   char* name = fdlg.szFullFile;
   bool rc = def_error;

   fdlg.cbSize = sizeof (FILEDLG);
   fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_SAVEAS_DIALOG;
   fdlg.pszTitle = "Export";

   WinFileDlg(HWND_DESKTOP, client_hwnd, &fdlg);

   if (fdlg.lReturn == DID_OK)
   {
      try
      {
         bool writeable_flg = def_no;

         if (access(name,0) == 0)
         {
            ULONG rc = WinMessageBox (
                          HWND_DESKTOP, client_hwnd,
                          "File already exist.\n\nOverwrite it?\n",
                          "Warning",
                          0,
                          MB_YESNOCANCEL | MB_NOICON | MB_DEFBUTTON1 | MB_APPLMODAL | MB_MOVEABLE
                       );
            if (rc == MBID_YES)
            {
               writeable_flg = def_yes;
               if (make_backup_flg) make_backup(name);
            }
         }
         else writeable_flg = def_yes;

         if (writeable_flg)
         {
            cdoc->buffer_write_file(name);
            mline_write(msg_xlator->xlate("block saved"));
            rc = def_ok;
         }
      }
      catch (...)
      {
         mline_write_error();
      }
   }
   return rc;
}
