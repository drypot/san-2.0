/*
   1994.
   1995.08.27
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#include <key\key.hpp>

void Main()
{
   KeyFrame keyframe;

   KeyOn();

   puts ("press Key...");
   forever
   {
      KeyGet(keyframe);
      if (keyframe.uCode == KEY_F10) break;

      printf ("%04X ", keyframe.uCode);
      printf (keyframe.fKeyDown ? "Down " : "Up   ");
      printf ("%04X %04X", keyframe.uShifted, keyframe.uToggled);
      printf ("\n");
   }
}
