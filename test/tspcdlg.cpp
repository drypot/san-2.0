/*
   1995.08.18  10.
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\vio.hpp>
#include <vio\textwin.hpp>
#include <key\key.hpp>
#include <dlg\spcdlg.hpp>

void Main()
{
   puts ("11");
   VioOn();
   puts ("22");
   KeyOn();
   puts ("33");

   TextWindow textwin;
   TextImage memTextWindow(80,30);
   SpcDialog spcDlg;

   int x;
   int y = 0;

   memTextWindow.Clear();
   while(spcDlg.Execute(), spcDlg.spcPage.cnt)
   {
      memTextWindow.XY(0,y);
      forcnt(x,spcDlg.spcPage.cnt) memTextWindow.Write(spcDlg.spcPage.contents[x]);
      y++;
      if (y == 30) y=0;
      textwin.Draw(memTextWindow);
   }

   KeyWaitMake();
}

