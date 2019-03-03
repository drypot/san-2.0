                                                                                                                       /*
--------------------------------------------------------------------------------
   text/test.cpp
   copyright(c) kyuhyun park
   1991.
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

void pdf_test1()
{
   mline_clear();
}

void pdf_test2()
{
   mline_write("Hello", def_yes);
}

void pdf_test3()
{
   mline_write("Hello Static");
}

void pdf_test4()
{
   put_msg("%d", mac_runner->get_arg_cnt());
}

void pdf_test5()
{
   WinMessageBox(
      HWND_DESKTOP,
      client_hwnd,
      "pdf_test5",
      "!",
      0,
      MB_OK | MB_APPLMODAL | MB_MOVEABLE
   );
}

