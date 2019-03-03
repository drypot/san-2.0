#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <win/spcdlg.hpp>

int pcs_main()
{
   cls_spc_dlg spc_dlg(HWND_DESKTOP, 10, 10, NULL);

   do
   {
      spc_dlg.execute();
   }
   while (spc_dlg.cnt);

   return 0;
}
