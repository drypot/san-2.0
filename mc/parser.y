%{
                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/parser.y
   copyright(c) kyuhyun park
   1994.11.06
--------------------------------------------------------------------------------                                        */

#include <malloc.h>
#include <mc/glb.hpp>

#ifndef YYDEBUG
#define YYDEBUG 0
#endif

%}

%token TK_NULL
%token TK_STRING TK_INT TK_CHAR TK_IDENT

%token TK_UDFUNC
%token TK_IF
%token TK_ELSE
%token TK_WHILE
%token TK_RETURN

%token TK_LOGICAL_AND
%token TK_LOGICAL_OR
%token TK_EQUAL
%token TK_NOT_EQUAL
%token TK_ABOVE_EQUAL
%token TK_BELOW_EQUAL

%token TK_KEYBIND
%token TK_MODE
%token TK_S TK_LS TK_RS
%token TK_C TK_LC TK_RC
%token TK_A TK_LA TK_RA
%token TK_M TK_LM TK_RM
%token TK_KEY_NAME

%%

program         : bifunc_part udfunc_part keybind_part
                ;

                /* built-in-function part */

bifunc_part     : bifunc_list
                ;

bifunc_list     : bifunc_list bifunc
                |
                ;

bifunc          : TK_IDENT                      { bifunc(); }
                ;

                /* user-defined-function part */

udfunc_part     : TK_UDFUNC func_list
                |
                ;

func_list       : func_list func
                | func
                |
                ;

func            : func_head func_body
                ;

func_head       : TK_IDENT                      { func_name(); }
                ;

func_body       : '{' statements '}'            { func_body_end(); }
                ;

statements      : statements statement
                | statement
                |
                ;

statement       : exp ';'                       { exp_discard(); }
                | if
                | while
                | block
                | TK_RETURN ';'                 { statement_return(); }
                | ';'
                ;

if              : TK_IF                         
                  '(' exp ')'                   { if_exp_end(); }
                  then_part
                  else_part
                ;

then_part       : statement

else_part       : TK_ELSE                       { else_begin(); }
                  statement                     { else_end();  }
                |                               { else_null(); }
                ;

while           : TK_WHILE                      { while_begin(); }
                  '(' exp ')'                   { while_exp_end(); }
                  statement                     { while_end(); }
                ;

block           : '{' statements '}'
                ;

exp             : logical_and
                  TK_LOGICAL_OR
                  logical_and                   { exp_logical_or(); }
                | logical_and
                ;

logical_and     : equality
                  TK_LOGICAL_AND
                  equality                       { exp_logical_and(); }
                | equality
                ;

equality        : relation TK_EQUAL relation     { exp_equal(); }
                | relation TK_NOT_EQUAL relation { exp_not_equal(); }
                | relation
                ;

relation        : plus '>' plus                 { exp_above(); }
                | plus '<' plus                 { exp_below(); }
                | plus TK_ABOVE_EQUAL plus      { exp_above_equal(); }
                | plus TK_BELOW_EQUAL plus      { exp_below_equal(); }
                | plus
                ;

plus            : mul '+' mul                   { exp_plus(); }
                | mul '-' mul                   { exp_minus(); }
                | mul

mul             : unary '*' unary               { exp_mul(); }
                | unary '/' unary               { exp_div(); }
                | unary
                ;


unary           : '!' primary                   { exp_not(); }
                | primary
                ;

primary         : call                          { exp_func_result(); }
                | TK_INT                        { exp_int(); }
                | TK_CHAR                       { exp_char(); }
                | TK_IDENT                      { exp_func_ptr(); }
                | '(' exp ')'
                ;

call            : call_name call_args
                ;

call_name       : TK_IDENT                      { call_name(); }
                ;

call_args       : '(' arg_list ')'              { call_arg_end(); }
                ;

arg_list        : arg_list ',' arg_item
                | arg_item
                |
                ;

arg_item        : TK_STRING                     { call_arg_str(); }
                | exp                           { call_arg_exp(); }
                ;

                /* keybind part */

keybind_part    : TK_KEYBIND mode_list
                |
                ;

mode_list       : mode_list mode
                | mode
                |
                ;

mode            : mode_head mode_body           { mode_end(); }
                ;

mode_head       : TK_MODE TK_STRING           { new_mode(); }
                ;

mode_body       : bind_list
                ;

bind_list       : bind_list bind
                | bind
                |
                ;

bind            : TK_IDENT                       { new_bind(); }
                  ':'                            { new_keyseq_list(); }
                  keyseq_list ';'
                ;

keyseq_list     : keyseq_list '|' keyseq_
                | keyseq_
                ;

keyseq_         :                                { new_keyseq(); }
                  keyseq
                ;

keyseq          : keyseq ',' key_exp_
                | key_exp_
                ;

key_exp_        :                                { new_key(); }
                  key_exp
                ;

key_exp         : modify_exp '-' key_code_exp
                ;

modify_exp      : modify_on_list modify_off_list
                ;

modify_on_list  : modify_list
                |
                ;

modify_off_list : '!'                           { not_modify(); }
                  modify_list
                |
                ;

modify_list     : modify_list modify_type
                | modify_type
                ;

modify_type     : TK_S                          { modify_s(); }
                | TK_LS                         { modify_ls(); }
                | TK_RS                         { modify_rs(); }

                | TK_C                          { modify_c(); }
                | TK_LC                         { modify_lc(); }
                | TK_RC                         { modify_rc(); }

                | TK_A                          { modify_a(); }
                | TK_LA                         { modify_la(); }
                | TK_RA                         { modify_ra(); }

                | TK_M                          { modify_m(); }
                | TK_LM                         { modify_lm(); }
                | TK_RM                         { modify_rm(); }
                ;

key_code_exp    : key_code
                | '!'                           { not_key(); }
                  key_code
                ;
key_code        : TK_KEY_NAME                   { key_name(); }
                | TK_STRING                     { key_name_str(); }
                ;
