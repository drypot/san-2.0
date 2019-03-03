                                                                                                                        /*
--------------------------------------------------------------------------------
   conpub/io.hpp

   copyright(C) kyuhyun park

   1994.12.18
--------------------------------------------------------------------------------                                        */

#ifdef CONdef_pub_IO_HPP
#error 'conpub/io.hpp' duplicated.
#endif

#define CONdef_pub_IO_HPP

#if defined def_watcomc || defined def_borlandc
#include <conio.h>
#endif

#if defined def_watcomc
#include <graph.h>

inline void clrscr()
{
   _cleartextwin(_GCLEARTEXTWIN);
}

inline void gotoxy(int x, int y)
{
   _settextposition(y,x);
}

inline void cputs(char* str)
{
   _outtext(str);
}

#endif

