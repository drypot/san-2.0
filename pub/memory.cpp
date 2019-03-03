                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/memory.cpp
   copyright(C) kyuhyun park
   1992.01.17
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
                                                                                                                        /*
--------------------------------------------------------------------------------
   memory allocation
--------------------------------------------------------------------------------                                        */

#ifdef def_debug

   #define def_fill_u16_head 0xfff0
   #define def_fill_u16_tail 0xfff2

   void mem_frame_mark(void* arg_pnt, size_t sz)
   {
      *(uint16*)((char*)arg_pnt + 0) = def_fill_u16_head;
      *(size_t*)((char*)arg_pnt + sizeof(uint16)) = sz;
      *(uint16*)((char*)arg_pnt + sizeof(uint16) + sizeof(size_t) + sz) = def_fill_u16_tail;
   }

   bool mem_frame_check(void* arg_pnt)
   {
      bool is_head_ok = *(uint16*)arg_pnt == def_fill_u16_head;
      bool is_tail_ok = *(uint16*)((char*)arg_pnt + sizeof(uint16) + sizeof(size_t) + *(size_t*)((char*)arg_pnt + sizeof(uint16))) == def_fill_u16_tail;
      return is_head_ok && is_tail_ok;
   }

   void* mem_alloc(size_t sz)
   {
      void* pnt = malloc(mem_frame_size(sz));

      if (!pnt) throw cls_xmsg_memory ("func: pub/memory.cpp/mem_alloc\ninfo: out of memory\n");
      mem_frame_mark(pnt,sz);
      return mem_frame_body(pnt);
   }

   void mem_free(void* arg_pnt)
   {
      if (arg_pnt)
      {
         mac_assert(mem_check(arg_pnt)==def_ok);
         free((char*)arg_pnt - sizeof(size_t) - sizeof(uint16));
      }
   }

   bool mem_check(void* arg_pnt)
   {
      return mem_frame_check( mem_frame_head(arg_pnt) );
   }

#else

   void* mem_alloc(size_t sz)
   {
      void* pnt = malloc(sz);

      if (!pnt) throw cls_xmsg_memory ("func: pub/memory.cpp/mem_alloc\ninfo: out of memory\n");
      return pnt;
   }

   void mem_free(void* arg_pnt)
   {
      free(arg_pnt);
   }

#endif
                                                                                                                        /*
--------------------------------------------------------------------------------
   memory access
--------------------------------------------------------------------------------                                        */

void* mem_or(void* arg_dst_pnt , void* arg_src_pnt , size_t sz)
{
   register byte* dst_pnt = (byte*)arg_dst_pnt;
   register byte* src_pnt = (byte*)arg_src_pnt;

   while (sz--)  *dst_pnt++ |= *src_pnt++;

   return arg_dst_pnt;
}

void* mem_chr16  (void* arg_pnt , uint16 val , size_t sz)
{
   register uint16* pnt = (uint16*) arg_pnt;

   while (sz && *pnt != val) sz--, pnt++;

   return sz ? (void*) pnt : NULL ;
}

int mem_cmp16  (void* arg_p1 , void* arg_p2 , size_t sz)
{
   register uint16* p1 = (uint16*) arg_p1;
   register uint16* p2 = (uint16*) arg_p2;

   while ( sz && *p1 == *p2 )
   {
      sz--;
      p1++;
      p2++;
   }

   return sz ? *p1 - *p2  : 0;
}

void* mem_set16 (void* arg_pnt , uint16 val , size_t sz)
{
   register uint16* pnt = (uint16*) arg_pnt;
   while (sz--) *pnt++ = val;
   return arg_pnt;
}

void* mem_or16 (void* arg_dst_pnt, void* arg_src_pnt, size_t sz)
{
   register uint16* dst_pnt = (uint16*) arg_dst_pnt;
   register uint16* src_pnt = (uint16*) arg_src_pnt;

   while (sz--) *dst_pnt++ |= *src_pnt++;

   return arg_dst_pnt;
}
