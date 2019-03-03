                                                                                                                        /*
--------------------------------------------------------------------------------
   vio/textimg.cpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <vio/textimg.hpp>

#define mac_steps() mac_step(0x00); mac_step(0x01); mac_step(0x02); mac_step(0x03); mac_step(0x04); mac_step(0x05); mac_step(0x06); mac_step(0x07); mac_step(0x08); mac_step(0x09); mac_step(0x0A); mac_step(0x0B); mac_step(0x0C); mac_step(0x0D); mac_step(0x0E); mac_step(0x0F)

static byte* stt_draw_buf_byte_pnt;
static int stt_draw_buf_width_int;

cls_text_img::cls_text_img(int cx, int cy) :
   width  (cx),
   height (cy),
   color_byte (0x07)
{
   img_byte_pnt = (byte*) mem_alloc(cx * cy * 16);
   color_byte_pnt = (byte*) mem_alloc(cx * cy);
   invalid_flg_pnt = (bool*) mem_alloc(cy * sizeof(bool));
   erase();

   if (stt_draw_buf_width_int < cx)
   {
      if (stt_draw_buf_byte_pnt) mem_free(stt_draw_buf_byte_pnt);
      stt_draw_buf_byte_pnt = (byte*) mem_alloc(cx*16);
      stt_draw_buf_width_int = cx;
   }
}

cls_text_img::~cls_text_img()
{
   mem_free (img_byte_pnt);
   mem_free (color_byte_pnt);
   mem_free (invalid_flg_pnt);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_text_img::validate ()
{
   memset (invalid_flg_pnt, 0, sizeof(bool)*height);
}

void cls_text_img::invalidate ()
{
   memset (invalid_flg_pnt, 0xff, sizeof(bool)*height);
}

void cls_text_img::invalidate (int y, int h)
{
   memset (invalid_flg_pnt+y, 0xff, sizeof(bool)*h);
}

void cls_text_img::fill (byte patt)
{
   memset (img_byte_pnt, patt, width*height*16);
   memset (color_byte_pnt, color_byte, width*height);
   invalidate();
}

void cls_text_img::erase ()
{
   fill(0);
}

void cls_text_img::cpy_img8    (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) = *((byte*)fnt_pnt + n);
   mac_steps();

   set_clr(x,y);
   invalidate(y);
}

void cls_text_img::cpy_img16   (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width - 1) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(uint16*)(tar_byte_pnt += width) = *((uint16*)fnt_pnt + n);
   mac_steps();

   set_clr(x,y);
   set_clr(x+1,y);
   invalidate(y);
}

void cls_text_img::cpy_img16l  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) = *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   set_clr(x,y);
   invalidate(y);
}

void cls_text_img::cpy_img16r  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   mac_change_type_of(fnt_pnt,byte*)++;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) = *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   set_clr(x,y);
   invalidate(y);
}

void cls_text_img::or8 (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) |= *((byte*)fnt_pnt + n);
   mac_steps();

   invalidate(y);
}

void cls_text_img::or16   (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width - 1) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(uint16*)(tar_byte_pnt += width) |= *((uint16*)fnt_pnt + n);
   mac_steps();

   invalidate(y);
}

void cls_text_img::or16L  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) |= *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   invalidate(y);
}

void cls_text_img::or16R  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less (x, -1, width - 1) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x + 1 - width;

   mac_change_type_of(fnt_pnt,byte*)++;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) |= *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   invalidate(y);
}

void cls_text_img::xor8 (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) ^= *((byte*)fnt_pnt + n);
   mac_steps();

   invalidate(y);
}

void cls_text_img::xor16   (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less(x, 0, width - 1) );
   mac_assert( is_inside_less(y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(uint16*)(tar_byte_pnt += width) ^= *((uint16*)fnt_pnt + n);
   mac_steps();

   invalidate(y);
}

void cls_text_img::xor16L  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less (x, 0, width) );
   mac_assert( is_inside_less (y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) ^= *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   invalidate(y);
}

void cls_text_img::xor16R  (int x, int y, void* fnt_pnt)
{
   mac_assert( is_inside_less (x, -1, width - 1) );
   mac_assert( is_inside_less (y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x + 1 - width;

   mac_change_type_of(fnt_pnt,byte*)++;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) ^= *((byte*)fnt_pnt + (n<<1));
   mac_steps();

   invalidate(y);
}

void cls_text_img::erase8 (int x, int y)
{
   mac_assert( is_inside_less (x, 0, width) );
   mac_assert( is_inside_less (y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(tar_byte_pnt += width) = 0;
   mac_steps();

   set_clr(x,y);
   invalidate(y);
}

void cls_text_img::erase16  (int x, int y)
{
   mac_assert( is_inside_less (x, 0, width - 1) );
   mac_assert( is_inside_less (y, 0, height) );

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x - width;

   #undef mac_step
   #define mac_step(n) *(uint16*)(tar_byte_pnt += width) = 0;
   mac_steps();

   set_clr(x,y);
   set_clr(x+1,y);
   invalidate(y);
}

void cls_text_img::inverse_rect (int x, int y, int w, int h)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w >= 0);
   mac_assert (h >= 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x;
   register int i;
   register int cnt = h * 16;

   while (cnt--)
   {
      forcnt (i, w) *(tar_byte_pnt+i) ^= 0xFF;
      tar_byte_pnt += width;
   }

   invalidate(y,h);
}

void cls_text_img::erase_rect   (int x, int y, int w, int h)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w >= 0);
   mac_assert (h >= 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x;
   register int cnt = h * 16;

   while (cnt--)
   {
      memset(tar_byte_pnt, 0, w);
      tar_byte_pnt += width;
   }

   register byte*  tar_clr_byte_pnt = color_byte_pnt + width*y + x;
   cnt = h;
   while (cnt--)
   {
      memset(tar_clr_byte_pnt, color_byte, w);
      tar_clr_byte_pnt += width;
   }

   invalidate(y,h);
}

void cls_text_img::save_rect (int x, int y, int w, int h, void* tar_pnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (x + w <=  width);
   mac_assert (y + h <=  height);

   register byte* src_byte_pnt = img_byte_pnt + width*16*y + x;
   register int cnt = h * 16;

   while (cnt--)
   {
      memcpy(tar_pnt, src_byte_pnt, w);
      mac_change_type_of(tar_pnt,byte*) += w;
      src_byte_pnt += width;
   }
}

void cls_text_img::restore_rect (int x, int y, int w, int h, void* src_byte_pnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (x + w <=  width);
   mac_assert (y + h <=  height);

   register byte* tar_byte_pnt = img_byte_pnt + width*16*y + x;
   register int cnt = h * 16;

   while (cnt--)
   {
      memcpy(tar_byte_pnt, src_byte_pnt, w);
      mac_change_type_of(src_byte_pnt,byte*) += w;
      tar_byte_pnt += width;
   }
   invalidate(y,h);
}

void cls_text_img::scroll_up()
{
   memcpy (img_byte_pnt, img_byte_pnt+width*16, (height-1)*width*16);
   memset (img_byte_pnt+(height-1)*width*16, 0, width*16);

   memcpy (color_byte_pnt, color_byte_pnt+width, (height-1)*width);
   memset (color_byte_pnt+(height-1)*width, color_byte, width);

   invalidate ();
}

void cls_text_img::scroll_down()
{
   memmove (img_byte_pnt+width*16, img_byte_pnt, (height-1)*width*16);
   memset  (img_byte_pnt, 0, width*16);

   memmove (color_byte_pnt+width, color_byte_pnt, (height-1)*width);
   memset  (color_byte_pnt, color_byte, width);

   invalidate ();
}

void cls_text_img::scroll_up (int x, int y, int w, int h, int cnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w > 0);
   mac_assert (h > 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   mac_assert (w == width);
   mac_assert (x == 0);

   if (cnt > h) cnt = h;

   memcpy (img_byte_pnt + y*width*16, img_byte_pnt+(y+cnt)*width*16, (h-cnt)*width*16);
   memset (img_byte_pnt+(y+h-cnt)*width*16, 0, width*16*cnt);

   memcpy (color_byte_pnt + y*width, color_byte_pnt+(y+cnt)*width, (h-cnt)*width);
   memset (color_byte_pnt+(y+h-cnt)*width, color_byte, width*cnt);

   invalidate(y,h);
}

void cls_text_img::scroll_down (int x, int y, int w, int h, int cnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w > 0);
   mac_assert (h > 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   mac_assert (w == width);
   mac_assert (x == 0);

   if (cnt > h) cnt = h;

   memmove (img_byte_pnt + (y+cnt)*width*16, img_byte_pnt+y*width*16, (h-cnt)*width*16);
   memset (img_byte_pnt + y*width*16, 0, width*16*cnt);

   memmove (color_byte_pnt + (y+cnt)*width, color_byte_pnt+y*width, (h-cnt)*width);
   memset (color_byte_pnt + y*width, color_byte, width*cnt);

   invalidate (y,h);
}

void cls_text_img::scroll_left (int x, int y, int w, int h, int cnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w > 0);
   mac_assert (h > 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   byte* start_byte_pnt;
   byte* end_byte_pnt;

   if (cnt > w) cnt = w;

   start_byte_pnt = img_byte_pnt + y*width*16 + x;
   end_byte_pnt = start_byte_pnt + h*width*16;
   while (start_byte_pnt < end_byte_pnt)
   {
      memcpy (start_byte_pnt, start_byte_pnt + cnt, w - cnt);
      memset (start_byte_pnt + w - cnt, 0, cnt);
      start_byte_pnt += width;
   }

   start_byte_pnt = color_byte_pnt + y*width + x;
   end_byte_pnt = start_byte_pnt + h*width;
   while (start_byte_pnt < end_byte_pnt)
   {
      memcpy (start_byte_pnt, start_byte_pnt+cnt, w - cnt);
      memset (start_byte_pnt + w - cnt, color_byte, cnt);
      start_byte_pnt += width;
   }
   invalidate(y,h);
}

void cls_text_img::scroll_right (int x, int y, int w, int h, int cnt)
{
   mac_assert (x >= 0);
   mac_assert (y >= 0);
   mac_assert (w > 0);
   mac_assert (h > 0);
   mac_assert (x+w <= width);
   mac_assert (y+h <= height);

   byte* start_byte_pnt;
   byte* end_byte_pnt;

   if (cnt > w) cnt = w;

   start_byte_pnt = img_byte_pnt + y*width*16 + x;
   end_byte_pnt = start_byte_pnt + h*width*16;
   while (start_byte_pnt < end_byte_pnt)
   {
      memmove (start_byte_pnt+cnt, start_byte_pnt, w - cnt);
      memset  (start_byte_pnt, 0, cnt);
      start_byte_pnt += width;
   }

   start_byte_pnt = color_byte_pnt + y*width + x;
   end_byte_pnt = start_byte_pnt + h*width;
   while (start_byte_pnt < end_byte_pnt)
   {
      memmove (start_byte_pnt+cnt, start_byte_pnt, w - cnt);
      memset  (start_byte_pnt, color_byte, cnt);
      start_byte_pnt += width;
   }
   invalidate(y,h);
}

#if defined def_pm

static LONG clr_long_ary[] =
{
   CLR_BLACK,
   CLR_DARKBLUE,
   CLR_DARKGREEN,
   CLR_DARKCYAN,
   CLR_DARKRED,
   CLR_DARKPINK,
   CLR_BROWN,
   CLR_PALEGRAY,
   CLR_DARKGRAY,
   CLR_BLUE,
   CLR_GREEN,
   CLR_CYAN,
   CLR_RED,
   CLR_PINK,
   CLR_YELLOW,
   CLR_WHITE
};

void cls_text_img::draw (HPS hps, int arg_x, int arg_y)
{
   arg_y += height * 16 - 1;

   SIZEL sizel_whole = { width*8, 16 };
   SIZEL sizel_part = { 0, 16 };
   POINTL pointl = {0, arg_y};
   int y;
   int begin_col, end_col;
   byte cur_clr;

   GpiSetBackMix (hps, BM_OVERPAINT);

   for (y = 0 ; y < height ; y++)
   {
      if (is_dirty(y))
      {
         begin_col = 0;
         pointl.x = arg_x;
         while (begin_col < width)
         {
            GpiSetColor (hps, clr_long_ary[get_fg(begin_col,y)]);
            GpiSetBackColor (hps, clr_long_ary[get_bg(begin_col,y)]);
            cur_clr = get_clr (begin_col,y);
            end_col = begin_col+1;
            while (end_col < width && get_clr(end_col,y) == cur_clr) end_col++;
            if (begin_col == 0 && end_col == width)
            {
               GpiMove (hps, &pointl);
               GpiImage (hps, 0, &sizel_whole, width*16, (PBYTE)(img_byte_pnt + y*width*16));
            }
            else
            {
               byte* pnt_dst = stt_draw_buf_byte_pnt;
               byte* pnt_src = img_byte_pnt + y*width*16 + begin_col;
               int w = end_col - begin_col;
               int cnt = 16;

               while (cnt--)
               {
                  memcpy (pnt_dst, pnt_src, w);
                  pnt_dst += w;
                  pnt_src += width;
               }
               mac_assert(mem_check(stt_draw_buf_byte_pnt));

               sizel_part.cx = w * 8;
               GpiMove (hps, &pointl);
               GpiImage (hps, 0, &sizel_part, w*16, (PBYTE)stt_draw_buf_byte_pnt);
               pointl.x += w * 8;
            }
            begin_col = end_col;
         }
      }
      pointl.y -= 16;
   }

   validate();
}

#endif
