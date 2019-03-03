/*
   tcrt.cpp

   1994.
   1995.09.17  09.24
*/

#include <pub\config.hpp>
#include <pub\common.hpp>
#pragma hdtstop

#include <vio\vio.hpp>
#include <cnt\sarray.hpp>

#include "test\logo.hpp"

#if defined PLATFORM_OS2
#define INCL_VIO
#include <os2.h>
#endif

static byte img_8[]=
{
 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF
};

static uint16 img_16[]=
{
 0x0100, 0x0300, 0x0700, 0x0F00, 0x1F00, 0x3F00, 0x7F00, 0xFF00,
 0xFF01, 0xFF03, 0xFF07, 0xFF0F, 0xFF1F, 0xFF3F, 0xFF7F, 0xFFFF
};

void DrawLogo()
{
   VioRestoreRect(10, 10, 10 + LOGO_WIDTH - 1, 10 + LOGO_HEIGHT - 1, logo_img);
}

void TestBox()
{
   VioClear();
   getchar();
   VioInverseRect(10,10,70,20);
   getchar();
   VioClearRect(11,11,69,19);
   getchar();
   VioInverseRect(40,0,79,29);
   getchar();
   VioInverseRect(41,1,78,28);
   getchar();
}

void TestSave()
{
   BitwiseStaticArrayOf<byte,(79-40+1)*(29-0+1)*16> buf;

   VioInverseRect(40,0,79,29);
   getchar();

   VioSaveRect(40,0,79,29,buf);
   VioClear();
   getchar();

   VioRestoreRect(40,0,79,29,buf);
   getchar();
}

void TestPut()
{
   VioPut8(1,1,img_8);
   VioPut16(1,3,img_16);
   VioPut16R(1,5,img_16);
   VioPut16L(1,7,img_16);
   getchar();
}

void TestXOr()
{
   VioXOr8(1,1,img_8); getchar();
   VioXOr8(1,1,img_8); getchar();
   VioXOr8(1,1,img_8); getchar();
   VioXOr8(1,1,img_8); getchar();

   VioXOr16(1,1,img_16); getchar();
   VioXOr16(1,1,img_16); getchar();
   VioXOr16(1,1,img_16); getchar();
   VioXOr16(1,1,img_16); getchar();
}

void TestXOr2()
{
   VioXOr16L(1,1,img_16); getchar();
   VioXOr16L(1,1,img_16); getchar();
   VioXOr16L(1,1,img_16); getchar();
   VioXOr16L(1,1,img_16); getchar();

   VioXOr16R(1,1,img_16); getchar();
   VioXOr16R(1,1,img_16); getchar();
   VioXOr16R(1,1,img_16); getchar();
   VioXOr16R(1,1,img_16); getchar();
}

#if defined PLATFORM_OS2

static byte colorTable[] =
{
    0, 0, 0,
    0, 0,42,
    0,42, 0,
    0,42,42,
   42, 0, 0,
   42, 0,42,
   42,21, 0,
   42,42,42,
   21,21,21,
   21,21,63,
   21,63,21,
   21,63,63,
   63,21,21,
   63,21,63,
   63,63,21,
   63,63,63
};

static char fgColor[] =
{
   42, 0, 0
};

static char bgColor[] =
{
    0, 0,42
};

static void SetColorTable()
{
   VIOCOLORREG vioColorReg;

   vioColorReg.cb = 12; //sizeof(VIOCOLORREG);
   vioColorReg.type = 3;

   /*
   vioColorReg.firstcolorreg = 0;
   vioColorReg.numcolorregs = 16;
   CHANGE_TYPE_OF(vioColorReg.colorregaddr,char __far16*) = bgColor;
   VioSetState(&vioColorReg,0);
   */

   /*
   vioColorReg.firstcolorreg = 0;
   vioColorReg.numcolorregs = 1;
   CHANGE_TYPE_OF(vioColorReg.colorregaddr,char __far16*) = bgColor;
   VioSetState(&vioColorReg,0);
   */

   vioColorReg.firstcolorreg = 63;
   vioColorReg.numcolorregs = 1;
   //CHANGE_TYPE_OF(vioColorReg.colorregaddr,char __far16*) = fgColor;
   vioColorReg.colorregaddr = (char __far16*) fgColor;
   VioSetState(&vioColorReg,0);
}

static void SetPalette()
{
   PVIOPALSTATE pPalette;
   int sz = sizeof(VIOPALSTATE)+30;

   pPalette = (PVIOPALSTATE) MemAlloc(sz);

   pPalette->cb     = sz;
   pPalette->type   = 0;
   pPalette->iFirst = 0;

   pPalette->acolor[0]  = 1;
   pPalette->acolor[1]  = 1;
   pPalette->acolor[2]  = 1;
   pPalette->acolor[3]  = 1;
   pPalette->acolor[4]  = 1;
   pPalette->acolor[5]  = 1;
   pPalette->acolor[6]  = 1;
   pPalette->acolor[7]  = 1;
   pPalette->acolor[8]  = 1;
   pPalette->acolor[9]  = 1;
   pPalette->acolor[10] = 1;
   pPalette->acolor[11] = 1;
   pPalette->acolor[12] = 1;
   pPalette->acolor[13] = 1;
   pPalette->acolor[14] = 1;
   pPalette->acolor[15] = 1;

   VioSetState(pPalette,0);
   MemFree (pPalette);
}

void TestColor()
{
   DrawLogo();
   getchar();

   //SetPalette();
   //getchar();

   SetColorTable();
   getchar();
}

void PrintPalette()
{
   PVIOPALSTATE pPalette;
   int sz = sizeof(VIOPALSTATE)+30;
   int i;

   VioOn();

   pPalette = (PVIOPALSTATE) MemAlloc(sz);
   pPalette->cb     = sz;
   pPalette->type   = 0;
   pPalette->iFirst = 0;

   /*
   pPalette->acolor[0]  = 1;
   pPalette->acolor[1]  = 1;
   pPalette->acolor[2]  = 1;
   pPalette->acolor[3]  = 1;
   pPalette->acolor[4]  = 1;
   pPalette->acolor[5]  = 1;
   pPalette->acolor[6]  = 1;
   pPalette->acolor[7]  = 1;
   pPalette->acolor[8]  = 1;
   pPalette->acolor[9]  = 1;
   pPalette->acolor[10] = 1;
   pPalette->acolor[11] = 1;
   pPalette->acolor[12] = 1;
   pPalette->acolor[13] = 1;
   pPalette->acolor[14] = 1;
   pPalette->acolor[15] = 1;

   VioSetState(pPalette,0);
   */

   VioGetState(pPalette,0);
   MemFree (pPalette);

   VioOff();

   forcnt(i,16) printf ("%d %d\n",i,int(pPalette->acolor[i]));

   SysExit();
}
#else // PLATFORM_OS2

void TestColor()
{
}

#endif

void main()
{
   //PrintPalette();

   int n;

   puts ("1. test box");
   puts ("2. test save");
   puts ("3. test put");
   puts ("4. test xor");
   puts ("5. test xor2");
   puts ("6. test color");
   puts ("");

   scanf ("%d",&n);
   getchar();

   VioOn();
   VioClear();
   switch (n)
   {
      case 1 : TestBox(); break;
      case 2 : TestSave(); break;
      case 3 : TestPut(); break;
      case 4 : TestXOr(); break;
      case 5 : TestXOr2(); break;
      case 6 : TestColor(); break;
   }

   VioOff();
}
