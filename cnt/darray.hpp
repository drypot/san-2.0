                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/darray.hpp
   copyright(C) kyuhyun park
   1994.12.22
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_darray_hpp
#error 'cnt/darray.hpp' duplicated.
#endif

#define def_cnt_darray_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif

template<class cls_t, int32 frame_size_i32>
class tem_dynamic_array
{
   public:  // because of borland's bug

      struct cls_frame
		{
         cls_frame* prev_frame_pnt;
         cls_frame* next_frame_pnt;
         int32      cnt_i32;
         cls_t      data_t_ary [frame_size_i32];

         int32 get_free_cnt() { return frame_size_i32 - cnt_i32; }
		};

      struct cls_null_frame
		{
         cls_frame* prev_frame_pnt;
         cls_frame* next_frame_pnt;
         int32      cnt_i32;
		};

      cls_null_frame head_frame;
      cls_null_frame tail_frame;

      cls_frame* cur_frame_pnt;
      int32 base_i32;
      int32 offset_i32;

      int32 cnt_i32;

	public:

      tem_dynamic_array       ();
     ~tem_dynamic_array       ();

      void reset      ();

      void locate     (int32 index_i32);
      void locate_rel (int32 adder_i32);
      void locate_end (int32 adder_i32= 0);

      void insert     (int32 = 1);
      void remove     (int32 = 1);

      void put_dary   (tem_dynamic_array<cls_t,frame_size_i32>*, int32);

      void get_ary    (cls_t*, int32);
      void put_ary    (cls_t*, int32);

      void put_pnt    (cls_t*);
      void put_pnt    (int32, cls_t*);

      void put_val    (cls_t);
      void put_val    (int32, cls_t);

      cls_t* get_pnt  ();
      cls_t* get_pnt  (int32);

      cls_t get_val   ();
      cls_t get_val   (int32);

      int32 get_cnt   ();

   private:

      void ctor          ();
      void dtor          ();

      void locate_core   (int32);

      int32 get_free_cnt ();
      int32 get_rest_cnt ();

      void link_frame    (int32);
      void prev_frame    ();
      void next_frame    ();
      static void unlink_frame (cls_frame*);
};

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::locate(int32 index_i32)
{
   if (base_i32 + offset_i32 != index_i32) locate_core(index_i32);
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::locate_rel(int32 adder_i32)
{
   locate(base_i32 + offset_i32 + adder_i32);
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::locate_end(int32 adder_i32)
{
   locate(cnt_i32 + adder_i32);
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::put_pnt(cls_t* pnt)
{
   cur_frame_pnt->data_t_ary[offset_i32] = *pnt;
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::put_pnt(int32 inx, cls_t* pnt)
{
   locate(inx);
   cur_frame_pnt->data_t_ary[offset_i32] = *pnt;
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::put_val(cls_t t)
{
   cur_frame_pnt->data_t_ary[offset_i32] = t;
}

template<class cls_t, int32 frame_size_i32> inline void tem_dynamic_array<cls_t,frame_size_i32>::put_val(int32 inx, cls_t t)
{
   locate(inx);
   cur_frame_pnt->data_t_ary[offset_i32] = t;
}

template<class cls_t, int32 frame_size_i32> inline cls_t* tem_dynamic_array<cls_t,frame_size_i32>::get_pnt()
{
   return cur_frame_pnt->data_t_ary + offset_i32;
}

template<class cls_t, int32 frame_size_i32> inline cls_t* tem_dynamic_array<cls_t,frame_size_i32>::get_pnt(int32 inx)
{
   locate(inx);
   return cur_frame_pnt->data_t_ary + offset_i32;
}

template<class cls_t, int32 frame_size_i32> inline cls_t tem_dynamic_array<cls_t,frame_size_i32>::get_val()
{
   return cur_frame_pnt->data_t_ary[offset_i32];
}

template<class cls_t, int32 frame_size_i32> inline cls_t tem_dynamic_array<cls_t,frame_size_i32>::get_val(int32 inx)
{
   locate(inx);
   return cur_frame_pnt->data_t_ary[offset_i32];
}

template<class cls_t, int32 frame_size_i32> inline int32 tem_dynamic_array<cls_t,frame_size_i32>::get_cnt()
{
   return cnt_i32;
}

template<class cls_t, int32 frame_size_i32> inline int32 tem_dynamic_array<cls_t,frame_size_i32>::get_free_cnt()
{
   return cur_frame_pnt->get_free_cnt();
}

template<class cls_t, int32 frame_size_i32> inline int32 tem_dynamic_array<cls_t,frame_size_i32>::get_rest_cnt()
{
   return cur_frame_pnt->cnt_i32 - offset_i32;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::ctor()
{
   cur_frame_pnt                 = (cls_frame*) mem_alloc(sizeof(cls_frame));
   cur_frame_pnt->cnt_i32        = 1;
   cur_frame_pnt->prev_frame_pnt = (cls_frame*) &head_frame;
   cur_frame_pnt->next_frame_pnt = (cls_frame*) &tail_frame;
   head_frame.prev_frame_pnt     = tail_frame.next_frame_pnt = NULL;
   head_frame.next_frame_pnt     = tail_frame.prev_frame_pnt = cur_frame_pnt;
   head_frame.cnt_i32            = tail_frame.cnt_i32 = frame_size_i32;
   base_i32   = 0;
   offset_i32 = 0;
   cnt_i32    = 0;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::dtor()
{
   cls_frame* next_frame_pnt = head_frame.next_frame_pnt;
   cls_frame* next_next_frame_pnt;

   while (next_frame_pnt != (cls_frame*) &tail_frame)
   {
      next_next_frame_pnt = next_frame_pnt->next_frame_pnt;
      mem_free (next_frame_pnt);
      next_frame_pnt = next_next_frame_pnt;
   }
}

template<class cls_t, int32 frame_size_i32> tem_dynamic_array<cls_t,frame_size_i32>::tem_dynamic_array()
{
   ctor();
}

template<class cls_t, int32 frame_size_i32> tem_dynamic_array<cls_t,frame_size_i32>::~tem_dynamic_array()
{
   dtor();
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::reset()
{
   dtor();
   ctor();
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::locate_core(int32 arg_inx)
{
   mac_assert(arg_inx >= 0 && arg_inx <= cnt_i32);

   bool upward_flg;

   if (is_inside_less(arg_inx - base_i32, 0, cur_frame_pnt->cnt_i32))
   {
      offset_i32 = arg_inx - base_i32;
      return;
   }

   if (arg_inx < base_i32)
   {
      if (arg_inx < base_i32 / 2)
      {
         cur_frame_pnt = head_frame.next_frame_pnt;
         base_i32 = 0;
         upward_flg = def_yes;
      }
      else upward_flg = def_no;
   }
   else
   {
      if (arg_inx < base_i32 + (cnt_i32 - base_i32) / 2) upward_flg = def_yes;
      else
      {
         cur_frame_pnt = tail_frame.prev_frame_pnt;
         base_i32 = cnt_i32+1 - cur_frame_pnt->cnt_i32;
         upward_flg = def_no;
      }
   }

   if (upward_flg)
   {
      int32 sz;
      while (sz = base_i32 + cur_frame_pnt->cnt_i32, sz <= arg_inx && cur_frame_pnt->cnt_i32)
      {
         base_i32 = sz;
         cur_frame_pnt = cur_frame_pnt->next_frame_pnt;
      }
   }
   else
   {
      while (base_i32 > arg_inx)
      {
         cur_frame_pnt = cur_frame_pnt->prev_frame_pnt;
         base_i32 -= cur_frame_pnt->cnt_i32;
      }
   }
   offset_i32 = arg_inx - base_i32;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::insert (int32 arg_ins_cnt)
{
   if (!arg_ins_cnt) return;

   cnt_i32 += arg_ins_cnt;

   if (offset_i32 == 0 &&  arg_ins_cnt <= cur_frame_pnt->prev_frame_pnt->get_free_cnt())
   {
      prev_frame();
      offset_i32 = cur_frame_pnt->cnt_i32;
      cur_frame_pnt->cnt_i32 += arg_ins_cnt;
      return;
   }

   if (offset_i32 && offset_i32 <= cur_frame_pnt->prev_frame_pnt->get_free_cnt())
   {
      cls_frame* prev_frame_pnt = cur_frame_pnt->prev_frame_pnt;
      cls_t* data_t_pnt = cur_frame_pnt->data_t_ary;
      int32 before_i32 = offset_i32;
      int32 after_i32 = get_rest_cnt();

      memcpy(prev_frame_pnt->data_t_ary + prev_frame_pnt->cnt_i32, data_t_pnt, sizeof(cls_t) * before_i32);
      cur_frame_pnt->cnt_i32 -= before_i32;
      prev_frame_pnt->cnt_i32 += before_i32;
      base_i32 += before_i32;
      offset_i32 = 0;

      if (arg_ins_cnt <= prev_frame_pnt->get_free_cnt())
      {
         memmove (data_t_pnt, data_t_pnt + before_i32, after_i32 * sizeof(cls_t));
         prev_frame ();
         offset_i32 = cur_frame_pnt->cnt_i32;
         cur_frame_pnt->cnt_i32 += arg_ins_cnt;
         return;
      }
      ef (arg_ins_cnt <= get_free_cnt())
      {
         memmove(data_t_pnt + arg_ins_cnt, data_t_pnt + before_i32, after_i32 * sizeof(cls_t));
         cur_frame_pnt->cnt_i32 += arg_ins_cnt;
         return;
      }
      else
      {
         memmove(data_t_pnt, data_t_pnt + before_i32, after_i32 * sizeof(cls_t));
      }
   }

   if (arg_ins_cnt <= get_free_cnt())
   {
      cls_t* data_t_pnt = cur_frame_pnt->data_t_ary;
      memmove (data_t_pnt + offset_i32 + arg_ins_cnt, data_t_pnt + offset_i32, get_rest_cnt() * sizeof(cls_t));
      cur_frame_pnt->cnt_i32 += arg_ins_cnt;
   }
   else
   {
      int32 r = arg_ins_cnt % frame_size_i32;

      if (get_rest_cnt() + r <= frame_size_i32)
      {
         arg_ins_cnt -= r;
      }
      else
      {
         r = 0;
      }
      link_frame(get_rest_cnt() + r);
      memcpy(cur_frame_pnt->next_frame_pnt->data_t_ary + r, cur_frame_pnt->data_t_ary + offset_i32, get_rest_cnt() * sizeof(cls_t));
      cur_frame_pnt->cnt_i32 -= get_rest_cnt();
      while (arg_ins_cnt >= frame_size_i32)
      {
         link_frame(frame_size_i32);
         arg_ins_cnt -= frame_size_i32;
      }
      if (arg_ins_cnt == 0)
      {
         next_frame();
      }
      ef (arg_ins_cnt > get_free_cnt())
      {
         if (arg_ins_cnt > cur_frame_pnt->next_frame_pnt->get_free_cnt())
         {
            link_frame(arg_ins_cnt);
            next_frame();
         }
         else
         {
            next_frame();
            cls_t* data_t_pnt = cur_frame_pnt->data_t_ary;
            memmove(data_t_pnt + offset_i32 + arg_ins_cnt, data_t_pnt + offset_i32, get_rest_cnt() * sizeof(cls_t));
            cur_frame_pnt->cnt_i32 += arg_ins_cnt;
         }
      }
      el
      {
         cur_frame_pnt->cnt_i32 += arg_ins_cnt;
      }
   }
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::remove(int32 arg_del_cnt)
{
   mac_assert(base_i32 + offset_i32 + arg_del_cnt <= cnt_i32);

   cnt_i32 -= arg_del_cnt;
   if (get_rest_cnt() <= arg_del_cnt)
   {
      int32 rest_cnt = get_rest_cnt();
      cur_frame_pnt->cnt_i32 -= rest_cnt;
      arg_del_cnt -= rest_cnt;
      while (cur_frame_pnt->next_frame_pnt->cnt_i32 <= arg_del_cnt)
      {
         arg_del_cnt -= cur_frame_pnt->next_frame_pnt->cnt_i32;
         unlink_frame(cur_frame_pnt->next_frame_pnt);
      }
      next_frame();
   }
   memmove(cur_frame_pnt->data_t_ary + offset_i32, cur_frame_pnt->data_t_ary + offset_i32 + arg_del_cnt, sizeof(cls_t) * (get_rest_cnt() - arg_del_cnt));
   cur_frame_pnt->cnt_i32 -= arg_del_cnt;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::link_frame(int32 arg_i32_cnt)
{
   mac_assert(arg_i32_cnt <= frame_size_i32);
   cls_frame* p = (cls_frame*) mem_alloc(sizeof(cls_frame));
   p->prev_frame_pnt = cur_frame_pnt;
   p->next_frame_pnt = cur_frame_pnt->next_frame_pnt;
   p->cnt_i32 = arg_i32_cnt;
   cur_frame_pnt->next_frame_pnt->prev_frame_pnt = p;
   cur_frame_pnt->next_frame_pnt = p;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::prev_frame()
{
   mac_assert(cur_frame_pnt->prev_frame_pnt != (cls_frame*) &head_frame);
   cur_frame_pnt = cur_frame_pnt->prev_frame_pnt;
   base_i32 -= cur_frame_pnt->cnt_i32;
   offset_i32 = 0;
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::next_frame()
{
   mac_assert(cur_frame_pnt->next_frame_pnt != (cls_frame*) &tail_frame);

   if (cur_frame_pnt->cnt_i32)
   {
      base_i32 += cur_frame_pnt->cnt_i32;
      cur_frame_pnt = cur_frame_pnt->next_frame_pnt;
      offset_i32 = 0;
   }
   else
   {
      cls_frame* p = cur_frame_pnt->next_frame_pnt;
      unlink_frame(cur_frame_pnt);
      cur_frame_pnt = p;
   }
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::unlink_frame(cls_frame* arg_frame_pnt)
{
   arg_frame_pnt->prev_frame_pnt->next_frame_pnt = arg_frame_pnt->next_frame_pnt;
   arg_frame_pnt->next_frame_pnt->prev_frame_pnt = arg_frame_pnt->prev_frame_pnt;
   mem_free(arg_frame_pnt);
}
                                                                                            
template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::put_dary(tem_dynamic_array<cls_t, frame_size_i32>* src_dary, int32 arg_cpy_cnt)
{
   mac_assert(this != src_dary);
   mac_assert(src_dary->base_i32 + src_dary->offset_i32 + arg_cpy_cnt <= src_dary->cnt_i32);
   mac_assert(base_i32 + offset_i32 + arg_cpy_cnt <= cnt_i32);

   int32 rd_cnt;
   int32 wr_cnt;

   while (arg_cpy_cnt)
   {
      arg_cpy_cnt -= rd_cnt = get_min(arg_cpy_cnt,src_dary->get_rest_cnt());
      while (rd_cnt)
      {
         rd_cnt -= wr_cnt = get_min(rd_cnt,get_rest_cnt());
         memcpy(cur_frame_pnt->data_t_ary + offset_i32, src_dary->cur_frame_pnt->data_t_ary + src_dary->offset_i32, wr_cnt * sizeof(cls_t));
         locate_rel(wr_cnt);
         src_dary->locate_rel(wr_cnt);
      }
   }
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::put_ary(cls_t* pnt_t_src, int32 arg_cpy_cnt)
{
   mac_assert(base_i32 + offset_i32 + arg_cpy_cnt <= cnt_i32);

   int32 wr_cnt;

   while (arg_cpy_cnt)
   {
      arg_cpy_cnt -= wr_cnt = get_min(arg_cpy_cnt,get_rest_cnt());
      memcpy(cur_frame_pnt->data_t_ary + offset_i32, pnt_t_src, wr_cnt * sizeof(cls_t));
      locate_rel(wr_cnt);
      pnt_t_src += wr_cnt;
   }
}

template<class cls_t, int32 frame_size_i32> void tem_dynamic_array<cls_t,frame_size_i32>::get_ary(cls_t* pnt_t_dst, int32 arg_cpy_cnt)
{
   mac_assert(base_i32 + offset_i32 + arg_cpy_cnt <= cnt_i32);

   int32 wr_cnt;

   while (arg_cpy_cnt)
   {
      arg_cpy_cnt -= wr_cnt = get_min(arg_cpy_cnt,get_rest_cnt());
      memcpy(pnt_t_dst, cur_frame_pnt->data_t_ary + offset_i32, wr_cnt * sizeof(cls_t));
      locate_rel(wr_cnt);
      pnt_t_dst += wr_cnt;
   }
}

/*
tem_dynamic_array<int,16> int_dary;
*/

