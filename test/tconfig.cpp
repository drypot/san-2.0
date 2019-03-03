/*
	94.12.16

*/

#include <pub\config.hpp>
#include <pub\config.hpp>
#include <stdpub\io.hpp>
#include <pub\stdlib.hpp>

#if defined WIN_WIN32
	FILE* outf;
	void outf_init()
	{
		if ((outf=fopen("t:\config.log","wt"))
		==NULL) exit(0);
	}

	void outf_finit()
	{
		fclose(outf);
	}

#else
	#define outf stdout
	void outf_init()
	{
	}
	void outf_finit()
	{
	}
#endif

void define_info()
{
	fprintf(outf,"define_info -------------------\n");
	#ifdef CONFIG_HPP
	fprintf(outf,"CONFIG_HPP\n");
	#endif

	#ifdef CL_BORLAND
	fprintf(outf,"CL_BORLAND\n");
	#endif

	#ifdef CL_GNU
	fprintf(outf,"CL_GNU\n");
	#endif

	#ifdef CL_WATCOM
	fprintf(outf,"CL_WATCOM\n");
	#endif

	#ifdef OS_DOS
	fprintf(outf,"OS_DOS\n");
	#endif

	#ifdef OS_OS2
	fprintf(outf,"OS_OS2\n");
	#endif

	#ifdef OS_NT
	fprintf(outf,"OS_NT\n");
	#endif

	#ifdef OS_UNIX
	fprintf(outf,"OS_UNIX\n");
	#endif

	#ifdef OS_POSIX
	fprintf(outf,"OS_POSIX\n");
	#endif

	#ifdef OS_SVID
	fprintf(outf,"OS_SVID\n");
	#endif

	#ifdef OS_BSD
	fprintf(outf,"OS_BSD\n");
	#endif

	#ifdef CPU_I8086
	fprintf(outf,"CPU_I8086\n");
	#endif

	#ifdef CPU_I80386
	fprintf(outf,"CPU_I80386\n");
	#endif

	#ifdef WIN_PM
	fprintf(outf,"WIN_PM\n");
	#endif

	fprintf(outf,"\n");
}

void type_info()
{
	puts("type info -----------------------\n");

	#define psize(type) fprintf(outf,"size of " #type "\t = %d\n",sizeof(type));
	#define pval(name) fprintf(outf,#name "\t = %ld\n",(long)name);
	#define puval(name) fprintf(outf,#name "\t = %lu\n",(unsigned long)name);

   pval(CHAR_BIT);
	puts("");

   psize(char);
   psize(byte);
   puts("");

	psize(int);
   psize(int8);
   psize(int16);
   psize(int32);
	puts("");

   psize(word);
	psize(uint8);
   psize(uint16);
   psize(uint32);
   puts("");

   psize(1<3);
	puts("");
   psize(size_t);
	puts("");

	pval(CHAR_MAX);
	pval(CHAR_MIN);

	puval(BYTE_MAX);

	pval(INT_MAX);
	pval(INT_MIN);
	pval(INT8_MAX);
	pval(INT8_MIN);
	pval(INT16_MAX);
	pval(INT16_MIN);
	pval(INT32_MAX);
	pval(INT32_MIN);

	puval(WORD_MAX);
	puval(WORD8_MAX);
	puval(WORD16_MAX);
	puval(WORD32_MAX);
}

#if defined WIN_WIN32
	#pragma argsused
	int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
#else
	int main()
#endif
{
	outf_init();
	define_info();
	type_info();
	outf_finit();
	return 0;
}
