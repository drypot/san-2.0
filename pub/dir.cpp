                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/dir.cpp
   copyright(C) kyuhyun park
   1991.04.04
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/dir.hpp>

#if defined def_borlandc
   #define mac_split fnsplit
   #define mac_merge fnmerge
   #define mac_expand _fullpath
#endif

#if defined def_watcomc
   #define mac_split _splitpath
   #define mac_merge _makepath
   #define mac_expand _fullpath
#endif

#if defined def_ibmc
   #define mac_split _splitpath
   #define mac_merge _makepath
   #define mac_expand _fullpath
#endif

char cls_fname::stt_path_ach [def_fn_path_max ];
char cls_fname::stt_drive_ach[def_fn_drive_max];
char cls_fname::stt_dir_ach  [def_fn_dir_max  ];
char cls_fname::stt_name_ach [def_fn_name_max ];
char cls_fname::stt_ext_ach  [def_fn_ext_max  ];

char cls_fname::stt_drive_dir_ach[def_fn_drive_max + def_fn_dir_max - 1];
char cls_fname::stt_name_ext_ach [def_fn_name_max  + def_fn_ext_max - 1];

cls_fname::~cls_fname()
{
   if (path_pch) mem_free(path_pch);
}

void cls_fname::split()
{
   mac_assert(path_pch);
   mac_split (path_pch, stt_drive_ach, stt_dir_ach, stt_name_ach, stt_ext_ach);
}

void cls_fname::merge()
{
   mac_merge (stt_path_ach, stt_drive_ach, stt_dir_ach, stt_name_ach, stt_ext_ach);
   set_path (stt_path_ach);
}

void cls_fname::reset()
{
   if (path_pch) mem_free (path_pch);
   path_pch = NULL;
}

void cls_fname::set_path(char* arg_path)
{
   bool  trail_slash_flg = def_no;
   char  buf_ach [def_fn_path_max];
   int   len;

   if (strncmp(arg_path, "@bindir", 7) == 0)
   {
      strcpy (buf_ach, get_bin_dir());
      strcat (buf_ach, arg_path + 7);
   }
   else
   {
      strcpy (buf_ach, arg_path);
   }
   len = strlen(buf_ach);
   mac_rtcheck (len < sizeof(buf_ach));
   if (len && (buf_ach[len-1] == '/' || buf_ach[len-1] == '\\'))
   {
      trail_slash_flg = def_yes;
      buf_ach[len-1] = 0;
   }
   if (!mac_expand(stt_path_ach, buf_ach, sizeof(stt_path_ach)))
   {
      strcpy(stt_path_ach, buf_ach);
   }
   if (trail_slash_flg) strcat(stt_path_ach, "/");

   reset();
   path_pch = str_dup(stt_path_ach);
}

void cls_fname::set_drive(char* _drive)
{
   mac_assert(strlen(_drive) < def_fn_drive_max);

   split();
   strcpy (stt_drive_ach, _drive);
   merge();
}

void cls_fname::set_dir(char* _dir)
{
   mac_assert(strlen(_dir) < def_fn_dir_max);

   split();
   strcpy (stt_dir_ach, _dir);
   merge();
}

void cls_fname::set_name(char* _name)
{
   mac_assert(strlen(_name) < def_fn_name_max);

   split();
   strcpy (stt_name_ach, _name);
   merge();
}

void cls_fname::set_ext (char* _ext)
{
   mac_assert(strlen(_ext) < def_fn_ext_max);

   split();
   strcpy (stt_ext_ach, _ext);
   merge();
}

void cls_fname::set_drive_dir(char* _drive_dir)
{
   mac_assert(strlen(_drive_dir) < def_fn_drive_max+def_fn_dir_max-1);

   split();
   mac_merge(stt_path_ach, _drive_dir, NULL, stt_name_ext_ach, stt_ext_ach);
   set_path(stt_path_ach);
}

void cls_fname::set_name_ext(char* _name_ext)
{
   mac_assert(strlen(_name_ext) < def_fn_name_max+def_fn_ext_max-1);

   split();
   mac_merge(stt_path_ach, stt_drive_ach, stt_dir_ach, _name_ext, NULL);
   set_path(stt_path_ach);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

char* cls_fname::get_drive()
{
   split();
   return stt_drive_ach;
}

char* cls_fname::get_dir()
{
   split();
   return stt_dir_ach;
}

char* cls_fname::get_name()
{
   split();
   return stt_name_ach;
}

char* cls_fname::get_ext()
{
   split();
   return stt_ext_ach;
}

char* cls_fname::get_drive_dir()
{
   split();
   strcpy(stt_drive_dir_ach, stt_drive_ach);
   strcat(stt_drive_dir_ach, stt_dir_ach);
   return stt_drive_dir_ach;
}

char* cls_fname::get_name_ext()
{
   split();
   strcpy(stt_name_ext_ach, stt_name_ach);
   strcat(stt_name_ext_ach, stt_ext_ach);
   return stt_name_ext_ach;
}
