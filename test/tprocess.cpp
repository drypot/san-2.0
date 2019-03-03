/*
	1994.05.05  12.17
   1995.08.23  10.07
*/

#include <pub\config.hpp>
#include <pub\init.hpp>
#include <pub\process.hpp>

#include <stdio.h>

void TestExit()
{
   Exit();
}

void TestAbort()
{
   Abort();
}

void TestLogMessageOverflow()
{
   forever LogMessage ("Hello!\n");
}

void IniterCallBack0()
{
   puts ("Initer Test : priority 0");
}

void IniterCallBackM10()
{
   puts ("Initer Test : priority -10");
}

void IniterCallBackP10()
{
   puts ("Initer Test : priority +10");
}

Initer initer1(IniterCallBack0);
Initer initer2(IniterCallBackM10,-10);
Initer initer3(IniterCallBackP10,+10);

void Main()
{
   int n;

   ErrorMessage ("\nErrorMessage Test : %d %s\n", 123, "Two");
   LogMessage ("\nLogMessage Test :%d %s in Main\n", 123, "STRING");

   puts ("1. Exit");
   puts ("2. Abort");
   puts ("3. Test LogMessage Overflow");
   scanf ("%d",&n);

   switch (n)
   {
      case 1 :
         TestExit();
         break;
      case 2 :
         TestAbort();
         break;
      case 3:
         TestLogMessageOverflow();
         break;
   }
}



