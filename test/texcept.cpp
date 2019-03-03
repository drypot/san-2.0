/*
   1994.
   1995.02.18  08.23  10.07
*/

#include <pub\config.hpp>
#include <pub\process.hpp>
#include <pub\except.hpp>
#include <stdio.h>

void ThrowExcept()
{
   throw char(10);
}

void TestException()
{
   try
   {
      ThrowExcept();
	}
	catch(...)
	{
      ErrorMessage("caught and re-throw\n");
		throw;
	}
}

void TestAssert()
{
	ASSERT(10<20);
	ASSERT(20<10);
}

void TestGetLibErrMsg()
{
   printf ("%2d : %s\n", errno = 0, GetLibErrMsg());
   printf ("%2d : %s\n", errno = 2, GetLibErrMsg());
   printf ("%2d : %s\n", errno = 5, GetLibErrMsg());
   printf ("%2d : %s\n", errno =10, GetLibErrMsg());
   printf ("%2d : %s\n", errno =20, GetLibErrMsg());
}

DEFINE_XMESSAGE_DERIVED(,Derived);

void ThrowXMessage()
{
   THROW_XMESSAGE("testing throw XMessage");
}

void ThrowXMessageDerived()
{
   THROW_XMESSAGE_DERIVED(Derived,"testing throw XMessageDerived");
}

void TestXMessage()
{
   try
   {
      ThrowXMessage();
   }
   catch (XMessage xmsg)
   {
      puts ("caught XMessage");
      puts (xmsg.GetInfo());
   }
}

void TestXMessageDerived()
{
   try
   {
      ThrowXMessageDerived();
   }
   catch (XMessageDerived xmsg)
   {
      puts ("caught XMessageDerived");
      puts (xmsg.GetInfo());
   }
}

void TestXMessageUncaught()
{
   THROW_XMESSAGE("This is a XMessage");
}

int main()
{
   int n;

   puts ("1. re-throw");
   puts ("2. assert");
   puts ("3. throw");
   puts ("4. GetLibErrMsg");
   puts ("5. XMessage");
   puts ("6. XMessage-Derived");
   puts ("7. XMessage-Uncaught");
   scanf ("%d",&n);

   switch (n)
   {
      case 1 :
         TestException();
         break;
      case 2 :
         TestAssert();
         break;
      case 3 :
         ThrowExcept();
         break;
      case 4 :
         TestGetLibErrMsg();
         break;
      case 5 :
         TestXMessage();
         break;
      case 6 :
         TestXMessageDerived();
      case 7 :
         TestXMessageUncaught();
         break;
   }
	return 0;
}

