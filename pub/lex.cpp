                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/lex.cpp
   copyright(c) kyuhyun park
   1994.11.05
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/dir.hpp>
#include <pub/lex.hpp>
#include <cnt/stack.hpp>

int  lex_line_num_int = 1;
char lex_fname_ach [def_fn_path_max];
char lex_val_ach [def_size_lex_val_ach];
int  lex_val_int;
char lex_val_char;

static tem_stack<int> sc_save_int_stack(5);

void yyerror(char* msg)
{
   char tmp_ach[1024];

   mac_fill_zero(tmp_ach);
   sprintf(tmp_ach, "func: pub/lex.cpp/yyerror\n\nyyerror at\nfile: %s\nline: %d\ninfo: %s\n", lex_fname_ach, lex_line_num_int, msg);
   if (strlen(tmp_ach) + 10 + yyleng < sizeof(tmp_ach))
   {
      strcat(tmp_ach,"yytext : ");
      strncat(tmp_ach, yytext, yyleng);
      strcat(tmp_ach,"\n");
   }
   throw cls_xmsg_lex(tmp_ach);
}

void lex_error()
{
   throw cls_xmsg_lex("func: pub/lex.cpp/lex_error\ninfo: lexical scanning error\n");
}

void lex_set_fname(char* arg_fname)
{
   mac_rtcheck (strlen(arg_fname) < def_fn_path_max);
   strcpy (lex_fname_ach, arg_fname);
}

void lex_set_str()
{
   mac_rtcheck(yyleng < def_size_lex_val_ach);
   strncpy(lex_val_ach, yytext, yyleng);
   lex_val_ach [yyleng] = 0;
}

void lex_parse_str()
{
   lex_set_str();
   str_parse(lex_val_ach);
}

bool lex_check_str()
{
   return strlen(lex_val_ach) < def_size_lex_val_ach;
}

void lex_set_int()
{
   lex_set_str();
   lex_val_int = atoi(lex_val_ach);
}

void lex_set_char()
{
   lex_val_char = lex_val_ach[0];
}

void lex_scpush_core(int sc)
{
   sc_save_int_stack.push_val(sc);
}

int lex_scpop_core()
{
   return sc_save_int_stack.pop_val();
}
