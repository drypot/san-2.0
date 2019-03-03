                                                                                                                        /*
--------------------------------------------------------------------------------
   fnt/spcfnt.cpp
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
#include <fnt/nulfnt.hpp>
#include <fnt/spcfnt.hpp>

#define def_sp1_fnt_cnt 128
#define def_sp2_fnt_cnt 1128

#define def_fnt_size sizeof(type_fnt16)

#define def_sp1_fnt_file_size ( def_sp1_fnt_cnt * def_fnt_size )
#define def_sp2_fnt_file_size ( def_sp1_fnt_cnt * def_fnt_size )

static tem_static_array<type_fnt16,def_sp1_fnt_cnt> sp1_fnt16_array;
static tem_static_array<type_fnt16,def_sp2_fnt_cnt> sp2_fnt16_array;
char* sp1_fnt_fname_pch;
char* sp2_fnt_fname_pch;

void load_spc_fnt( char* arg_sp1_fname , char* arg_sp2_fname )
{
   load_sp1_fnt ( arg_sp1_fname );
   load_sp2_fnt ( arg_sp2_fname );
}

void load_sp1_fnt( char* arg_sp1_fname )
{
   if (arg_sp1_fname != NULL)
   {
      cls_rfile rfile(arg_sp1_fname);
      rfile.read (sp1_fnt16_array.get_base_pnt(), def_sp1_fnt_file_size);
      mac_assert (sp1_fnt16_array.check());
   }
}

void load_sp2_fnt( char* arg_sp2_fname )
{
   if (arg_sp2_fname != NULL)
   {
      static int map_int_ary[]=
      {
         -1, 93,
         69, -25,
         94,
         94,
         10, -5, 10, -7, 24, -8, 24,-6,
         68, -26,
         79, -15,
         94,
         94,
         83, -11,
         86, -8,
         33, -15, 33,
         0
      };

      cls_rfile rfile(arg_sp2_fname);
      int map_inx = 0;
      int fnt_inx = 0;
      int cnt;

      while ((cnt = map_int_ary[map_inx++]) != 0)
      {
         if (cnt > 0)
         {
            rfile.read(sp2_fnt16_array.get_base_pnt() + fnt_inx, cnt * def_fnt_size);
         }
         else
         {
            cnt = -cnt;
         }
         fnt_inx += cnt;
      }
      mac_assert(sp2_fnt16_array.check());
   }
}

type_fnt16* get_spc_fnt(char16 ch)
{
   int inx;

   inx = sp2_to_cardi(ch);
   if (inx != -1) return sp2_fnt16_array.get_base_pnt() + inx;

   inx = sp1_to_cardi(ch);
   if (inx != -1) return sp1_fnt16_array.get_base_pnt() + inx;

   return get_nul_fnt();
}

static void ctor()
{
   cls_fname fname;

   try
   {
      fname.set_path(sp1_fnt_fname_pch != NULL ? sp1_fnt_fname_pch : "@bindir/../font/sys.spc");
      load_sp1_fnt(fname.get_path());

      fname.set_path(sp2_fnt_fname_pch != NULL ? sp2_fnt_fname_pch : "@bindir/../font/roman_c.sp2");
      load_sp2_fnt(fname.get_path());
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info(cls_form_expander("func: fnt/spcfnt.cpp/ctor()\ninfo: font loading error\nfile: %s\n",fname.get_path()).get_pch());
      throw;
   }
}

static cls_initer initer(ctor, def_init_pri_fnt_spcfnt);
