/*
   1994.12.21
   1995.08.23
*/

#include <pub\config.hpp>
#include <pub\init.hpp>
#include <stdio.h>

#define DEF_FUNC(no) void IFunc##no() {printf("Init %d\n",no);} void FFunc##no() {printf("Finit %d\n",no);}

DEF_FUNC(1);
DEF_FUNC(2);
DEF_FUNC(3);

Infiniter infiniter1(IFunc1, FFunc1);
Infiniter infiniter2(IFunc2, FFunc2);
Infiniter infiniter3(IFunc3, FFunc3);

void Main()
{
   printf("main\n");
}
