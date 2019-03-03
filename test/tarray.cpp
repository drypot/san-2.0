#define USE_SYNTAX
#define USE_ARRAY
#define USE_STDIO
#define USE_IOSTREAM

#include <pub\config.hpp>
#include <inccnt.list.hpp>

/*
struct int_node : dl_rearray_rec
{
   int val;
};

dl_rearray<int_node> dr_array(cntl_x_construct);
dl_rec_circular_list<int_node> dr_list(dr_array,cntl_x_construct);
dl_rec_circular_list<int_node> dr_list_2(dr_array,cntl_x_construct);

void test_dl_array()
{
   try
   {
      dr_array.construct(10);
      dr_list.construct();
      dr_list_2.construct();

      //
      // test array
      //

      #if 0
         int i;
         printf("index : rec_cnt : alloc_cnt : free_cnt \n");
         forcnt (i,20)
         {
            index j=dr_array.alloc();
            printf
            (
               "%d\t %d\t %d\t %d\t \n",
               j,
               dr_array.get_rec_cnt(),
               dr_array.get_allocation_cnt(),
               dr_array.get_free_cnt()
            );
         }
      #endif

      //
      // test list allocation
      //

      #if 0
         #define pr() \
            printf \
            ("%d\t %d\t %d\t %d\t %d\t\n", \
               dr_array.get_rec_cnt(),            \
               dr_array.get_allocation_cnt(),     \
               dr_array.get_free_cnt(),           \
               j1,                                \
               dr_list.get_allocation_cnt()      \
            )

         printf(" ar_rec_cnt : ar_alloc_cnt : ar_free_cnt :: list_get_index : list_alloc_cnt \n");
         index j1;
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
         j1=dr_list.alloc(); pr();
      #endif

      //
      // multi list and free test
      //

      #if 0
         #define pr() \
            printf \
            ("%d\t %d\t %d\t || %d\t %d\t || %d\t %d\t \n", \
               dr_array.get_rec_cnt(),            \
               dr_array.get_allocation_cnt(),     \
               dr_array.get_free_cnt(),           \
               j1,                                \
               dr_list.get_allocation_cnt(),      \
               j2,                              \
               dr_list_2.get_allocation_cnt()      \
            )

         printf(" ar_rec_cnt : ar_alloc_cnt : ar_free_cnt :: list_get_index : list_alloc_cnt \n");
         index j1,j2;
         j1=dr_list.alloc(); j2=dr_list_2.alloc(); pr();
         j1=dr_list.alloc(); j2=dr_list_2.alloc();pr();
         dr_list.free_tail();                           pr();
         j1=dr_list.alloc(); j2=dr_list_2.alloc();pr();
                                 dr_list_2.free_tail();   pr();
         j1=dr_list.alloc(); j2=dr_list_2.alloc();pr();
         j1=dr_list.alloc(); j2=dr_list_2.alloc();pr();
      #endif

      //
      //  print data;
      //

      #if 1
         printf("i)insert <num>     d)elete tail <num>    f)free <num>   m)move_to_head <num>\n");
         while (cin)
         {
            char ch;
            int val;
            word j,h;

            cin >> ch >> val;

            switch (ch)
            {
               case 'i' :
                  j= dr_list.alloc();
                  dr_list[j].val=val;
                  break;
               case 'd' :
                  dr_list.free_tail();
                  break;
               case 'm' :
                  dr_list.move_to_head(val);
                  break;
               case 'f' :
                  dr_list.free(val);
                  break;
            };

            printf("word    prev     next     val     tail_val\n");
            j=h=dr_list.get_head_index();
            while ( (j=dr_array[j].next) != h )
            {
               printf("%d \t %d \t %d \t %d \t %d\n",j,dr_list[j].prev,dr_list[j].next,dr_list[j].val,dr_list.get_tail().val);
            }
         }
      #endif

   }
   catch ( mem_err_no_mem )
   {
      printf("heap: no_mem\n");
   }
   catch ( dl_rearray<int_node>::err_no_rec )
   {
      printf("dl_rearray: no_rec\n");
   }
}
*/

void test_ins_rem()
{
   struct T
   {
      int val;

      T()
      {
         printf("construct\n");
         getchar();
         val=10;
      }

      ~T()
      {
         printf("destruct\n");
         getchar();
         val=20;
      }

      int operator = ( int v )
      {
         return val=v;
      }
   };

   array<T> table(10);
   int i;

   forcnt(i,10) table[i]=100+i;
   table.insert(7,1,8);
   table.remove(8,0,8);

}
void main(void)
{
   //test_dl_array();
   test_ins_rem();
}
