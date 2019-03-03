                                                                                                                        /*
--------------------------------------------------------------------------------
   fnt/hnjfnt.hpp
   copyright(C) kyuhyun park
   1992.07.17
--------------------------------------------------------------------------------                                        */

#ifdef def_fnt_hnjfnt_hpp
#error 'fnt/hnjfnt.hpp' duplicated.
#endif

#define def_fnt_hnjfnt_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_char_hpp
#include <pub/char.hpp>
#endif

#ifndef def_fnt_fnt_hpp
#include <fnt/fnt.hpp>
#endif

extern char* hnj_fnt_fname_pch;

void        load_hnj_fnt(char*);
type_fnt16* get_hnj_fnt(cls_wchar);
bool        is_hnj_fnt_avail();
