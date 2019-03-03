
#include <pub\config.hpp>
#include <stdio.h>
#include <dos.h>
#include <i86.h>
#include <conio.h>

char buf[32];
volatile int in_p;
volatile int out_p;

void (__interrupt __far *prev_int15)();

void __interrupt __cdecl int15( union INTPACK r)
{
   if (r.h.ah == 0x4f)
   {
      buf[in_p++]=r.h.al;
      if (in_p==sizeof(buf)) in_p=0;
      r.w.flags |= INTR_CF;
   } else _chain_intr(prev_int15);
}

void main()
{
   int ch;

   prev_int15 = _dos_getvect(0x15);
   _dos_setvect(0x15,(void (__interrupt __far*)())int15);
   for(;;)
   {
      int val;
      ch = getch();
      val = buf[out_p];
      printf("%x\n",val);
      out_p++;
      if (out_p==sizeof(buf)) out_p=0;
      if (val==0x1e) break;
   }
   _dos_setvect(0x15,prev_int15);
}

