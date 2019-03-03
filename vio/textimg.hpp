                                                                                                                        /*
--------------------------------------------------------------------------------
   vio/textimg.hpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#ifdef def_vio_textimg_hpp
#error 'vio/textimg.hpp' duplicated.
#endif

#define def_vio_textimg_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

enum
{
   def_clr_black,
   def_clr_dark_blue,
   def_clr_dark_green,
   def_clr_dark_cyan,
   def_clr_dark_red,
   def_clr_dark_pink,
   def_clr_brown,
   def_clr_pale_gray,

   def_clr_dark_gray,
   def_clr_blue,
   def_clr_green,
   def_clr_cyan,
   def_clr_red,
   def_clr_pink,
   def_clr_yellow,
   def_clr_white
};

class cls_text_img
{
   private:

      int   width;
      int   height;
      byte  color_byte;
      byte* img_byte_pnt;
      byte* color_byte_pnt;
      bool* invalid_flg_pnt;

   public:

      cls_text_img      (int, int);
     ~cls_text_img      ();

      void  validate ();

      void  invalidate   ();
      void  invalidate   (int);
      void  invalidate   (int y, int h);

      bool  is_dirty     (int);

      void  fill         (byte);
      void  erase        ();

      void  set_fg       (byte);
      void  set_bg       (byte);
      byte  get_fg       ();
      byte  get_bg       ();

      void  set_clr      (int, int);
      void  set_clr      (int, int, byte);
      byte  get_clr      (int, int);
      byte  get_fg       (int, int);
      byte  get_bg       (int, int);

      void  cpy_img8     (int, int, void*);
      void  cpy_img16    (int, int, void*);
      void  cpy_img16l   (int, int, void*);
      void  cpy_img16r   (int, int, void*);

      void  or8          (int, int, void*);
      void  or16         (int, int, void*);
      void  or16L        (int, int, void*);
      void  or16R        (int, int, void*);

      void  xor8         (int, int, void*);
      void  xor16        (int, int, void*);
      void  xor16L       (int, int, void*);
      void  xor16R       (int, int, void*);

      void  erase8       (int, int);
      void  erase16      (int, int);

      void  inverse_rect (int x, int y, int w, int h);
      void  erase_rect   (int x, int y, int w, int h);
      void  save_rect    (int x, int y, int w, int h, void*);
      void  restore_rect (int x, int y, int w, int h, void*);

      void  scroll_up    ();
      void  scroll_down  ();

      void  scroll_up    (int x, int y, int w, int h, int = 1);
      void  scroll_down  (int x, int y, int w, int h, int = 1);
      void  scroll_left  (int x, int y, int w, int h, int = 1);
      void  scroll_right (int x, int y, int w, int h, int = 1);

      int   get_width    ();
      int   get_height   ();
      void* get_img_base ();

#if defined def_pm
      void draw (HPS hps, int X = 0, int Y = 0);
#endif
};

inline void cls_text_img::invalidate(int y)
{
   invalid_flg_pnt [y] = def_yes;
}

inline bool cls_text_img::is_dirty(int y)
{
   return invalid_flg_pnt [y];
}

inline void cls_text_img::set_fg (byte arg_clr)
{
   masked_assign(&color_byte, arg_clr, 0x0F);
}

inline void cls_text_img::set_bg (byte arg_clr)
{
   masked_assign(&color_byte, arg_clr << 4, 0xF0);
}

inline byte cls_text_img::get_fg()
{
   return color_byte & 0x0F;
}

inline byte cls_text_img::get_bg()
{
   return color_byte >> 4;
}

inline void cls_text_img::set_clr (int x, int y)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   color_byte_pnt[width*y+x] = color_byte;
}

inline void cls_text_img::set_clr (int x, int y, byte arg_clr)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   color_byte_pnt[width*y+x] = arg_clr;
}

inline byte cls_text_img::get_clr (int x, int y)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   return color_byte_pnt[width*y+x];
}

inline byte cls_text_img::get_fg (int x, int y)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   return color_byte_pnt[width*y+x] & 0x0F;
}

inline byte cls_text_img::get_bg (int x, int y)
{
   mac_assert( is_inside_less(x, 0, width) );
   mac_assert( is_inside_less(y, 0, height) );

   return color_byte_pnt[width*y+x] >> 4;
}

inline int cls_text_img::get_width ()
{
   return width;
}

inline int cls_text_img::get_height ()
{
   return height;
}

inline void* cls_text_img::get_img_base()
{
   return img_byte_pnt;
}

