                                                                                                                        /*
--------------------------------------------------------------------------------
   text/os.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/misc.hpp>
#include <text/glb.hpp>

#define CMD_STR_CMAX 128

static bool wait_f;
static char cmd_str[CMD_STR_CMAX];
static char* pw;
static char* pe;
static bool exit_f;
static char shell_prompt_str[64];

static void cmd_str_add(char* p)
{
   int len = strlen(p);
   if (pw + len > pe)
   {
      cmd_str[0] = 0;
      exit_f = def_yes;
   }
   else
   {
      strcpy (pw, p);
      pw += len;
   }
}

static void cmd_str_add(char ch)
{
   if (pw == pe)
   {
      cmd_str[0] = 0;
      exit_f = def_yes;
   }
   else *pw++ = ch;
}

static bool cmd_str_set(char* p)
{
   pw = cmd_str;
   pe = cmd_str + CMD_STR_CMAX - 1;
   exit_f = def_no;

   while (*p && !exit_f)
   {
      if (*p == '%')
      {
         switch (tolower(*(p+1)))
         {
            case 'd' : cmd_str_add(cdoc->fname.Drive()); break;
            case 'i' : cmd_str_add(cdoc->fname.Dir()); break;
            case 'n' : cmd_str_add(cdoc->fname.Name()); break;
            case 'e' : cmd_str_add(cdoc->fname.Ext()); break;
            case 'p' : cmd_str_add(cdoc->fname.Path()); break;
            case '%' : cmd_str_add('%'); break;
            default  : cmd_str_add('%'); p--;
         }
         p += 2;
      }
      else cmd_str_add(*p++);
   }
   *pw = 0;
   return !exit_f;
}

static void system_off()
{
   EasyHanVioOff();
   EasyHanKeyOff();
   restore_int_vector();
}

static void system_on()
{
   set_int_vector();
   EasyHanKeyOn();
   if (wait_f)
   {
      printf("press a key...\n");
      KeyWaitmake_();
      KeyDiscard();
   }
   EasyHanVioOn();
   scn_invalidate();
}

void shell_prompt(char* p_new)
{
   char* p_prev = getenv("prompt");
   int p_prev_len = strlen(p_prev);
   char* p = shell_prompt_str;
   char* p_end = shell_prompt_str + sizeof(shell_prompt_str) - 1;

   while (*p_new && p < p_end)
   {
      if (*p_new == '*')
      {
         if (p + p_prev_len > p_end) break;
         strcpy(p, p_prev);
         p += p_prev_len;
         p_new++;
      }
      else *p++ = *p_new++;
   }
   *p = 0;
}

void shell_prompt_set_env()
{
   setenv("prompt",shell_prompt_str,1);
}

void pdf_os_fork_shell()
{
   wait_f = (bool) macro_argument(0);
   shell_prompt_set_env();
   system_off();
   system (getenv("comspec"));
   system_on();
}

void pdf_os_fork()
{
   char* p_cmd = (char*)macro_data_fetch(macro_argument(0));
   wait_f = (bool) macro_argument(1);

   if (cmd_str_set(p_cmd))
   {
      system_off();
      system (cmd_str);
      system_on();
   }
}

void pdf_os_fork_indicls_rect()
{
   static char buf[CMD_STR_CMAX];
   wait_f = (bool) macro_argument(0);

   if (user_str(mline_win,"DOS>",buf,sizeof(buf)))
   {
      if (cmd_str_set(buf))
      {
         system_off();
         system (cmd_str);
         system_on();
      }
   }
}
