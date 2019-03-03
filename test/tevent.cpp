
#include <pub\config.hpp>
#include <pub\easyhan.hpp>
#include <stdio.h>

void main()
{
   easy_han_input_init();
   easy_han_input_on();

   int ch;

   while ( ch = key_event_get_eng() , ch != 'q' )
   {
      putchar(ch);
   }
}
