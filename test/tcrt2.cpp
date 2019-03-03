/*
   crt2.cpp - hangul output speed test

   Kyuhyun Park

*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\hanfont.hpp>
#include <vio\easyhan.hpp>

void main()
{
   easy_han_output_init();
   easy_han_output_on();

   {
      int i,j,k,x,y;

      forcnt(i,32)
         forcnt(j,32)
            //forcnt(k,32)
               forcnt(y,30)
               {
                  forcnt(x,40)
                  {
                     crt_put_16x16(x*2,y,han_fnt_pos(hangul(i,i,j)));
                  }
               }
   }
}
