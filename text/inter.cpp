                                                                                                                        /*
--------------------------------------------------------------------------------
   text/inter.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#if defined def_dos

#include <pub/misc.hpp>
#include <pub/signal.hpp>

#include <key/key.hpp>
#include <dlg/user.hpp>

#include <text/glb.hpp>

int __far criti_err_handler ( unsigned deverr, unsigned errcode, unsigned far *devhdr)
{
   touch(deverr);
   touch(errcode);
   touch(devhdr);
   static char* msg[]=
   {
      "write-protect error",
      "unknown unit",
      "drive ont ready",
      "unknown command",
      "data error",
      "bad request structure length",
      "seek error",
      "unknown media type",
      "sector not found",
      "printer out of paper_",
      "write fault",
      "read fault",
      "general failure",
      "unknown error",
      "unknown error",
      "invalid disk change"
      "unknown error",
   };

   static char err_str[128];
   int index = errcode & 0x00FF;
   bool yesno_f = def_yes;

   if ( index >= mac_cnt_of(msg) ) index = mac_cnt_of(msg)-1;

   sprintf((char*) err_str ,"DOS Critical Error ( %s ) Retry? (def_yes/no)", msg[index] );
   forever
   {
      if (user_yes_no(mline_win,err_str,&yesno_f) == def_ok) return yesno_f ? _HARDERR_RETRY : _HARDERR_FAIL;
   }
}

void set_int_vector()
{

   signal (SIGBREAK, SIG_IGN);
   signal (SIGINT, SIG_IGN);

   #if PLATFORM_DOS
      union REGS regs;

      _harderr(criti_err_handler);
      regs.w.ax = 0x3301;
      regs.h.dl = 0;
      intdos(&regs,&regs);
   #endif
}

void restore_int_vector()
{
}

#endif

