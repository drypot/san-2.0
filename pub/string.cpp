                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/string.cpp
   copyright(c) kyuhyun park
   1992.01.17
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/stdarg.hpp>

cls_form_expander::cls_form_expander (char* form, ...)
{
   pch = (char*)mem_alloc(1024);
   va_list arg_list;

   va_start(arg_list,form);
   vsprintf(pch, form, arg_list);
   va_end(arg_list);

   mac_rtcheck(strlen(pch) < 1024);
}

cls_form_expander::~cls_form_expander ()
{
   mem_free(pch);
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   for C str
--------------------------------------------------------------------------------                                        */

char* str_expand(char* arg_pnt, size_t sz)
{
   char* cur_pnt;
   char* end_pnt;

   end_pnt = arg_pnt + sz;
   cur_pnt = arg_pnt + strlen(arg_pnt);

   if (cur_pnt<end_pnt) memset(cur_pnt, ' ', end_pnt - cur_pnt);
   *end_pnt = 0;

   return arg_pnt;
}

char* str_delspc(char* arg_pnt)
{
   char* tar_pnt;
   char* src_pnt;
   char* end_pnt;

   end_pnt = arg_pnt + strlen(arg_pnt);
   tar_pnt = arg_pnt;
   src_pnt = arg_pnt - 1;

   while (++src_pnt < end_pnt) if (*src_pnt != ' ') *tar_pnt++ = *src_pnt;
   *tar_pnt=0;

   return arg_pnt;
}

char* str_cat_va(char* org_dst_pnt, ... )
{
   char* dst_pnt;
   char* src_pnt;
   va_list arg_list;

   dst_pnt = (char*) org_dst_pnt + strlen(org_dst_pnt);
   va_start(arg_list, org_dst_pnt);

   while ( (src_pnt=va_arg(arg_list, char*)) != NULL )
   {
      strcat(dst_pnt, src_pnt);
      dst_pnt += strlen(src_pnt);
   }

   va_end(arg_list);

   return org_dst_pnt;
}

void str_parse(char* src_pnt)
{
   char val;
   char* dst_pnt = src_pnt;

   while(*src_pnt)
   {
      if ( *src_pnt == '\\' )
      {
         src_pnt++;
         switch (*src_pnt)
         {
            case 'a' : val = 0x07; break;
            case 'b' : val = 0x08; break;
            case 'f' : val = 0x0c; break;
            case 'n' : val = 0x0a; break;
            case 'r' : val = 0x0d; break;
            case 't' : val = 0x09; break;
            case 'v' : val = 0x0b; break;
            case '^' : val = toupper(*++src_pnt) -  '@'; break;
            default  : val = *src_pnt;
         }
         *dst_pnt++ = val;
         src_pnt++;
      }
      else
      {
         *dst_pnt++ = *src_pnt++;
      }
   }
   *dst_pnt = 0;
}

void str_upper(char* p)
{
   while (*p) *p=toupper(*p),p++;
}

char* str_dup (char* p)
{
   return strcpy((char*)mem_alloc(strlen(p)+1), p);
}

char* str_printf (char* form ...)
{
   char msg_ach [1024];
   va_list arg_list;

   va_start(arg_list, form);
   vsprintf(msg_ach, form, arg_list);
   va_end(arg_list);

   mac_rtcheck (strlen(msg_ach) < sizeof(msg_ach));

   return str_dup(msg_ach);
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   for char16 str
--------------------------------------------------------------------------------                                        */

char16* str_expand(char16* arg_pnt, size_t sz)
{
   char16* cur_pnt;
   char16* end_pnt;

   end_pnt = arg_pnt + sz;
   cur_pnt = arg_pnt + str_len(arg_pnt);

   while (cur_pnt<end_pnt) *cur_pnt++ = ' ';
   *cur_pnt = 0;

   return arg_pnt;
}

char16* str_make(char16* org_dst_pnt, char* src_pnt)
{
   register char16* dst_pnt = org_dst_pnt;

   while ( *src_pnt ) *dst_pnt++ = read_c16(&src_pnt);
   *dst_pnt=0;
   return org_dst_pnt;
}

char* str_make(char* org_dst_pnt, char16* src_pnt)
{
   register char* dst_pnt = org_dst_pnt;

   src_pnt--;
   while ( *++src_pnt )
   {
      if (is_single(*src_pnt))
      {
         *dst_pnt++ = (char) *src_pnt;
      }
      else
      {
         *dst_pnt++ = get_u16_high(*src_pnt);
         *dst_pnt++ = get_u16_low (*src_pnt);
      }
   }
   *dst_pnt=0;
   return org_dst_pnt;
}

char16* str_cpy(char16* org_dst_pnt, char16* src_pnt)
{
   register char16* dst_pnt = org_dst_pnt;
   while ( ( *dst_pnt++ = *src_pnt++ ) != 0 );
   return org_dst_pnt;
}

/*
char16*  str_cpy(char16* org_dst_pnt, char16* src_pnt, size_t sz)
{
}
*/

/*
char16*  str_cat(char16*, char16*)
{
}
*/

/*
char16*  str_cat(char16*, char16*, size_t)
{
}
*/

/*
int str_cmp(char16*, char16*)
{
   int result;

   while ( sz-- )
   {
      result = *p1 - *p2;
      if ( *p1 == 0 || *p2 == 0 || result ) return result;
      p1++;
      p2++;
   }

   return 0;
}
*/

/*
int str_cmp(char16*, char16*, size_t)
{
}
*/

size_t str_len (char16* arg_pnt)
{
   char16* pnt = (char16*) arg_pnt;
   while ( *pnt ) pnt++ ;
   return size_t(pnt - arg_pnt);
}

size_t str_lenvisual (char16* arg_pnt)
{
   char16* pnt = (char16*) arg_pnt;
   size_t sz = 0;
   while (*pnt) sz += get_c16_width(*pnt++);
   return sz;
}

/*
char16* str_chr(char16*, char16)
{
}
*/

/*
char16*  str_rchr(char16*, char16)
{
}
*/

/*
int str_spn(char16*, char16*)
{
}
*/

/*
int str_cspn(char16*, char16*)
{
}
*/

/*
char16* str_pbrk(char*, char16*)
{
}
*/

/*
char16* str_str(char16*, char16*)
{
}
*/

/*
char16* str_tok(char16*, char16*)
{
}
*/

char*   dup_msg(char* form ...)
{
   static char msg_ach[256];
   va_list arg_list;
   char* dup_pch;

   va_start(arg_list,form);
   vsprintf(msg_ach, form, arg_list);
   va_end(arg_list);
   mac_rtcheck (strlen(msg_ach) < sizeof(msg_ach));

   dup_pch = (char*) mem_alloc(strlen(msg_ach)+1);
   strcpy(dup_pch, msg_ach);
   mac_assert(mem_check(dup_pch));

   return dup_pch;
}
