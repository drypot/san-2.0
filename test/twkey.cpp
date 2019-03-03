

#include <pub\config.hpp>#define STRICT
#include <windows.h>
#include <stdio.h>
#include <string.h>

char buf[512*1024];

#pragma argsused
int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdStr, int nCmdShow)
{
	char szBuffer[80];
	int i;

	memset(buf,1,sizeof(buf));

	for(i=0; i<sizeof(buf) ; i++) if (buf[i]!=1) return 1;

	sprintf(szBuffer, "%d %d", sizeof(buf), sizeof(int));
	MessageBox(NULL, szBuffer, "SOLOMEM", MB_OK);
	return NULL;
}
