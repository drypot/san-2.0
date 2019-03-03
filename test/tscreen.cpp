/*
   95.10.10
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\textwin.hpp>
#include <key\key.hpp>

void Pause()
{
   KeyWaitMake();
   KeyDiscard();
}


void TestVio()
{
   Pause();
   VioFill(0);
   Pause();
   VioFill(0xAA);
   Pause();
}

void TestTextWindow()
{
   TextWindow scn1(20,20,5,5,TextWindow::SAVE_BACK);
   TextWindow scn2(20,20,35,5);
   TextImage textimg(20,20);

   int x,y;

   forcnt(y,20)
   {
      textimg.XY(0,y);
      forcnt(x,20) textimg.Write('A');
   }
   scn1.Draw(textimg);
   scn2.Draw(textimg);
   Pause();

   textimg.InverseRect(1,1,18,18);
   scn1.Draw(textimg);
   scn2.Draw(textimg);
   Pause();

   textimg.ClearRect(2,2,17,17);
   scn1.Draw(textimg);
   scn2.Draw(textimg);
   Pause();
}

void TestTextWindowAsciiDump()
{
   TextWindow scn;
   TextImage textimg(80,30);

   int x,y,k;

   forcnt(k,128)
   {
      forcnt(y,30)
      {
         textimg.XY(0,y);
         forcnt(x,80) textimg.Write(k);
      }
      scn.Draw(textimg);
   }
   Pause();
}

void TestTextWindowHangulDump()
{
   TextWindow scn;
   TextImage textimg(80,30);

   int x,y,k;
   Hangul hc;

   forcnt(k,32)
   {
      hc = Hangul(k,k,k);
      forcnt(y,30)
      {
         textimg.XY(0,y);
         forcnt(x,40) textimg.Write(hc);
      }
      scn.Draw(textimg);
      Pause();
   }
   Pause();
}

int Main()
{
   int i;

   puts ("1. Test Vio");
   puts ("2. Test TextWindow -- Normal");
   puts ("3. Test TextWindow -- Ascii Write");
   puts ("3. Test TextWindow -- Hangul Write");

   scanf ("%d",&i);

   VioOn();
   KeyOn();

   switch (i)
   {
      case 1 :
         TestVio();
         break;

      case 2 :
         TestTextWindow();
         Pause();
         break;

      case 3 :
         TestTextWindowAsciiDump();
         break;

      case 4 :
         TestTextWindowHangulDump();
         break;
   }

   return 0;
}
