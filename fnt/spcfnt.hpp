																																								/*
--------------------------------------------------------------------------------
   fnt/spcfnt.hpp
	copyright(C) kyuhyun park
	1991.
-------------------------------------------------------------------------------- 													*/

#ifdef def_fnt_spcfnt_HPP
#error 'fnt/spcfnt.hpp' duplicated.
#endif

#define def_fnt_spcfnt_HPP

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_fnt_fnt_hpp
#include <fnt/fnt.hpp>
#endif

extern char* sp1_fnt_fname_pch;
extern char* sp2_fnt_fname_pch;

void load_spc_fnt (char*,char*);
void load_sp1_fnt (char*);
void load_sp2_fnt (char*);

type_fnt16* get_spc_fnt (char16);

