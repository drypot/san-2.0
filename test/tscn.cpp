
#include <pub\config.hpp>
#include <pub\stdhdr.hpp>
#pragma hdrstop

#include <hanpub\fnt.hpp>
#include <pub\crt.hpp>
#include <conpub\io.hpp>

#include <pub\stdmain.inc>
{
   static uint8 textwin[80*480];
   static uint16 k;
   int x,y,i;
   int cx, cy;
   uint16* p;

   cx = 40;
   cy = 480 / 16;

	han_fnt_load("font\\sanigj.han");
   crt_init();
   crt_on();

   while (getch() != 'q')
   {
      p = (uint16*)han_fnt_pos (hangul(k,k,k));
      forcnt (y,cy)
         forcnt (x,cx)
            forcnt (i,16)
            {
               *(uint16*)&(textwin[(y*16+i)*cx*2+x*2]) = p[i];
            }
      k++;
      if (k==32) k=0;
      crt_restore_rect (0,0,79,29,textwin);
   }
   return 0;
}
