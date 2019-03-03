                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/main.cpp
   copyright(c) kyuhyun park
   1994.11.06
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/lex.hpp>
#include <pub/dir.hpp>

#include <mc/glb.hpp>

void cmd_line_error()
{
   put_msg("usage:mc ...\n");
   throw cls_xmsg("func: mc/main.cpp/cmd_line_error()\ninfo: command line error\n");
}

void parse_cmd_line()
{
   if (argc < 2) cmd_line_error();

   char base_ach[512];
   char tmp_ach[512];

   strcpy (base_ach, get_bin_dir());
   strcat (base_ach,"..\\macro\\");

   int inx = 1;

   while (inx < argc)
   {
      cls_fname fname(argv[inx]);

      if (stricmp(fname.get_ext(),"") == 0 || stricmp(fname.get_ext(),".mac") == 0)
      {
         strcpy(mac_fname_ach, fname.get_name());
         strcat(mac_fname_ach, ".mac");
         if (bin_fname_ach[0] == 0)
         {
            strcpy(bin_fname_ach, fname.get_name());
            strcat(bin_fname_ach, ".bin");
         }
      }
      ef (stricmp(fname.get_ext(),".bin") == 0)
      {
         strcpy(bin_fname_ach, fname.get_name());
         strcat(bin_fname_ach, ".bin");
      }
      ef (stricmp(fname.get_ext(),".kn") == 0)
      {
         strcpy(key_name_fname_ach, fname.get_name());
         strcat(key_name_fname_ach, ".kn");
      }
      else
      {
         cmd_line_error();
      }

      inx++;
   }

   if (mac_fname_ach[0] == 0 || bin_fname_ach[0] == 0) cmd_line_error();

   strcpy(tmp_ach, key_name_fname_ach);
   strcpy(key_name_fname_ach, base_ach);
   strcat(key_name_fname_ach, tmp_ach);

   strcpy(tmp_ach, mac_fname_ach);
   strcpy(mac_fname_ach, base_ach);
   strcat(mac_fname_ach, tmp_ach);

   strcpy(tmp_ach, bin_fname_ach);
   strcpy(bin_fname_ach, base_ach);
   strcat(bin_fname_ach, tmp_ach);
}

void open_error(char* pch_fname)
{
   put_msg("\nfile : %s\ninfo : file open error\n", pch_fname);
   pcs_exit(1);
}

int pcs_main()
{
   try
   {
      parse_cmd_line();
      read_key_name_file();
      compile_mac_file();
   }
   catch (cls_xmsg msg)
   {
      put_msg(msg.get_info());
      yyerror("");
   }
   return 0;
}
