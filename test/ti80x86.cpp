#define USE_STDIO
#define USE_I80X86
#define USE_SYNTAX

#include <pub\config.hpp>
#include <inccnt.list.hpp>

void cdecl main(void)
{
   cnt j;
   void* p;

   p=(void*) 0xA0100000UL;

   forcnt(j,32)
   {
      printf("%lp %lp\n",p,i8086_offset_ceiling(p));
      ((char*)p)++;
   }
}

