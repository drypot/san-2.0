                                                                                                                        /*
--------------------------------------------------------------------------------
   text/main.cpp
   copyright(c) kyuhyun park
   1991.
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

void pdf_quit()
{
   WinPostMsg(client_hwnd, WM_QUIT, 0, 0);
}

int pcs_main()
{
   frame_create();

   client_update();
   client_draw();

   doc_init();

   client_update();
   client_draw();

   msg_broker();
   frame_destroy();

   return 0;
}
