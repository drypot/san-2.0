                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/process.cpp
   copyright(c) kyuhyun park
   1993.02.02
-------------------------------------------------------------------------------- 													*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/stdarg.hpp>
#include <pub/misc.hpp>
#include <pub/init.hpp>

int    argc;
char** argv;
char   cls_xmsg::info_ach[512];

#if defined def_pm && !defined def_owl
HAB   hab;
HMQ   hmq;
QMSG  qmsg;
#endif

cls_xmsg::cls_xmsg (char* arg_info_pch)
{
   strcpy (info_ach, "\nexception message\n");
   add_info(arg_info_pch);
}

void cls_xmsg::add_info(char* arg_info_pch)
{
   if (strlen(info_ach) + strlen(arg_info_pch) + 1 >= sizeof(info_ach))
   {
      put_msg ("\noverflow @cls_xmsg::add_info\n");
      pcs_abort();
   }
   strcat (info_ach, arg_info_pch);
   strcat (info_ach, "\n");
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void put_msg (char* form ...)
{
   char msg_ach [1024];
   va_list arg_list;

   va_start(arg_list, form);
   vsprintf(msg_ach, form, arg_list);
   va_end(arg_list);

   if (strlen(msg_ach) >= sizeof(msg_ach))
   {
      log_msg ("\noverflow @put_msg\n");
      pcs_abort();
   }

#if defined def_pm || defined def_win
   log_msg(msg_ach);
#else
   fprintf(stderr, msg_ach);
   fflush(stderr);
#endif
}

void log_msg (char* form ...)
{
   static FILE* log_file;
   va_list arg_list;

   va_start(arg_list,form);
   if (log_file == NULL) log_file = fopen ("log", "w");
   vfprintf(log_file, form, arg_list);
   fflush(log_file);
   va_end(arg_list);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

char halt_ach[] = "impossible condition";

void assert_failed (char* pch_fname, int int_lnum, char* pch_exp)
{
   static char form[] = "\nmac_assert failed\nfile: %s\nline: %d\nexpr: %s\n";
   static bool reenterance_flg = def_no;

   if (!reenterance_flg)
   {
      reenterance_flg = def_yes;
      log_msg (form, pch_fname, int_lnum, pch_exp);
      pcs_exit(1);
   }
   else
   {
      put_msg("\nmac_assert failed again\n");
      put_msg(form, pch_fname, int_lnum, pch_exp);
      pcs_abort();
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

char* get_err_msg()
{
   static char buf[128];

   strncpy(buf, strerror(errno), sizeof(buf));
   buf[sizeof(buf)-1] = 0;
   size_t sz = strlen(buf);
   if (sz && buf[ sz - 1 ] == '\n') buf [ sz - 1 ] = 0;
   return buf;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pcs_exit(int exitCode)
{
   exit(exitCode);
}

void pcs_abort(void)
{
   put_msg("system aborted.\n");

#if defined def_watcomc && defined def_dos

   /* Watcom's abort fuction behaves like */
   /* other compilers exit fuction */

   REGS r;
   r.w.ax = 0x4cff;
   int386(0x21,&r,&r);

#else

   abort();

#endif
}

int begin_thread(void (*pnt_start)(void*), uint uint_size_stack, void* pnt_args)
{
#ifdef def_borlandc
   return _beginthread(pnt_start, uint_size_stack, pnt_args);
#endif

#ifdef def_watcomc
   return _beginthread(pnt_start, NULL, uint_size_stack, pnt_args);
#endif
}

#if defined def_pm && !defined def_owl

void msg_broker()
{
   while (WinGetMsg (hab, &qmsg, 0, 0, 0)) WinDispatchMsg (hab, &qmsg);
}

#endif

static void not_caught_exception_handler()
{
   put_msg("\nnot caught exception.\n");
   pcs_exit(1);
}

static void unexpected_exception_handler()
{
   put_msg("\nunexpected exception.\n");
   pcs_exit(1);
}

#if defined def_ibmc
static void _Optlink shutdown_process()
#else
static void shutdown_process()
#endif
{
   static bool checked_flg = def_no;

   try
   {
      if (checked_flg)
      {
         put_msg ("\nreentrance @shutdown_process\n");
         pcs_abort();
      }
      else
      {
         checked_flg = def_yes;
         cls_finiter::execute();

#if defined def_pm && ! defined def_owl
         WinDestroyMsgQueue(hmq);
         WinTerminate(hab);
#endif
      }
   }
   catch (cls_xmsg xmsg)
   {
      put_msg(xmsg.get_info());
      pcs_abort();
   }
}

static void boot_process()
{
   set_terminate ( not_caught_exception_handler );
   set_unexpected ( unexpected_exception_handler );

   atexit (shutdown_process);

#if defined def_pm && !defined def_owl
   hab = WinInitialize (0);
   hmq = WinCreateMsgQueue (hab, 0);
#endif

   cls_initer::execute();
}

#if defined def_owl
int OwlMain(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
   int ret_val = 0;

   ::argc = argc;
   ::argv = argv;

   try
   {
      boot_process();
      ret_val = pcs_main();
   }
   catch (cls_xmsg xmsg)
   {
      put_msg(xmsg.get_info());
      ret_val = 1;
   }

   return ret_val;
}
