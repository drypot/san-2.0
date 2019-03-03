                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/queue.hpp
   copyright(C) kyuhyun park
   1993.07.16
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_queue_hpp
#error 'cnt/queue.hpp' duplicated.
#endif

#define def_cnt_queue_hpp

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
class tem_queue
{
   private:
      cls_t* getp;
      cls_t* putp;
      cls_t* basep;
      cls_t* endp;

   public:

      tem_queue (size_t);
     ~tem_queue ();

      void reset ();

      void push_pnt (cls_t*);
      void push_val (cls_t);
      cls_t pop_val ();

      bool is_empty ();
      bool is_holding ();
      bool is_full ();

   private:

      cls_t* get_next_pnt (cls_t*);
};

//tem_queue<int> queue(10);

template<class cls_t> tem_queue<cls_t>::tem_queue (size_t cnt)
{
   mac_assert(cnt);

   getp = putp = basep=(cls_t*) mem_alloc(cnt * sizeof(cls_t));
   endp = basep + cnt;
}

template<class cls_t> tem_queue<cls_t>::~tem_queue ()
{
   mem_free(basep);
   basep = NULL;
}

template<class cls_t> cls_t* tem_queue<cls_t>::get_next_pnt (cls_t* arg_pnt)
{
   return arg_pnt == endp - 1 ? basep : arg_pnt + 1;
}

template<class cls_t> void tem_queue<cls_t>::push_pnt (cls_t* pnt)
{
   cls_t* next_pnt = get_next_pnt(putp);

   mac_assert( next_pnt != getp );

   *putp = *pnt;
   putp = next_pnt;

   mac_assert(mem_check(basep));
}

template<class cls_t> void tem_queue<cls_t>::push_val (cls_t t)
{
   cls_t* next_pnt = get_next_pnt(putp);

   mac_assert( next_pnt != getp );

   *putp = t;
   putp = next_pnt;

   mac_assert(mem_check(basep));
}

template<class cls_t> cls_t tem_queue<cls_t>::pop_val ()
{
   mac_assert ( putp != getp );

   cls_t* prev_get_pnt = getp;
   getp = get_next_pnt(getp);
   return *prev_get_pnt;
}

template<class cls_t> inline bool tem_queue<cls_t>::is_empty ()
{
   return getp == putp;
}

template<class cls_t> inline bool tem_queue<cls_t>::is_holding ()
{
   return getp != putp;
}

template<class cls_t> bool tem_queue<cls_t>::is_full ()
{
   return get_next_pnt(putp) == getp;
}

template<class cls_t> inline void tem_queue<cls_t>::reset()
{
   getp=putp;
}

