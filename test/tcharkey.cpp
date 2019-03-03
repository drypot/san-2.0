
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\key.hpp>
#include <pub\metacode.hpp>

#ifndef KEYLIST_HPP
#include <keycnt.list.hpp>
#endif

void main(void)
{
   key k;
   meta_code chkey;
   meta_code_map map;

   key_init("keyboard\\ks103.drv");
   map.load("keyboard\\ks103\\qwerty.map");

   key_on();

   forever
   {
      printf("<wait signal>");
      while ( ! k.signal() );
      printf(" <receive>");
      k.receive();
      printf(" %04X:%04X:%04X",k.code() & (~KEY_MASK_BREAK),k.shift(),k.toggle());

      if ( k.code_break() )
      {
         printf(" <break>\n");
      }
      else
      {
         if ( k.code_type() == KEY_TYPE_CHAR )
         {
            chkey =  k.shift_shift() ? map.mapping_page_1(k) : map.mapping_page_0(k);
            printf (" %c\n", chkey.code() );
         }
         else
         {
            printf ("\n");
         }
      }
      if ( k.code() == KEY_F10 ) return;
   }
}
