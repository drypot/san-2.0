#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <win/hnjdlg.hpp>

int pcs_main()
{
   cls_hnj_dlg hnj_dlg(HWND_DESKTOP, 10, 10, NULL);

   cls_wchar wchar(0x8861);
   hnj_dlg.execute(&wchar);

   return 0;
}
