																																								/*
--------------------------------------------------------------------------------
   fnt/engfnt.cpp
	copyright(C) kyuhyun park
	1991.
-------------------------------------------------------------------------------- 													*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <pub/dir.hpp>
#include <pub/init.hpp>
#include <cnt/array.hpp>
#include <fnt/engfnt.hpp>

type_fnt8 eng_fnt8_ary[256];
char* eng_fnt_fname_pch;

static void load_eng_fnt (char* pnt_fname)
{
   const sz = sizeof(type_fnt8) * 256;
   cls_rfile rfile(pnt_fname);
   tem_array<byte> byte_array(sz);

   rfile.read (byte_array.get_base() , sz);
   memcpy (eng_fnt8_ary , byte_array.get_base() , sz);
}

static void ctor()
{
   cls_fname fname;

   try
   {
      fname.set_path(eng_fnt_fname_pch != NULL ? eng_fnt_fname_pch : "@bindir/../font/sanigj.eng");
      load_eng_fnt(fname.get_path());
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info(cls_form_expander("func: fnt/engfnt.cpp/ctor\ninfo: font loading error\nfile: %s\n",fname.get_path()).get_pch());
      throw;
   }
}

static cls_initer initer(ctor, def_init_pri_fnt_engfnt);
