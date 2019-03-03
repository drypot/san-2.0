                                                                                                                        /*
--------------------------------------------------------------------------------
   text/docwin.cpp
	copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

static bool invalid_flg;
static bool line_invalid_flg;

static cls_paper_iter iter;

static int32 llen;
static int32 lcnt;

static int32 block_begin_x;
static int32 block_begin_y;
static int32 block_end_x;
static int32 block_end_y;

static int32 brd_width;

void view_invalidate()
{
   invalid_flg = def_yes;
   line_invalid_flg = def_no;
}

void view_invalidate_line()
{
   if (!invalid_flg) line_invalid_flg = def_yes;
}

bool view_is_invalid()
{
   return invalid_flg;
}

bool view_is_line_invalid()
{
   return line_invalid_flg;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void set_blocked_color()
{
   ebrd->set_fg(clr_blocked_fg);
   ebrd->set_bg(clr_blocked_bg);
}

static void set_normal_color()
{
   ebrd->set_fg(clr_normal_fg);
   ebrd->set_bg(clr_normal_bg);
}

static void update_line_column_block()
{
   /*
   char16 ch;
   int32 ch_begin;
   int32 ch_end;

   if (block_begin_x <= iter.get_vx()) set_blocked_color();
   else set_normal_color();

   if (block_end_x <= iter.get_vx()) set_normal_color();
   
   while (ebrd->get_x() < brd_width)
   {
      ch = iter.get_val();
      ch_begin = iter.get_vx();

      if (is_double(ch))
      {
         ch_end = ch_begin + 1;
         if (is_inside(block_begin_x, ch_begin, ch_end) || is_inside(block_end_x, ch_begin, ch_end))
         {
            if (ch_begin == block_begin_x) set_blocked_color();
            if (ch_begin == block_end_x) set_normal_color();
            tty_output_left(ch);
            if (ch_end == block_begin_x) set_blocked_color();
            if (ch_end == block_end_x) set_normal_color();
            tty_output_right(ch);
         }
         else tty_output(ch);
      }
      ef (ch == '\t')
      {
         ch_end = ch_begin + iter.get_width();
         while (ch_begin < ch_end)
         {
            if (ch_begin == block_begin_x) set_blocked_color();
            if (ch_begin == block_end_x) set_normal_color();
            tty_skip_erase(1);
            ch_begin++;
         }
      }
      else
      {
         if (ch_begin == block_begin_x) set_blocked_color();
         if (ch_begin == block_end_x) set_normal_color();
         tty_output(ch);
      }
      iter.x_rel(1);
   }
   */
}

static void update_line_blk_edge (bool check_begin_flg, bool check_end_flg)
{
   bool normal_flg = def_no;

   if (check_begin_flg && iter.get_x() < block_begin_x) normal_flg = def_yes;
   if (check_end_flg && iter.get_x() >= block_end_x) normal_flg = def_yes;

   if (normal_flg) set_normal_color();
   else set_blocked_color();

   while (ebrd->get_x() < brd_width)
   {
      if (check_begin_flg && iter.get_x() == block_begin_x) set_blocked_color();
      if (check_end_flg && iter.get_x() == block_end_x) set_normal_color();

      if (iter.get_val() == '\t') ebrd->write_space(iter.get_width());
      else ebrd->write(iter.get_val());

      iter.set_x_rel (1);
   }
}

static void update_line_normal()
{
   while (iter.get_x() < llen && ebrd->get_x() < brd_width)
   {
      if (iter.get_val() == '\t') ebrd->write_space(iter.get_width());
      else ebrd->write (iter.get_val());
      iter.set_x_rel (1);
   }
   if (ebrd->get_x() < brd_width) ebrd->erase_to_eol();
}

static void update_line(int y , int32 num)
{
   if (!is_inside (num,0,lcnt-1))
   {
      set_normal_color();
      ebrd->set_xy(0, y);
      ebrd->write('~');
      ebrd->erase_to_eol();
   }
   else
   {
      iter.set_y (num);
      iter.locate ();
      iter.set_vx (cdoc->window.x);
      llen = cdoc->paper.get_line_len();

      ebrd->set_xy(iter.get_vx() - cdoc->window.x, y);

      if (cdoc->block_enabled_flg)
      {
         switch(cdoc->block_type)
         {
            case def_block_type_char :
               if (num == block_begin_y || num == block_end_y)
                  update_line_blk_edge(num==block_begin_y, num==block_end_y);
               else
               {
                  if (is_outside (num, block_begin_y, block_end_y)) set_normal_color();
                  else set_blocked_color();
                  update_line_normal();
               }
               break;

            case def_block_type_line :
               if (is_inside (num, block_begin_y, block_end_y)) set_blocked_color();
               else set_normal_color();
               update_line_normal();
               break;

            case def_block_type_column :
               if (is_inside (num, block_begin_y, block_end_y))
               {
                  update_line_column_block();
               }
               else
               {
                  set_normal_color();
                  update_line_normal();
               }
               break;
         }
      }
      else
      {
         set_normal_color();
         update_line_normal();
      }
   }
}

void view_update()
{
   iter.reset(&cdoc->paper);
   lcnt = cdoc->paper.get_line_cnt();
   brd_width = ebrd->get_width();

   if (cdoc->block_enabled_flg)
   {
      block_begin_x = cdoc->block_begin.x;
      block_begin_y = cdoc->block_begin.y;
      block_end_x = cdoc->block_end.x;
      block_end_y = cdoc->block_end.y;
   }

   if (line_invalid_flg)
   {
      update_line(cdoc->cursor.y, cdoc->window.y + cdoc->cursor.y);
      line_invalid_flg = def_no;
   }
   ef (invalid_flg)
   {
      int32 base_y = cdoc->window.y;
      int height = ebrd->get_height();
      int i;

      for (i = 0; i < height ; i++)
      {
         update_line (i , base_y + i);
      }
      cdoc->iter.locate();
      invalid_flg = def_no;
   }

   ebrd->set_xy(cdoc->cursor.x, cdoc->cursor.y);
   ebrd->calc_cursor_width(cdoc->iter.get_val());
}

void view_draw(HPS hps)
{
   ebrd->draw(hps,0,32);
}

void view_draw()
{
   HPS hps = WinGetPS(client_hwnd);
   view_draw(hps);
   WinReleasePS(hps);
}

