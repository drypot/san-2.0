                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mcp.cpp
   copyright(C) kyuhyun park
   1994.10.22
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <pub/dir.hpp>
#include <pub/init.hpp>
#include <key/mcp.hpp>
                                                                                                                        /*
--------------------------------------------------------------------------------
   cls_mcp
--------------------------------------------------------------------------------                                        */

cls_mcp::cls_mcp() :
   name_pch(NULL),
   file_img_u32_pnt(NULL)
{
   memset (line_ary , 0 , sizeof(line_ary));
}

cls_mcp::~cls_mcp()
{
   if (file_img_u32_pnt) mem_free(file_img_u32_pnt);
}

void cls_mcp::load(char* fname)
{
   mac_assert(file_img_u32_pnt == NULL);

   cls_rfile map_file(fname);
   size_t file_sz = map_file.get_size();

   file_img_u32_pnt = (uint32*) mem_alloc(file_sz);
   map_file.read (file_img_u32_pnt, file_sz);

   uint32* base_u32_pnt = (uint32*) ((byte*)file_img_u32_pnt + def_mcp_name_size + sizeof(lang_u32));
   int page_sz = 0;
   int adder = 0;
   int i;

   name_pch = (char*) file_img_u32_pnt;
   lang_u32 = *(uint32*)((byte*)file_img_u32_pnt + def_mcp_name_size);

   forcnt(i,def_mcp_line_cnt) page_sz += base_u32_pnt[i];

   adder += def_mcp_line_cnt;
   forcnt(i,def_mcp_line_cnt)
   {
      uint32 u32_tmp = base_u32_pnt[i];

      line_ary[i].cnt = u32_tmp;
      line_ary[i].page0_u32_pnt = base_u32_pnt + adder;
      line_ary[i].page1_u32_pnt = base_u32_pnt + adder + page_sz;

      adder += u32_tmp;
   }
}

char* cls_mcp::get_name()
{
   mac_assert(file_img_u32_pnt);
   return name_pch;
}

uint32 cls_mcp::get_lang()
{
   mac_assert(file_img_u32_pnt);
   return lang_u32;
}

uint32 cls_mcp::get_mc(int num_page, cls_key_event* key_event)
{
   mac_assert (file_img_u32_pnt);
   mac_assert (key_event->get_code_type() == def_key_type_char);
   mac_assert (key_event->get_char_code_line() < def_mcp_line_cnt);
   mac_assert (key_event->get_char_code_col() < line_ary [key_event->get_char_code_line()].cnt);
   mac_assert (num_page == 0 || num_page == 1);
   return num_page == 0 ? line_ary [key_event->get_char_code_line()].page0_u32_pnt [key_event->get_char_code_col()]
                        : line_ary [key_event->get_char_code_line()].page1_u32_pnt [key_event->get_char_code_col()];
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   mcPageList
--------------------------------------------------------------------------------                                        */

#define def_size_mcp_list 8

static cls_mcp  mcp_ary[def_size_mcp_list];
static cls_mcp* mcp_ary_end_pnt = mcp_ary;
static int mcp_cnt;

bool is_mcp_list_null()
{
   return mcp_cnt == 0;
}

void mcp_add (char* name)
{
   mac_rtcheck(mcp_cnt < def_size_mcp_list);
   mcp_ary[mcp_cnt].load (name);
   mcp_ary_end_pnt++;
   mcp_cnt++;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_mcp_list_iter::cls_mcp_list_iter() : mcp_pnt (mcp_ary)
{
}

void cls_mcp_list_iter::reset()
{
   mcp_pnt = mcp_ary;
}

void cls_mcp_list_iter::next_mcp()
{
   mac_rtcheck(mcp_cnt);
   mcp_pnt++;
   if (mcp_pnt == mcp_ary_end_pnt) mcp_pnt = mcp_ary;
}

bool cls_mcp_list_iter::locate_mcp (uint32 lang_u32)
{
   mac_rtcheck(mcp_cnt);
   cls_mcp* mrx_mcp_pnt = mcp_ary;
   while (mrx_mcp_pnt < mcp_ary_end_pnt)
   {
      if (mrx_mcp_pnt->get_lang() == lang_u32)
      {
         mcp_pnt = mrx_mcp_pnt;
         return def_ok;
      }
      mrx_mcp_pnt++;
   }
   return def_error;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void ctor()
{
   try
   {
      if (is_mcp_list_null())
      {
         mcp_add (cls_fname("@bindir/../etc/qwerty.mcp").get_path());
         mcp_add (cls_fname("@bindir/../etc/han3-90.mcp").get_path());
      }
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info("func: key/mcp.cpp/ctor\ninfo: meta-code-page loading error\n");
      throw;
   }
}

static cls_initer initer(ctor, def_init_pri_key_mcp);
