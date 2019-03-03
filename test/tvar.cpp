#define USE_VAR
#define USE_STDIO
#define USE_IOSTREAM

#include <pub\config.hpp>
#include <inccnt.list.hpp>

void test1 () {
   /*
   local_var<char,15> name_buf;

   strcpy(name_buf,"hello world");
   ASSERT(name_buf.check());
   cout << (char*)name_buf << endl;
   name_buf[0]='H';
   name_buf[1]='E';
   name_buf[2]='L';
   ASSERT(name_buf.check());
   cout << (char*)name_buf << endl;
   name_buf[14]='H';
   //name_buf[15]='H';
   strcpy(name_buf,"1234567890123456");
   ASSERT(name_buf.check());
   return 0;
   */
   }

void test2() {

   array<int,3> a;

   a[0]=10;
   ASSERT(a.check());
   a[1]=20;
   ASSERT(a.check());
   a[2]=30;
   ASSERT(a.check());
   //a[3]=40;
   *(a+3)=40;
   ASSERT(a.check());
   }

int cdecl main(void) {
   test2();
   }
   




