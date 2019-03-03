                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/paper.cpp -- text line container
   copyright(C) kyuhyun park
   1987
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/buf.hpp>
#include <cnt/paper.hpp>
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_paper
--------------------------------------------------------------------------------                                        */

#define def_disk_buf_size (16*1024)

static tem_wbuf<char16, def_size_paper_frame> stt_wbuf;
static int32 stt_line_len_i32;

cls_paper::cls_paper() :
   line_base_i32(0),
   line_num_i32(0)
{
}

cls_paper::~cls_paper()
{
}

void cls_paper::reset()
{
   reset_core();
   len_dary.insert(1);
   len_dary.put_val(0);
}

void cls_paper::reset_core()
{
   char_dary.reset();
   len_dary.reset();
   line_base_i32 = 0;
   line_num_i32 = 0;
}

void cls_paper::read_file_front_end()
{
   reset_core();
   stt_line_len_i32 = 0;
}

void cls_paper::read_file_back_end()
{
   if (!stt_wbuf.is_empty()) read_file_flush_buf();
   if (stt_line_len_i32 || get_line_cnt() == 0) read_file_line_end();
}

void cls_paper::read_file_flush_buf()
{
   int32 pub_sz = stt_wbuf.get_cnt();
   char_dary.insert (pub_sz);
   char_dary.put_ary (stt_wbuf.get_base(), pub_sz);
   char_dary.locate_end ();
   stt_wbuf.reset ();
}

void cls_paper::read_file_line_end()
{
   len_dary.insert ();
   len_dary.put_val (stt_line_len_i32);
   len_dary.locate_end ();
   stt_line_len_i32 = 0;
}

void cls_paper::read_file_johab (char* arg_fname)
{
   cls_rfbuf rfbuf (arg_fname, def_disk_buf_size);
   char16 ch1;
   char16 ch2;

   read_file_front_end();

	forever
	{
      if ( rfbuf.get_rest_cnt() < 3 )
		{
         if ( rfbuf.get_file_rest_cnt() == 0 )
			{
            if (rfbuf.get_rest_cnt() == 1 && is_double(rfbuf.peek_val())) break;
            if (rfbuf.get_rest_cnt() == 0) break;
			}
         else rfbuf.fill();
		}

      if (stt_wbuf.is_full()) read_file_flush_buf();

      ch1 = rfbuf.get_val();
      if (is_single((byte)ch1))
      {
         if (iscntrl(ch1))
         {
            if (ch1 == '\r' && rfbuf.get_rest_cnt() && rfbuf.peek_val() == '\n') ch1 = rfbuf.get_val();
            if (ch1 == '\n')
            {
               read_file_line_end();
               continue;
            }
         }
         stt_wbuf.put_val(ch1);
      }
      else
      {
         ch2 = rfbuf.get_val();
         stt_wbuf.put_val(make_c16(ch1,ch2));
      }
      stt_line_len_i32++;
   }

   read_file_back_end();
}

void cls_paper::read_file_wansung (char* arg_fname)
{
   cls_rfbuf rfbuf (arg_fname, def_disk_buf_size);
   cls_wchar wchar;
	char16 ch;

   read_file_front_end();

	forever
	{
      if ( rfbuf.get_rest_cnt() < 3 )
		{
         if ( rfbuf.get_file_rest_cnt() == 0 )
			{
            if (rfbuf.get_rest_cnt() == 1 && is_double(rfbuf.peek_val())) break;
            if (rfbuf.get_rest_cnt() == 0) break;
			}
         else rfbuf.fill();
		}

      if (stt_wbuf.is_full()) read_file_flush_buf();

      ch = rfbuf.get_val();
		if (is_single((byte)ch))
		{
			if (iscntrl(ch))
			{
            if (ch == '\r' && rfbuf.get_rest_cnt() && rfbuf.peek_val() == '\n') ch = rfbuf.get_val();
            if (ch == '\n')
				{
               read_file_line_end();
					continue;
				}
			}
         stt_wbuf.put_val(ch);
      }
      else
      {
         wchar.bytes.high = (byte) ch;
         wchar.bytes.low = (byte) rfbuf.get_val();
         wchar.to_johab();
         stt_wbuf.put_val( wchar.c16 );
      }
      stt_line_len_i32++;
   }

   read_file_back_end();
}

void cls_paper::write_file_johab (char* arg_fname)
{
   cls_wfbuf wfbuf(arg_fname, def_disk_buf_size);
   char16 ch;
   int32 ln , end_ln;
   int32 inx;

   ln = 0;
   end_ln = get_line_cnt();
   inx = 0;

   while (ln < end_ln)
   {
      stt_line_len_i32 = len_dary.get_val(ln);
      while (stt_line_len_i32--)
      {
         if (wfbuf.get_free_cnt() < 4) wfbuf.flush();
         ch = char_dary.get_val(inx++);
         if (is_single(ch)) wfbuf.put_val((byte)ch);
         else
         {
            wfbuf.put_val(get_u16_high(ch));
            wfbuf.put_val(get_u16_low(ch));
         }
      }
      wfbuf.put_val('\r');
      wfbuf.put_val('\n');
      ln++;
   }
}

void cls_paper::write_file_wansung (char* arg_fname)
{
   cls_wfbuf wfbuf(arg_fname, def_disk_buf_size);
   char16 ch;
   int32 ln , end_ln;
   int32 inx;
   cls_wchar wchar;

   ln = 0;
   end_ln = get_line_cnt();
   inx = 0;

   while (ln < end_ln)
   {
      stt_line_len_i32 = len_dary.get_val(ln);
      while (stt_line_len_i32--)
      {
         if (wfbuf.get_free_cnt() < 4) wfbuf.flush();
         ch = char_dary.get_val(inx++);
         if (is_single(ch)) wfbuf.put_val((byte)ch);
         else
         {
            wchar.c16 = ch;
            wchar.to_wansung();
            wfbuf.put_val(wchar.bytes.high);
            wfbuf.put_val(wchar.bytes.low);
         }
      }
      wfbuf.put_val('\r');
      wfbuf.put_val('\n');
      ln++;
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_paper - locate
--------------------------------------------------------------------------------                                        */

void cls_paper::locate_rel(int32 dy)
{
   if (dy) locate(line_num_i32 + dy);
}

void cls_paper::locate(int32 y)
{
   mac_assert(y >= 0 && y < get_line_cnt());

   int upward_flg;

   if (y == line_num_i32) return;

   if (y < line_num_i32)
   {
      if (y < line_num_i32 / 2)
      {
         line_num_i32 = 0;
         line_base_i32 = 0;
         upward_flg = def_yes;
      }
      else upward_flg = def_no;
   }
   else
   {
      if (y < line_num_i32 + (get_line_cnt() - line_num_i32) /2) upward_flg = def_yes;
      else
      {
         line_num_i32 = get_line_cnt() - 1;
         line_base_i32 = char_dary.get_cnt() - len_dary.get_val(line_num_i32);
         upward_flg = def_no;
      }
   }

   if (upward_flg)
   {
      while (line_num_i32 < y) line_base_i32 += len_dary.get_val(line_num_i32++);
   }
   else
   {
      while (line_num_i32 > y) line_base_i32 -= len_dary.get_val(--line_num_i32);
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_paper - edit
--------------------------------------------------------------------------------                                        */

int32 cls_paper::get_line_begin()
{
   int32 len = get_line_len();
   int32 inx = 0;

   while (inx < len && is_space(char_dary.get_val(line_base_i32 + inx))) inx++;
   return inx == len ? 0 : inx;
}

void cls_paper::insert_line (int32 cnt)
{
   int32 inx     = line_num_i32;
   int32 end_inx = inx + cnt;

   len_dary.locate (inx);
   len_dary.insert (cnt);
   while (inx < end_inx) len_dary.put_val (inx++,0);
}

void cls_paper::insert_line_below (int32 cnt)
{
   int32 inx     = line_num_i32 + 1;
   int32 end_inx = inx + cnt;

   len_dary.locate (inx);
   len_dary.insert (cnt);
   while (inx < end_inx) len_dary.put_val (inx++, 0);
}

void cls_paper::remove_line (int32 cnt)
{
   mac_assert (line_num_i32 + cnt < get_line_cnt());

   int32 inx     = line_num_i32;
   int32 end_inx = inx + cnt;
   int32 ch_cnt  = 0;

   while (inx < end_inx) ch_cnt += len_dary.get_val (inx++);
   char_dary.locate (line_base_i32);
   char_dary.remove (ch_cnt);
   len_dary.locate (line_num_i32);
   len_dary.remove (cnt);
}

void cls_paper::remove_line_below (int32 cnt)
{
   mac_assert (line_num_i32 + 1 + cnt <= get_line_cnt());

   int32 inx     = line_num_i32 + 1;
   int32 end_inx = inx + cnt;
   int32 ch_cnt  = 0;

   while (inx < end_inx) ch_cnt += len_dary.get_val (inx++);
   char_dary.locate (line_base_i32 + get_line_len());
   char_dary.remove (ch_cnt);
   len_dary.locate (line_num_i32+1);
   len_dary.remove (cnt);
}

void cls_paper::clear ()
{
   char_dary.locate (line_base_i32);
   len_dary.locate (line_num_i32);
   char_dary.remove (len_dary.get_val());
   len_dary.put_val (0);
}

void cls_paper::truncate (int32 sz)
{
   len_dary.locate (line_num_i32);
   int32 len = len_dary.get_val ();
   if (sz < len)
   {
      char_dary.locate (line_base_i32 + sz);
      char_dary.remove (len - sz);
      len_dary.put_val (sz);
   }
}

void cls_paper::remove (int32 inx, int32 cnt)
{
   len_dary.locate (line_num_i32);
   int32 len = len_dary.get_val ();
   if (inx < len)
   {
      if (len < inx + cnt) cnt = len - inx;
      char_dary.locate (line_base_i32 + inx);
      char_dary.remove (cnt);
      len_dary.put_val (len - cnt);
   }
}

void cls_paper::separate (int32 inx)
{
   insert_line_below ();
   len_dary.locate (line_num_i32);
   int32 len = len_dary.get_val ();
   if (inx < len)
   {
      len_dary.put_val (inx);
      len_dary.put_val (line_num_i32+1, len - inx);
   }
}

void cls_paper::insert_no_fill (int32 inx, int32 cnt)
{
   expand (inx);
   char_dary.locate (line_base_i32 + inx);
   char_dary.insert (cnt);
   *len_dary.get_pnt (line_num_i32) += cnt;
}

void cls_paper::insert (int32 inx, int32 cnt)
{
   len_dary.locate (line_num_i32);
   int32 len = len_dary.get_val ();
   if (inx < len)
   {
      char_dary.locate (line_base_i32 + inx);
      char_dary.insert (cnt);
      len_dary.put_val (len + cnt);
   }
   fill(inx,' ',cnt);
}

void cls_paper::expand (int32 sz)
{
   int32 len = get_line_len ();
   if (len < sz) fill (len,' ',sz - len);
}

void cls_paper::fill (int32 inx, char16 ch, int32 cnt)
{
   int32 len = get_line_len ();

   if (len < inx)
   {
      fill(len, ' ', inx - len);
      len = inx;
   }
   if (len < inx + cnt)
   {
      int32 expand_sz = inx + cnt - len;
      char_dary.locate (line_base_i32 + len);
      char_dary.insert (expand_sz);
      len_dary.put_val (line_num_i32, inx + cnt);
   }

   int32 loop_inx = line_base_i32 + inx;
   int32 end_inx = loop_inx + cnt;
   while (loop_inx < end_inx) char_dary.put_val (loop_inx++, ch);
}

void cls_paper::join (int32 inx)
{
   mac_assert(line_num_i32 + 1 < get_line_cnt());
   mac_assert(get_line_len() <= inx);
   if (get_line_len() < inx) expand(inx);
   *len_dary.get_pnt(line_num_i32) += len_dary.get_val(line_num_i32+1);
   len_dary.put_val(line_num_i32+1, 0);
   remove_line_below();
}

void cls_paper::put_paper (int32 dst_inx, cls_paper* src_paper, int32 src_inx, int32 cnt)
{
   mac_assert(this != src_paper);

   if (get_line_len() < dst_inx + cnt) expand(dst_inx + cnt);
   char_dary.locate(line_base_i32 + dst_inx);
   if (src_inx + cnt <= src_paper->get_line_len())
   {
      src_paper->char_dary.locate(src_paper->line_base_i32 + src_inx);
      char_dary.put_dary(&src_paper->char_dary,cnt);
      cnt = 0;
   }
   ef (src_inx < src_paper->get_line_len())
   {
      int32 tr_cnt = src_paper->get_line_len() - src_inx;
      src_paper->char_dary.locate(src_paper->line_base_i32 + src_inx);
      char_dary.put_dary(&src_paper->char_dary,tr_cnt);
      dst_inx += tr_cnt;
      cnt -= tr_cnt;
   }
   if (cnt) fill(dst_inx, ' ', cnt);
}

void cls_paper::put_char_dary (int32 inx, cls_paper_char_dary* src_char_dary, int32 cnt)
{
   mac_assert(&char_dary != src_char_dary);

   if (get_line_len() < inx + cnt) expand (inx + cnt);
   char_dary.locate (line_base_i32 + inx);
   char_dary.put_dary (src_char_dary,cnt);
}

void cls_paper::put_ary (int32 inx, char16* pnt_c16, int32 cnt)
{
   if (get_line_len() < inx + cnt) expand (inx + cnt);
   char_dary.locate (line_base_i32 + inx);
   char_dary.put_ary (pnt_c16,cnt);
}

void cls_paper::put_val (int32 inx, char16 ch)
{
   if (get_line_len() <= inx) expand (inx+1);
   char_dary.locate (line_base_i32 + inx);
   char_dary.put_val (ch);
}

void cls_paper::get_char_dary (int32 inx, cls_paper_char_dary* dst_cfile, int32 cnt)
{
   mac_assert(&char_dary != dst_cfile);

   int32 len = get_line_len();
   int32 fill_cnt = len <= inx ? cnt : len < inx + cnt ? inx + cnt - len : 0;
   cnt -= fill_cnt;

   if (cnt)
   {
      char_dary.locate (line_base_i32 + inx);
      dst_cfile->put_dary (&char_dary,cnt);
   }
   while (fill_cnt--)
   {
      dst_cfile->put_val (' ');
      dst_cfile->locate_rel (1);
   }
}

void cls_paper::get_ary (int32 inx, char16* pnt_c16, int32 cnt)
{
   int32 len = get_line_len();
   int32 fill_cnt = len < inx ? cnt : len < inx + cnt ? inx + cnt - len : 0;
   cnt -= fill_cnt;
   pnt_c16[cnt] = 0;
   if (cnt)
   {
      char_dary.locate(line_base_i32 + inx);
      char_dary.get_ary(pnt_c16, cnt);
   }
   if (fill_cnt) mem_set16 (pnt_c16 + cnt, ' ', fill_cnt);
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_paper_iter
--------------------------------------------------------------------------------                                        */

void cls_paper_iter::set_x (int32 arg_x)
{
   int32 len = paper_pnt->get_line_len();

   if (arg_x < x)
   {
      if (arg_x > (x - arg_x))
      {
         if (len < x)
         {
            int32 tmp_pre = get_max(arg_x, len);
            vx -= x - tmp_pre;
            x = tmp_pre;
            if (x == arg_x) return;
         }

         bool tab_bool = def_no;
         int32 inx = arg_x;

         while (inx < x)
         {
            if (paper_pnt->get_val(inx) == '\t')
            {
               tab_bool = def_yes;
               break;
            }
            inx++;
         }

         if (!tab_bool)
         {
            while (arg_x < x)
            {
               x--;
               vx -= get_width();
            }
            return;
         }
      }
      x = vx = 0;
   }

   int32 tmp_end = get_min (arg_x, len);

   while (x < tmp_end)
   {
      vx += get_width ();
      x++;
   }

   if (x < arg_x)
   {
      vx += arg_x - x;
      x = arg_x;
   }
}

void cls_paper_iter::set_vx (int32 arg_vx)
{
   if (arg_vx < vx) x = vx = 0;

   int32 len = paper_pnt->get_line_len();
   int32 new_val = vx;

   while (new_val += get_width(), new_val <= arg_vx)
   {
      vx = new_val;
      x++;
      if (len <= x)
      {
         x += arg_vx - vx;
         vx = arg_vx;
         break;
      }
   }
}

void cls_paper_iter::set_vx_inclusive (int32 arg_x)
{
   set_vx(arg_x);
   if (vx < arg_x) set_x_rel(1);
}
