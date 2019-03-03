                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/ini.cpp
   copyright(c) kyuhyun park
   1995.12.17
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/dir.hpp>
#include <pub/lex.hpp>
#include <pub/ini.hpp>

typedef void (*type_func_pch)(char*);

static FILE* fh;

static cls_ini_item_desc* parse_item_name(char* item_name_pch, cls_ini_item_desc* desc_pnt)
{
   while (desc_pnt->type_int != 0)
   {
      if (strcmp(desc_pnt->name_pch, item_name_pch) == 0) break;
      desc_pnt++;
   }

   if (desc_pnt->type_int == 0) throw cls_xmsg ("func: pub/ini.cpp/parse_item_name\ninfo: unknown item name\n");

   return desc_pnt;
}

static void parse_value(char* value_pch, cls_ini_item_desc* desc_pnt)
{
   switch (desc_pnt->type_int)
   {
      case def_ini_ignore :
         break;

      case def_ini_int :
         *(int*)desc_pnt->var_pnt = atoi(value_pch);
         break;

      case def_ini_pch :
         *(char**)desc_pnt->var_pnt = strdup(value_pch);
         break;

      case def_ini_path :
         *(char**)desc_pnt->var_pnt = strdup(cls_fname(value_pch).get_path());
         break;

      case def_ini_func_pch :
         ((type_func_pch)desc_pnt->var_pnt)(value_pch);
         break;

      case def_ini_func_path :
         ((type_func_pch)desc_pnt->var_pnt)(cls_fname(value_pch).get_path());
         break;

      case def_ini_bool :
         if (stricmp(value_pch, "yes") == 0 || stricmp(value_pch, "on")  == 0) *(bool*)desc_pnt->var_pnt = def_yes;
         ef (stricmp(value_pch, "no")  == 0 || stricmp(value_pch, "off") == 0) *(bool*)desc_pnt->var_pnt = def_no;
         else throw cls_xmsg("func: pub/ini.cpp/parse_value\ninfo: type mismatch\n");
         break;

      default :
         mac_halt();
   };
}

void parse_ini (char* arg_fname, cls_ini_item_desc* arg_desc_pnt)
{
   int line_num = 0;

   if (fh = fopen(arg_fname,"rt"), fh == NULL)
   {
      throw cls_xmsg(cls_form_expander("func: pub/ini.cpp/parse_ini\ninfo: open error\nfile: %s\n", arg_fname).get_pch());
   }

   try
   {
      char buf_ach[512];
      char* item_name_pch;
      char* end_item_name_pch;
      char* pch;
      int len;

      while (fgets(buf_ach, sizeof(buf_ach), fh) != NULL)
      {
         line_num++;
         len = strlen(buf_ach);
         while (len && isspace(buf_ach[len-1])) len--;
         buf_ach[len] = 0;

         pch = buf_ach;
         while (isspace(*pch)) pch++;

         if (*pch == '#' || *pch == 0) continue;

         item_name_pch = pch;
         while (*pch && !isspace(*pch) && *pch != '=') pch++;
         end_item_name_pch = pch;
         while (isspace(*pch)) pch++;

         if (*pch != '=') throw cls_xmsg ("func: pub/ini.cpp/parse_ini\ninfo: equal expected\n");
         *end_item_name_pch = 0;
         pch++;
         while (isspace(*pch)) pch++;
         if (*pch == '"' && buf_ach[len-1] == '"')
         {
            pch++;
            buf_ach[len-1] = 0;
            str_parse(pch);
         }

         if (*pch == 0) throw cls_xmsg ("func: pub/ini.cpp/parse_ini\ninfo: empty value\n");
         parse_value(pch, parse_item_name(item_name_pch, arg_desc_pnt));
      }
   }
   catch(cls_xmsg xmsg)
   {
      fclose(fh);
      xmsg.add_info(cls_form_expander("\nfunc: pub/ini.cpp/parse_ini\ninfo: ini parsing error\nfile: %s\nline: %d\n", arg_fname, line_num).get_pch());
      throw;
   }

   fclose(fh);
}

