#define USE_SYNTAX
#define USE_PGMEM
#define USE_PGMCNV
#define USE_PGMXMS
#define USE_STDIO
#define USE_STDLIB
#define USE_MEM
#define USE_ERROR


#include <pub\config.hpp>
#include <inccnt.list.hpp>

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
         table[table_cnt].seed=table_cnt; //rand();
         printf("alloc page %d with %X\n",table_cnt,table[table_cnt].seed);
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


void alloc_and_set_page()
{
   printf("page allocation: ");
   table_cnt=0;
   try
   {
      while(table_cnt<pg_mem_page_cmax)
      {
         table[table_cnt].pgm.alloc();
         table[table_cnt].seed=table_cnt; //rand();
         void* p=table[table_cnt].pgm.lock();
         mem_set_16(p,table[table_cnt].seed,pg_mem_page_size/2);
         ASSERT(sh_mem_check_bp(p));
         table[table_cnt].pgm.unlock();
         printf("alloc and set page %d with %X\n",table_cnt,table[table_cnt].seed);
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
      printf("set page %d with %X\n",i,table[i].seed);
   }
   printf("press a key");
   getchar();
}


void compare_data()
{
   word i,j;
   void* p;
   forcnt(i,table_cnt)
   {
      p=table[i].pgm.lock();
      printf("compare data: page %d : table val %X , page val %X %X\n",
         i,table[i].seed,*(uint16*)p,*((uint16*)p+1)
         );
     /**/ table[i].pgm.unlock();
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
         if ( *((uint16*)p+j)!=table[i].seed ) halt("not match");
      }

      table[i].pgm.unlock();
      printf("verify page %d with %X OK\n",i,table[i].seed);
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
      printf("free page %d\n",i);
   }
   printf("press a key");
   getchar();
}

void cdecl main(void)
{
//   printf("size of pg_mem %d\n",sizeof (pg_mem));
//   halt();
   pg_mem_xms::max_size_k(1024);
   pg_mem_cnv::init();
   pg_mem_xms::init();
   pg_mem::init();

   alloc_page();
   set_page();
   compare_data();
   verify_page();

   free_page();
// verify_page();

// alloc_page();
// set_page();
// verify_page();

}

