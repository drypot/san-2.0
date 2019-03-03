/*
   95.10.16
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdrstop

#include <vio\vio.hpp>
#include <vio\textwin.hpp>
#include <dlg\yesnodlg.hpp>
#include <key\key.hpp>

void Main()
{
   VioOn();
   KeyOn();

   TextWindow textwin;
   TextImage textimg(80,30);
   YesNoDialog yesno("File Save?");
   int rc;

   textimg.Clear();

   yesno.SetVal(YES);
   rc = yesno.Execute();
   textimg.Write(rc ? "RC:OK " : "RC:CANCEL ");
   textimg.Write(yesno.GetVal()? "YES " : "NO ");
   textwin.Draw(textimg);

   yesno.SetVal(NO);
   rc = yesno.Execute();
   textimg.Write(rc ? "RC:OK " : "RC:CANCEL ");
   textimg.Write(yesno.GetVal()? "YES " : "NO ");
   textwin.Draw(textimg);

   yesno.SetVal(YES);
   rc = yesno.Execute();
   textimg.Write(rc ? "RC:OK " : "RC:CANCEL ");
   textimg.Write(yesno.GetVal()? "YES " : "NO ");
   textwin.Draw(textimg);

   yesno.SetVal(NO);
   rc = yesno.Execute();
   textimg.Write(rc ? "RC:OK " : "RC:CANCEL ");
   textimg.Write(yesno.GetVal()? "YES " : "NO ");
   textwin.Draw(textimg);

   KeyWaitMake();
}
