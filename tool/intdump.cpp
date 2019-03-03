/*
   intdump.cpp

   1995.02.02
*/

#include <dos.h>
#include <stdio.h>

#ifdef def_watcomc
#define getvect _dos_getvect
#endif

void main()
{
   int inx = 0;
   while (inx < 256)
   {
      printf("%02X %Fp\n",inx,(void far*)getvect(inx));
      inx++;
   }
}
