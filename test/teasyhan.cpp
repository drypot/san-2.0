
#include <pub\config.hpp>
#include <pub\easyhan.hpp>
#include <conio.h>

void main(void)
{
   char* a = "* �A�b�a�e �� ���a�a���᷁ ���w �b���A ���e ���w�i �a�� �g�s���a.";
   char* b = "* �A�b�a�e �� ���a�a����A ���e ϡЁ�A ��Ё ���w�i �����i ���� �g�s���a.";
   char* c = "* �� �a���a���e ������� �����a. �q�A ͡�q�E ��w �����i�i ���ẁ�����a.";

   easy_han_output_init();
   easy_han_output_on();

   tty_output(a);

   tty_xy(0,1);
   tty_output(b);

   tty_xy(0,2);
   tty_output(c);

   getch();
}
