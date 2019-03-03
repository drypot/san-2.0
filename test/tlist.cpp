
#include <pub\config.hpp>
#include <cnt\list.tem>
#include <stdpub\io.hpp>

circular_list<int> list;

void test_link_next()
{
   list.link_next();
   list.next();
   list.ref() = 10;

   list.link_next();
   list.next();
   list.ref() = 20;

   list.link_next();
   list.next();
   list.ref() = 30;

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());
}

void test_unlink_cur()
{
   list.link_next();
   list.next();
   list.ref() = 10;

   list.link_next();
   list.next();
   list.ref() = 20;

   list.link_next();
   list.next();
   list.ref() = 30;

   list.next();
   list.next();
   list.unlink_cur();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());
}

void test_unlink_cur2()
{
   list.link_next();
   list.next();
   list.ref() = 10;

   list.link_next();
   list.next();
   list.ref() = 20;

   list.link_next();
   list.next();
   list.ref() = 30;

   printf("%d ",list.ref());
   list.unlink_cur();

   printf("%d ",list.ref());
   list.unlink_cur();

   printf("%d ",list.ref());
   list.unlink_cur();

   //printf("%d ",list.ref());
   list.unlink_cur();
}

void test_first()
{
   list.link_next();
   list.next();
   list.ref() = 10;

   list.link_next();
   list.next();
   list.ref() = 20;

   list.link_next();
   list.next();
   list.ref() = 30;

   list.first();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());

   list.next();
   printf("%d ", list.ref());
}

void test_con_dest()
{
   struct base_struct
   {
      base_struct() { printf("base construct\n"); }
     ~base_struct() { printf("base destruct\n"); }
   };

   struct test_struct
   {
      int data;
      base_struct bs;

      test_struct() { printf("constrcut\n"); }
     ~test_struct() { printf("destruct %d\n",data); }
   };

   circular_list<test_struct> list;

   list.link_next();
   list.next();
   list.ref().data = 10;

   list.link_next();
   list.next();
   list.ref().data = 20;

   list.link_next();
   list.next();
   list.ref().data = 30;

   list.next();
   printf("%d ", list.ref().data);

   list.next();
   printf("%d ", list.ref().data);

   list.next();
   printf("%d ", list.ref().data);

   list.next();
   printf("%d ", list.ref().data);
}

void test_iter()
{
   list.link_next();
   list.next();
   list.ref() = 10;

   list.link_next();
   list.next();
   list.ref() = 20;

   list.link_next();
   list.next();
   list.ref() = 30;

   list.first();
   list.next();
   circular_list_iter<int> iter(&list);
   int cnt = 3;
   while (cnt--)
   {
      printf("%d\n", iter.ref());
      iter.next();
      if (cnt == 2) list.unlink_cur();
   }
   printf("%d\n", iter.ref());
   iter.next();
   printf("%d\n", iter.ref());
   iter.next();
}

void main()
{
   //list.ref() = 10;
   //list.unlink_cur();

   //list.next();
   //list.ref() = 10;

   //list.prev();
   //list.ref() = 10;

   //test_link_next();
   //test_unlink_cur();
   //test_unlink_cur2();
   //test_first();
   //test_con_dest();
   test_iter();
}
