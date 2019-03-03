
#include <pub\config.hpp>
#include <pub\crt.hpp>

#ifndef INLINE_HPP
   #include <pub\inline.hpp>
#endif

#ifndef ERROR_HPP
   #include <pub\except.hpp>
#endif

#ifndef HANFONT_HPP
   #include <hanpub\fnt.hpp>
#endif

#ifndef ENGFONT_HPP
   #include <pub\engpub\fnt.hpp>
#endif

#ifndef TTY_HPP
   #include <pub\tty.hpp>
#endif

#ifndef MEMORY_HPP
   #include <pub\heap.hpp>
#endif

#ifndef WINDOW_HPP
   #include <pub\window.hpp>
#endif

#include <conio.h>

void test_window()
{
   int x,y;

   forcnt (y,25)
   {
      tty_xy(0,y);
      forcnt (x,80) tty_output('A'+x+y);
   }

   window::open(0,0,10,10);
   getch();
   window::close();
   getch();

   window::open(1,1,11,11);
   window::open(5,5,15,15);
   window::open(10,10,20,20);
   getch();
   window::close();
   getch();
   window::close();
   getch();
   window::close();
   getch();

   int i;
   forcnt (i,10)
   {
      window::open( i*2, i*2, i*2 + 40 , i*2 + 5 );
      getch();
   }

}

extern unsigned _stklen=65000U;


void cdecl main(void)
{
      eng_fnt.init("eng.fnt\\default.eng");
      han_fnt.init("han.fnt\\default.han");
		crt.init("drv\\c_vga80.drv");
		tty.init();
      window::init(80*25);
		crt.on();

      //test_cur();
      //test_han_attr();
      test_window();

		crt.off();
}
