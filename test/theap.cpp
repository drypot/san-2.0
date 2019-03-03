
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <pub\inline.hpp>
#include <pub\except.hpp>
#include <stdpub\io.hpp>
#include <pub\string.hpp>
#include <pub\heap.hpp>

void test_alloc()
{
   void* p;

   try {
      p=mem_alloc(4);
      memset(p,0xF2,4);
      ASSERT(mem_check(p));
      printf("-- %d\n",sh_mem_body_size_bp(p));

      p=mem_realloc(p,5);
      memset(p,0xEE,6);
      ASSERT(mem_check(p));
      printf("-- %d\n",sh_mem_body_size_bp(p));
      mem_free(p);

      p=mem_alloc(5);
      byte* pb=(byte*)p;
      pb[7]=0;
      printf("-- %d\n",sh_mem_body_size_bp(p));
      ASSERT(mem_check(pb));
      }
   catch ( mem_err_no_mem ) {
      halt("no more memory");
      }
}

class class_a
{
   char* str;

   public:

   class_a(char* s);
   class_a();

   ~class_a();

};

class_a::class_a()
{
   static char* ary[]
   = { "one" , "two", "three" , "four"};
   static int i;

   str=ary[i++];
   printf("construct () A: %s\n",str);
}

class_a::class_a(char* s) : str(s)
{
   printf("construct A : %s\n",str);
}

class_a::~class_a()
{
   printf("destruct A : %s\n",str);
}

void test_new()
{
   class_a* pa;

   pa=mem_array_alloc(class_a,3);
   ASSERT(mem_check(pa));
   mem_array_free(pa);

   /*pa=mem_array_alloc(class_a(),3);
   ASSERT(mem_check(pa));
   mem_array_free(pa);*/

   /*pa=new class_a[3];
   ASSERT(mem_check(pa));
   delete[] pa;*/
}

void main(void)
{
   printf("mem test...............\n");
   test_new();
   //test_alloc();
}

