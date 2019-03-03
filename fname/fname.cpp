/*
   fnode.cpp
   copyright(c) kyuhyun park
   1996.07.06
*/

#include <windows.h>
#include <stdio.h>

bool rcvf;
bool quietf;

void lower_string(char* p)
{
   while (*p)
   {
      if ((unsigned char)*p >= 0x80)
      {
         p++;
         if (*p != 0) p++;
      }
      else
      {
         *p = (char)tolower(*p);
         p++;
      }
   }
}

void iter(char* wildname)
{
   WIN32_FIND_DATA fdata;
   char* fname = fdata.cFileName;
   char prev_dir[MAX_PATH];
   char dir[MAX_PATH];
   char new_fname[MAX_PATH];
   char* dir_fname_ptr;
   bool contf;
   HANDLE sh;

   {
      int len;
      strcpy(new_fname, wildname);
      len = strlen(new_fname);
      if (new_fname[len-1] == '\\' || new_fname[len-1] == '/')
         new_fname[len-1] = 0;
   }

   if (GetFullPathName(new_fname, sizeof(dir), dir, &dir_fname_ptr) && GetCurrentDirectory(sizeof(prev_dir), prev_dir))
   {
      //printf("full path :%s\n", dir);
      //printf("name part :%s\n", dir_fname_ptr);
      {
         char dir_fname[MAX_PATH];

         strcpy(dir_fname, dir_fname_ptr);
         *dir_fname_ptr = 0;
         SetCurrentDirectory(dir);
         sh = FindFirstFile(dir_fname, &fdata);
      }

      contf = sh != INVALID_HANDLE_VALUE;
      while (contf)
      {
         if (strcmp(fname, ".") != 0 && strcmp(fname, "..") != 0)
         {
            strcpy(new_fname, fname);
            lower_string(new_fname);
            if (strcmp(fname, new_fname) != 0)
            {
               if (!quietf)
                  printf("%s%s\n", dir, new_fname);
               rename(fname, new_fname);
            }
            if (rcvf && fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
               char* new_wildname = new char[strlen(fname) + strlen("/*") + 1];
               strcpy(new_wildname, fname);
               strcat(new_wildname, "/*");
               iter(new_wildname);
            }
         }
         contf = FindNextFile(sh, &fdata);
      }
      FindClose(sh);
      SetCurrentDirectory(prev_dir);
   }
}

void main(int argc, char* argv[])
{
   int i = 1;

   if (argc == 1)
   {
      puts("fname -- file name lower");
      puts("copyright(c) kyuhyun park");
      puts("");
      puts("date  : " __DATE__);
      puts("usage : fname <options> file(s)");
      puts("");
      puts("options");
      puts("-r : recursive");
      puts("-q : quiet");
   }

   while (i < argc && argv[i][0] == '-')
   {
      switch (argv[i][1])
      {
         case 'r' :
         {
            rcvf = true;
            break;
         }
         case 'q' :
         {
            quietf = true;
            break;
         }
      }
      i++;
   }

   while (i < argc)
   {
      iter(argv[i]);
      i++;
   }
}
