
#include <pub\config.hpp>
#include <stdio.h>
#include <pub\inline.hpp>

void test_uint16()
   {

      printf(
	 "hi=%x  lo=%x ",
	  UINT16_HI(0x1234),UINT16_LO(0x1234)
	  );

      int i=0xABCD;
      printf("%x ",i);
      UINT16_HI_REF(i)=0xDD;
      UINT16_LO_REF(i)=0xFF;
      printf("%x ",i);

      int j;
      j=MAKE_UINT16(0x56,0x78);
      printf("%x ",j);
      printf("\n");
   }

void test_uint32()
   {

      printf(
	 "hi=%x  lo=%x ",
     uint32_hi(0x12345678L),uint32_lo(0x12345678L)
     );

      int32 i=0x1234ABCDL;
      printf("i=%lx ",i);
      uint32_hi_ref(i)=0xABCD;
      uint32_lo_ref(i)=0x1234;
      printf("i=%lx ",i);

      int32 j;
      j=uint32_make(0xFEDC,0xBA98);
      printf("j=%lx ",j);
      printf("\n");
   }

void test_typing()
   {
      printf("to_flag: 10>1 =%d \t 1>10=%d\n",10>1,1>10);
      printf("sizeof(1>10) = %d\n",sizeof(1>10));
      printf("\n");

      int16 a=0x1234;
      int16 b=0x1234;
      printf("a=%x \t b=%x\n",a,b);
      a=0xabcd;
      change_type_of(b,byte)=(byte)0xabcd;
      printf("a=%x \t b=%x\n",a,b);
      printf("\n");

      struct T
      {
	 int a;
	 int8 b;
	 int16 c;
	 int32 d;
	 char e;
      };

      printf("offset of\n");
      printf(
	 "int=%d  int8=%d  int16=%d  int32=%d  char=%d\n",
	 offset_of(T,a),
	 offset_of(T,b),
	 offset_of(T,c),
	 offset_of(T,d),
	 offset_of(T,e)
	 );
      printf("\n");

      int array[12];
      uint32 array2[74];
      printf("count_of array a  [...] = %d\n",count_of(array));
      printf("count_of array a2 [...] = %d\n",count_of(array2));
      puts("");
   }

#define pr(it) printf(#it "=%d \t",it);
#define nl puts("");
#define wait getchar();

void test_bool()
   {
   pr(IsInside(5,1,10)) pr(IsInside(1,1,10)) pr(IsInside(10,1,10)) pr(IsInside(0,1,10)) pr(IsInside(11,1,10)) nl
   pr(IsInside(0,-5,5)) nl
   nl
   pr(outside(5,1,10)) pr(outside(1,1,10)) pr(outside(10,1,10)) pr(outside(0,1,10)) pr(outside(11,1,10)) nl
   pr(outside(0,-5,5)) nl
   nl
   pr(in(10,1,10)) pr (in(10,1,2)) pr(in(10,1,1)) nl
   pr(in(10,1,5,10)) pr(in(10,1,2,3)) pr(in(10,10,100,10)) nl
   pr(in(100,1,10,100,100)) pr(in(100,1,10,20,30)) pr(in(100,100,100,10,100)) nl
   puts("---end");
   wait
   }

void test_assignment()
   {
   bool i=TRUE;
   pr(i) turn(i); pr(i) turn(i); pr(i) nl
   nl

   int j=5;
   pr(j) turn(j,10,20); pr(j) turn(j,10,20); pr(j) turn(j,10,20); pr(j) nl
   nl

   int m=10,n=20;
   pr(m) pr(n) nl
   m=renew(n,30);
   pr(m) pr(n) nl
   m=renew(n,40);
   pr(m) pr(n) nl
   nl

   int s1=11,s2=22;
   pr(s1) pr(s2) nl
   swap(s1,s2);
   pr(s1) pr(s2) nl
   swap(s1,s2);
   pr(s1) pr(s2) nl
   nl

   byte tbl[]={ 1,2,3,4,5,6,7,8,9,10 };
   pr(sum(tbl,count_of(tbl)))nl
   wait
   }

void line(void)
   {
   printf("\n----------------------------------------------------------\n");
   }

void test_unit()
{
   int i;

   for (i=-12 ; i<=12 ; i++)
      printf("%d --> %d,%d\n",i,unit_num(i,5), unit_offset(i,5));
}

void main(void)
{
   //line();
   //test_uint16();
   //test_uint32();
   //test_typing();
   //test_bool();
   //test_assignment();
   test_unit();
}
