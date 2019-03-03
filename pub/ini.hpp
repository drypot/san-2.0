                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/ini.hpp
   copyright(c) kyuhyun park
   1995.12.17
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_ini_hpp
#error 'pub/ini.hpp' duplicated.
#endif

#define def_pub_ini_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

enum
{
   def_ini_null,
   def_ini_ignore,
   def_ini_int,
   def_ini_pch,
   def_ini_path,
   def_ini_func_pch,
   def_ini_func_path,
   def_ini_bool
};

struct cls_ini_item_desc
{
   char* name_pch;
   int   type_int;
   void* var_pnt;
};

void parse_ini (char*, cls_ini_item_desc*);

