/*
   1995.08.26
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <pub\time.hpp>
#include <vio\crt.hpp>
#include <vio\hanfont.hpp>

StopWatch watch;

void Type1()
{
   int x,y,h1,h2;
   Hangul han;

   watch.Start();
   forcnt (h1, 32)
      //forcnt (h2, 32)
      {
         han.bit5.h1 = h1;
         han.bit5.h2 = h1;
         han.bit5.h3 = h1;

         forcnt (y, 28)
            forcnt (x, 78 / 2)
            {
               crt_put_16x16 (x*2 + 1, y + 1 , HanFont(han));
            }
         getchar();
      }
   watch.Stop();
}

void Type2()
{
   int x,y,h1,h2;
   int width = 78;
   int height = 28;
   MemBlock memBlock(width*height*16);
   uint16* pFont;
   byte* pDst;

   Hangul han;

   watch.Start();
   forcnt (h1, 32)
      //forcnt (h2, 32)
      {
         han.bit5.h1 = h1;
         han.bit5.h2 = h1;
         han.bit5.h3 = h1;

         forcnt (y, 28)
            forcnt (x, 78 / 2)
            {
               pFont = (uint16*)HanFont(han);
               pDst = (byte*)memBlock + y*16*width + x*2;

               *(uint16*)(pDst) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;

               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;

               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;

               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
               *(uint16*)(pDst += width) = *pFont++;
            }
         ASSERT(memBlock.Check());
         crt_restore_Rect(1,1,78,28,memBlock);
         getchar();
      }
   watch.Stop();
}

void main()
{
   int i;

   HanFontLoad("..\\font\\sanigj.han");

   puts ("1. Direct");
   puts ("2. Through TextImage");
   scanf ("%d",&i);

   crt_init(0);
   crt_on();
   crt_clear();
   crt_inverse(0,0,79,29);

   switch (i)
   {
      case 1 : Type1(); break;
      case 2 : Type2(); break;
   }

   crt_off();
   printf ("%ld\n",watch.Diff());
   getchar();
}
