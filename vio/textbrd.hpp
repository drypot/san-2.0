                                                                                                                        /*
--------------------------------------------------------------------------------
   vio/textbrd.hpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#ifdef def_vio_textbrd_hpp
#error 'vio/textbrd.hpp' duplicated.
#endif

#define def_vio_textbrd_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_vio_textimg_hpp
#include <vio/textimg.hpp>
#endif

class cls_text_brd : public cls_text_img
{
   private:
      enum
      {
         def_mask_inverse = 0x01,
         def_mask_underline = 0x02
      };

      int    x, y;
      uint   attr;

      bool   show_cursor_flg;
      bool   outline_cursor_flg;
      bool   wide_cursor_flg;
      char16 cursor_code_c16;
      byte   cursor_back_img_byte_ary[32];
      byte   cursor_back_clr1_byte;
      byte   cursor_back_clr2_byte;

   public:

      cls_text_brd             (int,int);
     ~cls_text_brd             ();

      void  set_xy             (int, int);
      void  set_x              (int);
      void  set_y              (int);
      void  set_x_rel          (int);
      void  set_y_rel          (int);

      int   get_x              ();
      int   get_y              ();

      void  set_attr           (uint);
      uint  get_attr           ();

      void  set_normal         ();
      void  set_inverse        (bool);
      void  set_underline      (bool);

      void  write_img8         (void*);
      void  write_img16        (void*);

      void  write              (char16);
      void  write              (char*);

      void  write_space        (int);

      void  insert_char        (int = 1);
      void  remove_char        (int = 1);

      void  insert_line        (int = 1);
      void  remove_line        (int = 1);

      void  erase              ();
      void  erase_line         ();
      void  erase_to_bol       ();
      void  erase_to_eol       ();
      void  erase_to_bos       ();
      void  erase_to_eos       ();

      void  draw_edge          ();

      void  show_cursor        (bool);
      void  set_outline_cursor (bool);
      void  set_wide_cursor    (bool);
      void  set_img_cursor     (char16);
      void  calc_cursor_width  (char16);
      void  draw_cursor        ();
      void  erase_cursor       ();

   #if defined def_pm
      void draw (HPS hps, int x = 0, int y = 0);
   #endif

   private:

      void  pcs_attr8  (void*);
      void  pcs_attr16 (void*);
};

inline void cls_text_brd::set_xy (int arg_x, int arg_y)
{
   x = arg_x;
   y = arg_y;
}

inline void cls_text_brd::set_x (int arg_x)
{
   x = arg_x;
}

inline void cls_text_brd::set_y (int arg_y)
{
   y = arg_y;
}

inline void cls_text_brd::set_x_rel (int dx)
{
   x += dx;
}

inline void cls_text_brd::set_y_rel (int dy)
{
   y += dy;
}

inline int cls_text_brd::get_x()
{
   return x;
}

inline int cls_text_brd::get_y()
{
   return y;
}

inline void cls_text_brd::set_attr (uint arg_attr)
{
   attr = arg_attr;
}

inline uint cls_text_brd::get_attr ()
{
   return attr;
}

#if defined def_pm

inline void cls_text_brd::draw (HPS hps, int x, int y)
{
   draw_cursor();
   cls_text_img::draw (hps, x, y);
   erase_cursor();
}

#endif
