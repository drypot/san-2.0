                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/func.cpp
   copyright(c) kyuhyun park
   1994.11.07
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/lex.hpp>
#include <key/mac.hpp>

#include <mc/glb.hpp>
#include <mc/tmp/parser.h>

#define def_func_list_size 1024

struct cls_func_frame
{
   char name_ach[def_id_size];
   uint32 addr_u32;
};

static cls_func_frame func_frame_ary[def_func_list_size];
static cls_func_frame* func_frame_limit_pnt = func_frame_ary + def_func_list_size;
static cls_func_frame* func_frame_end_pnt   = func_frame_ary;

uint32 scan_func(char* func_name_pch)
{
   cls_func_frame* iter_pnt = func_frame_ary;
   while (iter_pnt < func_frame_end_pnt)
   {
      if (strcmp(iter_pnt->name_ach, func_name_pch) == 0) return iter_pnt->addr_u32;
      iter_pnt++;
   }
   return 0;
}

void regi_func(char* func_name_pch, uint32 addr_u32)
{
   if (strlen(func_name_pch) >= def_id_size)
   {
      throw cls_xmsg("func: mc\func.cpp\regi_func(char*,uint32)\ninfo: too big function name\n");
   }
   if (func_frame_end_pnt >= func_frame_limit_pnt)
   {
      throw cls_xmsg("func: mc\func.cpp\regi_func(char*,uint32)\ninfo: function table overflow\n");
   }

   if (scan_func(func_name_pch)) throw cls_xmsg("func: mc/func.cpp/regi_func(char*,uint32)\ninfo: function already defined\n");
   strcpy(func_frame_end_pnt->name_ach, func_name_pch);
   func_frame_end_pnt->addr_u32 = addr_u32;
   func_frame_end_pnt++;
}


