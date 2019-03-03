																																								/*
--------------------------------------------------------------------------------
   fnt/engfnt.hpp
	copyright(C) kyuhyun park
	1991.
-------------------------------------------------------------------------------- 													*/

#ifdef def_fnt_eng_fnt_hpp
#error 'fnt/engfnt.hpp' duplicated.
#endif

#define def_fnt_eng_fnt_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_fnt_fnt_hpp
#include <fnt/fnt.hpp>
#endif

extern type_fnt8 eng_fnt8_ary[];
extern char* eng_fnt_fname_pch;

void load_eng_fnt (char*);

inline type_fnt8* get_eng_fnt (char16 ch)
{
   return eng_fnt8_ary + ch;
}

