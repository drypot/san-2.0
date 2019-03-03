																																								/*
--------------------------------------------------------------------------------
   pub/point.hpp
   copyright(c) kyuhyun park
   1993.10.04
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_point_hpp
#error 'pub/point.hpp' duplicated.
#endif

#define def_pub_point_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

struct cls_point
{
   int x;
   int y;

   cls_point(int arg_x = 0, int arg_y = 0) : x (arg_x), y (arg_y)
   {
   }

   void set(int arg_x, int arg_y)
   {
      x = arg_x;
      y = arg_y;
   }

   void reset()
   {
      x = y = 0;
   }
};

struct cls_rect
{
   int x1;
   int y1;
   int x2;
   int y2;

   cls_rect()
   {
      x1 = y1 = x2 = y2 = 0;
   }

   cls_rect(int arg_x1, int arg_y1, int arg_x2, int arg_y2)
   {
      x1 = arg_x1;
      y1 = arg_y1;
      x2 = arg_x2;
      y2 = arg_y2;
   }

   int get_width()
   {
      return x2 - x1 + 1;
   }

   int get_height()
   {
      return y2 - y1 + 1;
   }

   void set(int arg_x1, int arg_y1, int arg_x2, int arg_y2)
   {
      x1 = arg_x1;
      y1 = arg_y1;
      x2 = arg_x2;
      y2 = arg_y2;
   }

   void reset()
   {
      x1 = y1 = x2 = y2 = 0;
   }
};

class cls_boxed_point
{
   private:

      int width, height, cnt;
      int x, y;

   private:

      void adjust ()
      {
         if (get_index() >= cnt) set_last();
      }

   public:

      cls_boxed_point (int arg_width, int arg_cnt)
      {
         reset (arg_width, arg_cnt);
      }

      void reset (int arg_width, int arg_cnt)
      {
         width = arg_width;
         cnt = arg_cnt;
         height = get_seg_cnt(arg_cnt, arg_width);
         x = y = 0;
      }

      void set_x (int nx)
      {
         set_index (y*width + nx);
      }

      void set_x_rel (int dx)
      {
         set_x (x + dx);
      }

      void set_x_first()
      {
         x = 0;
      }

      void set_x_last()
      {
         x = width - 1;
         adjust ();
      }

      void set_y (int ny)
      {
         y = get_offset (ny, height);
         adjust ();
      }

      void set_y_rel (int dy)
      {
         set_y (y + dy);
      }

      void set_y_first()
      {
         y = 0;
      }

      void set_y_last()
      {
         y = height - 1;
         adjust ();
      }

      void set_index (int ni)
      {
         ni = get_offset (ni, cnt);
         x = ni % width;
         y = ni / width;
         adjust ();
      }

      void set_index_rel (int di)
      {
         set_index (get_index() + di);
      }

      void set_first ()
      {
         set_index (0);
      }

      void set_last ()
      {
         set_index (cnt - 1);
      }

      int get_x ()
      {
         return x;
      }

      int get_y ()
      {
         return y;
      }

      int get_index ()
      {
         return y*width + x;
      }

      cls_point get_point()
      {
         return cls_point(x,y);
      }

      bool is_x_first()
      {
         return x == 0;
      }

      bool is_x_last()
      {
         return x == width -1;
      }

      bool is_y_first()
      {
         return y == 0;
      }

      bool is_y_last()
      {
         return y == height - 1;
      }

      bool is_first()
      {
         return is_x_first() && is_y_first();
      }

      bool is_last()
      {
         return is_x_last() && is_y_last();
      }
};

