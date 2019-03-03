                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/stack.hpp
   copyright(c) kyuhyun park
   1993.07.24
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_stack_hpp
#error 'cnt/stack.hpp' duplicated.
#endif

#define def_cnt_stack_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif
                        
template<class cls_t>
class tem_stack
{
   private:

      cls_t* basep;
      cls_t* endp;
      cls_t* topp;

   public:

      tem_stack (size_t);
     ~tem_stack ();

      void reset ();

      void push_pnt (cls_t*);
      void push_ary (cls_t*, size_t);
      void push_val (cls_t);

      cls_t pop_val ();

      void discard (size_t=1);

      cls_t* get_pnt (size_t);
      cls_t* get_top_pnt ();
      size_t get_cnt ();
      size_t get_cnt_in_byte ();
      cls_t* get_base_pnt ();

      bool is_empty ();
      bool is_holding ();
      bool is_full ();
};

//tem_stack<size_t> stack(10);

template<class cls_t> inline tem_stack<cls_t>::tem_stack(size_t cnt)
{
   mac_assert(cnt);
   topp = basep = (cls_t*)mem_alloc(cnt*sizeof(cls_t));
   endp = basep+cnt;
}

template<class cls_t> tem_stack<cls_t>::~tem_stack()
{
   mem_free(basep);
   basep = NULL;
}

template<class cls_t> inline void tem_stack<cls_t>::reset()
{
   topp = basep;
}

template<class cls_t> void tem_stack<cls_t>::push_pnt (cls_t* pnt)
{
   mac_assert (topp < endp);
   *topp++ = *pnt;
   mac_assert (mem_check(basep));
}

template<class cls_t> void tem_stack<cls_t>::push_ary (cls_t* arg_pnt, size_t arg_cnt)
{
   mac_assert (topp + arg_cnt <= endp);
   memcpy(topp, arg_pnt, sizeof(cls_t) * arg_cnt);
   topp += arg_cnt;
   mac_assert (mem_check(basep));
}

template<class cls_t> void tem_stack<cls_t>::push_val (cls_t arg_t)
{
   mac_assert (topp < endp);
   *topp++ = arg_t;
   mac_assert (mem_check(basep));
}

template<class cls_t> cls_t tem_stack<cls_t>::pop_val ()
{
   mac_assert (topp > basep);
   return *--topp;
}

template<class cls_t> inline void tem_stack<cls_t>::discard (size_t num)
{
   mac_assert (topp >= basep + num);
   topp -= num;
}

template<class cls_t> cls_t* tem_stack<cls_t>::get_pnt (size_t inx)
{
   mac_assert (topp-inx-1 < topp && topp-inx-1 >= basep);
   return topp-inx-1;
}

template<class cls_t> inline cls_t* tem_stack<cls_t>::get_top_pnt()
{
   mac_assert (topp > basep);
   return topp-1;
}

template<class cls_t> inline size_t tem_stack<cls_t>::get_cnt()
{
   return size_t(topp - basep);
}

template<class cls_t> inline size_t tem_stack<cls_t>::get_cnt_in_byte()
{
   return (size_t)(topp - basep) * sizeof(cls_t);
}

template<class cls_t> inline cls_t* tem_stack<cls_t>::get_base_pnt()
{
   return basep;
}

template<class cls_t> inline bool tem_stack<cls_t>::is_empty()
{
   return topp == basep;
}

template<class cls_t> inline bool tem_stack<cls_t>::is_holding()
{
   return topp != basep;
}

template<class cls_t> inline bool tem_stack<cls_t>::is_full()
{
   return topp == endp;
}

