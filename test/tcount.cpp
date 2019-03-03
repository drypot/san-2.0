#define USE_SYNTAX
#define USE_COUNT
#define USE_STDIO

#include <pub\config.hpp>
#include <inccnt.list.hpp>

void int_test() {
   circular<int> a(3,int(12),0),b(5,word(3)),c(10);

   printf("%d %d %d\n",(int)a,(int)b,(int)c);
   printf("3 +=3 : \n");
   a+=3;    printf("%d ",(int)a);
   a+=3;    printf("%d ",(int)a);
   a+=3;    printf("%d ",(int)a);
   a+=3;    printf("%d ",(int)a);
   a+=3;    printf("%d ",(int)a);

   printf("\n -=3 : \n");
   a-=3;    printf("%d ",(int)a);
   a-=3;    printf("%d ",(int)a);
   a-=3;    printf("%d ",(int)a);
   a-=3;    printf("%d ",(int)a);
   a-=3;    printf("%d ",(int)a);

   a=3; a=12;
   //a=2;
   //a=13;
   //a=-5;

   printf("\n inc() : \n");
   a.inc(); printf("%d ",(int)a);
   a.inc(); printf("%d ",(int)a);
   a.inc(); printf("%d ",(int)a);
   a.inc(); printf("%d ",(int)a);
   a.inc(); printf("%d ",(int)a);

   printf("\n dec() : \n");
   a.dec(); printf("%d ",(int)a);
   a.dec(); printf("%d ",(int)a);
   a.dec(); printf("%d ",(int)a);
   a.dec(); printf("%d ",(int)a);
   a.dec(); printf("%d ",(int)a);
   }

void p_test() {
   int ary[10];
   circular<int*> a(ary,ary+9,0);

   int i;
   for ( i=0 ; i< 10 ; i++ ) {
      printf("%d:%lp ",i,ary+i);
      }
   printf("\n");
   printf("3 +=3 : \n");
   a+=3;    printf("%lp ",(int*)a);
   a+=3;    printf("%lp ",(int*)a);
   a+=3;    printf("%lp ",(int*)a);
   a+=3;    printf("%lp ",(int*)a);
   a+=3;    printf("%lp ",(int*)a);

   printf("\n -=3 : \n");
   a-=3;    printf("%lp ",(int*)a);
   a-=3;    printf("%lp ",(int*)a);
   a-=3;    printf("%lp ",(int*)a);
   a-=3;    printf("%lp ",(int*)a);
   a-=3;    printf("%lp ",(int*)a);

   printf("= ary+3\n");
   a=ary+3;
   printf("%lp ",(int*)a);
   a=3;   // temporary..
   printf("%lp ",(int*)a);
   a=12;  // temporary..
   printf("%lp ",(int*)a);
   //a=2;
   //a=13;
   //a=-5;

   printf("\n inc() : \n");
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);

   printf("\n dec() : \n");
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   }


void non_circular_test() {
   int ary[10];
   non_circular<int*> a(ary,4);

   int i;
   for ( i=0 ; i< 6 ; i++ ) {
      printf("%d:%lp ",i,ary+i);
      }
   printf("\n inc() : \n");
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);
   a.inc(); printf("%lp ",(int*)a);

   printf("\n dec() : \n");
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   a.dec(); printf("%lp ",(int*)a);
   }

int cdecl main(void) {
   //int_test();
   //p_test();
   non_circular_test();
	return 0;
	}
