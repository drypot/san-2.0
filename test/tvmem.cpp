
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\stdlib.hpp>
#include <pub\except.hpp>
#include <pub\mem.hpp>
#include <cnt\array.hpp>
#include <pgpub\mem.hpp>
#include <pgmcnv.hpp>
#include <pgmxms.hpp>
#include <vpub\mem.hpp>

#define table_cmax 510
#define frame_size (4096)

array<byte,frame_size> frame;
vmem vm;

void info(char* name, int i)
{
   printf("%s: i=%d   vm_size=%dk   pg_mem_free = %d k\n",name,i,word(vm.size()/1024),pg_mem::space_k());
}

void ins1()
{
   printf("INS 1 -------------------\n");

   vm.lock();

   int i;
   forcnt(i,table_cmax)
   {
      mem_set_16(frame,i,frame_size/2);
      ASSERT( frame.check() );
      vm.seek_end(0);
      vm.insert(frame,frame_size);
      info("ins1",i);
      i++;
   }
   vm.unlock();
}


void ins2()
{
   printf("INS 2 -------------------\n");
   vm.lock();
   vm.seek(0);

   int i;
   forcnt(i,table_cmax)
   {
      i++;
      mem_set_16(frame,i,frame_size/2);
      ASSERT( frame.check() );
      vm.seek_cur(frame_size);
      vm.insert(frame,frame_size);
      vm.seek_cur(frame_size);
      info("ins2",i);
   }
   vm.unlock();
}

void check()
{
   printf("CHECK --------------------------\n");

   vm.lock();
   vm.seek(0);
   int i,j;
   forcnt(i,table_cmax)
   {
      vm.read(frame,frame_size);
      ASSERT(frame.check());
      forcnt(j,frame_size/2)
      {
         if ( *((uint16*)(void*)frame+j)!=i ) halt("not match");
      }
      vm.seek_cur(frame_size);
      printf("verify: table=%d OK\n",i);
   }
   vm.unlock();
   printf("press a key");
   getchar();

}

void free1()
{
   printf("FREE 1 -------------------\n");

   vm.lock();
   vm.seek(0);

   int i;
   forcnt(i,table_cmax)
   {
      vm.remove(frame_size);
      printf("free1: i=%d   vm_size=%dk   pg_mem_free = %d k\n",i,word(vm.size()/1024),pg_mem::space_k());
      i++;
      vm.seek_cur(frame_size);
      info("free1",i);
   }
   vm.unlock();
}

void check2()
{
   printf("CHECK 2--------------------------\n");

   vm.lock();
   vm.seek(0);
   int i,j;
   forcnt(i,table_cmax)
   {
      i++;
      vm.read(frame,frame_size);
      ASSERT(frame.check());
      forcnt(j,frame_size/2)
      {
         if ( *((uint16*)(void*)frame+j)!=i ) halt("not match");
      }
      vm.seek_cur(frame_size);
      printf("check2: verify: table=%d OK\n",i);
   }
   vm.unlock();
   printf("press a key");
   getchar();

}

void destruct_test()
{
   vmem vm;

   vm.lock();
   vm.insert(frame,frame_size);
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
}

extern unsigned _stklen=32767U;

void cdecl main(void)
{
   pg_mem_xms::init();
   pg_mem_cnv::init();
   pg_mem::init();

   /*
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();

   destruct_test();

   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   */

   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   ins1();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   ins2();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   check();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   free1();
   printf("free size: %ld k\n",pg_mem::space_k());
   getchar();
   check2();

   halt("bye");
}



