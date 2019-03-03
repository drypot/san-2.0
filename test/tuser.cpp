
#include <pub\config.hpp>
#include <pub\easyhan.hpp>
#include <stdpub\io.hpp>
#include <pub\macro.hpp>
#include <pub\window.hpp>
#include <cnt\array.hpp>
#include <pub\user.hpp>

void test_string()
{
   #define BUF_SIZE 20
   array<char,BUF_SIZE> buf;
   int v,i;
   v = 0;

   tty_xy(0,0);
   forcnt(i,80) tty_output('0' + i%10);

   forcnt(i,30)
   {
      tty_xy(0,i);
      tty_output('0' + i%10);
      tty_xy(21,i);
      tty_output('<');
   }

   buf[0]= 0;
   forcnt (v,30)
   {
      if (!user_string(&rect(1,v+1,20,v+1),"data:",buf,BUF_SIZE)) break;
      ASSERT(buf.check());
      tty_range();
      tty_xy(40,v+1);
      tty_output(buf);
      tty_output('<');
   }
}

void test_yes_no_sub(bool b)
{
   static int v = 0;
   bool result;
   rect rc(0,v,40,v);
   char buf[80];

   result = user_yes_no (&rc, "hello", &b);
   sprintf(buf,"bool : %d,  result : %d",(int)b, (int)result);
   tty_range();
   tty_xy(40,v);
   tty_output(buf);
   v++;
}

void test_yes_no()
{
   test_yes_no_sub(TRUE);
   test_yes_no_sub(TRUE);
   test_yes_no_sub(TRUE);
   test_yes_no_sub(TRUE);
   test_yes_no_sub(FALSE);
   test_yes_no_sub(FALSE);
   test_yes_no_sub(FALSE);
   test_yes_no_sub(FALSE);
   key_wait_make();
}

void main()
{
   easy_han_output_init();
   easy_han_output_on();
   easy_han_input_init();
   easy_han_input_on();

   macro_init("san.bin");
   window::init(80*30);

   test_string();
   //test_yes_no();
}


