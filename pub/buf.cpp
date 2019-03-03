                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/buf.cpp
   copyright(C) kyuhyun park
   1994.06.29
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/buf.hpp>

cls_rfbuf::cls_rfbuf (char* file_name, size_t sz) :
   file (file_name)
{
   buf_byte_array.alloc(sz);
   file_sz  = file.get_size();
   base_pnt = buf_byte_array.get_base();
   end_pnt  = base_pnt + sz;
   cur_pnt  = end_pnt;
}

void cls_rfbuf::fill ()
{
   size_t move_sz;
   size_t read_sz;

   move_sz = (size_t) ( end_pnt - cur_pnt );
   read_sz = (size_t) get_min ( (off_t) ( cur_pnt - base_pnt ), file_sz );

   memmove (base_pnt , cur_pnt, move_sz);
   file.read (base_pnt + move_sz, read_sz);
   mac_assert (buf_byte_array.check());

   end_pnt = base_pnt + move_sz + read_sz;
   cur_pnt = base_pnt ;
   file_sz -= read_sz;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_wfbuf::cls_wfbuf (char* file_name, size_t sz) :
   file (file_name)
{
   buf_byte_array.alloc(sz);
   base_pnt = buf_byte_array.get_base();
   end_pnt  = base_pnt + sz;
   cur_pnt  = base_pnt;
}

cls_wfbuf::~cls_wfbuf ()
{
   if (cur_pnt > base_pnt) flush();
}

void cls_wfbuf::flush ()
{
   mac_assert(buf_byte_array.check());

   size_t write_cnt = size_t(cur_pnt - base_pnt);
   cur_pnt = base_pnt;
   file.write (base_pnt, write_cnt);
} 
