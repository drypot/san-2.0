/*
   1995.08.18  10.15
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\vio.hpp>
#include <vio\textwin.hpp>
#include <key\key.hpp>
#include <dlg\hanjadlg.hpp>

WCharType ch_list[] = {'´e', '¢…', '¤b', '‹A', 'Ñe'};

void Main()
{
   int i;

   VioOn();
   KeyOn();

   TextWindow textwin(80,30);
   TextImage textimg(80,30);

   textimg.Clear();

   forcnt(i,5)
   {
      textimg.XY(0,i);
      textimg.Write(ch_list[i]);
      HangulHanjaToggle(*(ch_list+i));
      textimg.XY(2,i);
      textimg.Write(ch_list[i]);
      textwin.Draw(textimg);
   }

   forcnt(i,5)
   {
      textimg.XY(0,i+10);
      textimg.Write(ch_list[i]);
      HangulHanjaToggle(*(ch_list+i));
      textimg.XY(2,i+10);
      textimg.Write(ch_list[i]);
      textwin.Draw(textimg);
   }

   KeyWaitMake();
}
