                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/buf.hpp
   copyright(c) kyuhyun park
   1994.06.29
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_buffer_hpp
#error "pub/buf.hpp" duplicated.
#endif

#define def_pub_buffer_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif

#ifndef def_pub_file_hpp
#include <pub/io.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

#ifndef def_cnt_array_hpp
#include <cnt/array.hpp>
#endif

template <class cls_t, int sz>
class tem_wbuf
{
   private:

      cls_t  room_ary[sz];
      cls_t* end_pnt;
      cls_t* cur_pnt;

   public:

      tem_wbuf()
      {
         cur_pnt = room_ary;
         end_pnt = room_ary + sz;
      }

     ~tem_wbuf()
      {
      }

      void reset()
      {
         cur_pnt = room_ary;
      }

      bool is_full()
      {
         return end_pnt == cur_pnt;
      }

      bool is_empty()
      {
         return room_ary == cur_pnt;
      }

      void put_pnt(cls_t* pnt)
      {
         mac_assert(cur_pnt < end_pnt);
         *cur_pnt++ = *pnt;
      }

      void put_val(cls_t val)
      {
         mac_assert(cur_pnt < end_pnt);
         *cur_pnt++ = val;
      }

      size_t get_cnt()
      {
         return cur_pnt - room_ary;
      }

      size_t get_free_cnt()
      {
         return (room_ary+sz) - cur_pnt;
      }

      size_t get_cnt_in_byte()
      {
         return (cur_pnt - room_ary) * sizeof(cls_t);
      }

      size_t get_free_cnt_in_byte()
      {
         return ((room_ary+sz) - cur_pnt) * sizeof(cls_t);
      }

      cls_t* get_base()
      {
         return room_ary;
      }
};

class cls_rfbuf
{
   private:

      cls_rfile file;
      off_t file_sz;

      tem_array<byte> buf_byte_array;

      byte* base_pnt;
      byte* end_pnt;
      byte* cur_pnt;

   public:

      cls_rfbuf(char*, size_t = 4096);

      void fill();

      size_t get_rest_cnt()
      {
         return size_t(end_pnt - cur_pnt);
      }

      off_t get_file_rest_cnt()
      {
         return file_sz;
      }

      bool is_eof()
      {
         return get_file_rest_cnt() == 0 && get_rest_cnt() == 0;
      }

      uint8 get_val()
      {
         mac_assert (cur_pnt < end_pnt);
         return *cur_pnt++;
      }

      /*
      uint16 get_u16()
      {
         mac_assert (cur_pnt+1 < end_pnt);
         return *mac_change_type_of(cur_pnt, uint16*)++;
      }
      */

      uint8 peek_val()
      {
         mac_assert (cur_pnt < end_pnt);
         return *cur_pnt;
      }

      /*
      uint16 peek_u16()
      {
         mac_assert (cur_pnt+1 < end_pnt);
         return *mac_change_type_of(cur_pnt, uint16*);
      }
      */

      void skip (size_t sz = 1)
      {
         mac_assert(cur_pnt+sz <= end_pnt);
         cur_pnt += sz;
      }
};

class cls_wfbuf
{
   private:

      cls_wfile file;
      tem_array<byte> buf_byte_array;

      byte* base_pnt;
      byte* end_pnt;
      byte* cur_pnt;

   public:

      cls_wfbuf(char*, size_t = 4096);
     ~cls_wfbuf();

      void flush();

      size_t get_free_cnt()
      {
         return size_t (end_pnt - cur_pnt);
      }

      void put_val (uint8 val)
      {
         mac_assert (cur_pnt < end_pnt);
         *cur_pnt++ = val;
      }

      /*
      void put_u16 (uint16 val)
      {
         mac_assert (cur_pnt + 1 < end_pnt);
         *mac_change_type_of(cur_pnt,uint16*)++ = val;
      }
      */
};
