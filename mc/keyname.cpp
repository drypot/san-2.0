                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/keyname.cpp
   copyright(c) kyuhyun park
   1994.11.06
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/lex.hpp>

#include <mc/glb.hpp>
#include <mc/tmp/parser.h>

#define def_key_name_list_size 1024
#define def_key_name_size 16

struct cls_kname_frame
{
   char name_ach[def_key_name_size];
   uint16 code_u16;
};

cls_kname_frame kname_frame_ary[def_key_name_list_size];
cls_kname_frame* kname_frame_list_end_pnt;

uint16 scan_key_name()
{
   cls_kname_frame* p = kname_frame_ary;

   while ( p < kname_frame_list_end_pnt )
   {
      if (strcmp(p->name_ach, lex_val_ach) == 0) return p->code_u16;
      p++;
   }
   return 0;
}

void read_key_name_file()
{
   scanner_key_name_mode();

   cls_kname_frame* name_pnt;
   cls_kname_frame* code_pnt;
   int token;

   name_pnt = code_pnt = kname_frame_ary;
   kname_frame_list_end_pnt = kname_frame_ary + def_key_name_list_size;

   forever
   {
      token = yylex();
      if (token == TK_IDENT || token == TK_STRING)
      {
         mac_rtcheck (strlen(lex_val_ach) < def_key_name_size);
         mac_rtcheck (name_pnt < kname_frame_list_end_pnt);
         strcpy((name_pnt++)->name_ach,lex_val_ach);
      }
      ef ( token == TK_INT )
      {
         mac_assert (name_pnt > code_pnt);
         while (name_pnt > code_pnt) (code_pnt++)->code_u16 = lex_val_int;
      }
      else break;
   }
   if (token != 0) throw cls_xmsg("func: mc/keyname.cpp/read_key_name_file()\ninfo: syntax error\n");
   if (name_pnt != code_pnt) throw cls_xmsg ("func: mc/keyname.cpp/read_key_name_file()\ninfo: key code missing\n");
   kname_frame_list_end_pnt = name_pnt;
}
