                                                                                                                        /*
--------------------------------------------------------------------------------
   text/mode.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

//#include <key/mcp.hpp>
//#include <key/mac.hpp>

#include <text/glb.hpp>

void pdf_code_set_wansung()
{
   if (cdoc->code_type != def_ct_wansung)
   {
      cdoc->code_type = def_ct_wansung;
      cdoc->set_modified(def_yes);
      sline_invalidate();
   }
}

void pdf_code_set_johab()
{
   if (cdoc->code_type != def_ct_johab)
   {
      cdoc->code_type = def_ct_johab;
      cdoc->set_modified(def_yes);
      sline_invalidate();
   }
}

int32 pdf_code_is_johab()
{
   return cdoc->code_type == def_ct_johab;
}

#define make_mode_pdf(name) \
   void pdf_mode_set_##name() { name##_flg = mac_runner->get_arg_i32(0); sline_invalidate(); } \
   int32 pdf_mode_is_##name() { return name##_flg; }

make_mode_pdf(insert)
make_mode_pdf(indent)
make_mode_pdf(unindent)
make_mode_pdf(wrap)
make_mode_pdf(show_match)
make_mode_pdf(smart_tab)
