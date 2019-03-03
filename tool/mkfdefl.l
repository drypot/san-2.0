%{
                                                                                                                        /*
--------------------------------------------------------------------------------
   mkfdefl.l -- make macro-function define list

   copyright(C) kyuhyun park

   1994.11.08
   1995.10.03
--------------------------------------------------------------------------------                                        */

#include <string.h>
#include <ctype.h>

#include <pub/lex.hpp>
#include "tool\mkfdef.hpp"

%}

delim           [ \t]
new_line        \n
letter          [A-Za-z_]
digit           [0-9]
digit_hex       [0-9A-Fa-f]

ws              {delim}+
ident           {letter}({letter}|{digit})*
int_dec         {digit}+
int_hex         0(x|X){digit_hex}+

str_normal   [^"\n\\]
str_escape   \\.
str          ({str_normal}|{str_escape})*

%x STRING LINE_COMMENT C_COMMENT
%%

"#"                     lex_scpush(); BEGIN(LINE_COMMENT);
"//"                    lex_scpush(); BEGIN(LINE_COMMENT);
<LINE_COMMENT>.*        ;
<LINE_COMMENT>\n        lex_scpop(); lex_line_num_int++;

"/*"                    lex_scpush(); BEGIN(C_COMMENT);
<C_COMMENT>[^*\n]*
<C_COMMENT>"*"+[^*/\n]*
<C_COMMENT>\n           lex_line_num_int++;
<C_COMMENT>"*"+"/"      lex_scpop();

{new_line}              lex_line_num_int++;
{ws}                    ;

{int_dec}               lex_set_int(); return def_tk_int;
{int_hex}               lex_set_str(); sscanf(lex_val_ach,"%x",&lex_val_int); return def_tk_int;

\"                      lex_scpush(); BEGIN(STRING);
<STRING>{str}/\"        {
                           input();
                           lex_parse_str();
                           lex_scpop();
                           return def_tk_str;
                        }
{ident}                 lex_set_str(); return def_tk_ident;
^"%%"                   return 0;
.                       lex_error();

%%
