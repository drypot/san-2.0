																																								/*
--------------------------------------------------------------------------------
   cnt/paper.hpp -- text line container
	copyright(C) kyuhyun park
   1987
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_paper_hpp
#error 'cnt/paper.hpp' duplicated.
#endif

#define def_cnt_paper_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_char_hpp
#include <pub/char.hpp>
#endif

#ifndef def_pub_tab_hpp
#include <pub/tab.hpp>
#endif

#ifndef def_cnt_darray_hpp
#include <cnt/darray.hpp>
#endif
																																								/*
--------------------------------------------------------------------------------
   cls_paper
--------------------------------------------------------------------------------                                        */

#define def_size_paper_frame int(4 * 1024 / sizeof(char16))

typedef tem_dynamic_array<char16,def_size_paper_frame> cls_paper_char_dary;
typedef tem_dynamic_array<int32,256> cls_paper_len_dary;

class cls_paper
{
	private:

      cls_paper_len_dary  len_dary;
      cls_paper_char_dary char_dary;

      int32 line_base_i32;
      int32 line_num_i32;

   public:

      cls_paper  ();
     ~cls_paper  ();

      void reset ();

      void read_file_johab  (char*);
      void read_file_wansung  (char*);

      void write_file_johab (char*);
      void write_file_wansung (char*);

      int32 get_line_cnt ()
      {
         return len_dary.get_cnt ();
      }

      int32 get_line_len ()
      {
         return len_dary.get_val (line_num_i32);
      }

      int32 get_line_len (int32 num)
      {
         return len_dary.get_val(num);
      }

      int32 get_line_begin ();

      int32 get_char_cnt ()
      {
         return char_dary.get_cnt();
      }

      void locate     (int32);
      void locate_rel (int32);

      void insert_line       (int32 = 1);
      void insert_line_below (int32 = 1);
      void remove_line       (int32 = 1);
      void remove_line_below (int32 = 1);

      void clear           ();
      void truncate        (int32);
      void remove          (int32,int32);
      void separate        (int32);
      void expand          (int32);
      void insert_no_fill  (int32,int32);
      void insert          (int32,int32);
      void fill            (int32,char16,int32);
      void join            (int32);

      void put_paper     (int32,cls_paper*,int32,int32);
      void put_char_dary (int32,cls_paper_char_dary*,int32);
      void put_ary       (int32,char16*,int32);
      void put_val       (int32,char16);

      void get_char_dary  (int32,cls_paper_char_dary*,int32);
      void get_ary        (int32,char16*,int32);

      char16 get_val (int32 inx)
      {
         return inx >= 0 && inx < get_line_len() ? char_dary.get_val(line_base_i32+inx) : ' ';
      }

   private:

      void reset_core ();

      void read_file_front_end ();
      void read_file_back_end  ();
      void read_file_flush_buf ();
      void read_file_line_end  ();
};
                                                                                                                        /*
--------------------------------------------------------------------------------
   paper_iter
--------------------------------------------------------------------------------                                        */

class cls_paper_iter;
class cls_paper_quick_iter;

class cls_paper_iter
{
   private:

      cls_paper* paper_pnt;
      int32 y;
      int32 x;
      int32 vx;

   public:

      cls_paper_iter(cls_paper* arg_paper) : paper_pnt(arg_paper), y(0), x(0), vx(0)
      {
      }

      cls_paper_iter(): paper_pnt(NULL), y(0), x(0), vx(0)
      {
      }

      void reset()
      {
         y = x = vx = 0;
      }

      void reset(cls_paper* arg_paper)
      {
         y = x = vx = 0;
         paper_pnt = arg_paper;
      }

      void reset_x()
      {
         x = vx = 0;
      }

      void set_y (int32 ny)
      {
         y = ny;
         x = vx = 0;
      }

      void set_y_rel (int32 dy)
      {
         set_y (y + dy);
      }

      void set_x (int32);

      void set_x (int32 nx, int32 nxv)
      {
         x = nx;
         vx = nxv;
      }

      void set_x_rel (int32 dx)
      {
         set_x (x + dx);
      }

      void set_vx (int32);
      void set_vx_inclusive (int32);

      int32 get_y()
      {
         return y;
      }

      int32 get_x()
      {
         return x;
      }

      int32 get_vx()
      {
         return vx;
      }

      void locate()
      {
         paper_pnt->locate(y);
      }

      void put_val (char16 ch)
      {
         paper_pnt->put_val(x,ch);
      }

      void put_val_rel (int32 dx, char16 ch)
      {
         paper_pnt->put_val(x + dx,ch);
      }

      char16 get_val ()
      {
         return paper_pnt->get_val(x);
      }

      char16 get_val_rel (int32 dx)
      {
         return paper_pnt->get_val(x + dx);
      }

      int get_width ()
      {
         return get_width (get_val());
      }

      int get_width (char16 ch)
      {
         if (is_single (ch)) return ch == '\t' ? (vx / tab_width_int + 1) * tab_width_int - vx : 1 ;
         else return 2 ;
      }

   friend class cls_paper_quick_iter;
};
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_paper_quick_iter
--------------------------------------------------------------------------------                                        */

class cls_paper_quick_iter
{
   private:

      cls_paper* paper_pnt;
      int32 y;
      int32 x;

   public:

      cls_paper_quick_iter (cls_paper_iter* iter) : paper_pnt(iter->paper_pnt), y(iter->y), x(iter->x)
      {
      }

      cls_paper_quick_iter (cls_paper* arg_paper) : paper_pnt(arg_paper), y(0), x(0)
      {
      }

      cls_paper_quick_iter () : paper_pnt(NULL), y(0), x(0)
      {
      }

      void reset ()
      {
         y = x = 0;
      }

      void reset (cls_paper* arg_paper)
      {
         y = x = 0;
         paper_pnt = arg_paper;
      }

      void reset_x ()
      {
         x = 0;
      }

      void set_y (int32 ny)
      {
         y = ny;
         x = 0;
      }

      void set_y_rel (int32 dy)
      {
         set_y (y + dy);
      }

      void set_x (int32 nx)
      {
         x = nx;
      }

      void set_x_rel (int32 dx)
      {
         set_x (x + dx);
      }

      int32 get_y ()
      {
         return y;
      }

      int32 get_x ()
      {
         return x;
      }

      void locate ()
      {
         paper_pnt->locate (y);
      }

      void put_val (char16 ch)
      {
         paper_pnt->put_val (x,ch);
      }

      char16 get_val ()
      {
         return paper_pnt->get_val (x);
      }

      char16 get_val_rel (int32 dx)
      {
         return paper_pnt->get_val(x + dx);
      }
};
