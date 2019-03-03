                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/memory.hpp
   copyright(c) kyuhyun park
   1992.01.17
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_memory_hpp
#error 'pub/memory.hpp' duplicated.
#endif

#define def_pub_memory_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_string_hpp
#include <pub/string.hpp>
#endif

#include <new.h>

#if defined def_watcomc || defined def_borlandc || defined def_ibmc
#include <malloc.h>
#endif
                                                                                                                        /*
--------------------------------------------------------------------------------
   memory allocation
--------------------------------------------------------------------------------                                        */

mac_define_xmsg1(memory);

#ifdef def_debug
   #define mem_frame_size(sz) (sizeof(uint16) + sizeof(size_t) + sz + sizeof(uint16))

   inline void* mem_frame_body(void* p)
   {
      return (char*)p + sizeof(uint16) + sizeof(size_t);
   }

   inline void* mem_frame_head(void* p)
   {
      return (char*)p - sizeof(size_t) - sizeof(uint16);
   }

   void  mem_frame_mark(void*, size_t);
   bool  mem_frame_check(void*);

   void* mem_alloc (size_t);
   void  mem_free (void*);
   bool  mem_check (void*);
#else
   #define mem_frame_size(sz) (sz)
   #define mem_frame_body(p)  (p)
   #define mem_frame_head(p)  (p)
   #define mem_frame_mark(p,sz)

   void*  mem_alloc (size_t);
   void   mem_free (void*);
#endif
                                                                                                                        /*
--------------------------------------------------------------------------------
   memory initailization
--------------------------------------------------------------------------------                                        */

template<class cls_t> void construct_ary (cls_t* arg_pnt, int cnt)
{
   cls_t* end_pnt = arg_pnt + cnt;
   while (arg_pnt < end_pnt) new((void*)arg_pnt++) cls_t;
}

template<class cls_t> void destruct_ary (cls_t* arg_pnt, int cnt)
{
   cls_t* end_pnt = arg_pnt + cnt;
   while (arg_pnt < end_pnt) (arg_pnt++)->~cls_t();
}

inline void* operator new (size_t sz)      { return mem_alloc(sz); }
inline void* operator new[] (size_t sz)    { return mem_alloc(sz); }
inline void  operator delete (void* p)     { mem_free(p); }
inline void  operator delete[] (void* p)   { mem_free(p); }
                                                                                                                              /*
--------------------------------------------------------------------------------
   memory access
--------------------------------------------------------------------------------                                        */

void* mem_or (void*, void*, size_t);

void* mem_chr16  (void*, uint16, size_t);
int   mem_cmp16  (void*, void*, size_t);

inline void* mem_cpy16  (void* pnt_dst , void* pnt_src, size_t sz)
{
   return memcpy (pnt_dst, pnt_src, sz * 2);
}

inline void* mem_move16 (void* pnt_dst , void* pnt_src , size_t sz)
{
   return memmove (pnt_dst , pnt_src , sz * 2);
}

void* mem_set16  (void*, uint16, size_t);
void* mem_or16   (void*, void*, size_t);

#define mac_fill_zero(id) memset(&id, 0, sizeof(id))

