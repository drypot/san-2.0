
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <keycnt.list.hpp>
#include <pub\key.hpp>
#include <stdpub\io.hpp>
#include "san\program.hpp"
#include "macro/procarry.h"
#include "macro/proclist.h"

void main()
{
   uint32 proc_id;
   key tmp_key;

   key_init("keyboard\\ks103.drv");
   key_on();

   program_binary_init();
   keybind_set_field("edit");

   do
   {
      while ( ! tmp_key.signal() );
      tmp_key.receive();
      proc_id = keybind_search_proc(&tmp_key);
      if ( proc_id == KB_SEARCH_NULL ) printf("no proc\n");
      ef ( proc_id == KB_SEARCH_CONT ) printf(".");
      ef ( proc_id == KB_SEARCH_IGNORE ) ;
      else printf("proc: %s\n",proc_list[(int)proc_id]);
   } while ( tmp_key.code() != KEY_ESC );
}






