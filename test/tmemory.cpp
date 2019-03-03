/*
   1993.
   1994.
   1995.08.23
*/

#include <pub\config.hpp>
#include <pub\inline.hpp>
#include <pub\memory.hpp>
#include <stdio.h>

void TestMemMap()
{
   MemMapOf<uint16> textwin(0xB8000);
   int i,j;

   forcnt(i,5)
      forcnt(j,80)
         textwin[i*80+j]='A'+i+0x123*j;
}

void DumpHex(byte* p, int cnt)
{
   while (cnt--)
   {
      printf ("%02X ",*p++);
   }
   puts("");
}

void TestMemFrame()
{
   int body_sz = sizeof(byte[5]);
   int frame_sz = MemFrameSize(body_sz);
   byte stg[100];

   printf ("Body Size = %d, MemFrame Size = %d\n");

   memset(stg,0,sizeof(stg));
   DumpHex (stg-4,frame_sz+8);
   MemFrameMark(stg,sizeof(byte[5]));
   DumpHex (stg-4,frame_sz+8);
   puts("");

   *((byte*)MemFrameBody(stg)+0) = 1;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));

   *((byte*)MemFrameBody(stg)+1) = 2;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));

   *((byte*)MemFrameBody(stg)+2) = 3;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));

   *((byte*)MemFrameBody(stg)+3) = 4;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));

   *((byte*)MemFrameBody(stg)+4) = 5;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));

   *((byte*)MemFrameBody(stg)+5) = 6;
   DumpHex (stg,frame_sz);
   ASSERT(MemFrameCheck(stg));
}

void TestMemAllocNoMem()
{
   try
   {
      MemAlloc(1024L*1024*1024);
   }
   catch (XMessage xmsg)
   {
      puts (xmsg.GetInfoString());
   }
}

void TestNewNoMem()
{
   try
   {
      MemAlloc(1024L*1024*1024);
   }
   catch (XMessage xmsg)
   {
      puts (xmsg.GetInfoString());
   }
}

void TestMemAlloc()
{
   int body_sz = sizeof(byte[5]);
   byte* p = (byte*) MemAlloc(body_sz);

   DumpHex (p-4,body_sz+8);
   puts("");

   *(p+0) = 1;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

   *(p+1) = 2;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

   *(p+2) = 3;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

   *(p+3) = 4;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

   *(p+4) = 5;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

   *(p+5) = 6;
   DumpHex (p-8,body_sz+10);
   ASSERT(MemCheck(p));

}

struct A
{
   byte data;
   A () { puts ("A's Ctor"); data=0xFF; }
   ~A() { puts ("A's Dtor"); data=0xEE; }
};

byte CtorTestBuf[100];

void TestCtor()
{
   DumpHex(CtorTestBuf,10);
   ConstructArray((A*)CtorTestBuf,5);
   DumpHex(CtorTestBuf,10);
   DestructArray((A*)CtorTestBuf,5);
   DumpHex(CtorTestBuf,10);
}

void TestPointerTo()
{
   PointerTo<A> pa = new A;
   DumpHex((byte*)(A*)pa,20);
}

void TestPointerToArrayOf()
{
   PointerToArrayOf<A> pa = new A[5];
   DumpHex((byte*)(A*)pa,20);
}

int main()
{
   int n;

   puts ("1. MemMap");
   puts ("2. MemFrame");
   puts ("3. MemAlloc-NoMem");
   puts ("4. New-NoMem");
   puts ("5. MemAlloc");
   puts ("6. CtArray & DtArray");
   puts ("7. PointerTo");
   puts ("8. PointerToArrayOf");

   scanf("%d",&n);

   switch (n)
   {
      case 1 : TestMemMap(); break;
      case 2 : TestMemFrame(); break;
      case 3 : TestMemAllocNoMem(); break;
      case 4 : TestNewNoMem(); break;
      case 5 : TestMemAlloc(); break;
      case 6 : TestCtor(); break;
      case 7 : TestPointerTo(); break;
      case 8 : TestPointerToArrayOf(); break;
   }
   return 0;
}
