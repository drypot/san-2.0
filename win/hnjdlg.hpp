                                                                                                                        /*
--------------------------------------------------------------------------------
   win\hnjdlg.hpp
   copyright(C) kyuhyun park
   1990.
--------------------------------------------------------------------------------                                        */

#ifdef def_win_hnjdlg_hpp
#error 'win\hnjdlg.hpp' duplicated.
#endif

#define def_win_hnjdlg_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

class cls_hnj_dlg
{
   public:

      HWND parent;
      int x;
      int y;
      HWND owner;

   public:

      cls_hnj_dlg(HWND arg_parent, int arg_x, int arg_y, HWND arg_owner);

      void execute(cls_wchar*);
};

