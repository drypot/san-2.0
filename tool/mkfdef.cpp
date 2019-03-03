                                                                                                                        /*
--------------------------------------------------------------------------------
   mkfdef.cpp -- make macro-function define list
   copyright(C) kyuhyun park
   1994.11.08
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/lex.hpp>
#include <tool/mkfdef.hpp>

#define def_size_list 2048
#define def_size_func_name 32

char list[def_size_list][def_size_func_name];
int  cnt_list;

void regi_id(char* name)
{
   if (strlen(name) >= def_size_func_name)
   {
      put_msg("too long function name @regi_id\n");
      pcs_exit(1);
   }
   strcpy(list[cnt_list++],name);
}

int search_id(char* name)
{
   int i;
   forcnt(i,cnt_list) if (strcmp(name,list[i])==0) return def_ok;
   return def_no;
}

void open_error(char* name)
{
   throw cls_xmsg (cls_form_expander("func: tool/mkfdef.cpp/open_error()\ninfo: file open error\nfile: %s\n", name).get_pch());
}

int pcs_main()
{
   FILE* fh_def = NULL;
   FILE* fh_map = NULL;
   int token;
   int cnt = 0;
   char ach_src[512];
   char ach_def[512];
   char ach_map[512];
   char* pch_prefix;
   char* pch_module;

   if (argc < 2)
   {
      fprintf(stderr,"usage:funclist <module name> <prefix>\n");
      pcs_exit(1);
   }

   pch_prefix = (argc == 2) ? "pdf_" : argv[2];
   pch_module = argv[1];

   ach_src[0]=0;
   ach_def[0]=0;
   ach_map[0]=0;
   str_cat_va (ach_src, get_bin_dir(), "../macro/"  , pch_module, ".mac", NULL);
   str_cat_va (ach_def, get_bin_dir(), "../macro/tmp/", pch_module, ".def", NULL);
   str_cat_va (ach_map, get_bin_dir(), "../macro/tmp/", pch_module, ".map", NULL);

   if ( fh_def=fopen(ach_def,"wt"), !fh_def) open_error(ach_def);
   if ( fh_map=fopen(ach_map,"wt"), !fh_def) open_error(ach_map);
   if ( yyin  =fopen(ach_src,"rt"), !yyin  ) open_error(ach_src);

   fprintf(fh_map,"static cls_mac_mapper mac_mapper[] =\n{\n");

   while ( token = yylex() , token != 0 )
   {
      if (token == def_tk_ident)
      {
         if (!search_id(lex_val_ach))
         {
            regi_id(lex_val_ach);
            fprintf(fh_def,"#define def_pdfid_%s\t0x%lx\n", lex_val_ach,--cnt);
            fprintf(fh_map,"   {def_pdfid_%s, %s%s},\n", lex_val_ach, pch_prefix, lex_val_ach);
         }
         //puts (lex_val_ach);
         fflush(stdout);
      }
      else
      {
         put_msg("unknown token\n");
         pcs_exit(1);
      }
   }
   fprintf(fh_map,"   {0, NULL}\n};\n");

   return 0;
}

