/*
   95.10.08
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\vio.hpp>
#include <vio\textwin.hpp>
#include <key\key.hpp>
#include <fnt\engfont.hpp>

void Pause()
{
   KeyWaitMake();
   KeyDiscard();
}

void TestBase()
{
   TextWindow textwin1(0,0,10,10);
   TextWindow textwin2(10,10,10,10);

   TextImage textimg1 (10,10);
   TextImage textimg2 (10,10);

   int i,x,y;

   forcnt(i,10)
   {
      forcnt (x,10)
         forcnt (y,10)
            textimg1.Put8(x, y, EngFont('0'+i));

      forcnt (x,10)
         forcnt (y,10)
            textimg2.Put8(x, y, EngFont('A'+i));

      textwin1.Draw(textimg1);
      textwin2.Draw(textimg2);

      Pause();
   }
}

void TestScroll()
{
   TextWindow textwin;
   TextImage textimg(40,20);

   textimg.Fill(0xAA);
   textimg.Inverse();
   textimg.ClearRect(1,1,38,18);
   textimg.Normal();
   textimg.ClearRect(2,2,36,16);
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollUp();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollUp();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollDown();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollDown();
   textwin.Draw(textimg);
}

void TestTTYWrite()
{
}

void Main()
{
   int i;

   puts ("1. TestBase");
   puts ("2. TestScroll");
   puts ("3. TestTTYWrite");

   scanf ("%d",&i);

   VioOn();
   KeyOn();

   switch (i)
   {
      case 1 :
         TestBase();
         break;

      case 2 :
         TestScroll();
         break;

      case 3 :
         TestTTYWrite();
         break;
   }

   Pause();
}
