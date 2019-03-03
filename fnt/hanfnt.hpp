																																								/*
--------------------------------------------------------------------------------
   fnt/hanfnt.hpp
	copyright(C) kyuhyun park
	1991.
-------------------------------------------------------------------------------- 													*/

#ifdef def_fnt_han_fnt_hpp
#error 'fnt/hanfnt.hpp' duplicated.
#endif

#define def_fnt_han_fnt_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_char_hpp
#include <pub/char.hpp>
#endif

#ifndef def_fnt_fnt_hpp
#include <fnt/fnt.hpp>
#endif

extern char* han_fnt_fname_pch;

void load_han_fnt(char*);
type_fnt16* get_han_fnt(cls_wchar);

