/*
   1995.08.26
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\crt.hpp>
#include <vio\nullfont.hpp>

void main()
{
   int x,y;

   crt_init(0);
   crt_on();
   crt_clear();
   crt_inverse(0,0,79,29);

   forcnt (y,28)
      forcnt(x,78/2)
      {
         crt_put_16x16 (x*2 + 1, y+1, NullFont());
      }
   getchar();
}
