
#include <pub\config.hpp>
#include <stdio.h>
#include <dos.h>
#include <pub\easyhan.hpp>
#include <env.h>
#include <stdlib.h>

void print_int_15()
{
   union REGS regs;
   struct SREGS sregs;

   segread(&sregs);
   regs.w.ax = 0x3515;
   int386x(0x21,&regs,&regs,&sregs);
   printf("%x %x\n",int(sregs.es), int(regs.x.ebx));
}

void int_15()
{
   union REGS regs;

   regs.h.ah = 0;
   int386(0x15,&regs,&regs);
   printf("intted\n");
}

void main()
{
   print_int_15();
   easy_han_input_init();
   print_int_15();
   easy_han_input_on();
   key_wait_make();
   print_int_15();
   int_15();
   int_15();
   int_15();
   easy_han_input_off();
   print_int_15();
   printf("begin--\n");
   system(getenv("comspec"));
   printf("end--\n");
}
