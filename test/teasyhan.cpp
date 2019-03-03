
#include <pub\config.hpp>
#include <pub\easyhan.hpp>
#include <conio.h>

void main(void)
{
   char* a = "* ¹A¸b¸a“e ·¡ ­¡ÏaËa¶Á´á· ¸÷¬w ¸b•·µA ”Ðe ¥¡»w·i Ða»¡ ´g¯s“¡”a.";
   char* b = "* ¹A¸b¸a“e ·¡ ­¡ÏaËa¶Á´áµA ·Ðe Ï¡ÐµA ”Ð ¤¬wÐi ·¢Ÿi »¡»¡ ´g¯s“¡”a.";
   char* c = "* ·¡ Ïa¡‹aœ‘·e ®Á´á¶Á´á ·³“¡”a. ÐqA Í¡Ðq–E ¬é¡w ÑÁ·©—i·i ·ª´áº¯³¯¡¶a.";

   easy_han_output_init();
   easy_han_output_on();

   tty_output(a);

   tty_xy(0,1);
   tty_output(b);

   tty_xy(0,2);
   tty_output(c);

   getch();
}
