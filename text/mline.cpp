                                                                                                                        /*
--------------------------------------------------------------------------------
   text/mline.cpp
	copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

#define def_auto_erase_cmax 3

static int auto_erase_cnt;
static bool auto_erase_flg;
static char* msg_pch;

void mline_set_msg(char* pch)
{
   if (msg_pch)
   {
      mem_free(msg_pch);
      msg_pch = NULL;
   }
   if (pch)
   {
      msg_pch = str_dup(pch);
   }
}

void mline_clear()
{
   mline_set_msg(NULL);
   mline->set_x(0);
   mline->erase_to_eol();
   auto_erase_flg = def_no;
   mline_draw();
}

void mline_write(char* pch, bool arg_auto_erase_flg)
{
   mline_set_msg(pch);
   mline->set_x(0);
   mline->write(msg_pch);
   mline->erase_to_eol();
   auto_erase_cnt = 0;
   auto_erase_flg = arg_auto_erase_flg;
   mline_draw();
}

void mline_write(int msg_num, bool arg_auto_erase_flg)
{
   mline_write(msg_get(msg_num), arg_auto_erase_flg);
}

void mline_write_error()
{
   mline_write(get_err_msg(), def_yes);
}

void mline_update()
{
   mline->set_x(0);
   if (msg_pch) mline->write(msg_pch);
   mline->erase_to_eol();
}

void mline_draw(HPS hps)
{
   mline->draw(hps,0,0);
}

void mline_draw()
{
   HPS hps = WinGetPS(client_hwnd);
   mline_draw(hps);
   WinReleasePS(hps);
}

void mline_wm_timer()
{
   if (auto_erase_flg)
   {
      if ( ++auto_erase_cnt > def_auto_erase_cmax )
      {
         mline_clear();
      }
   }
}

