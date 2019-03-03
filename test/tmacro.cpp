
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\key.hpp>
#include <pub\macro.hpp>

void macro_excute_call_back_main(uint32 id)
{
   printf("excute id %d\n",id);
   macro_result = OK;
}

void main()
{
   key_sig ks;

   key_on();
   macro_init ("san.bin");
   macro_field_alloc("spc_box");
   forever
   {
      key_wait();
      ks.receive();
      if (ks.code() == KEY_F10) break;
      int result = macro_search(&ks);

      if ( result == MACRO_SEARCH_NULL ) printf("null\n");
      ef ( result == MACRO_SEARCH_CONT ) printf("continue\n");
      ef ( result == MACRO_SEARCH_IGNORE ) printf("ignore\n");
      else
      {
         printf("matched\n");
         macro_excute(macro_excute_call_back_main);
      }
   }
}
