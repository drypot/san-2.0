                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/array.hpp
   copyright(c) kyuhyun park
   1993.07.28
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_array_hpp
#error 'cnt/array.hpp' duplicated.
#endif

#define def_cnt_array_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif

template <class clt_t>
class tem_array
{
   private:

      clt_t* base_pnt;
      int cnt;

   public:

      tem_array (int = 0);
     ~tem_array();

      void alloc (int = 0);
      void free ();

      void fill_zero();

      void insert (int, int = 1);
      void remove (int, int = 1);

      clt_t* get_pnt (int n)
      {
         mac_assert (base_pnt);
         mac_assert (n < cnt);
         return base_pnt + n;
      }

      clt_t* get_base()
      {
         mac_assert(base_pnt);
         return base_pnt;
      }

#ifdef def_debug
      bool check ()
      {
         mac_assert(base_pnt);
         return mem_check(base_pnt);
      }
#endif

};

template<class clt_t> tem_array<clt_t>::tem_array (int arg_cnt) : base_pnt(NULL), cnt(arg_cnt)
{
   if (cnt) alloc (cnt);
}

template<class clt_t> tem_array<clt_t>::~tem_array ()
{
   if (base_pnt) free();
}

template<class clt_t> void tem_array<clt_t>::alloc (int arg_cnt)
{
   if (arg_cnt == 0) arg_cnt = cnt;

   mac_assert (arg_cnt);
   mac_assert (base_pnt == NULL);

   cnt = arg_cnt;
   base_pnt = (clt_t*) mem_alloc (sizeof(clt_t) * arg_cnt);
}

template<class clt_t> void tem_array<clt_t>::free ()
{
   mac_assert (base_pnt);
   mem_free (base_pnt);
   base_pnt = NULL;
}

template<class clt_t> void tem_array<clt_t>::insert (int n, int arg_cnt)
{
   mac_assert (base_pnt);
   mac_assert (n < cnt);
   mac_assert (n + arg_cnt <= cnt);

   memmove (base_pnt + n + arg_cnt, base_pnt + n, (cnt-(n+arg_cnt))*sizeof(clt_t));

   mac_assert (mem_check(base_pnt));
}

template<class clt_t> void tem_array<clt_t>::remove (int n, int arg_cnt)
{
   mac_assert (base_pnt);
   mac_assert (n < cnt);
   mac_assert (n+arg_cnt <= cnt);

   memmove (base_pnt+n, base_pnt+n+arg_cnt, (cnt-(n+arg_cnt))*sizeof(clt_t));
   mac_assert (mem_check(base_pnt));
}

template<class clt_t> void tem_array<clt_t>::fill_zero ()
{
   mac_assert (base_pnt);
   memset (base_pnt, 0, sizeof(clt_t)*cnt);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

template<class clt_t, uint n>
class tem_static_array
{
   private:

      byte stg_byte_ary[ mem_frame_size(sizeof(clt_t[n])) ];
#ifdef def_debug
      uint items;
#endif

   public:

      tem_static_array()
      {
         mem_frame_mark(stg_byte_ary, sizeof(clt_t[n]));

#ifdef def_debug
         items = n;
#endif
      }

      clt_t* get_pnt (uint n)
      {
         mac_assert(n<items);
         return (clt_t*)mem_frame_body(stg_byte_ary)+n;
      }

      clt_t* get_base_pnt()
      {
         return (clt_t*)mem_frame_body(stg_byte_ary);
      }

#ifdef def_debug
      bool check()
      {
         return mem_frame_check(stg_byte_ary);
      }
#endif
};

//tem_array<int> tmp;
