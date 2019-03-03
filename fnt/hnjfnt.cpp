                                                                                                                        /*
--------------------------------------------------------------------------------
   fnt/hnjfnt.cpp
   copyright(C) kyuhyun park
   1992.07.17
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/misc.hpp>
#include <pub/io.hpp>
#include <pub/dir.hpp>
#include <pub/init.hpp>
#include <fnt/nulfnt.hpp>
#include <fnt/hanfnt.hpp>
#include <fnt/hnjfnt.hpp>

#define def_fnt_cnt 4888
#define def_fnt_size sizeof(type_fnt16)
#define def_fnt_file_size (def_fnt_size*def_fnt_cnt)

type_fnt16 hnj_fnt16_ary [def_fnt_cnt];
bool hnj_fnt_avail_flg;

static type_fnt16* __get_hnj_fnt (cls_wchar);
static type_fnt16* __get_han_fnt (cls_wchar);

static type_fnt16* (*get_fnt_func) (cls_wchar) = __get_han_fnt;
char* hnj_fnt_fname_pch;

static type_fnt16* __get_hnj_fnt (cls_wchar wch)
{
   mac_assert (hnj_fnt_avail_flg);

   int inx = hnj_to_cardi(wch);
   return inx == -1 ? get_nul_fnt() : hnj_fnt16_ary + inx;
}

static type_fnt16* __get_han_fnt (cls_wchar /*wch*/)
{
   /*
   wch.to_Hangul();
   return Han_fnt(wch);
   */
   return get_nul_fnt();
}

type_fnt16* get_hnj_fnt(cls_wchar wch)
{
   return get_fnt_func(wch);
}

void load_hnj_fnt(char* fname)
{
   mac_assert(!hnj_fnt_avail_flg);

   cls_rfile rfile(fname);
   rfile.read (hnj_fnt16_ary, def_fnt_file_size);
   get_fnt_func = __get_hnj_fnt;
   hnj_fnt_avail_flg = def_yes;
}

bool is_hnj_fnt_avail()
{
   return hnj_fnt_avail_flg;
}

static void ctor()
{
   cls_fname fname(hnj_fnt_fname_pch ? hnj_fnt_fname_pch : "@bindir/../font/normal.hnj");

   try
   {
      load_hnj_fnt(fname.get_path());
   }
   catch (cls_xmsg xmsg)
   {
      //xmsg.add_info(cls_form_expander("func: fnt/hnjfnt.cpp/ctor()\ninfo: font loading error\nfile: %s\n",fname.get_path()).get_pch());
      //throw;
   }
}

static cls_initer initer(ctor, def_init_pri_fnt_hnjfnt);
