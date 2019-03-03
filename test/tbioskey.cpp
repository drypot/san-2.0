
#include <pub\config.hpp>#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\bioskey.hpp>

void main()
{
   while (!bios_key_pressed());

   printf("pressed!\n");
}

