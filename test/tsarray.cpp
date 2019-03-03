
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\stdlib.hpp>

#ifdef CL_BORLAND
#define mem_alloc heap::alloc
#define mem_free heap::free
#define touch(x) ((void)x)
#define int32 int
#include <x:\lib\cnt\sarray.hpp>
#include <x:\lib\cnt.sarray.tem>
#else
#include <cnt\sarray.tem>
#endif

#include <conio.h>

#define CMAX 13
typedef sarray<int16,CMAX> array;
array ary,ary2;

void view(array* pa)
{
   array::frame* p;
   int i,j;

   p = pa->head.p_next;
   j=0;
   while (p!= (array::frame*) &pa->tail)
   {
      forcnt(i,p->cnt) printf("*");
      while(i++<CMAX) printf("-");
      printf("\n");
      p = p->p_next;
      j++;
      if (j==20)
      {
         printf("pause\n");
         getch();
         j=0;
      }
   }
}

void set()
{
   int i;
   ary.reset();
   ary.expand(100);
   forcnt(i,100)
   {
      ary[i] = i;
   }
   forcnt(i,100) ASSERT(ary[i]==i);
}

void print_h()
{
   printf("------------------------------------------\n");
}

void title(char* name)
{
   printf("%s %%%%%%%%%%%%%%%%%%%\n",name);
}

void test_insert()
{
   title("insert");

   int i,v;
   ary.reset();
   forcnt(i,50)
   {
      v = i*2;
      ary.append();
      ary[i] = v;
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
      view(&ary);
      getch();
   }
   print_h();
   forcnt(i,50)
   {
      v = i*2+1;
      ary.locate(v);
      ary.insert(1);
      ary.ref() = v;
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
      view(&ary);
      getch();
   }

   forcnt(i,100) ASSERT(ary[i]==i);
}

void test_insert2()
{
   title("insert2");

   int i,j,v;
   ary.reset();
   forcnt(i,10)
   {
      v = i*10;
      ary.append();
      ary[i] = v;
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
      view(&ary);
      getch();
   }
   print_h();
   forcnt(i,10)
   {
      v = i*10+1;
      ary.locate(v);
      ary.insert(9);
      forcnt(j,9) ary[v+j] = v+j;
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
      view(&ary);
      getch();
   }

   forcnt(i,100) ASSERT(ary[i]==i);
}

void test_clear()
{
   title("clear");
   test_insert2();
   getch();
   ary.reset();
   getch();
   test_insert();
}

void test_remove()
{
   title("remove");

   int i,v;
   ary.reset();
   forcnt(i,100)
   {
      v = i;
      ary.append();
      ary[i] = v;
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
   }
   forcnt(i,50)
   {
      v = i;
      ary.locate(v);
      ary.remove(1);
      printf("i = %d \t val = %d \t cnt=%d\n",i,v,ary.cnt());
      view(&ary);
      getch();
   }
   print_h();
   forcnt(i,50) ASSERT(ary[i]==i*2+1);
}

void test_remove2()
{
   title("remove2");

   int i;

   set();
   ary.locate(20);
   ary.remove(20);
   forcnt(i,20) ASSERT(ary[i]==i);
   forcnt(i,60) ASSERT(ary[i+20]==i+20+20);
   view(&ary);
   getch();
   print_h();
   ary.locate(30);
   ary.remove(30);
   forcnt(i,20) ASSERT(ary[i]==i);
   forcnt(i,10) ASSERT(ary[i+20]==i+20+20);
   forcnt(i,20) ASSERT(ary[i+30]==i+30+20+30);
   view(&ary);
   getch();
}

void test_write()
{
   title("test_read");

   int i,v;

   ary2.reset();

   set();
   forcnt(i,50)
   {
      v = i;
      ary.locate(v);
      ary.remove(1);
   }
   forcnt(i,50) ASSERT(ary[i]==i*2+1);

   ary.locate(0);
   ary2.locate(0);
   ary2.insert(50);
   ary2.write(ary,50);
   forcnt(i,50) ASSERT(ary[i]==i*2+1);
   forcnt(i,50) ASSERT(ary2[i]==i*2+1);
}

void test_write2()
{
   title("test_read2");

   int16 table[100];
   int i;

   forcnt(i,100) table[i]=i;
   ary.reset();
   ary.insert(100);
   ary.write(table,100);
   forcnt(i,100) ASSERT(ary[i]==i);
}

void test_read()
{
   title("test_write");

   int16 table[100];
   int i;

   set();
   ary.locate(0);
   ary.read(table,100);
   forcnt(i,100) ASSERT(table[i]==i);
}

void test_break_frame()
{
   ary.p_cur_frame->room[7] = 10;
}

void main()
{
   //test_insert();
   //test_insert2();
   //test_remove();
   //test_remove2();
   //test_clear();
   //test_write();
   //test_write2();
   test_read();
}

