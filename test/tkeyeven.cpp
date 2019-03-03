/*
   1994.
   1995.08.27
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#include <key\keyevent.hpp>

void Main()
{
   KeyEvent keyevent;

   KeyOn();

   puts ("press Key...");
   forever
   {
      keyevent.Set();
      if (keyevent.GetKeyCode() == KEY_F10) break;

      printf ("%04X ", keyevent.GetKeyCode());
      printf (keyevent.IsMakeEvent() ? "make  " : "break ");
      printf ("%04X %02X ", keyevent.GetKeyCodeType(), keyevent.GetKeyCodeOffset());

      printf (keyevent.IsRShiftShifted()   ? "rS" : "  ");
      printf (keyevent.IsLShiftShifted()   ? "lS" : "  ");
      printf (keyevent.IsRCtrlShifted()    ? "rC" : "  ");
      printf (keyevent.IsLCtrlShifted()    ? "lC" : "  ");
      printf (keyevent.IsRAltShifted()     ? "rA" : "  ");
      printf (keyevent.IsLAltShifted()     ? "lA" : "  ");
      printf (keyevent.IsRMachineShifted() ? "rM" : "  ");
      printf (keyevent.IsLMachineShifted() ? "lM" : "  ");
      printf (keyevent.IsNumLockShifted()  ? "NL" : "  ");
      printf (keyevent.IsCapsLockShifted() ? "CL" : "  ");

      printf ("| ");

      printf (keyevent.IsRShiftToggled()   ? "rS" : "  ");
      printf (keyevent.IsLShiftToggled()   ? "lS" : "  ");
      printf (keyevent.IsRCtrlToggled()    ? "rC" : "  ");
      printf (keyevent.IsLCtrlToggled()    ? "lC" : "  ");
      printf (keyevent.IsRAltToggled()     ? "rA" : "  ");
      printf (keyevent.IsLAltToggled()     ? "lA" : "  ");
      printf (keyevent.IsRMachineToggled() ? "rM" : "  ");
      printf (keyevent.IsLMachineToggled() ? "lM" : "  ");
      printf (keyevent.IsNumLockToggled()  ? "NL" : "  ");
      printf (keyevent.IsCapsLockToggled() ? "CL" : "  ");

      printf ("\n");
   }
}
