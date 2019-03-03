                                                                                                                        /*
--------------------------------------------------------------------------------
   win\spcdlg.hpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#ifdef def_win_spcdlg_hpp
#error 'win\spcdlg.hpp' duplicated.
#endif

#define def_win_spcdlg_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#define def_spc_page_cmax 256

class cls_spc_dlg
{
   public:

      HWND parent;
      int x;
      int y;
      HWND owner;

      char16 contents[def_spc_page_cmax];
      int cnt;

   public:

      cls_spc_dlg(HWND arg_parent, int arg_x, int arg_y, HWND arg_owner);

      void execute();
};
