                                                                                                                        /*
--------------------------------------------------------------------------------
   text/log.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

enum
{
   def_log_null,
   def_log_focus_set_x,
   def_log_focus_set_y,
   def_log_paper_insert_line,
   def_log_paper_insert_line_below,
   def_log_paper_remove_line,
   def_log_paper_remove_line_below,
   def_log_paper_insert,
   def_log_paper_insert_paper,
   def_log_paper_insert_char_dary,
   def_log_paper_remove,
   def_log_paper_fill,
   def_log_paper_separate,
   def_log_paper_join,
   def_log_paper_write_char16,
   def_log_paper_write_char_dary,
   def_log_set_modifed,
   def_log_mark,
   def_log_block_set_enabled,
   def_log_block_set_type,
   def_log_block_set_marking,
   def_log_view_invalidate
};

cls_log_frame::cls_log_frame() :
   type(def_log_null), new_group_flg(def_no), index(0), cnt(0), dary_cnt(0)
{
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::log_new_group()
{
   new_group_flg = def_yes;
}

void cls_doc::log_append_frame(cls_log_frame* frame)
{
   if (new_group_flg)
   {
      new_group_flg = def_no;
      frame->new_group_flg = def_yes;
   }
   log_frame_dary->locate_end();
   log_frame_dary->insert();
   log_frame_dary->put_pnt(frame);
}

bool cls_doc::log_common()
{
   bool rc = def_error;

   if (undo_step_cmax_int)
   {
      if (new_group_flg && redo_frame_dary.get_cnt() && !in_redo_process_flg && !in_undo_process_flg)
      {
         redo_frame_dary.reset();
         redo_char_dary.reset();
      }

      if (new_group_flg && !in_undo_process_flg)
      {
         if (log_cnt == undo_step_cmax_int)
         {
            int32 inx = 0;
            int32 cnt = log_frame_dary->get_cnt();
            int32 dary_cnt = 0;

            do
            {
               dary_cnt += log_frame_dary->get_pnt(inx)->dary_cnt;
               inx++;
            } while (inx < cnt && !log_frame_dary->get_pnt(inx)->new_group_flg);

            log_frame_dary->locate(0);
            log_frame_dary->remove(inx);
            log_char_dary->locate(0);
            log_char_dary->remove(dary_cnt);
         }
         else
         {
            log_cnt++;
         }
      }
      rc = def_ok;
   }
   return rc;
}

void cls_doc::log_focus_set_x ()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_focus_set_x;
      frame.index = iter.get_x();
      frame.cnt = iter.get_vx();
      log_append_frame(&frame);
   }
}

void cls_doc::log_focus_set_y ()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_focus_set_y;
      frame.index = iter.get_y();
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_insert_line()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_insert_line;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_insert_line_below()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_insert_line_below;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_remove_line()
{
   if (log_common())
   {
      cls_log_frame frame;
      int32 len;

      frame.type = def_log_paper_remove_line;
      frame.dary_cnt = len = paper.get_line_len();
      log_char_dary->locate_end();
      log_char_dary->insert(len);
      paper.get_char_dary(0, log_char_dary, len);
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_remove_line_below()
{
   if (log_common())
   {
      cls_log_frame frame;
      int32 len;

      paper.locate_rel(1);
      frame.type = def_log_paper_remove_line_below;
      frame.dary_cnt = len = paper.get_line_len();
      log_char_dary->locate_end();
      log_char_dary->insert(len);
      paper.get_char_dary(0, log_char_dary, len);
      paper.locate_rel(-1);
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_insert(int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_insert;
      frame.index = inx;
      frame.cnt = cnt;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_insert_paper (int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_insert_paper;
      frame.index = inx;
      frame.cnt = cnt;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_insert_char_dary(int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_insert_char_dary;
      frame.index = inx;
      frame.cnt = cnt;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_remove(int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_remove;
      frame.index = inx;
      frame.dary_cnt = cnt;
      log_char_dary->locate_end();
      log_char_dary->insert(cnt);
      paper.get_char_dary(inx,log_char_dary,cnt);
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_fill(int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_fill;
      frame.index = inx;
      frame.dary_cnt = cnt;
      log_char_dary->locate_end();
      log_char_dary->insert(cnt);
      paper.get_char_dary(inx,log_char_dary,cnt);
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_separate(int32 inx)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_separate;
      frame.index = inx;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_join(int32 inx)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_join;
      frame.index = inx;
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_write_char16()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_write_char16;
      frame.index = iter.get_val();
      log_append_frame(&frame);
   }
}

void cls_doc::log_paper_write_char_dary(int32 inx, int32 cnt)
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_paper_write_char_dary;
      frame.index = inx;
      frame.dary_cnt = cnt;
      log_char_dary->locate_end();
      log_char_dary->insert(cnt);
      paper.get_char_dary(inx,log_char_dary,cnt);
      log_append_frame(&frame);
   }
}

void cls_doc::log_mark(cls_mark* mark)
{
   if (log_common())
   {
      char16 buf[(sizeof(cls_mark)+1)/2];
      cls_log_frame frame;
      int cnt = (sizeof(buf)+1)/2;

      frame.type  = def_log_mark;
      frame.index = (int32) mark;
      frame.dary_cnt = cnt;
      memcpy(buf, mark, sizeof(cls_mark));
      log_char_dary->locate_end();
      log_char_dary->insert(cnt);
      log_char_dary->put_ary(buf, cnt);
      log_append_frame(&frame);
   }
}

void cls_doc::log_block_begin()
{
   log_mark(&block_begin);
}

void cls_doc::log_block_end()
{
   log_mark(&block_end);
}

void cls_doc::log_block_set_enabled()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_block_set_enabled;
      frame.index = block_enabled_flg;
      log_append_frame(&frame);
   }
}

void cls_doc::log_block_set_type()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_block_set_type;
      frame.index = block_type;
      log_append_frame(&frame);
   }
}

void cls_doc::log_block_set_marking()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_block_set_marking;
      frame.index = block_marking_flg;
      log_append_frame(&frame);
   }
}

void cls_doc::log_view_invalidate()
{
   if (log_common())
   {
      cls_log_frame frame;
      frame.type = def_log_view_invalidate;
      log_append_frame(&frame);
   }
}

                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::log_replay(cls_log_frame_dary* frame_dary, cls_paper_char_dary* char_dary)
{
   cls_log_frame frame;
   int32 cnt;
   int32 inx;
   int32 len;

   cnt = inx = frame_dary->get_cnt();

   if (cnt)
   {
      do
      {
         frame = frame_dary->get_val(--inx);
         len = frame.dary_cnt;
         if (len) char_dary->locate_end(-len);
         switch (frame.type)
         {
            case def_log_focus_set_x :
               log_focus_set_x();
               iter.set_x(frame.index, frame.cnt);
               focus_set_prev_vx();
               break;

            case def_log_focus_set_y :
               log_focus_set_x();
               log_focus_set_y();
               if (view_is_line_invalid()) view_update();
               iter.set_y(frame.index);
               iter.locate();
               break;

            case def_log_paper_insert_line :
               log_paper_remove_line();
               paper.remove_line();
               view_invalidate();
               break;

            case def_log_paper_insert_line_below :
               log_paper_remove_line_below();
               paper.remove_line_below();
               view_invalidate();
               break;

            case def_log_paper_remove_line :
               log_paper_insert_line();
               paper.insert_line();
               log_paper_insert_char_dary(0, len);
               paper.insert_no_fill(0, len);
               paper.put_char_dary(0, char_dary, len);
               view_invalidate();
               break;

            case def_log_paper_remove_line_below :
               log_paper_insert_line_below();
               paper.insert_line_below();
               focus_set_y_rel(1);
               log_paper_insert_char_dary(0, len);
               paper.insert_no_fill(0, len);
               paper.put_char_dary(0, char_dary, len);
               focus_set_y_rel(-1);
               view_invalidate();
               break;

            case def_log_paper_insert :
            case def_log_paper_insert_paper :
            case def_log_paper_insert_char_dary :
               log_paper_remove(frame.index, frame.cnt);
               paper.remove(frame.index, frame.cnt);
               view_invalidate_line();
               break;

            case def_log_paper_remove :
               log_paper_insert_char_dary(frame.index, len);
               paper.insert_no_fill(frame.index, len);
               paper.put_char_dary(frame.index, char_dary, len);
               view_invalidate_line();
               break;

            case def_log_paper_fill :
               log_paper_write_char_dary(frame.index, len);
               paper.put_char_dary(frame.index, char_dary, len);
               view_invalidate_line();
               break;

            case def_log_paper_separate :
               log_paper_join(frame.index);
               paper.join(frame.index);
               view_invalidate();
               break;

            case def_log_paper_join :
               log_paper_separate(frame.index);
               paper.separate(frame.index);
               view_invalidate();
               break;

            case def_log_paper_write_char16 :
               log_paper_write_char16();
               iter.put_val ((char16)frame.index);
               view_invalidate_line();
               break;

            case def_log_paper_write_char_dary :
               log_paper_write_char_dary(frame.index, len);
               paper.put_char_dary(frame.index, char_dary, len);
               view_invalidate_line();
               break;

            case def_log_mark :
              {
                  char16 buf[(sizeof(cls_mark)+1)/2];
                  cls_mark* mark = (cls_mark*)frame.index;

                  log_mark(mark);
                  char_dary->get_ary(buf, len);
                  memcpy(mark, buf, sizeof(cls_mark));
               }
               break;

            case def_log_block_set_enabled :
               log_block_set_enabled();
               block_enabled_flg = frame.index;
               view_invalidate();
               break;

            case def_log_block_set_type :
               log_block_set_type();
               block_type = frame.index;
               break;

            case def_log_block_set_marking :
               log_block_set_marking();
               block_marking_flg = frame.index;
               break;

            case def_log_view_invalidate :
               log_view_invalidate();
               view_invalidate();
               break;
         }
         if (len)
         {
            char_dary->locate_end(-len);
            char_dary->remove(len);
         }
      } while (!frame.new_group_flg && inx);
      frame_dary->remove(cnt - inx);
   }
}

void cls_doc::log_undo()
{
   in_undo_process_flg = def_yes;
   log_frame_dary = &redo_frame_dary;
   log_char_dary  = &redo_char_dary;

   if (undo_frame_dary.get_cnt())
   {
      log_new_group();
      log_replay (&undo_frame_dary, &undo_char_dary);
      log_cnt--;
   }

   log_frame_dary = &undo_frame_dary;
   log_char_dary  = &undo_char_dary;
   in_undo_process_flg = def_no;
}

void cls_doc::log_redo()
{
   in_redo_process_flg = def_yes;
   log_replay (&redo_frame_dary, &redo_char_dary);
   in_redo_process_flg = def_no;
}

void cls_doc::log_reset()
{
   undo_frame_dary.reset();
   undo_char_dary.reset();
   new_group_flg = def_yes;
   log_cnt = 0;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_log_undo()
{
   cdoc->log_undo();
}

void pdf_log_redo()
{
   cdoc->log_redo();
}

void pdf_log_reset()
{
   cdoc->log_reset();
}

void pdf_log_continue_group()
{
   cdoc->new_group_flg = def_no;
}

