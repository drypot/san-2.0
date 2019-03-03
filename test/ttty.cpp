
#include <pub\config.hpp>
#include <pub\hangul.hpp>
#include <pub\easyhan.hpp>
#include <conio.h>

void han_test()
{
   crt_clear();

   int i,j,k;
   hangul han;

   han.bits.sign=1;
   forinc(k,0,20)
   {
      han.bits.h1=k;
      han.bits.h2=k;
      han.bits.h3=k;
      forcnt(i,30)
      {
         tty_xy(point(0-i%2,i));
         forcnt(j,41)
         {
            tty_output(han.word);
         }
      }
      getch();
   }
}

void eng_test()
{
   int i,x,y;
   forinc(i,32,127)
   {
      forcnt(y,30)
      {
         tty_xy(0,y);
         forcnt(x,80)
         {
            tty_output(i);
         }
      }
      getch();
      crt_inverse();
   }
}

void test_output()
{
   char* p = "´e1‘w2Ða3­A4¶a. ¤eˆs¯s“¡”a.";
   char16 buf[100];
   int i;

   tty_range();
   tty_output("     012345678901234567890123456789012345678901234567890123456789");
   str_make(buf,p);
   forcnt (i,29)
   {
      tty_xy(4,i+1);
      tty_output('>');
      getch();
      tty_output(buf,i,20);
      tty_output('<');
   }
}

void test_output2()
{
   char* p = "´e1‘w2Ða3­A4¶a. ¤eˆs¯s“¡”a.";
   int i;

   tty_range();
   tty_output("     012345678901234567890123456789012345678901234567890123456789");
   forcnt (i,29)
   {
      tty_xy(4,i+1);
      tty_output('>');
      getch();
      tty_output(p,i,20);
      tty_output('<');
   }
}

void test_output3()
{
   hangul ch('´','e');
   tty_output('*');
   tty_output(ch);
   tty_output('*');
   tty_output_left(ch);
   tty_output('*');
   tty_output_right(ch);
   tty_output('*');
}

void main()
{
   easy_han_output_init();
   easy_han_output_on();
   //han_test();
   //eng_test();
   //test_output();
   //test_output2();
   test_output3();
   getch();
}
