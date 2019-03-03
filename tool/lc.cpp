/*
   lc.cpp

   95.08.18
*/

#include <pub/config.hpp>
#include <pub/config.hpp>
#include <pub/stdio.hpp>

int sum_char, sum_line;

void do_it(char* name)
{
   int local_line = 0;
   int local_char = 0;
   int ch;
   int prev_ch;
   FILE* f;

   f = fopen(name,"rt");
   prev_ch = 0;
   while (ch = fgetc(f) , ch != EOF)
   {
      if (ch == '\n') local_line++;
      local_char++;
      prev_ch = ch;
   }
   if (prev_ch != '\n') local_line++;
   fclose(f);
   printf("%-20s  %10d chars  %10d lines\n",name,local_char,local_line);
   sum_char += local_char;
   sum_line += local_line;
}

void main(int glb_argc, char* argv[])
{
   int files = glb_argc - 1;
   while (--glb_argc) do_it(*(++argv));
   printf("total %8d files  %10d chars  %10d lines\n",files,sum_char,sum_line);
}
