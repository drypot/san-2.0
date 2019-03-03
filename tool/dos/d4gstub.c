																																								/*
--------------------------------------------------------------------------------
   d4gstub.c -- stub module for DOS4G

	Copyright(C) Park, Kyu Hyun.
--------------------------------------------------------------------------------                                        */

#include <process.h>
#include <dir.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

#ifdef __cplusplus
   #define __CPPARGS ...
#else
   #define __CPPARGS
#endif

#define video_service           0x10
#define bios_set_palette_all    0x1002   // es:dx address of table
#define bios_set_color          0x1012   // es:dx address of color table ( 3 bytes for each )
													  // bx    starting index
													  // cx    number of registers to set
#define bios_select_color_page  0x1013   // bl    0 : select paging-mode

typedef void interrupt (*int_handler)(__CPPARGS);

extern unsigned _stklen = 2048;
int_handler prev_int15_handler;
int_handler prev_real_mode_server;
unsigned short real_mode_server_int_num;

#define BUF_CMAX 16
unsigned char buf[BUF_CMAX];
int buf_inx;

unsigned char palette[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0
};

unsigned char color[] =
{
	0, 0, 0  ,
	0, 0,42  ,
	0,42, 0  ,
	0,42,42  ,
	42, 0, 0 ,
	42, 0,42 ,
	42,21, 0 ,
	42,42,42 ,
	21,21,21 ,
	21,21,63 ,
	21,63,21 ,
	21,63,63 ,
	63,21,21 ,
	63,21,63 ,
	63,63,21 ,
	42,42,42 // 63,63,63
};

#pragma argsused
void __interrupt real_mode_server
(
	unsigned bp,unsigned di,unsigned si,
	unsigned ds,unsigned es,
	unsigned dx,unsigned cx,unsigned bx, unsigned ax,
	unsigned ip,unsigned cs,unsigned flags
)
{
	static unsigned short color_cmax = sizeof(color)/sizeof(color[0]);

	switch (ax)
	{
		case 0 :

			// set palette

			asm mov     ax,ds
			asm mov     es,ax
			asm mov     dx,offset palette
			asm mov     ax,bios_set_palette_all
			asm int     video_service

			// set color table

			asm mov     ax,ds
			asm mov     es,ax
			asm mov     dx,offset color
			asm mov     bx,0
			asm mov     cx,color_cmax
			asm mov     ax,bios_set_color
			asm int     video_service

			// select color page

			asm mov     bx,0000h                        // select 16 color mode
			asm mov     ax,bios_select_color_page
			asm int     video_service

			asm mov     bx,0001h                        // select page 0 of 4 pages
			asm mov     ax,bios_select_color_page
			asm int     video_service

			break;
	}
}

int install_real_mode_server()
{
   real_mode_server_int_num = 0x60;
   while (real_mode_server_int_num<0x100)
	{
      if (_dos_getvect(real_mode_server_int_num)==NULL) break;
      real_mode_server_int_num++;
	}
   if (real_mode_server_int_num == 0x100) return 0;

   prev_real_mode_server = (int_handler) _dos_getvect(real_mode_server_int_num);
   _dos_setvect(real_mode_server_int_num, (int_handler) real_mode_server);
   return 1;
}

void uninstall_real_mode_server()
{
   _dos_setvect(real_mode_server_int_num,(int_handler) prev_real_mode_server);
}

#pragma argsused
void __interrupt int15_handler
(
	unsigned bp,unsigned di,unsigned si,
	unsigned ds,unsigned es,
	unsigned dx,unsigned cx,unsigned bx, unsigned ax,
	unsigned ip,unsigned cs,unsigned flags
)
{
	asm pushf
	_disable();
	if ((ax & 0xff00) == 0x4f00)
	{
		if (buf_inx < BUF_CMAX)
         buf[buf_inx++] = ax & 0xff;
	}
	_enable();
	asm popf
	_chain_intr(prev_int15_handler);
}

/*
void main()
{
	int cnt = 0;

   prev_int15_handler = (int_handler) _dos_getvect(0x15);
   _dos_setvect(0x15,(int_handler) int15_handler);
	while (cnt<10)
	{
		if (buf_inx)
		{
			_disable();
			while (buf_inx) printf("%x ",buf[--buf_inx]);
			printf("\n");
			_enable();
			cnt++;
		}
	}
   _dos_setvect(0x15,(int_handler) prev_int15_handler);
}
*/


void install_int15_handler()
{
   prev_int15_handler = (int_handler) _dos_getvect(0x15);
   _dos_setvect(0x15,(int_handler) int15_handler);
}

void uninstall_int15_handler()
{
   _dos_setvect(0x15,(int_handler) prev_int15_handler);
}

void pass_pointer()
{
	*(unsigned long*)MK_FP(0xbfff, 0x0000) = ((unsigned long) FP_SEG(buf) << 4) + (unsigned)FP_OFF(buf);
	*(unsigned long*)MK_FP(0xbfff, 0x0004) = ((unsigned long) FP_SEG(&buf_inx) << 4) + (unsigned)FP_OFF(&buf_inx);
   *(unsigned long*)MK_FP(0xbfff, 0x0008) = real_mode_server_int_num;

	//printf("%Fp %lx %Fp\n", MK_FP(0xbfff, 0x0000), *(unsigned long*)MK_FP(0xbfff, 0x0000), buf);
	//printf("%Fp %lx %Fp\n", MK_FP(0xbfff, 0x0004), *(unsigned long*)MK_FP(0xbfff, 0x0004), &buf_inx);
}

	/* Add environment strings to be searched here */
	char *paths_to_check[] = {
		"DOS4GPATH",
		"PATH"};

	char *dos4g_path()
	{
      static char fullpath[80];
      int i;

      for( i = 0; i < sizeof( paths_to_check ) / sizeof( paths_to_check[0] ); i++ )
      {
         _searchenv( "dos4gw.exe", paths_to_check[i], fullpath );
         if( fullpath[0] ) return( fullpath );
      }
      for( i = 0; i < sizeof( paths_to_check ) / sizeof( paths_to_check[0] ); i++ )
      {
         _searchenv( "dos4g.exe", paths_to_check[i], fullpath );
         if( fullpath[0] ) return( fullpath );
      }
      return( "dos4gw.exe" );
	}

#pragma argsused
int main(int argc, char** argv)
{
	static char cmdline[128];
	static char* new_argv[4];

	new_argv[0] = dos4g_path();
	new_argv[1] = argv[0];
	new_argv[2] = cmdline;
	new_argv[3] = NULL;

	putenv("DOS4G=QUIET");

	while (*++argv)
	{
		strcat(cmdline, *argv);
		strcat(cmdline, " ");
	}

	//puts("DOS/4GW Real Mode Server  Version 1.1");
	//puts("Copyright(C) Park, Kyu Hyun. 1994-1995");

	if (install_real_mode_server())
	{
		//printf("real_mode_server_interrupt_number = %x\n",real_mode_server_int_num);
		////puts("protected mode session open");
		//puts("");
		install_int15_handler();
		pass_pointer();
		spawnvp (P_WAIT, new_argv[0], new_argv);
		uninstall_int15_handler();
		uninstall_real_mode_server();
		////puts("protected mode session close");
	}
	else
	{
		puts ("can't install real mode server.");
	}

	return 0;
}
