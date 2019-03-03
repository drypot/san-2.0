
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\stdlib.hpp>
#include <pub\mem.hpp>
#include <pgpub\mem.hpp>
#include <pgmcnv.hpp>
#include <pgmxms.hpp>
#include <pgmdisk.hpp>

struct pair
{
   pg_mem pgm;
   uint16 seed;
};

pair table[pg_mem_page_cmax];
word table_cnt;

void alloc_page()
{
   printf("page allocation: ");
   table_cnt=0;
   try
   {
      while(table_cnt<pg_mem_page_cmax)
      {
         table[table_cnt].pgm.alloc();
         table[table_cnt].seed=rand();
         printf("alloc page %d with %X \t free_space_k = %ld\n",table_cnt,table[table_cnt].seed,pg_mem::space_k());
         table_cnt++;
      }
      printf("max pages (%d) allocated.\n",table_cnt);
   }
   catch( pg_mem::err_no_mem )
   {
      printf("%d pages allocated.\n",table_cnt);
   }
   printf("total %d KB allocated.\n",table_cnt*pg_mem_page_size_k);
   printf("press a key");
   getchar();
}

void set_page()
{
   word i;
   void* p;
   forcnt(i,table_cnt)
   {
      p=table[i].pgm.lock();
      mem_set_16(p,table[i].seed,pg_mem_page_size_k*1024/2);
      ASSERT(sh_mem_check_bp(p));
      table[i].pgm.unlock();
      printf("set page %d with %X \t free_space_k = %ld\n",i,table[i].seed,pg_mem::space_k());
   }
   printf("press a key");
   getchar();
}

void verify_page()
{
   word i,j;
   void* p;
   forcnt(i,table_cnt)
   {
      p=table[i].pgm.lock();
      forcnt(j,pg_mem_page_size_k*1024/2)
      {
         if ( *((uint16*)p+j)!=table[i].seed ) halt("at veify_page");
      }
      table[i].pgm.unlock();
      printf("verify page %d with %X OK \t free_space_k = %ld\n",i,table[i].seed,pg_mem::space_k());
   }
   printf("press a key");
   getchar();
}

void free_page()
{
   word i;
   forcnt(i,table_cnt)
   {
      table[i].pgm.free();
      printf("free page %d \t free_space_k = %ld\n",i,pg_mem::space_k());
   }
   printf("press a key");
   getchar();
}

extern unsigned _stklen=32767;

void cdecl main(void)
{
   //pg_mem_cnv::free_min_k(128);

   pg_mem_xms::max_k(1024);
   pg_mem_xms::init();
   pg_mem_disk::init("san.swp");
   pg_mem_cnv::init();
   pg_mem::init();

   printf("pg_mem free size = %d k\n",pg_mem::space_k());
   getchar();

   alloc_page();
   set_page();
   verify_page();

   free_page();
   //verify_page();

   alloc_page();
   set_page();
   verify_page();

   printf("pg_mem free size = %d k\n",pg_mem::space_k());
   getchar();
}

