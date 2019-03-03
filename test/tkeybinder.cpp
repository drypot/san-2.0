/*
   tkeybinder.cpp

   1995.12.18
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#include <key\keyevent.hpp>
#include <mac\keybinder.hpp>

#include <mac\tmp\test.def>

int32 PrintA()
{
   puts ("A");
   return 0;
}

int32 PrintB()
{
   puts ("B");
   return 0;
}

int32 PrintC()
{
   puts ("C");
   return 0;
}

#include <mac\tmp\test.map>

static int32 KeyBinderCallBack(int32 id)
{
   return MacDispatchFunc(id, MacFuncMapper);
}

void Main()
{
   KeyEventType KeyEvent;
   KeyBinderType KeyBinder("..\\macro\\test.bin");

   KeyOn();

   forever
   {
      KeyEvent.Set();
      switch (KeyEvent.GetKeyCode())
      {
         case KEY_F10: Exit();
                       break;

         case KEY_F5 : KeyBinder.SetMode("First");
                       break;

         case KEY_F6 : KeyBinder.SetMode("Second");
                       break;

         case KEY_F7 : KeyBinder.SetMode("Third");
                       break;

         default     : if (KeyBinder.Scan(KeyEvent) == KB_ScanMatch)
                           KeyBinder.Execute(KeyBinderCallBack);
                       break;
      }
   }
}
