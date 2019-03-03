                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/process.hpp
   copyright(c) kyuhyun park
   1993.02.02
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_process_hpp
#error 'pub/process.hpp' duplicated.
#endif

#define def_pub_process_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#if defined def_watcomc
#include <except.h>
#include <process.h>
#endif

#if defined def_borlandc
#include <except.h>
#include <process.h>
#endif

#if defined def_ibmc
#include <unexpect.h>
#include <terminat.h>
#include <process.h>
#endif

class cls_xmsg
{
   private:
      static char info_ach[];

   public:

      cls_xmsg (char*);

      void  add_info(char*);

      char* get_info()
      {
         return info_ach;
      }
};

#define mac_define_xmsg1(derived)\
   class cls_xmsg_##derived : public cls_xmsg\
   { public: cls_xmsg_##derived (char* info) : cls_xmsg (info) {} }

#define mac_define_xmsg2(base, derived)\
   class cls_xmsg_##derived : public cls_xmsg_##base\
   { public: cls_xmsg_##derived (char* info) : cls_xmsg_##base (info) {} }
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void put_msg (char* ...);
void log_msg (char* ...);
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#ifdef def_debug
   #define mac_assert(exp) ( (exp) ? nothing : assert_failed (__FILE__,__LINE__,#exp) )
#else
   #define mac_assert(exp) nothing
#endif

#define mac_rtcheck(exp) ( (exp) ? nothing : assert_failed (__FILE__,__LINE__,#exp) )
#define mac_halt() (assert_failed (__FILE__,__LINE__,halt_ach))

extern char halt_ach[];

void assert_failed (char* fname, int lnum, char* msg);
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

char* get_err_msg();
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

extern int argc;
extern char** argv;

#if defined def_pm
extern HAB hab;
extern HMQ hmq;
extern QMSG qmsg;
void msg_broker();
#endif

void pcs_exit (int = 0);
void pcs_abort ();
int  begin_thread(void (*pnt_start)(void*), unsigned uint_size_stack, void*);

int pcs_main();
