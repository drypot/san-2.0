                                                                                                                        /*
--------------------------------------------------------------------------------
   text/paper.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

void cls_doc::paper_insert_line()
{
   mark_insert_line(iter.get_y());
   log_paper_insert_line();
   paper.insert_line();
   set_modified(def_yes);
}

void cls_doc::paper_insert_line_below()
{
   mark_insert_line(iter.get_y()+1);
   log_paper_insert_line_below();
   paper.insert_line_below();
   set_modified(def_yes);
}

void cls_doc::paper_remove_line()
{
   mark_remove_line(iter.get_y());
   log_paper_remove_line();
   paper.remove_line();
   set_modified(def_yes);
}

void cls_doc::paper_remove_line_below()
{
   mark_remove_line(iter.get_y()+1);
   log_paper_remove_line_below();
   paper.remove_line_below();
   set_modified(def_yes);
}

void cls_doc::paper_insert(int32 inx, int32 cnt)
{
   mark_insert(inx, cnt);
   log_paper_insert(inx, cnt);
   paper.insert(inx, cnt);
   set_modified(def_yes);
}

void cls_doc::paper_insert(int32 dst_inx, cls_paper* src_paper, int32 src_inx, int32 cnt)
{
   mark_insert(dst_inx, cnt);
   log_paper_insert_paper(dst_inx, cnt);
   paper.insert_no_fill(dst_inx, cnt);
   paper.put_paper(dst_inx, src_paper, src_inx, cnt);
   set_modified(def_yes);
}

void cls_doc::paper_insert(int32 inx, cls_paper_char_dary* src_char_dary, int32 cnt)
{
   mark_insert(inx, cnt);
   log_paper_insert_char_dary(inx,cnt);
   paper.insert_no_fill(inx,cnt);
   paper.put_char_dary(inx,src_char_dary,cnt);
   set_modified(def_yes);
}

void cls_doc::paper_remove(int32 inx, int32 cnt)
{
   mark_remove(inx, cnt);
   log_paper_remove(inx,cnt);
   paper.remove(inx, cnt);
   set_modified(def_yes);
}

void cls_doc::paper_replace (int32 inx , int32 ins_ch_cnt, int32 vis_ins_ch_cnt)
{
   cls_paper_iter iter(&paper);
   int32 del_ch_cnt = 0;
   int32 vis_del_ch_cnt = 0;

   iter.set_x (inx);

   while (vis_del_ch_cnt < vis_ins_ch_cnt)
   {
      del_ch_cnt++;
      vis_del_ch_cnt += iter.get_width();
      iter.set_x_rel(1);
   }

   int32 remove_size = del_ch_cnt ;
   int32 insert_size = ins_ch_cnt + (vis_del_ch_cnt - vis_ins_ch_cnt);
   int32 diff = remove_size - insert_size;

   if (diff > 0)
   {
      paper_remove (inx, diff);
      paper_fill (inx,' ',insert_size);
   }
   ef (diff < 0)
   {
      paper_fill (inx,' ',insert_size + diff);
      paper_insert (inx+insert_size+diff, -diff);
   }
   el
   {
      paper_fill (inx,' ',insert_size);
   }
   set_modified(def_yes);
}

void cls_doc::paper_fill(int32 inx, char16 ch, int32 cnt)
{
   if (cnt)
   {
      log_paper_fill(inx,cnt);
      paper.fill(inx, ch, cnt);
      set_modified(def_yes);
   }
}

void cls_doc::paper_separate()
{
   paper_separate(iter.get_x());
}

void cls_doc::paper_separate(int32 x)
{
   mark_separate(x);
   log_paper_separate(x);
   paper.separate(x);
   set_modified(def_yes);
}

void cls_doc::paper_join()
{
   paper_join(get_max(iter.get_x(), paper.get_line_len()));
}

void cls_doc::paper_join(int32 x)
{
   if (iter.get_y() < paper.get_line_cnt() - 1)
   {
      mark_join(x);
      log_paper_join(x);
      paper.join(x);
      set_modified(def_yes);
   }
}

void cls_doc::paper_write(char16 ch)
{
   log_paper_write_char16();
   iter.put_val (ch);
   set_modified(def_yes);
}

void cls_doc::paper_write(int32 inx, cls_paper_char_dary* src_char_dary, int32 cnt)
{
   log_paper_write_char_dary(inx,cnt);
   paper.put_char_dary(inx, src_char_dary, cnt);
   set_modified(def_yes);
}

void cls_doc::set_modified(bool f)
{
   if (f != modified_flg)
   {
      modified_flg = f;
      sline_invalidate();
   }
}

bool cls_doc::paper_is_space (int32 inx, int32 end)
{
   cls_paper_iter iter(&paper);

   iter.set_x(inx);
   while (iter.get_x() < end)
   {
      if (!is_space(iter.get_val())) return def_no;
      iter.set_x_rel(1);
   }
   return def_yes;
}

bool cls_doc::paper_is_space_from (int32 inx)
{
   int32 l = paper.get_line_len();
   return paper_is_space(inx, l);
}

bool cls_doc::paper_is_space_till (int32 inx)
{
   return paper_is_space(0, inx);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void paper_line_edit_common()
{
   cdoc->focus_set_prev_vx();
   cdoc->set_modified(def_yes);
   view_invalidate_line();
}

void paper_remove_trailing_space()
{
   cls_paper_quick_iter iter(&cdoc->iter);
   int32 prev_x;

   if (remove_trailing_space_flg)
   {
      prev_x = cdoc->paper.get_line_len();
      iter.set_x(prev_x);
      while (iter.get_x() && is_space(iter.get_val_rel(-1))) iter.set_x_rel(-1);
      if (iter.get_x() < prev_x) cdoc->paper_remove(iter.get_x(), prev_x - iter.get_x());
   }
}

void pdf_char_remove()
{
   paper_line_edit_common();
   cdoc->paper_remove(cdoc->iter.get_x(), 1);
}

void pdf_char_erase()
{
   paper_line_edit_common();
   cdoc->paper_replace(cdoc->iter.get_x(),  1, 1);
}

void pdf_char_flip()
{
   char16 ch = cdoc->iter.get_val();
   if (is_alpha(ch))
   {
      paper_line_edit_common();
      if (is_upper(ch)) cdoc->paper_write(tolower(ch));
      else cdoc->paper_write(toupper(ch));
   }
}

void pdf_char_lower()
{
   char16 ch = cdoc->iter.get_val();
   if (is_upper(ch))
   {
      paper_line_edit_common();
      cdoc->paper_write(tolower(ch));
   }
}

void pdf_char_upper()
{
   char16 ch = cdoc->iter.get_val();
   if (is_lower(ch))
   {
      paper_line_edit_common();
      cdoc->paper_write(toupper(ch));
   }
}

void pdf_line_insert()
{
   cdoc->paper_insert_line();
   cdoc->focus_reset_vx();
   view_invalidate();
}

void pdf_line_insert_below()
{
   cdoc->paper_insert_line_below();
   view_invalidate();
}

void pdf_line_remove()
{
   cdoc->paper_remove_line();
   cdoc->focus_reset_vx();
   view_invalidate();
}

void pdf_line_remove_below()
{
   cdoc->paper_remove_line_below();
   view_invalidate();
}

void pdf_line_split()
{
   paper_line_edit_common();
   cdoc->paper_separate();
   view_invalidate();
}

void pdf_line_join()
{
   paper_line_edit_common();
   cdoc->paper_join();
   view_invalidate();
}

void pdf_line_indent()
{
   cls_paper& paper = cdoc->paper;
   cls_paper_iter iter(&paper);

   int32 num;
   int32 vx;

   paper_line_edit_common();

   num = cdoc->iter.get_y();
   vx = cdoc->iter.get_vx();

   while (num--)
   {
      iter.set_y(num);
      iter.locate();
      iter.set_x(paper.get_line_len());
      if (iter.get_vx() > vx) break;
   }

   if (num >= 0)
   {
      int32 len = paper.get_line_len();
      iter.set_vx(vx);
      while (iter.get_x() < len && !is_space(iter.get_val())) iter.set_x_rel(1);
      while (iter.get_x() < len && is_space(iter.get_val())) iter.set_x_rel(1);
      cdoc->iter.locate();
      if (insert_flg) cdoc->paper_insert(cdoc->iter.get_x(),  iter.get_vx() - vx);
      cdoc->focus_set_vx(iter.get_vx());
      if (!insert_flg && vx == cdoc->iter.get_vx()) cdoc->focus_set_x_rel(1);
   }
}

void pdf_line_unindent()
{
   cls_paper& paper = cdoc->paper;
   cls_paper_iter iter(&paper);

   int32 num;
   int32 vx;

   paper_line_edit_common();

   num = cdoc->iter.get_y();
   vx = cdoc->iter.get_vx();

   while (num--)
   {
      iter.set_y(num);
      iter.locate();
      if (paper.get_line_len())
      {
         iter.set_x(paper.get_line_begin());
         if (iter.get_vx() < vx || iter.get_vx()==0) break;
      }
   }

   if (num >= 0)
   {
      iter.set_vx(vx);
      while (iter.get_x() && is_space(iter.get_val_rel(-1))) iter.set_x_rel(-1);
      while (iter.get_x() && !is_space(iter.get_val_rel(-1))) iter.set_x_rel(-1);
      vx = iter.get_vx();

      iter = cdoc->iter;
      iter.locate();
      if (insert_flg)
      {
         int32 prev_p = iter.get_x();
         int32 begin;
         int32 adder = 0;
         while (iter.get_vx() > vx)
         {
            iter.set_x_rel(-1);
            if (!is_space(iter.get_val()))
            {
               adder++;
               break;
            }
         }
         cdoc->focus_set_x(begin = iter.get_x());
         begin += adder;
         cdoc->paper_remove(begin, prev_p - begin);
      }
      else cdoc->focus_set_vx(vx);
   }
}

void pdf_line_align_prev()
{
   cls_paper& paper = cdoc->paper;
   cls_paper_iter iter(&paper);
   int32 num = cdoc->iter.get_y();

   paper_line_edit_common();
   while (num--)
   {
      iter.set_y(num);
      iter.locate();
      if (paper.get_line_len())
      {
         iter.set_x(paper.get_line_begin());
         break;
      }
   }

   if ( num >= 0 )
   {
      cdoc->iter.locate();
      cdoc->focus_set_x(0);
      cdoc->paper_insert(cdoc->iter.get_x(), iter.get_vx());
      cdoc->focus_set_x(iter.get_vx());
   }
}

void pdf_line_align_left()
{
}

void pdf_line_align_right()
{
}

void pdf_line_align_center()
{
}

int32 pdf_line_is_empty()
{
   return cdoc->paper_is_space_till(cdoc->paper.get_line_len());
}

int32 pdf_line_is_space_from()
{
   return cdoc->paper_is_space_from(cdoc->iter.get_x());
}

int32 pdf_line_is_space_till()
{
   return cdoc->paper_is_space_till(cdoc->iter.get_x());
}
