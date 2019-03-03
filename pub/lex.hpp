                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/lex.hpp
   copyright(c) kyuhyun park
   1994.11.05
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_lex_hpp
#error 'pub/lex.hpp' duplicated.
#endif

#define def_pub_lex_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifdef __cplusplus
   #ifndef def_pub_process_hpp
   #include <pub/process.hpp>
   #endif

   #ifndef def_pub_string_hpp
   #include <pub/string.hpp>
   #endif

   mac_define_xmsg1(lex);
   mac_define_xmsg1(yacc);
#endif

#ifdef __cplusplus
extern "C" {
#endif

   /*
      lexer & parser interface
   */

   extern FILE *yyin,*yyout;
   extern int yyleng;
   extern char* yytext;

   int yylex(void);
   int yyparse(void);
   void yyerror(char*);
   void yyrestart(FILE *);

   /*
      utilities
   */

   #define def_size_lex_val_ach 1024

   extern int  lex_line_num_int;
   extern char lex_val_ach [];
   extern int  lex_val_int;
   extern char lex_val_char;

   void lex_error();

   void lex_set_fname(char*);
   void lex_set_str();
   void lex_parse_str();
   bool lex_check_str();

   void lex_set_int();
   void lex_set_char();

   void lex_scpush_core(int);
   int  lex_scpop_core();

   #define lex_scpush() lex_scpush_core(yy_start)
   #define lex_scpop() (yy_start=lex_scpop_core())

#ifdef __cplusplus
}
#endif
