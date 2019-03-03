
#if
#include <pub\config.hpp>ndef SYATAX_HPP
   #include <pub\config.hpp>
#endif

#ifndef HANCODE_HPP
   #include <hancode.hpp>
#endif

#include <stdio.h>
#include <string.h>

extern unsigned _stklen=32768U;

int main(int argc , char* argv[] )
{
   char buf[256];

   if ( argc != 2 )
   {
      fputs("usage: <command> [cf|fc]\n",stderr);
      return 1;
   }

   if ( strcmp(argv[1],"fc") == 0 )
   {
      while ( fgets(buf,sizeof(buf),stdin) )
      {
         han_code_to_combi(buf);
         fputs(buf,stdout);
      }
   }
   else
   {
      while ( fgets(buf,sizeof(buf),stdin) )
      {
         han_code_to_fixed(buf);
         fputs(buf,stdout);
      }
   }

   return 0;
}
