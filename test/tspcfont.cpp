/*
   1995.08.27
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\crt.hpp>
#include <vio\spcfont.hpp>

void main()
{
   int i,j;

   crt_init(0);
   crt_on();
   crt_clear();
   crt_inverse(0,0,79,29);

   SpcFontLoad("..\\font\\sys.spc","..\\font\\roman_c.sp2");

   forcnt (j,256)
   {
      Hangul han(0xd4, j);
      crt_put_16x16 ((j % 40)*2, j / 40, SpcFont(han));
   }
   getchar();
   crt_clear();
   crt_inverse(0,0,79,29);

   forcnt (i,6)
   {
      forcnt (j,256)
      {
         Hangul han(0xd9+i, j);
         crt_put_16x16 ((j % 40)*2, j / 40, SpcFont(han));
      }
      getchar();
   }
}
