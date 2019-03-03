%{
                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/scanner.l
   copyright(c) kyuhyun park
   1994.11.06
--------------------------------------------------------------------------------                                        */

#include <pub/lex.hpp>

#include <mc/glb.hpp>
#include <mc/tmp/parser.h>

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

char_normal     [^'\n\\]
char_escape     \\.
char            ({char_normal}|{char_escape})*

%x CHAR_WORK STRING LINE_COMMENT C_COMMENT
%s KEYNAME
%s PDFUNC
%s UDFUNC
%s KEYBIND KB_MODIFY KB_KEYNAME

%%
                        /* single line LINE_COMMENT */

"#"                     lex_scpush(); BEGIN(LINE_COMMENT);
"//"                    lex_scpush(); BEGIN(LINE_COMMENT);
<LINE_COMMENT>.*        ;
<LINE_COMMENT>\n        lex_scpop(); lex_line_num_int++;

                        /* C Style LINE_COMMENT */

"/*"                    lex_scpush(); BEGIN(C_COMMENT);
<C_COMMENT>[^*\n]*
<C_COMMENT>"*"+[^*/\n]*
<C_COMMENT>\n           lex_line_num_int++;
<C_COMMENT>"*"+"/"      lex_scpop();

                        /* white space */

{new_line}              lex_line_num_int++;
{ws}                    ;

                        /* integer constant */

{int_dec}               lex_set_int(); return TK_INT;
{int_hex}               lex_set_str(); sscanf(lex_val_ach,"%x",&lex_val_int); return TK_INT;

                        /* char constant */

\'                      lex_scpush(); BEGIN(CHAR_WORK);
<CHAR_WORK>{char}/\'    {
                           input();
                           lex_parse_str();
                           lex_set_char();
                           lex_scpop();
                           return TK_CHAR;
                        }


                        /* STRING constant */

\"                      lex_scpush(); BEGIN(STRING);
<STRING>{str}/\"     {
                           input();
                           lex_parse_str();
                           lex_scpop();
                           return TK_STRING;
                        }

                        /* KeyNameList scanning mode */

<KEYNAME>{ident}        lex_set_str(); return TK_IDENT;

                        /* PDFuncList scanning mode */

<PDFUNC>{ident}         lex_set_str(); return TK_IDENT;
<PDFUNC>^"%%"           BEGIN(UDFUNC); return TK_UDFUNC;

                        /* UDFunc scanning mode */

<UDFUNC>"{"             return '{';
<UDFUNC>"}"             return '}';
<UDFUNC>";"             return ';';
<UDFUNC>"("             return '(';
<UDFUNC>")"             return ')';
<UDFUNC>"!"             return '!';
<UDFUNC>"&&"            return TK_LOGICAL_AND;
<UDFUNC>"||"            return TK_LOGICAL_OR;
<UDFUNC>"=="            return TK_EQUAL;
<UDFUNC>"!="            return TK_NOT_EQUAL;
<UDFUNC>">"             return '>';
<UDFUNC>"<"             return '<';
<UDFUNC>">="            return TK_ABOVE_EQUAL;
<UDFUNC>"<="            return TK_BELOW_EQUAL;
<UDFUNC>"/"             return '/';
<UDFUNC>"*"             return '*';
<UDFUNC>"+"             return '+';
<UDFUNC>"-"             return '-';
<UDFUNC>","             return ',';
<UDFUNC>if              return TK_IF;
<UDFUNC>else            return TK_ELSE;
<UDFUNC>while           return TK_WHILE;
<UDFUNC>return          return TK_RETURN;
<UDFUNC>{ident}         lex_set_str(); return TK_IDENT;
<UDFUNC>^"%%"           BEGIN(KEYBIND); return TK_KEYBIND;

                        /* KeyBind scanning mode */

<KEYBIND>"mode"         return TK_MODE;
<KEYBIND>{ident}        lex_set_str(); return TK_IDENT;
<KEYBIND>":"            BEGIN(KB_MODIFY); return ':';

<KB_MODIFY>(s|S)        return TK_S;
<KB_MODIFY>(ls|LS)      return TK_LS;
<KB_MODIFY>(rs|RS)      return TK_RS;

<KB_MODIFY>(c|C)        return TK_C;
<KB_MODIFY>(lc|LC)      return TK_LC;
<KB_MODIFY>(rc|RC)      return TK_RC;

<KB_MODIFY>(a|A)        return TK_A;
<KB_MODIFY>(la|LA)      return TK_LA;
<KB_MODIFY>(ra|RA)      return TK_RA;

<KB_MODIFY>(m|M)        return TK_M;
<KB_MODIFY>(lm|LM)      return TK_LM;
<KB_MODIFY>(rm|RM)      return TK_RM;

<KB_MODIFY>"!"          return '!';
<KB_MODIFY>"-"          BEGIN(KB_KEYNAME); return '-';
<KB_MODIFY>";"          BEGIN(KEYBIND); return ';';

<KB_KEYNAME>{ident}     lex_set_str(); return TK_KEY_NAME;
<KB_KEYNAME>"!"         return '!';
<KB_KEYNAME>","         BEGIN(KB_MODIFY); return ',';
<KB_KEYNAME>"|"         BEGIN(KB_MODIFY); return '|';
<KB_KEYNAME>";"         BEGIN(KEYBIND); return ';';

                        /* unknown token */

.                       lex_error();

%%

void scanner_key_name_mode()
{
   if (yyin=fopen(key_name_fname_ach,"rt") , !yyin) open_error(key_name_fname_ach);
   lex_set_fname(key_name_fname_ach);
   BEGIN(KEYNAME);
   lex_line_num_int = 1;
}

void scanner_mac_mode()
{
   if (yyin=fopen(mac_fname_ach,"rt") , !yyin) open_error(mac_fname_ach);
   lex_set_fname(mac_fname_ach);
   yyrestart(yyin);
   BEGIN(PDFUNC);
   lex_line_num_int = 1;
}
