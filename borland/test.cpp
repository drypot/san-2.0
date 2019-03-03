#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

int pcs_main()
{
   cls_spc_dlg spc_dlg;

   do
   {
      spc_dlg.excute();
   }
   while (spc_dlg.cnt);
}
