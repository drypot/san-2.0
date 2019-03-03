/*
   bin2src.cpp -- binary to C source converter

   copyright(C) kyuhyun park
*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#include <pub/io.hpp>
#include <pub/heap.hpp>

void pcs_main()
{
   if (glb_argc != 2) pcs_exit(1);

   ifile in(argv[1]);

   if (in.size() == 0) return;

   byte* p = (byte*) mem_alloc(in.size());
   byte* p_end = p + in.size();
   int cnt = 0;

   in.read(p,in.size());
   mac_assert(mem_check(p));

   forever
   {
      if (cnt == 0) printf("   ");

      printf ("0x%02x",*p);
      p++;
      cnt++;
      if (p < p_end)
      {
         putchar (',');
         if (cnt == 16)
         {
            putchar ('\n');
            cnt = 0;
         }
         else
         {
            putchar (' ');
            if (cnt % 4 == 0) putchar (' ');
         }
      }
      else
      {
         break;
      }
   }
}

