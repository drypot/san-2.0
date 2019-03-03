																																								/*
--------------------------------------------------------------------------------
   text/focus.cpp
	copyright(c) kyuhyun park
   1991
-------------------------------------------------------------------------------- 													*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::focus_set_prev_vx()
{
   prev_vx = iter.get_vx();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

bool cls_doc::focus_set_x(int32 nx)
{
   int32 prev_x = iter.get_x();
   bool rc = def_error;

   if (nx < 0) nx = 0;
   if (prev_x != nx)
   {
      log_focus_set_x();
      iter.set_x(nx);
      focus_set_prev_vx();
      rc = def_ok;
   }
   return rc;
}

void cls_doc::focus_set_x (int32 nx, int32 nvx)
{
   log_focus_set_x();
   iter.set_x(nx, nvx);
   focus_set_prev_vx();
}

bool cls_doc::focus_set_x_rel (int32 dx)
{
   return focus_set_x (iter.get_x() + dx);
}

bool cls_doc::focus_set_vx (int32 nx)
{
   int32 prev_x = iter.get_x();

	if (nx<0) nx = 0;
   log_focus_set_x();
   iter.set_vx(nx);
   focus_set_prev_vx();
   return prev_x != iter.get_x();
}

void cls_doc::focus_reset_vx()
{
   log_focus_set_x();
   iter.reset_x();
   iter.set_vx(prev_vx);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

bool cls_doc::focus_set_y(int32 ny)
{
   int32 prev_y = iter.get_y();
   bool rc = def_error;

   if (ny < 0)
   {
      ny = 0;
   }
	else
	{
      int32 l = paper.get_line_cnt();
		if (ny >= l) ny = l - 1;
	}

   if (prev_y != ny)
   {
      if (view_is_line_invalid()) view_update();
      paper_remove_trailing_space();
      log_focus_set_x();
      log_focus_set_y();
      iter.set_y(ny);
      iter.locate();
      iter.set_vx(prev_vx);
      return def_ok;
   }

   return rc;
}

bool cls_doc::focus_set_y_rel (int32 dy)
{
   return focus_set_y (iter.get_y() + dy);
}

bool cls_doc::focus_set_xy(int32 x, int32 y)
{
   int32 prev_x = iter.get_x();
   int32 prev_y = iter.get_y();
   focus_set_x(0);
   focus_set_y(y);
   focus_set_x(x);
   return prev_x != iter.get_x() || prev_y != iter.get_y();
}

bool cls_doc::focus_set_xy_rel(int32 dx, int32 dy)
{
   return focus_set_xy(iter.get_x() + dx, iter.get_y() + dy);
}

bool cls_doc::focus_mark(int inx)
{
   int32 x;
   int32 y;
   return mark_get(inx,&x,&y) ? focus_set_xy(x,y) : def_error;
}

bool cls_doc::focus_skip_prev (bool (*fn)(char16))
{
   cls_paper_quick_iter tmp_iter(&iter);
   while (tmp_iter.get_x() && fn(tmp_iter.get_val_rel(-1))) tmp_iter.set_x_rel(-1);
   return focus_set_x(tmp_iter.get_x());
}

bool cls_doc::focus_skip_next(bool (*fn)(char16))
{
   int32 l = paper.get_line_len();
   cls_paper_quick_iter tmp_iter(&iter);
   while (tmp_iter.get_x() < l && fn (tmp_iter.get_val())) tmp_iter.set_x_rel(1);
   return focus_set_x(tmp_iter.get_x());
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::cursor_adjust_x()
{
   cursor.x = iter.get_vx() - window.x;
   if (cursor.x + iter.get_width() >= ebrd->get_width())
	{
      cursor.x = ebrd->get_width() - iter.get_width();
      window.x = iter.get_vx() - cursor.x;
		view_invalidate();
	}
   if (cursor.x < 0)
	{
      window.x += cursor.x;
      cursor.x = 0;
		view_invalidate();
	}
}

void cls_doc::cursor_adjust_y()
{
   cursor.y = iter.get_y() - window.y;
   if (cursor.y < 0)
	{
      window.y += cursor.y;
      cursor.y = 0;
		view_invalidate();
	}
   ef (cursor.y >= ebrd->get_height())
	{
      cursor.y = ebrd->get_height() - 1;
      window.y = iter.get_y() - cursor.y;
		view_invalidate();
	}
}

void cls_doc::cursor_adjust_xy()
{
   cursor_adjust_y();
   cursor_adjust_x();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::window_adjust_x()
{
   int32 new_x = iter.get_vx() - cursor.x;

   if (new_x < 0)
	{
      cursor.x += window.x;
      new_x = 0;
	}
   if (window.x != new_x)
   {
      window.x = new_x;
		view_invalidate();
   }
   cursor_adjust_x();
}

void cls_doc::window_adjust_y()
{
   int32 new_y = iter.get_y() - cursor.y;

   if (new_y < 0)
	{
      new_y = 0;
      cursor.y = iter.get_y();
	}
   if (window.y != new_y)
   {
      window.y = new_y;
      view_invalidate();
   }
}

void cls_doc::window_adjust_xy()
{
   window_adjust_y();
   window_adjust_x();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static bool not_word (char16 ch)
{
   return !is_word(ch);
}

int32 pdf_focus_prev_char()
{
   return cdoc->focus_set_x_rel(-1);
}

int32 pdf_focus_next_char()
{
   return cdoc->focus_set_x_rel(1);
}

int32 pdf_focus_prev_line()
{
   return cdoc->focus_set_y_rel(-1);
}

int32 pdf_focus_next_line()
{
   return cdoc->focus_set_y_rel(1);
}

int32 pdf_focus_prev_page()
{
   return cdoc->focus_set_y_rel(-ebrd->get_height());
}

int32 pdf_focus_next_page()
{
   return cdoc->focus_set_y_rel(ebrd->get_height());
}

int32 pdf_focus_line_begin()
{
   return cdoc->focus_set_x (cdoc->paper.get_line_begin());
}

int32 pdf_focus_line_end()
{
   return cdoc->focus_set_x (cdoc->paper.get_line_len());
}

void pdf_focus_block_begin()
{
   cdoc->focus_block_begin();
}

void pdf_focus_block_end()
{
   cdoc->focus_block_end();
}

int32 pdf_focus_doc_begin()
{
   return cdoc->focus_set_xy(0,0);
}

int32 pdf_focus_doc_end()
{
   int rc1 = cdoc->focus_set_y(cdoc->paper.get_line_cnt()-1);
   int rc2 = cdoc->focus_set_x(cdoc->paper.get_line_len());
   return rc1 || rc2;
}

int32 pdf_focus_window_top()
{
   return cdoc->focus_set_y (cdoc->window.y);
}

int32 pdf_focus_window_mid()
{
   return cdoc->focus_set_y (cdoc->window.y + ebrd->get_height()/2);
}

int32 pdf_focus_window_bottom()
{
   return cdoc->focus_set_y (cdoc->window.y + ebrd->get_height() - 1);
}

int32 pdf_focus_skip_prev_word()
{
   return cdoc->focus_skip_prev (is_word);
}

int32 pdf_focus_skip_next_word()
{
   return cdoc->focus_skip_next(is_word);
}

int32 pdf_focus_skip_prev_non_word()
{
   return cdoc->focus_skip_prev (not_word);
}

int32 pdf_focus_skip_next_non_word()
{
   return cdoc->focus_skip_next(not_word);
}

int32 pdf_focus_skip_prev_space()
{
   return cdoc->focus_skip_prev(is_space);
}

int32 pdf_focus_skip_next_space()
{
   return cdoc->focus_skip_next(is_space);
}

int32 pdf_focus_mark()
{
   int inx = mac_runner->get_arg_i32(0);
   mac_rtcheck(inx < 10);
   return cdoc->focus_mark(inx);
}

int32 pdf_focus_prev_mark()
{
   int32 prev_x = cdoc->iter.get_x();
   int32 prev_y = cdoc->iter.get_y();
   int32 rc = cdoc->focus_mark(def_mark_prev);
   cdoc->mark_set(def_mark_prev, prev_x, prev_y);
   return rc;
}

int32 pdf_focus_tmp_mark()
{
   return cdoc->focus_mark(def_mark_tmp);
}

int32 pdf_focus_line()
{
   bool rc = def_error;

   if (mac_runner->get_arg_cnt())
   {
      int32 new_y = mac_runner->get_arg_i32(0) - 1;

      rc = cdoc->focus_set_y(new_y);
   }
   else
   {
      /*
      static char buf[20];
      if (user_str(mline_win, msg_get(msg_line),buf,sizeof(buf)))
      {
         int32 n = atol(buf);
         return cdoc->focus_set_y(n-1);
      } else return def_error;
      */
   }
   return rc;
}

int32 pdf_focus_column()
{
   bool rc = def_error;

   if (mac_runner->get_arg_cnt())
   {
      int32 new_x = mac_runner->get_arg_i32(0) - 1;
      mac_rtcheck (new_x >= 0);
      rc = cdoc->focus_set_vx(new_x);
   }
   else
   {
      /*
      static char buf[20];
      if (user_str(mline_win, msg_get(msg_column),buf,sizeof(buf)))
      {
         int32 n = (int32)atol(buf);
         return cdoc->focus_set_vx(n-1);
      } else return def_error;
      */
   }
   return rc;
}

int32 pdf_focus_match()
{
   return def_error;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

int32 pdf_window_scroll_left()
{
   int32 rc = def_error;
   if (cdoc->window.x)
   {
      cdoc->window.x--;
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

int32 pdf_window_scroll_right()
{
   int32 rc = def_error;
   if (cdoc->window.x < def_int32_max - 2048)
   {
      cdoc->window.x++;
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

int32 pdf_window_scroll_up()
{
   int32 rc = def_error;
   if (cdoc->window.y)
   {
      cdoc->window.y--;
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

int32 pdf_window_scroll_down()
{
   int32 rc = def_error;
   if (cdoc->window.y < cdoc->paper.get_line_cnt() - 1)
   {
      cdoc->window.y++;
      view_invalidate();
      rc = def_ok;
   }
   return rc;
}

void pdf_cursor_adjust()
{
   cdoc->cursor_adjust_xy();
   ebrd->set_xy(cdoc->cursor.x, cdoc->cursor.y);
}

void pdf_window_adjust()
{
   cdoc->window_adjust_xy();
   ebrd->set_xy(cdoc->cursor.x, cdoc->cursor.y);
}

int32 pdf_focus_is_column_one()
{
   return cdoc->iter.get_x() == 0;
}

int32 pdf_focus_is_line_head()
{
   return cdoc->paper_is_space_till(cdoc->iter.get_x()) && !is_space(cdoc->iter.get_val());
}

int32 pdf_focus_is_line_out()
{
   return cdoc->iter.get_x() >= cdoc->paper.get_line_len();
}

int32 pdf_focus_is_first_line()
{
   return cdoc->iter.get_y() == 0;
}

int32 pdf_focus_is_last_line()
{
   return cdoc->iter.get_y() == cdoc->paper.get_line_cnt() - 1;
}

int32 pdf_focus_is_window_top()
{
   return cdoc->iter.get_y() == cdoc->window.y;
}

int32 pdf_focus_is_window_bottom()
{
   return cdoc->iter.get_y() == cdoc->window.y + ebrd->get_height() - 1;
}

int32 pdf_focus_is_in_block()
{
   return cdoc->focus_is_in_block();
}

int32 pdf_focus_get_line_num()
{
   return cdoc->iter.get_y() + 1;
}

int32 pdf_focus_get_column_num()
{
   return cdoc->iter.get_vx() + 1;
}

