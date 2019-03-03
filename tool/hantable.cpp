
#include <pub/config.hpp>
#include <pub/common.hpp>

void output (hangul ch)
{
   static char buf[3];
   static int cnt;

   char16_make(buf,(char16)ch);
   printf(buf);
   if (++cnt == 40)
   {
      printf("\n");
      cnt = 0;
   }
}

void pcs_main()
{
   int h1,h2,h3;

   forcnt (h1, PHONEME_H1_CMAX)
      forcnt (h2, PHONEME_H2_CMAX)
         forcnt (h3, PHONEME_H3_CMAX)
            output (hangul (phoneme_cardinal_to_h1(h1), phoneme_cardinal_to_h2(h2), phoneme_cardinal_to_h3(h3)));

   return 0;
}
