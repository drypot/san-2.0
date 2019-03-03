                                                                                                                        /*
--------------------------------------------------------------------------------
   text/doc.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <cnt/list.hpp>
#include <pub/io.hpp>

#include <text/glb.hpp>

int32 cls_doc::id_seed;
cls_paper cls_doc::buffer;
int cls_doc::buffer_type;

cls_doc::cls_doc() : id(id_seed++), iter(&paper)
{
   reset();
}

cls_doc::~cls_doc()
{
}

void cls_doc::reset()
{
   fname.reset();
   paper.reset();
   iter.reset();
   code_type = default_code_type_int;
   prev_vx=0;
   modified_flg = def_no;
   cursor.reset();
   window.reset();
   block_type = 0;
   block_marking_flg = def_no;
   block_enabled_flg = def_no;

   in_undo_process_flg = def_no;
   in_redo_process_flg = def_no;
   new_group_flg = def_yes;
   log_cnt = 0;

   log_frame_dary = &undo_frame_dary;
   log_char_dary = &undo_char_dary;

   undo_frame_dary.reset();
   undo_char_dary.reset();

   redo_frame_dary.reset();
   redo_char_dary.reset();

   mark_reset();
}

void cls_doc::load (char* fname_pch, int option)
{
   reset();
   code_type = option == def_ct_auto ? detect_hangul_code_type(fname_pch) : option;
   switch (code_type)
   {
      case def_ct_johab :
         cdoc->paper.read_file_johab(fname_pch);
         break;
      case def_ct_wansung :
         cdoc->paper.read_file_wansung(fname_pch);
         break;
   }
   fname.set_path(fname_pch);
}

void cls_doc::save()
{
   switch(code_type)
   {
      case def_ct_johab :
         cdoc->paper.write_file_johab(fname.get_path());
         break;
      case def_ct_wansung :
         cdoc->paper.write_file_wansung(fname.get_path());
         break;
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#define def_close 0
#define def_discard 1

#define def_save 0
#define def_save_as 1

static tem_obj_list<cls_doc> doc_list;
static bool iterating_flg;

int32 doc_get_cnt()
{
   return doc_list.get_cnt();
}

void doc_changed()
{
   if (doc_list.get_cnt() == 0)
   {
      cdoc = NULL;
   }
   else
   {
      cdoc = doc_list.get_pnt();
      sline_invalidate();
      view_invalidate();

      cdoc->block_marking_flg = def_no;
   }
}

bool doc_search(char* name)
{
   cls_fname fname(name);
   int cnt = doc_list.get_cnt();
   bool rc = def_error;

   doc_list.save_pos();
   doc_list.first();
   while (cnt--)
   {
      if (!doc_list.get_pnt()->fname.is_null() && stricmp(fname.get_path(), doc_list.get_pnt()->fname.get_path()) == 0)
      {
         doc_changed();
         rc = def_ok;
         break;
      }
      doc_list.next();
   }
   if (!rc)
   {
      doc_list.restore_pos();
   }
   return rc;
}

void doc_new()
{
   doc_list.link();
   doc_changed();
   mline_write(msg_xlator->xlate("new document"));
}

bool doc_open(char* fname_pch, int option)
{
   static FILEDLG fdlg;
   bool rc = def_error;
   bool fname_valid_flg = def_no;
   bool use_fdlg_flg = def_no;

   if (fname_pch == NULL)
   {
      use_fdlg_flg = def_yes;
   }

   if (!use_fdlg_flg)
   {
      if (strpbrk(fname_pch,"*?") != NULL)
      {
         strcpy (fdlg.szFullFile, fname_pch);
         use_fdlg_flg = def_yes;
      }
   }

   if (!use_fdlg_flg)
   {
      struct stat s;

      if (stat(fname_pch,&s) == 0 && (s.st_mode & S_IFDIR))
      {
         strcpy (fdlg.szFullFile, fname_pch);
         //char ch = fdlg.szFullFile [strlen(fdlg.szFullFile)-1];
         //if (ch != '\\' && ch != '/') strcat(fdlg.szFullFile,"\\");
         strcat(fdlg.szFullFile,"/");
         use_fdlg_flg = def_yes;
      }
   }

   if (use_fdlg_flg)
   {
      fdlg.cbSize = sizeof (FILEDLG);
      fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_OPEN_DIALOG;

      WinFileDlg(HWND_DESKTOP, client_hwnd, &fdlg);
      fname_pch = fdlg.szFullFile;
      fname_valid_flg = fdlg.lReturn == DID_OK;
   }
   else
   {
      fname_valid_flg = def_yes;
   }

   if (fname_valid_flg)
   {
      if (doc_search(fname_pch))
      {
         mline_write(msg_xlator->xlate("document already loaded"));
         rc = def_ok;
      }
      else
      {
         doc_list.link();
         doc_changed();

         if (access(fname_pch,0) == 0)
         {
            try
            {
               mline_write(msg_xlator->xlate("loading document"));
               cdoc->load(fname_pch, option);
               mline_clear();
               rc = def_ok;
            }
            catch (...)
            {
               mline_write_error();
            }
         }
         else
         {
            if (errno != ENOENT)
            {
               mline_write_error();
            }
            else
            {
               mline_write(msg_xlator->xlate("new document"));
               cdoc->fname.set_path(fname_pch);
               rc = def_ok;
            }
         }
         if (!rc)
         {
            doc_list.unlink();
            doc_changed();
         }
      }
   }

   if (cdoc == NULL)
   {
      doc_new();
   }
   return rc;
}

bool doc_save(int option)
{
   static FILEDLG fdlg;
   bool rc = def_error;
   bool fname_valid_flg = def_no;

   sline_update();
   sline_draw();

   if (cdoc->fname.is_null() || option == def_save_as)
   {
      view_update();
      view_draw();

      fdlg.cbSize = sizeof (FILEDLG);
      fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_SAVEAS_DIALOG;

      WinFileDlg(HWND_DESKTOP, client_hwnd, &fdlg);
      if (fdlg.lReturn == DID_OK)
      {
         cdoc->fname.set_path(fdlg.szFullFile);
         sline_invalidate();
         fname_valid_flg = def_yes;
      }
   }
   else
   {
      fname_valid_flg = def_yes;
   }

   if (fname_valid_flg)
   {
      if (make_backup_flg) make_backup(cdoc->fname.get_path());

      try
      {
         cdoc->save();
         cdoc->set_modified(def_no);
         sline_invalidate();
         mline_write(msg_xlator->xlate("document saved"));
         rc = def_ok;
      }
      catch (...)
      {
         mline_write_error();
      }
   }

   return rc;
}

bool doc_close(int option)
{
   bool rc = def_error;
   bool safe_flg = def_no;

   if (cdoc->modified_flg)
   {
      sline_update();
      view_update();
      sline_draw();
      view_draw();

      ULONG rc = WinMessageBox (
                    HWND_DESKTOP, client_hwnd,
                    option == def_discard ? "Do you want to DISCARD this document ?" : "Do you want to SAVE this document ?",
                    "Warning: Document modified",
                    0,
                    MB_YESNOCANCEL | MB_NOICON | MB_DEFBUTTON1 | MB_APPLMODAL | MB_MOVEABLE
                 );

      if (option == def_discard)
      {
         if (rc == MBID_YES) safe_flg = def_yes;
      }
      el
      {
         if (rc == MBID_YES)
         {
            safe_flg = doc_save(def_save);
         }
         ef (rc == MBID_NO)
         {
            safe_flg = def_yes;
         }
      }
   }
   else
   {
      safe_flg = def_yes;
   }

   if (safe_flg)
   {
      if (cdoc == bdoc) bdoc = NULL;
      doc_list.unlink();
      doc_changed();
      if (cdoc == NULL)
      {
         doc_new();
      }
      rc = def_ok;
   }

   return rc;
}

bool doc_close_all(bool option)
{
   int32 cnt = doc_list.get_cnt();

   doc_list.first();
   doc_changed();

   while (cnt)
   {
      if (!doc_close(option)) break;
      doc_list.next();
      doc_changed();
      cnt--;
   }

   return cnt == 0;
}

void doc_init()
{
   if (argc > 1)
   {
      int inx;
      for (inx = 1; inx < argc; inx++)
      {
         if (!doc_open(argv[inx], def_ct_auto)) break;
      }
      doc_list.first();
      doc_changed();
   }
   else
   {
      doc_new();
   }
}

void pdf_doc_new()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_new()\ninfo: now iterating\n");
   doc_new();
}

int32 pdf_doc_open()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_open()\ninfo: now iterating\n");
   return doc_open(NULL, def_ct_auto);
}

int32 pdf_doc_open_johab()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_open_johab()\ninfo: now iterating\n");
   return doc_open(NULL, def_ct_johab);
}

int32 pdf_doc_open_wansung()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_open_wansung()\ninfo: now iterating\n");
   return doc_open(NULL, def_ct_wansung);
}

int32 pdf_doc_save()
{
   return doc_save(def_save);
}

int32 pdf_doc_save_as()
{
   return doc_save(def_save_as);
}

int32 pdf_doc_close()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_close()\ninfo: now iterating\n");
   return doc_close(def_close);
}

int32 pdf_doc_discard()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_discard()\ninfo: now iterating\n");
   return doc_close(def_discard);
}

int32 pdf_doc_close_all()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_close_all()\ninfo: now iterating\n");
   return doc_close_all(def_close);
}

int32 pdf_doc_discard_all()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_discard_all()\ninfo: now iterating\n");
   return doc_close_all(def_discard);
}

int32 pdf_doc_prev()
{
   bool rc = def_error;

   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_prev()\ninfo: now iterating\n");
   if (doc_list.get_cnt() > 1)
   {
      doc_list.prev();
      doc_changed();
      rc = def_ok;
   }
   return rc;
}

int32 pdf_doc_next()
{
   bool rc = def_error;

   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_next()\ninfo: now iterating\n");
   if (doc_list.get_cnt() > 1)
   {
      doc_list.next();
      doc_changed();
      rc = def_ok;
   }
   return rc;
}

void pdf_doc_list()
{
}

void pdf_doc_iterate()
{
   if (iterating_flg) throw cls_xmsg("func: text/doc.cpp/pdf_doc_iterate()\ninfo: now iterating\n");

   uint32 func_id = mac_runner->get_arg_i32(0);
   int32 cnt = doc_list.get_cnt();

   iterating_flg = def_yes;
   while (cnt--)
   {
      cdoc->log_new_group();
      mac_runner->execute(func_id);

      doc_list.next();
      doc_changed();
   }
   iterating_flg = def_no;
}

int32 pdf_doc_is_modifed()
{
   return cdoc->is_modified();
}
