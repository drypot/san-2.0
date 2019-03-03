/*
   1995.08.26
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\crt.hpp>
#include <vio\engfont.hpp>

void main()
{
   int inx;

   crt_init(0);
   crt_on();
   crt_clear();
   crt_inverse(0,0,79,29);

   EngFontLoad("..\\font\\sanigj.eng");

   forcnt (inx,128)
      crt_put_8x16 (inx % 78 + 1, inx / 78 + 1, EngFont(inx));

   getchar();
}
