#define USE_SYNTAX
#define USE_STDIO
#define USE_XMSBLK
#define USE_ERROR
#define USE_MEM

#include <pub\config.hpp>
#include <inccnt.list.hpp>

byte table[10][1024];
   xms_blk xb;

void print_tb()
{
   int i;
   forcnt(i,10)
   {
      printf("%2d ",int(table[i][0]));
   }
   printf("\n");
}

int cdecl main(void)
{
   cnt i,j;

   xb.alloc_k(10);
   forcnt(i,10)
   {
      memset(table[i],i,1024);
      xb.move_reset(i*1024);
      xb.move_to_xms(table[i],1024);
      printf("set %d page\n",i);
   };
   print_tb();

   memset(table,GARBAGE_BYTE,sizeof(table));
   print_tb();
   forcnt(i,10)
   {
      xb.move_reset(i*1024);
      xb.move_from_xms(table[i],1024);
      forcnt(j,1024)
      {
         ASSERT(table[i][j]==i);
      }
      printf("check %d page\n",i);
   }
   print_tb();
   return 0;
}


