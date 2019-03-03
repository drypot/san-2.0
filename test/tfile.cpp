
#include <pub\config.hpp>
#include <pub\config.hpp>
#include <pub\file.hpp>

char buf[100];

void main()
{
   iofile f("ttt");

   f.write(buf,sizeof(buf));
   f.offset(0);
   f.read(buf,sizeof(buf));
   f.close();
}

