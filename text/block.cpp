                                                                                                                        /*
--------------------------------------------------------------------------------
   text/block.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

cls_mark cls_doc::block_get_mark()
{
   return cls_mark (iter.get_x(), iter.get_y(), block_type != def_block_type_char);
}

void cls_doc::block_save_focus()
{
   mark_set(def_mark_internal_tmp);
}

void cls_doc::block_restore_focus()
{
   focus_mark(def_mark_internal_tmp);
   mark_reset(def_mark_internal_tmp);
}

bool cls_doc::block_mark_is_ok(cls_mark* begin, cls_mark* end, int type)
{
   bool rc = def_error;
   switch (type)
   {
      case def_block_type_char : rc = *begin <= *end; break;
      case def_block_type_line : rc = *begin <= *end; break;
      case def_block_type_column : rc = *begin <= *end && begin->x <= end->x; break;
   }
   return rc;
}

void cls_doc::block_set_enabled(bool flg)
{
   if (block_enabled_flg != flg)
   {
      log_block_set_enabled();
      block_enabled_flg = flg ? block_mark_is_ok() : def_no;
   }
}

void cls_doc::block_set_type(int new_type)
{
   if (block_type != new_type)
   {
      log_block_set_type();
      log_block_begin();
      log_block_end();
      block_type = new_type;
      switch(new_type)
      {
         case def_block_type_char :
         case def_block_type_column :
            block_begin.make_null();
            block_end.make_null();
            block_set_enabled(def_no);
            break;

         case def_block_type_line :
            block_begin.ignore_x_flg = def_yes;
            block_end.ignore_x_flg = def_yes;
            break;
      }
      if (block_enabled_flg)
      {
         log_view_invalidate();
         view_invalidate();
      }
   }
}

bool cls_doc::block_mark_is_ok()
{
   return block_mark_is_ok(&block_begin, &block_end, block_type);
}

void cls_doc::block_set_marking(bool flg)
{
   if (block_marking_flg != flg)
   {
      log_block_set_marking();
      block_marking_flg = flg;
      if (flg)
      {
         cls_mark cur_mark = block_get_mark();
         if (block_type == def_block_type_column) cur_mark.x = iter.get_vx();
         log_mark(&block_anchor);
         log_block_begin();
         log_block_end();
         block_anchor = block_begin = block_end = cur_mark;
      }
   }
}

void cls_doc::block_continue_marking()
{
   cls_mark cur_mark = block_get_mark();

   log_block_begin();
   log_block_end();
   switch(block_type)
   {
      case def_block_type_char :
      case def_block_type_line :
         if (cur_mark <= block_anchor)
         {
            block_begin = cur_mark;
            block_end = block_anchor;
         }
         else
         {
            block_begin = block_anchor;
            block_end = cur_mark;
         }
         break;

      case def_block_type_column :
         cur_mark.x = iter.get_vx();
         if (cur_mark.y <= block_anchor.y)
         {
            block_begin.y = cur_mark.y;
            block_end.y = block_anchor.y;
         }
         else
         {
            block_begin.y = block_anchor.y;
            block_end.y = cur_mark.y;
         }
         if (cur_mark.x < block_anchor.x)
         {
            block_begin.x = cur_mark.x;
            block_end.x = block_anchor.x;
         }
         else
         {
            block_begin.x = block_anchor.x;
            block_end.x = cur_mark.x;
         }
         break;
   }
   if (block_enabled_flg)
   {
      log_view_invalidate();
      view_invalidate();
   }
}

void cls_doc::block_set_begin()
{
   log_block_begin();
   block_begin = block_get_mark();
}

void cls_doc::block_set_end()
{
   log_block_end();
   block_end = block_get_mark();
}

void cls_doc::block_expand()
{
   if (block_mark_is_ok() && !focus_is_in_block())
   {
      cls_mark cur_mark = block_get_mark();
      log_block_begin();
      log_block_end();
      switch(block_type)
      {
         case def_block_type_char :
         case def_block_type_line :
            (cur_mark < block_begin ? block_begin : block_end ) = cur_mark;
            break;

         case def_block_type_column :
            cur_mark.x = iter.get_vx();
            if (cur_mark.y < block_begin.y) block_begin.y = cur_mark.y;
            ef (cur_mark.y > block_end.y) block_end.y = cur_mark.y;
            if (cur_mark.x < block_begin.x) block_begin.x = cur_mark.x;
            ef (cur_mark.x > block_end.x) block_end.x = cur_mark.x;
            break;
      }
      if (block_enabled_flg)
      {
         log_view_invalidate();
         view_invalidate();
      }
   }
}

bool cls_doc::block_remove(cls_mark* bp, cls_mark* ep, int type)
{
   int32 cnt;
   bool rc = def_error;

   if (block_mark_is_ok(bp, ep, type))
   {
      block_save_focus();
      switch(type)
      {
         case def_block_type_char :
            focus_set_xy(bp->x, bp->y);
            cnt = ep->y - bp->y - 1;
            if (cnt >= 0)
            {
               while (cnt--) paper_remove_line_below();
               paper_join();
            }
            paper_remove(iter.get_x(), ep->x - bp->x);
            break;

         case def_block_type_line :
            focus_set_y(bp->y);
            cnt = ep->y - bp->y + 1;
            if (ep->y == paper.get_line_cnt() - 1)
            {
               cnt--;
               while (cnt--) paper_remove_line();
               paper_remove(0, paper.get_line_len());
            }
            else
            {
               while (cnt--) paper_remove_line();
            }
            break;

         case def_block_type_column :
            break;
      }
      block_restore_focus();
      log_view_invalidate();
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

bool cls_doc::block_remove()
{
   return block_remove(&block_begin, &block_end, block_type);
}

bool cls_doc::block_insert_head(char16 ch)
{
   bool rc = def_error;

   if (block_type == def_block_type_line && block_mark_is_ok())
   {
      int32 begin_y = block_begin.y;
      int32 end_y = block_end.y;

      block_save_focus();
      focus_set_x(0);
      while (begin_y <= end_y)
      {
         focus_set_y(begin_y++);
         paper_insert(iter.get_x(), 1);
         paper_write(ch);
      }
      block_restore_focus();
      log_view_invalidate();
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

bool cls_doc::block_remove_head_space(int32 cnt)
{
   bool rc = def_error;

   if (block_type == def_block_type_line && block_mark_is_ok() && cnt > 0)
   {
      int32 begin_y = block_begin.y;
      int32 end_y = block_end.y;
      cls_paper_iter tmp_iter(&paper);

      block_save_focus();
      focus_set_x(0);
      while (begin_y <= end_y)
      {
         focus_set_y(begin_y);
         tmp_iter.set_y(begin_y);
         while (is_space(tmp_iter.get_val()) && tmp_iter.get_vx() < cnt) tmp_iter.set_x_rel(1);
         if (tmp_iter.get_vx() <= cnt) paper_remove(iter.get_x(), tmp_iter.get_x());
         else
         {
            paper_replace(iter.get_x(), cnt,cnt);
            paper_remove(iter.get_x(), cnt);
         }
         begin_y++;
      }
      block_restore_focus();
      log_view_invalidate();
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::hiden_block_set_begin()
{
   //log_mark(&hiden_block_begin);
   hiden_block_begin = cls_mark(iter.get_x(), iter.get_y());
}

void cls_doc::hiden_block_set_end()
{
   //log_mark(&hiden_block_end);
   hiden_block_end = cls_mark(iter.get_x(), iter.get_y());
}

void cls_doc::hiden_block_remove()
{
   block_remove(&hiden_block_begin, &hiden_block_end, def_block_type_char);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::focus_block_begin()
{
   if (block_mark_is_ok())
   {
      switch (block_type)
      {
         case def_block_type_char : focus_mark(def_mark_block_begin); break;
         case def_block_type_line : focus_set_y(block_begin.y); break;
         case def_block_type_column: focus_set_y(block_begin.y); focus_set_vx(block_begin.x); break;
      }
   }
}

void cls_doc::focus_block_end()
{
   if (block_mark_is_ok())
   {
      switch (block_type)
      {
         case def_block_type_char : focus_mark(def_mark_block_end); break;
         case def_block_type_line : focus_set_y(block_end.y); break;
         case def_block_type_column: focus_set_y(block_end.y); focus_set_vx(block_end.x); break;
      }
   }
}

bool cls_doc::focus_is_in_block()
{
   cls_mark cur_mark = block_get_mark();
   int32 vx = iter.get_vx();
   bool rc = def_no;
   switch(block_type)
   {
      case def_block_type_char : rc = block_begin <= cur_mark && cur_mark < block_end; break;
      case def_block_type_line : rc = block_begin <= cur_mark && cur_mark <= block_end; break;
      case def_block_type_column : rc = block_begin <= cur_mark && cur_mark <= block_end && block_begin.x <= vx && vx < block_end.x; break;
   }
   return rc;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_block_set_char_type()
{
   cdoc->block_set_type(def_block_type_char);
}

void pdf_block_set_line_type()
{
   cdoc->block_set_type(def_block_type_line);
}

void pdf_block_set_column_type()
{
   cdoc->block_set_type(def_block_type_column);
}

void pdf_block_set_marking()
{
   cdoc->block_set_marking(mac_runner->get_arg_i32(0));
}

int32 pdf_block_is_marking()
{
   return cdoc->block_marking_flg;
}

void pdf_block_set_enabled()
{
   bool flg = mac_runner->get_arg_i32(0);

   if (flg)
   {
      if (bdoc) bdoc->block_set_enabled(def_no);
      bdoc = cdoc;
   }
   cdoc->block_set_enabled(flg);
   view_invalidate();
}

int32 pdf_block_is_enabled()
{
   return cdoc->block_enabled_flg;
}

int32 pdf_block_is_enabled_existent()
{
   return bdoc != NULL;
}

void pdf_block_set_begin()
{
   cdoc->block_set_begin();
}

void pdf_block_set_end()
{
   cdoc->block_set_end();
}

void pdf_block_expand()
{
   cdoc->block_expand();
}

int32 pdf_block_remove()
{
   return bdoc->block_remove();
}

void pdf_block_fill()
{
}

void pdf_block_flip()
{
}

void pdf_block_lower()
{
}

void pdf_block_upper()
{
}

void pdf_block_align_left()
{
}

void pdf_block_align_right()
{
}

void pdf_block_align_center()
{
}

int32 pdf_block_indent()
{
   return bdoc == cdoc && bdoc->block_insert_head('\t');
}

int32 pdf_block_unindent()
{
   return bdoc == cdoc && bdoc->block_remove_head_space(tab_width_int);
}

int32 pdf_block_shift_left()
{
   return bdoc == cdoc && bdoc->block_remove_head_space(1);
}

int32 pdf_block_shift_right()
{
   return bdoc == cdoc && bdoc->block_insert_head(' ');
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_hiden_block_set_begin()
{
   cdoc->hiden_block_set_begin();
}

void pdf_hiden_block_set_end()
{
   cdoc->hiden_block_set_end();
}

void pdf_hiden_block_remove()
{
   cdoc->hiden_block_remove();
}

void pdf_hiden_block_set_find_string()
{
}
