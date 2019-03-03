
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <pub\stdlib.hpp>
#include <pub\except.hpp>
#include <charcnt.list.hpp>
#include <pub\mem.hpp>
#include <cnt\paper.hpp>
#include <conpub\io.hpp>
#include <stdpub\io.hpp>
#include <pub\easyhan.hpp>

paper text;
ppy top;

void move(int adder)
{
   top += adder;
   if (top<0) top = 0;
   ef (top>=text.line_cnt()) top = text.line_cnt() - 1;
}

void set(char* name)
{
   text.fread(name);
}

void puts(char16* str)
{
   while (*str) putchar(*str++);
   putchar('\n');
}

void print_line_cnt()
{
   gotoxy(1,25);
   cprintf("%ld",text.line_cnt());
}

void print()
{
   int i=0,len;
   int ch;
   char buf[100];

   while (top + i < text.line_cnt() && i<24)
   {
      int j=0;
      memset(buf,' ',80);
      text.locate(top+i);
      len = text.line_len();
      if (len>79) len = 79;
      j=0;
      while (len--)
      {
         ch = text.read(j);
         buf[j++]=ch;
      }
      buf[j++]='<';
      buf[80]=0;

      gotoxy(1,i+1);
      cputs(buf);
      i++;
   }

   memset(buf,' ',80);
   buf[80]=0;
   while ( i<24 )
   {
      gotoxy(1,i+1);
      cputs(buf);
      i++;
   }
}

void test_io()
{
   int ch;

   do
   {
      //gotoxy(10,25);
      //cprintf("%ld mem_free=%ld k  pg_mem_free=%ld k",num,mem_space_k(),pg_mem::space_k());
      print();
      ch=getch();
      switch ( ch )
      {
         case 'r':  move(-24); break;
         case 'c':  move(24); break;
         case 'e':  move(-1); break;
         case 'x':  move(1); break;
         case 'w':  text.fwrite("test.wr"); break;
      }
   } while ( ch!='q' );
}

void test_reset()
{
   text.reset();
   print_line_cnt();
   print();
}

void test_edit1()
{
   text.locate(4);
   text.insert_line_below(5);
   print_line_cnt(); print(); getch();

   text.locate(2);
   text.insert_line_below(4);
   text.insert_line(3);
   print_line_cnt(); print(); getch();

   text.locate(0);
   text.insert_line_below(2);
   text.insert_line(1);
   print_line_cnt(); print(); getch();

   text.locate(0);
   text.remove_line();
   text.remove_line_below(2);
   print_line_cnt(); print(); getch();

   text.locate(2);
   text.remove_line(3);
   text.remove_line_below(4);
   print_line_cnt(); print(); getch();

   text.locate(4);
   text.remove_line_below(5);
   print_line_cnt(); print(); getch();
}

void test_edit2()
{
   print(); getch();

   text.locate(0);
   text.clear();
   print_line_cnt(); print(); getch();

   text.locate(2);
   text.expand(10);
   print_line_cnt(); print(); getch();

   text.locate(1);
   text.truncate(5);
   print_line_cnt(); print(); getch();

   text.locate(3);
   text.insert(5,10);
   text.fill(5,'*',10);
   print_line_cnt(); print(); getch();

   text.locate(2);
   text.remove(1,3);
   print_line_cnt(); print(); getch();

   text.locate(1);
   text.fill(10,'%',5);
   print_line_cnt(); print(); getch();

   text.locate(0);
   text.insert(5,5);
   print_line_cnt(); print(); getch();

   text.locate(0);
   text.join(20);
   print_line_cnt(); print(); getch();

   text.locate(3);
   text.separate(5);
   print_line_cnt(); print(); getch();
}

void test_read()
{
   char16 buf[100];
   int i;

   text.locate(1);

   forcnt(i,50) buf[i] = '%';
   text.read(5,buf,5);
   puts(buf);

   forcnt(i,50) buf[i] = '%';
   text.read(5,buf,10);
   puts(buf);

   forcnt(i,50) buf[i] = '%';
   text.read(15,buf,10);
   puts(buf);
}

void test_write()
{
   char16 str[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

   text.locate(0);
   text.write(3,'A');
   print(); getch();

   text.locate(0);
   text.write(4,'B');
   print(); getch();

   text.locate(0);
   text.write(5,'C');
   print(); getch();

   text.locate(0);
   text.write(6,'D');
   print(); getch();

   text.locate(0);
   text.write(7,'E');
   print(); getch();

   text.locate(1);
   text.write(5,str,7);
   print(); getch();
}

void main(int argc, char* argv[])
{
   if (argc!=2) return;
   sys_exit_msg_buffering_off();
   clrscr();

   easy_han_input_init();
   easy_han_output_init();
   easy_han_input_on();
   easy_han_input_off();
   easy_han_output_on();
   easy_han_output_off();
   set(argv[1]);
   test_io();
   //test_reset();
   //test_edit1();
   //test_edit2();
   //test_read();
   //test_write();
}
