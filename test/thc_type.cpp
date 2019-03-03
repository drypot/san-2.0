

#if
#include <pub\config.hpp>ndef SYATAX_HPP
   #include <pub\config.hpp>
#endif

#ifndef HANCODE_HPP
   #include <hancode.hpp>
#endif

#include <stdio.h>

extern unsigned _stklen=32768U;

int main(int argc , char* argv[] )
{
   if ( argc != 2 )
   {
      fputs("usage: <command> <file name>\n",stderr);
      return 1;
   }

   if ( han_code_type_detect(argv[1]) == HAN_CODE_FIXED ) fputs ("FIXED\n",stdout);
   else fputs ("COMBI\n",stdout);

   return 0;
}

