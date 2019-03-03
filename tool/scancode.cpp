/*
   scancode.cpp -- Scan Code Viewer

	copyright(C) kyuhyun park.

	1995.09.08
*/

#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <bios.h>

typedef void interrupt (*int_handler) (...);
int_handler prev_int15_handler;
clock_t prev_clock;
int exit_flag;

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
		clock_t cur_clock = clock();
		if (cur_clock - prev_clock > ((int)CLOCKS_PER_SEC/10) ) puts("");
		prev_clock = cur_clock;
		printf ("%02X ", ax & 0xff);
		if ( (ax & 0xff) == (0x44 | 0x80) ) exit_flag = 1;
		ax = 1;
	}

	_enable();
	asm popf
	_chain_intr(prev_int15_handler);
}

void install_int15_handler()
{
	prev_int15_handler = (int_handler) _dos_getvect(0x15);
	_dos_setvect(0x15,(int_handler) int15_handler);
}

void uninstall_int15_handler()
{
	_dos_setvect(0x15,(int_handler) prev_int15_handler);
}

void main()
{
	typedef void (*int_func)(int);

	puts ("");
	puts ("Scancode 1.0  copyright(C) 1995 kyuhyun park");
	puts ("to_ exit press F10");
	puts ("");
	signal (SIGINT,(int_func)SIG_IGN);
	install_int15_handler();
	while (!exit_flag)
		while (bioskey(_KEYBRD_READY)) bioskey(_KEYBRD_READ);
	uninstall_int15_handler();
	while (bioskey(_KEYBRD_READY)) bioskey(_KEYBRD_READ);
}


