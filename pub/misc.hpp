                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/misc.hpp
   copyright(c) kyuhyun park
   1990
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_misc_hpp
#error 'pub/misc.hpp' duplicated.
#endif

#define def_pub_misc_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#if defined def_borlandc
#include <dos.h>
#endif

#if defined def_watcomc
#include <dos.h>
   #if defined def_dos
      #include <i86.h>
      #include <bios.h>
   #endif
#endif

void beep();

#if defined def_pm
   void set_frame_size_from_client(HWND, int, int);
   void set_frame_pos_center(HWND);
   void set_frame_activate(HWND);
#endif
