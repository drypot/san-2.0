                                                                                                                        /*
--------------------------------------------------------------------------------
   fnt/nulfnt.hpp
   copyright(C) kyuhyun park
   1994.07.07
--------------------------------------------------------------------------------                                        */

#ifdef def_fnt_nulfnt_hpp
#error 'fnt/nulfnt.hpp' duplicated.
#endif

#define def_fnt_nulfnt_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_fnt_fnt_hpp
#include <fnt/fnt.hpp>
#endif

extern type_fnt16 nul_fnt16;

inline type_fnt16* get_nul_fnt()
{
   return &nul_fnt16;
}



