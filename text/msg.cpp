                                                                                                                        /*
--------------------------------------------------------------------------------
   text/msg.cpp -- text messaging system
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

char* msg_pch_ary[]=
{
   "¶¥·¥ ¦‰¡w ¢…¹A ¤i¬—",
   "¡A¡¡Ÿ¡ ¦¹¢",
   "ÑÁ·© ÀáŸ¡ ¢…¹A ¤i¬—",

   "¬ ÑÁ·©",
   "ÑÁ·© ¸á¸w",
   "·¥­á º—»¡",

   "ÑÁ·© ·ª‹¡:",
   "ÑÁ·© ¸á¸w:",
   "ÑÁ·© ·¡Ÿq:",

   "•¡¶‘ i",

   "ÑÁ·© ¸á¸w? (def_yes/no)",
   "ÑÁ·© ¸á¸w? (yes/def_no)",

   "line:",
   "column:",
   "literal",

   "§iœâ ·ª‹¡:",
   "§iœâ ³a‹¡:",
   "ÑÁ·©·¡ ·¡£¡ ¹¥¸Ðs“¡”a. ”ü´á ³iŒa¶a? (def_yes/no)",
   "§iœâ ¸á¸w"
};


char* msg_get(int num)
{
   mac_assert(num < mac_cnt_of(msg_pch_ary));
   return msg_pch_ary[num];
}
