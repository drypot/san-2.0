/*
   1995.08.27
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\crt.hpp>
#include <vio\hanjafont.hpp>

void main()
{
   int i,j;

   HanjaFontLoad("..\\font\\normal.hj");

   crt_init(0);
   crt_on();
   crt_clear();
   crt_inverse(0,0,79,29);

   forcnt (i,26)
   {
      forcnt (j,256)
      {
         Hangul han(0xe0+i, j);
         crt_put_16x16 ((j % 40)*2, j / 40, HanjaFont(han));
      }
      getchar();
   }
}
