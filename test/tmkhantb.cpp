
#if
#include <pub\config.hpp>ndef SYATAX_HPP
   #include <pub\config.hpp>
#endif

#include <fstream.h>

ofstream out("fixed.txt");

void line(int hi)
{
   int i;

   out.put(' ');
   out.put(' ');

   forinc ( i , 0xA1 , 0xFE )
   {
      out.put( char(hi) );
      out.put( char(i) );
      if ( ( i & 0xF ) == 0xF ) out.put('\n');
   }

   out.put('\n');
   out.put('\n');
}

int main(void)
{
   int i;

   forinc ( i , 0xA1 , 0xAC ) line(i);
   forinc ( i , 0xB0 , 0xC8 ) line(i);
   forinc ( i , 0xCA , 0xFD ) line(i);

   return 0;
}
