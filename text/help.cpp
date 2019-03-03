                                                                                                                        /*
--------------------------------------------------------------------------------
   text/help.cpp -- text help information
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/init.hpp>

#include <text/glb.hpp>

/*
static char* help_list[200];
static int help_list_cnt;
static int top;
static bool exit_f;
*/

/*
static void help_scn_update()
{
   int i;
   int y = top;
   forcnt(i,work_win_height)
   {
      tty_xy(0,i);
      if (y<help_list_cnt) tty_output(help_list[y]);
      tty_clear_rest();
      y++;
   }
}

void macro_excute_cback_help(uint32 id)
{
   switch (id)
   {
      case CURSOR_UP :
         if (top!=0) top--;
         break;

      case CURSOR_DOWN :
         if (top!=help_list_cnt-1) top++;
         break;

      case CURSOR_PAGE_UP :
         top-=work_win_height;
         if (top<0) top=0;
         break;

      case CURSOR_PAGE_DOWN :
         top+=work_win_height;
         if (top>=help_list_cnt) top=help_list_cnt-1;
         break;

      case CURSOR_HOME :
      case CURSOR_PAGE_UP_ACC :
         top = 0;
         break;

      case CURSOR_END :
      case CURSOR_PAGE_DOWN_ACC :
         top = help_list_cnt - 1;
         break;

      case ENTER :
      case CANCEL :
         exit_f = def_yes;
         break;
   }
}
*/

void pdf_info_quick_help()
{
/*
   int result;
   KeyMessage ks;

   sline_clear();
   mline_write(msg_get(msg_help));

   scn_work();
   VioNormal();

   exit_f = def_no;
   macro_field_alloc("help");
   do
   {
      ks.Receive();
      result = macro_search(&ks);
      if (result == MACRO_SEARCH_MATCH) macro_excute(macro_excute_cback_help);
      help_scn_update();
   } while (!exit_f);
   macro_field_free();
   view_invalidate();
   mline_clear();
   sline_invalidate();
*/
}

static void ctor()
{
/*
   #define BUF_SIZE 128

   FILE *fh;
   char buf[128];
   int len;
   char* result;

   fh=fopen (help_file_name,"rt");
   if (fh==NULL) return;
   forever
   {
      if (help_list_cnt==200) break;
      buf[0]=0;
      result = fgets(buf,BUF_SIZE,fh);
      if ( result || result==NULL && buf[0]!=0 )
      {
         len = strlen(buf);
         if (buf[len-1]=='\n') buf[len-1]=0;
         help_list[help_list_cnt]=(char*)mem_alloc(len+1);
         strcpy(help_list[help_list_cnt],buf);
         help_list_cnt++;
      }
      if (result==NULL) break;
   }
   fclose (fh);
*/
}

static cls_initer initer(ctor,-1);
