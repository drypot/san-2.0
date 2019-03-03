/*
	grepc.cpp - grep & change

	copyright(C) kyuhyun park

	1995.08.12
*/

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <malloc.h>
#include <str.h>

char* find_str;
int find_str_len;
char* replace_str;
int replace_str_len;
int glb_argc;
char** argv;

class err{};

void errmsg (char* msg)
{
	puts (msg);
	perror ("");
	throw err();
}

void work(char* fname)
{
	printf ("%s ... ",fname);

	int infh, outfh;
	void* buf;
	off_t fsize;

	infh = open(fname, O_RDONLY|O_BINARY);
	if (infh == -1) errmsg("input file open error");

	fsize = filelength(infh);
	if (!fsize) return;

	buf = malloc (fsize);
	if (!buf) errmsg("memory allocation error");

	if (read(infh,buf,fsize) != fsize) errmsg("input file read error");
	close(infh);

	outfh = -1;

	char* p_base = (char*)buf;
	char* p_end = p_base + fsize;
	char* p_work = p_base;

	while (p_work + find_str_len <= p_end)
	{
		if (strncmp(p_work, find_str, find_str_len) == 0)
		{
			if (outfh == -1)
			{
            //printf ("processing ... ");
            printf ("processing");
				outfh = open("grepc.$$$", O_WRONLY|O_BINARY|O_CREAT|O_TRUNC, S_IWRITE|S_IREAD);
				if (outfh == -1) errmsg ("output file open error");
			}
			if (
				write(outfh, p_base, p_work - p_base) != p_work - p_base ||
				write(outfh, replace_str, replace_str_len) != replace_str_len
				)
				errmsg ("output file write error");
			p_base = (p_work += find_str_len);
		}
		else p_work++;
	}
	if (outfh != -1 && p_base < p_end)
	{
		if (write(outfh, p_base, p_end - p_base) != p_end - p_base) errmsg("output file write error 2");
		close(outfh);
		if (remove(fname) == -1) errmsg("can't remove oldfile");
		if (rename("grepc.$$$",fname) == -1) errmsg("file renaming error");
	}
	free (buf);
   //puts ("end");
   puts("");
}

void work()
{
	while (glb_argc--) work(*(argv++));
}

void help()
{
	puts ("grepc - grep & change - 1995.08.12 by kyuhyun park");
	puts ("usage: grepc <find_str> <replace_str> <file_list>");
}

#ifdef def_borlandc
int __stdcall main (int glb_argc, char* argv[])
#else
int main (int glb_argc, char* argv[])
#endif
{
	try {
	  if (glb_argc < 4)
	  {
		  help();
	  }
	  else
	  {
		  find_str = argv[1];
		  replace_str = argv[2];
		  find_str_len = strlen(find_str);
		  replace_str_len = strlen(replace_str);
		  ::glb_argc = glb_argc - 3;
		  ::argv = argv + 3;
		  work();
	  }
	}
	catch (...)
	{
		puts ("\nprocessing error\n");
	}
	return 0;
}
