                                                                                                                        /*
--------------------------------------------------------------------------------
   vio/textbrd.cpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <fnt/hanfnt.hpp>
#include <fnt/engfnt.hpp>
#include <fnt/spcfnt.hpp>
#include <fnt/hnjfnt.hpp>
#include <fnt/nulfnt.hpp>
#include <vio/textbrd.hpp>

#define mac_steps() mac_step(0x00); mac_step(0x01); mac_step(0x02); mac_step(0x03); mac_step(0x04); mac_step(0x05); mac_step(0x06); mac_step(0x07); mac_step(0x08); mac_step(0x09); mac_step(0x0A); mac_step(0x0B); mac_step(0x0C); mac_step(0x0D); mac_step(0x0E); mac_step(0x0F)

static byte stt_ary_byte_fnt_buf[32];

cls_text_brd::cls_text_brd(int cx, int cy) :
   cls_text_img(cx, cy) ,
   x(0),
   y(0),
   attr(0),
   show_cursor_flg    (def_yes),
   outline_cursor_flg (def_no),
   wide_cursor_flg    (def_no),
   cursor_code_c16     (0)
{
}

cls_text_brd::~cls_text_brd()
{
}

void cls_text_brd::set_normal ()
{
   attr = 0;
}

void cls_text_brd::set_inverse (bool b)
{
   attr &= ~def_mask_inverse;
   if (b) attr |= def_mask_inverse;
}

void cls_text_brd::set_underline (bool b)
{
   attr &= ~def_mask_underline;
   if (b) attr |= def_mask_underline;
}

void cls_text_brd::write_img8 (void* arg_fnt_pnt)
{
   if (is_inside_less(y, 0, get_height()))
   {
      if (is_inside_less(x, 0, get_width())) cpy_img8(x, y, arg_fnt_pnt);
      x++;
   }
}

void cls_text_brd::write_img16 (void* arg_fnt_pnt)
{
   if (is_inside_less(y, 0, get_height()))
   {
      if (is_inside_less(x, 0, get_width()-1)) cpy_img16  (x, y, arg_fnt_pnt);
      ef (x == -1)                             cpy_img16r (0, y, arg_fnt_pnt);
      ef (x == get_width() - 1)                cpy_img16l (x, y, arg_fnt_pnt);
      x+=2;
   }
}

void cls_text_brd::write (char16 ch)
{
   if (is_single (ch))
   {
      if (!attr)
      {
         write_img8 (get_eng_fnt(ch));
      }
      else
      {
         pcs_attr8(get_eng_fnt(ch));
         write_img8 (stt_ary_byte_fnt_buf);
      }
   }
   else
   {
      void* fnt_pnt;

      if (is_hangul  (ch)) fnt_pnt = get_han_fnt(ch);
      ef (is_special (ch)) fnt_pnt = get_spc_fnt(ch);
      ef (is_hanja   (ch)) fnt_pnt = get_hnj_fnt(ch);
      el                   fnt_pnt = get_nul_fnt();

      if (!attr)
      {
         write_img16 (fnt_pnt);
      }
      else
      {
         pcs_attr16 (fnt_pnt);
         write_img16 (stt_ary_byte_fnt_buf);
      }
   }
}

void cls_text_brd::write (char* p)
{
   while (*p) write (read_c16(&p));
}

void cls_text_brd::write_space (int cnt)
{
   if (is_inside_less(y,0,get_height()))
   {
      int x1 = get_max (x, 0);
      int x2 = get_min (x + cnt, get_width()) - 1;

      if (x1 <= x2) erase_rect(x1,y,x2-x1+1,1);
   }
   x += cnt;
}

void cls_text_brd::insert_char(int cnt)
{
   if (is_inside_less(x,0,get_width()) && is_inside_less(y,0,get_height()))
   {
      scroll_right(x, y, get_width() - x, 1, cnt);
   }
}

void cls_text_brd::remove_char(int cnt)
{
   if (is_inside_less(x,0,get_width()) && is_inside_less(y,0,get_height()))
   {
      scroll_left(x, y, get_width() - x, 1, cnt);
   }
}

void cls_text_brd::insert_line(int cnt)
{
   if (is_inside_less(y,0,get_height()))
   {
      scroll_down(0, y, get_width(), get_height()-y, cnt);
   }
}

void cls_text_brd::remove_line(int cnt)
{
   if (is_inside_less(y,0,get_height()))
   {
      scroll_up(0, y, get_width(), get_height()-y, cnt);
   }
}

void cls_text_brd::erase()
{
   cls_text_img::erase();
   set_xy(0,0);
}

void cls_text_brd::erase_line ()
{
   if (is_inside_less(y,0,get_height()))
   {
      erase_rect(0, y, get_width(), 1);
   }
}

void cls_text_brd::erase_to_bol ()
{
   if (is_inside_less(y,0,get_height()) && x > 0)
   {
      int w = get_min (x, get_width());
      erase_rect(0, y, w, 1);
   }
}

void cls_text_brd::erase_to_eol ()
{
   if (is_inside_less(y,0,get_height()) && x < get_width())
   {
      int mrx_x = get_max (x, 0);
      erase_rect(mrx_x, y, get_width() - mrx_x, 1);
   }
}

void cls_text_brd::erase_to_bos ()
{
   erase_to_bol();
   if (y > 0) erase_rect(0, 0, get_width(), get_min(get_height(), y));
}

void cls_text_brd::erase_to_eos ()
{
   erase_to_eol();
   if (y + 1 < get_height()) erase_rect(0, get_max(y + 1,0), get_width(), get_height() - (y + 1));
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static byte box_img_byte_ary[] =
{
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

static byte outline_img_byte_ary[] =
{
   0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
   0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF
};

static byte left_outline_img_byte_ary[] =
{
   0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
   0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF
};

static byte right_outline_img_byte_ary[] =
{
   0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF
};

void cls_text_brd::show_cursor(bool val)
{
   show_cursor_flg = val;
}

void cls_text_brd::set_outline_cursor(bool val)
{
   outline_cursor_flg = val;
}

void cls_text_brd::set_wide_cursor(bool val)
{
   wide_cursor_flg = val;
}

void cls_text_brd::set_img_cursor (char16 ch)
{
   cursor_code_c16 = ch;
}

void cls_text_brd::calc_cursor_width (char16 ch)
{
   wide_cursor_flg = is_double(ch);
}

void cls_text_brd::draw_cursor ()
{
   if (show_cursor_flg && is_inside_less(y, 0, get_height()))
   {
      if (cursor_code_c16)
      {
         uint prev_attr = attr;
         uint prev_x    = x;

         if (is_inside_less (x, 0, get_width()))
         {
            save_rect (x, y, 1, 1, cursor_back_img_byte_ary);
            cursor_back_clr1_byte = get_clr(x,y);
         }

         if (is_inside_less (x+1, 0, get_width()))
         {
            save_rect (x+1, y, 1, 1, cursor_back_img_byte_ary+16);
            cursor_back_clr2_byte = get_clr(x+1,y);
         }

         set_inverse(def_yes);
         write(cursor_code_c16);

         x    = prev_x;
         attr = prev_attr;
      }
      else
      {
         if (wide_cursor_flg)
         {
            if (outline_cursor_flg)
            {
               if (is_inside_less (x, 0, get_width()))
               {
                  save_rect (x, y, 1, 1,cursor_back_img_byte_ary);
                  or8 (x, y, left_outline_img_byte_ary);
               }

               if (is_inside_less (x+1, 0, get_width()))
               {
                  save_rect (x+1, y, 1, 1, cursor_back_img_byte_ary+16);
                  or8 (x+1, y, right_outline_img_byte_ary);
               }
            }
            else
            {
               if (is_inside_less (x, 0, get_width())) xor8 (x, y, box_img_byte_ary);
               if (is_inside_less (x+1, 0, get_width())) xor8 (x+1, y, box_img_byte_ary);
            }
         }
         else
         {
            if (is_inside_less (x, 0, get_width()))
            {
               if (outline_cursor_flg)
               {
                  save_rect (x, y, 1, 1, cursor_back_img_byte_ary);
                  or8 (x, y, outline_img_byte_ary);
               }
               else
               {
                  xor8 (x, y, box_img_byte_ary);
               }
            }
         }
      }
   }
}

void cls_text_brd::erase_cursor ()
{
   if (show_cursor_flg && is_inside_less(y, 0, get_height()))
   {
      if (cursor_code_c16)
      {
         if (is_inside_less (x, 0, get_width()))
         {
            restore_rect (x, y, 1, 1, cursor_back_img_byte_ary);
            set_clr(x, y, cursor_back_clr1_byte);
         }

         if (is_inside_less (x+1, 0, get_width()))
         {
            restore_rect (x+1, y, 1, 1, cursor_back_img_byte_ary+16);
            set_clr(x, y, cursor_back_clr2_byte);
         }
      }
      else
      {
         if (wide_cursor_flg)
         {
            if (outline_cursor_flg)
            {
               if (is_inside_less (x, 0, get_width())) restore_rect (x, y, 1, 1, cursor_back_img_byte_ary);
               if (is_inside_less (x+1, 0, get_width())) restore_rect (x+1, y, 1, 1, cursor_back_img_byte_ary+16);
            }
            else
            {
               if (is_inside_less (x, 0, get_width())) xor8 (x, y, box_img_byte_ary);
               if (is_inside_less (x+1, 0, get_width())) xor8 (x+1, y, box_img_byte_ary);
            }
         }
         else
         {
            if (is_inside_less (x, 0, get_width()))
            {
               if (outline_cursor_flg) restore_rect (x, y, 1, 1, cursor_back_img_byte_ary);
               else xor8 (x, y, box_img_byte_ary);
            }
         }
      }
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#define def_edge_up_left     ( edge_fnt8_ary + 0 )
#define def_edge_up          ( edge_fnt8_ary + 1 )
#define def_edge_up_right    ( edge_fnt8_ary + 2 )
#define def_edge_left        ( edge_fnt8_ary + 3 )
#define def_edge_right       ( edge_fnt8_ary + 4 )
#define def_edge_down_left   ( edge_fnt8_ary + 5 )
#define def_edge_down        ( edge_fnt8_ary + 6 )
#define def_edge_down_right  ( edge_fnt8_ary + 7 )
#define def_edge_in          ( edge_fnt8_ary + 8 )
#define def_edge_line        ( edge_fnt8_ary + 9 )

static type_fnt8 edge_fnt8_ary[] =
{
   /*
   {  0x00, 0x0a, 0x15, 0x3f,  0x5f, 0x3a, 0x55, 0x38,  0x55, 0x39, 0x55, 0x39,  0x55, 0x39, 0x55, 0x39 },
   {  0x00, 0xaa, 0x55, 0xff,  0xff, 0xaa, 0x55, 0x00,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff },
   {  0x00, 0xa8, 0x54, 0xfa,  0xfc, 0xaa, 0x5c, 0x2a,  0x9c, 0xaa, 0x9c, 0xaa,  0x9c, 0xaa, 0x9c, 0xaa },
   {  0x55, 0x39, 0x55, 0x39,  0x55, 0x39, 0x55, 0x39,  0x55, 0x39, 0x55, 0x39,  0x55, 0x39, 0x55, 0x39 },
   {  0x9c, 0xaa, 0x9c, 0xaa,  0x9c, 0xaa, 0x9c, 0xaa,  0x9c, 0xaa, 0x9c, 0xaa,  0x9c, 0xaa, 0x9c, 0xaa },
   {  0x55, 0x39, 0x55, 0x39,  0x55, 0x39, 0x55, 0x39,  0x54, 0x3a, 0x5d, 0x3f,  0x5f, 0x2a, 0x15, 0x00 },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0x00, 0xaa, 0x55, 0xff,  0xff, 0xaa, 0x55, 0x00 },
   {  0x9c, 0xaa, 0x9c, 0xaa,  0x9c, 0xaa, 0x9c, 0xaa,  0x1c, 0xaa, 0x5c, 0xfa,  0xfc, 0xa8, 0x50, 0x00 },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xaa,  0x55, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff }
   */

   {  0x00, 0x00, 0x00, 0x00,  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f },
   {  0x00, 0x00, 0x00, 0x00,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff },
   {  0x00, 0x00, 0x00, 0x00,  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0 },
   {  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f },
   {  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0 },
   {  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f,  0x0f, 0x0f, 0x0f, 0x0f,  0x00, 0x00, 0x00, 0x00 },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0x00, 0x00, 0x00, 0x00 },
   {  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0,  0xf0, 0xf0, 0xf0, 0xf0,  0x00, 0x00, 0x00, 0x00 },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff },
   {  0xff, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0x00,  0x00, 0xff, 0xff, 0xff,  0xff, 0xff, 0xff, 0xff }
};

void cls_text_brd::draw_edge ()
{
   int i, j;

   forinc (i , 1 , get_width() - 2)
   {
      cpy_img8 (i , 0 , def_edge_up);
      cpy_img8 (i , get_height() - 1 , def_edge_down);
   }

   forinc (i , 1 , get_height() - 2)
   {
      cpy_img8 (0, i, def_edge_left);
      cpy_img8 (get_width() - 1, i, def_edge_right);
   }

   forinc (j,1,get_height()-2)
      forinc (i,1,get_width()-2)
      {
         cpy_img8(i,j,def_edge_in);
      }

   cpy_img8 (0,             0,              def_edge_up_left   );
   cpy_img8 (get_width()-1, 0,              def_edge_up_right  );
   cpy_img8 (0,             get_height()-1, def_edge_down_left );
   cpy_img8 (get_width()-1, get_height()-1, def_edge_down_right);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_text_brd::pcs_attr8 (void* fnt_pnt)
{
   if (attr & def_mask_inverse)
   {
      byte* tar_byte_pnt = stt_ary_byte_fnt_buf;

      #undef mac_step
      #define mac_step(n) *tar_byte_pnt++ = *(mac_change_type_of(fnt_pnt,byte*)++) ^ 0xFF
      mac_steps();
   }
   else
   {
      memcpy (stt_ary_byte_fnt_buf, fnt_pnt, 16);
   }

   if (attr & def_mask_underline) stt_ary_byte_fnt_buf[15] = 0xFF;
}

void cls_text_brd::pcs_attr16 (void* fnt_pnt)
{
   if (attr & def_mask_inverse)
   {
      byte* tar_byte_pnt = stt_ary_byte_fnt_buf;

      #undef mac_step
      #define mac_step(n) *mac_change_type_of(tar_byte_pnt,uint16*)++ = *mac_change_type_of(fnt_pnt,uint16*)++ ^ 0xFFFF
      mac_steps();
   }
   else
   {
      memcpy (stt_ary_byte_fnt_buf, fnt_pnt, 32);
   }

   if (attr & def_mask_underline) ((uint16*)stt_ary_byte_fnt_buf)[15] = 0xFFFF;
}
