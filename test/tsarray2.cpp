
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\except.hpp>
#include <pub\inline.hpp>
#include <pub\char.hpp>
#include <cnt\sarray.tem>
#include <conpub\io.hpp>
#include <time.h>
#include <pub\buffer.hpp>
#include <pub\fbuf.hpp>

typedef sarray<char16,8*1024> arrayt;

//char* fname = "fmid";
char* fname = "fbig";

buffer<char16,8*1024> buf;
arrayt ary;
clock_t clk;
FILE* f;
int32 cnt,i;


void view(arrayt* pa)
{
   arrayt::frame* p;

   p = pa->head.p_next;
   while (p!= (arrayt::frame*) &pa->tail)
   {
      printf("%4d ",p->cnt);
      p = p->p_next;
   }
   printf("\n");
}

void iter_test()
{
   printf("iter ready\n");
   getch();
   printf("iter start\n");
   clk = clock();
   forcnt(i,cnt) ary[i]=ary[i]+1;
   printf("%u clocks\n",clock()-clk);
   printf("end\n");
}

void fread_test()
{
   //ifbuf f("fbig",32*1024);
   int ch;

   cnt = 0;
   buf.reset();
   ary.reset();
   f = fopen(fname,"rb");
   printf("ready\n");
   getch();
   printf("start\n");
   clk = clock();
   while (ch = fgetc(f) , ch != EOF) ary[cnt++] = ch;
   printf("%u clocks\n",clock()-clk);
   printf("%d chars\n",cnt);
   fclose(f);
}

void fread2_test()
{
   //ifbuf f("fbig",32*1024);
   int ch;
   int ch2;

   cnt = 0;
   buf.reset();
   ary.reset();
   f = fopen(fname,"rb");
   printf("ready\n");
   getch();
   printf("start\n");
   clk = clock();
   while (ch = fgetc(f) , ch != EOF)
   {
      cnt++;
      if (is_full((byte)ch))
      {
         ch2 = fgetc(f);
         buf.append(char16_make(ch,ch2));
      }
      else buf.append(ch);
      if (buf.is_full())
      {
         ary.locate_end();
         ary.insert(buf.cnt());
         ary.read(buf,buf.cnt());
         buf.reset();
         //view(&ary);
         //getch();
      }
   }
   printf("%u clocks\n",clock()-clk);
   printf("%d chars\n",cnt);
   fclose(f);
}

void fread3_test()
{
   ifbuf f(fname,16*1024);
   int ch;
   int ch2;

   cnt = 0;
   buf.reset();
   ary.reset();
   printf("ready\n");
   getch();
   printf("start\n");
   clk = clock();
   forever
   {
      if ( f.rest() <= 2 )
      {
         if ( f.file_rest() == 0 )
         {
            if ( f.rest() == 1 && is_full(f.peek8()) ) f.append(0);
            if ( f.rest() == 0 ) break;
         }
         else f.fill();
      }
      ch = f.get8();
      cnt++;
      if (is_full((byte)ch))
      {
         ch2 = f.get8();
         buf.append(char16_make(ch,ch2));
      }
      else buf.append(ch);
      if (buf.is_full())
      {
         ary.locate_end();
         ary.insert(buf.cnt());
         ary.read(buf,buf.cnt());
         buf.reset();
         //view(&ary);
         //getch();
      }
   }
   printf("%u clocks\n",clock()-clk);
   printf("%d chars\n",cnt);
}

void main()
{
   touch_err_module();
   throw int();
   fread_test();
   fread2_test();
   //fread3_test();
   //test_iter();
}
