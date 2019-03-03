                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/string.hpp
   copyright(c) kyuhyun park
   1992.01.17
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_string_hpp
#error 'pub/string.hpp' duplicated.
#endif

#define def_pub_string_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#include <string.h>

class cls_form_expander
{
   private:
      char* pch;

   public:
      cls_form_expander (char* form, ...);
      ~cls_form_expander ();

      char* get_pch ()
      {
         return pch;
      }
};
                                                                                                                        /*
--------------------------------------------------------------------------------
   char
--------------------------------------------------------------------------------                                        */

inline bool str_same(char* a, char* b) { return strcmp(a,b)==0; }
inline bool str_less(char* a, char* b) { return strcmp(a,b) <0; }
inline bool str_more(char* a, char* b) { return strcmp(a,b) >0; }

char* str_expand (char*,size_t);
char* str_del_spc (char*);
char* str_cat_va (char* ...);

void str_parse (char*);
void str_upper (char*);

char* str_dup (char*);
char* str_printf (char* ...);
                                                                                                                        /*
--------------------------------------------------------------------------------
   char16
--------------------------------------------------------------------------------                                        */

char16* str_expand(char16*,size_t);

char16* str_make(char16*, char*);
char*   str_make(char*, char16*);

char16* str_cpy(char16*, char16*);
char16* str_cpy(char16*, char16*,size_t);

char16* str_cat(char16*, char16*);
char16* str_cat(char16*, char16*, size_t);

int     str_cmp(char16*, char16*);
int     str_cmp(char16*, char16*, size_t);

size_t  str_len(char16*);
size_t  str_len_visual(char16*);

char16* str_chr(char16*, char16);
char16* str_rchr(char16*, char16);

int     str_spn(char16*, char16*);
int     str_cspn(char16*, char16*);

char16* str_pbrk(char*, char16*);

char16* str_str(char16*, char16*);

char16* str_tok(char16*, char16*);

char*   dup_msg(char* ...);
