#define USE_SYS
#define USE_SYNTAX
#define USE_PGMEM
#define USE_PGMCNV
#define USE_PGMXMS
#define USE_STDIO
#define USE_STDLIB
#define USE_MEM
#define USE_ERROR
#define USE_VAR
#define USE_PGMSTK

#include <pub\config.hpp>
#include <inccnt.list.hpp>

#define table_cmax 63
#define frame_max 32000

array<byte,frame_max> frame;
word table[table_cmax];
int cnt; // table_cnt
uint32 total;
pgm_stack stack;

void test_push()
{
   printf("page allocation: ");
   cnt=0;
   total=0;
//   try
 //  {
      while(cnt<table_cmax)
      {
         table[cnt]=frame_max; //rand()%frame_max;
         mem_set_16(frame,table[cnt],table[cnt]/2);
         ASSERT( frame.check() );
         stack.push(frame,table[cnt]);
         total+=table[cnt];
         printf("alloc : cnt=%d seed=%x , total size=%d k\n",cnt,table[cnt], int(total/1024) );
         cnt++;
      }
/*   }
   catch( pg_mem::err_no_mem )
   {
      printf("exception!\n");
   }
*/
   printf("press a key");
   getchar();
}

void test_pop()
{
   int i,j;
   fordec(i,cnt-1,0)
   {
      stack.pop(frame,table[i]);
      forcnt(j,table[i]/2)
      {
         if ( *((uint16*)(void*)frame+j)!=table[i] ) halt("not match");
      }
      printf("verify: table=%d OK\n",i);
   }
   printf("press a key");
   getchar();
}

void destruct_test()
{
   pgm_stack stack;

   stack.push(frame,frame_max-10);
   stack.push(frame,frame_max-20);
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
}

void cdecl main(void)
{
   pg_mem_cnv::init();
   pg_mem_xms::init();
   pg_mem::init();

   sys_x_buffering_err_msg();
   /*
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();

   destruct_test();

   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();

   halt("bye");
   */

   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   test_push();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   //test_pop();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();

}


