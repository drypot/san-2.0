																																								/*
--------------------------------------------------------------------------------
   pub/env.cpp
	copyright(C) kyuhyun park
	1994.06.01
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/dir.hpp>
#include <pub/init.hpp>

static cls_fname bin_fname;
static char bin_dir_ach [def_fn_path_max];

static void set_bin_dir(char* p)
{
   bin_fname.set_path(p);
   strcpy (bin_dir_ach, bin_fname.get_drive_dir());
}

char* get_bin_dir()
{
   return bin_dir_ach;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void ctor()
{
   set_bin_dir(argv[0]);
}

static cls_initer initer(ctor, def_init_pri_pub_env);
