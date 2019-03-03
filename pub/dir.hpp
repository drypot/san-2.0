                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/dir.hpp
   copyright(c) kyuhyun park
   1991.04.04
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_dir_hpp
#error 'pub/dir.hpp' duplicated.
#endif

#define def_pub_dir_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#if defined def_gnuc
#include <dirent.h>
#endif

#if defined def_borlandc
#include <dirent.h>
#include <dir.h>
#endif

#if defined def_watcomc
#include <direct.h>
#endif

#if defined def_ibmc
#include <direct.h>
#endif

#if defined def_borlandc
   #define def_fn_path_max    MAXPATH
   #define def_fn_drive_max   MAXDRIVE
   #define def_fn_dir_max     MAXDIR
   #define def_fn_name_max    MAXFILE
   #define def_fn_ext_max     MAXEXT
#elif defined def_watcomc || defined def_ibmc
   #define def_fn_path_max    _MAX_PATH
   #define def_fn_drive_max   _MAX_DRIVE
   #define def_fn_dir_max     _MAX_DIR
   #define def_fn_name_max    _MAX_FNAME
   #define def_fn_ext_max     _MAX_EXT
#endif

class cls_fname
{
   private:
      static char stt_path_ach [def_fn_path_max ];
      static char stt_drive_ach[def_fn_drive_max];
      static char stt_dir_ach  [def_fn_dir_max  ];
      static char stt_name_ach [def_fn_name_max ];
      static char stt_ext_ach  [def_fn_ext_max  ];

      static char stt_drive_dir_ach [def_fn_drive_max + def_fn_dir_max - 1];
      static char stt_name_ext_ach  [def_fn_name_max  + def_fn_ext_max - 1];

      char* path_pch; /* instance path */

      void split();
      void merge();

    public:

       cls_fname       ();
       cls_fname       (char*);
      ~cls_fname       ();

       void reset         ();
       bool is_null       ();

       void set_path       (char*);
       void set_drive      (char*);
       void set_dir        (char*);
       void set_name       (char*);
       void set_ext        (char*);

       void set_drive_dir   (char*);
       void set_name_ext    (char*);

       char* get_path      ();
       char* get_drive     ();
       char* get_dir       ();
       char* get_name      ();
       char* get_ext       ();

       char* get_drive_dir  ();
       char* get_name_ext   ();
};

inline cls_fname::cls_fname() : path_pch(NULL)
{
}

inline cls_fname::cls_fname(char* arg_path) : path_pch(NULL)
{
   set_path (arg_path);
}

inline bool cls_fname::is_null()
{
   return path_pch == NULL;
}

inline char* cls_fname::get_path()
{
   mac_assert (path_pch);
   return path_pch;
}
