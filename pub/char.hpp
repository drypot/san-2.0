                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/char.hpp
   copyright(c) kyuhyun park
   1993.07.08
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_char_hpp
#error 'pub/char.hpp' duplicated.
#endif

#define def_pub_char_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

#include <ctype.h>
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline bool is_double (byte b)     { return b & 0x80; }
inline bool is_single (byte b)     { return !is_double (b); }

inline bool is_hangul (byte b)     { return is_inside (b,0x84,0xd3); }
inline bool is_special (byte b)    { return is_inside (b,0xd4,0xdf); }
inline bool is_hanja (byte b)      { return b >=0xe0; }

inline bool is_double (char ch)    { return is_double ( (byte) ch ) ; }
inline bool is_single (char ch)    { return is_single ( (byte) ch ) ; }

inline bool is_hangul (char ch)    { return is_hangul ( (byte) ch ) ; }
inline bool is_special (char ch)   { return is_special ( (byte) ch ) ; }
inline bool is_hanja (char ch)     { return is_hanja ( (byte) ch ) ; }

inline bool is_double (char16 ch)  { return ch & 0x8000; }
inline bool is_single (char16 ch)  { return !is_double (ch); }

inline bool is_hangul (char16 ch)  { return is_inside_less (ch,0x8400,0xd400); }
inline bool is_special (char16 ch) { return is_inside_less (ch,0xd400,0xe000); }
inline bool is_hanja (char16 ch)   { return ch >=0xe000; }

inline bool is_alnum (char16 ch)   { return is_single (ch) && isalnum ((char)ch); }
inline bool is_alpha (char16 ch)   { return is_single (ch) && isalpha ((char)ch); }
inline bool is_cntrl (char16 ch)   { return is_single (ch) && iscntrl ((char)ch); }
inline bool is_digit (char16 ch)   { return is_single (ch) && isdigit ((char)ch); }
inline bool is_graph (char16 ch)   { return is_single (ch) && isgraph ((char)ch); }
inline bool is_lower (char16 ch)   { return is_single (ch) && islower ((char)ch); }
inline bool is_print (char16 ch)   { return is_single (ch) && isprint ((char)ch); }
inline bool is_punct (char16 ch)   { return is_single (ch) && ispunct ((char)ch); }
inline bool is_space (char16 ch)   { return is_single (ch) && isspace ((char)ch); }
inline bool is_upper (char16 ch)   { return is_single (ch) && isupper ((char)ch); }

inline bool is_line (char16 ch)    { return is_inside ( ch , 0xd4b3 , 0xd4da ) || is_inside ( ch , 0xdba1 , 0xdbe4 ) ; }
inline bool is_word (char16 ch)    { return is_hangul(ch) || is_hanja(ch) || is_alnum(ch); }
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline int get_c16_width (char16 ch)
{
   return is_double (ch) ? 2 : 1;
}

inline char16 make_c16 (char16 hi, char16 lo)
{
   return make_u16 (hi,lo);
}

inline char16 read_c16 (char* p)
{
   return is_single (*p) ? *p : make_u16 (*p, *(p+1));
}

inline char16 read_c16 (char** pp)
{
   if (is_single (**pp))
   {
      return *(*pp)++;
   }
   else
   {
      char16 ch = make_u16 (**pp, *(*pp + 1));
      *pp += 2;
      return ch;
   }
}

inline void write_c16 (char* p, char16 ch)
{
   if (is_single (ch))
   {
      *p = get_u16_low (ch);
   }
   else
   {
      write_as_big_endian (p,ch);
   }
}

inline void write_c16 (char** pp, char16 ch)
{
   if (is_single(ch))
   {
      **pp = get_u16_low (ch);
      *pp += 1;
   }
   else
   {
      write_as_big_endian (*pp,ch);
      *pp += 2;
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

struct cls_hanja_page
{
   char16 contents[65];
   int cnt;
};

struct cls_wchar
{
   #if defined def_watcomc || defined def_borlandc || defined def_ibmc
      union
      {
         struct
         {
            byte low;
            byte high;
         } bytes;

         struct
         {
            uint16 h3: 5;
            uint16 h2: 5;
            uint16 h1: 5;
            uint16 sign: 1;
         } parts;

         uint16 c16;
      };
   #else
      #error unsupported compiler.
   #endif

   cls_wchar ()
   {
   }

   cls_wchar (char16 ch) : c16 (ch)
   {
   }

   cls_wchar (uint h1, uint h2, uint h3)
   {
      parts.sign = 1;
      parts.h1 = h1;
      parts.h2 = h2;
      parts.h3 = h3;
   }

   cls_wchar (uint high, uint low)
   {
      bytes.high = high;
      bytes.low = low;
   }

   void swap ()
   {
      ::swap(&bytes.high, &bytes.low);
   }

   bool is_wansung ();
   bool is_johab ();

   void to_wansung ();
   void to_johab ();

   void to_hangul ();
   void set_hanja_page (cls_hanja_page*);
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

extern char16 h1_to_cardi_ary[];
extern char16 h2_to_cardi_ary[];
extern char16 h3_to_cardi_ary[];

extern char16 cardi_to_h1_ary[];
extern char16 cardi_to_h2_ary[];
extern char16 cardi_to_h3_ary[];

inline char16 h1_to_cardi (char16 h1)    { return h1_to_cardi_ary[h1]; }
inline char16 h2_to_cardi (char16 h2)    { return h2_to_cardi_ary[h2]; }
inline char16 h3_to_cardi (char16 h3)    { return h3_to_cardi_ary[h3]; }

inline char16 cardi_to_h1 (char16 cardi) { return cardi_to_h1_ary[cardi]; }
inline char16 cardi_to_h2 (char16 cardi) { return cardi_to_h2_ary[cardi]; }
inline char16 cardi_to_h3 (char16 cardi) { return cardi_to_h3_ary[cardi]; }
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void to_wansung (char*);
void to_wansung (char*, size_t);
void to_wansung (char16*);
void to_wansung (char16*, size_t);

void to_johab (char*);
void to_johab (char* , size_t);
void to_johab (char16*);
void to_johab (char16* , size_t);

inline char16 get_wansung (char16 ch)
{
   cls_wchar tmp(ch);
   tmp.to_wansung();
   return tmp.c16;
}

inline char16 get_johab (char16 ch)
{
   cls_wchar tmp(ch);
   tmp.to_johab();
   return tmp.c16;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

enum
{
   def_ct_auto,
   def_ct_johab,
   def_ct_wansung
};

int detect_hangul_code_type (char* , int = def_ct_wansung);

int sp1_to_cardi (cls_wchar);
int sp2_to_cardi (cls_wchar);
int hnj_to_cardi (cls_wchar);

inline bool is_chcl (int low)
{
   return is_inside ( low , 0x31 , 0x7E ) || is_inside ( low , 0x91 , 0xfe );
}

inline int chcl_to_index (int low)
{
   return low > 0x90 ? low - 0x91 + 78 : low - 0x31 ;
}

inline int index_to_chcl (int low)
{
   return low >= 78 ? low - 78 + 0x91 : low + 0x31 ;
}

