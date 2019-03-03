                                                                                                                        /*
--------------------------------------------------------------------------------
   pub\time.cpp -- timer

   Copyright(C) Park, kyu hyun.

   1993.02.03  06.22
   1994.07.01
--------------------------------------------------------------------------------                                        */

/*
#define  USE_BASIS
#define  USE_XCPT
#define  USE_INLINE
#define  USE_CHAR
#define  USE_TIME
#define  USE_STDIO_H
#define  USE_STDLIB_H
#define  USE_STRING_H
#define  USE_TIME_H

#include <inclist.hpp>
                                                                                /*
-------------------------------------------------------------------------------
   essential functions
------------------------------------------------------------------------------- */

VOID TIME::set (BYTE h,BYTE m,BYTE s)
{
   hour  (h);
   minute(m);
   second(s);
}

VOID TIME::set (time_t t)
{
   struct tm *ptblock;

   ptblock=localtime(&t);
   iHour  =ptblock->tm_hour;
   iMinute=ptblock->tm_min;
   iSecond=ptblock->tm_sec;
}

VOID TIME::set(PSTRZ str,WORD option)
{
   CHAR  acTempStr [15];
   PSTRZ sToken=":";
   PCHAR pcMark;

   // copy str to buf and
   // replace separater ':' with NUL char.

   strcpy(acTempStr,str);

   if ( strtok ( acTempStr, sToken ) )
      while ( strtok ( NULL, sToken ) ) nothing;

   // clear work ptr;

   pcMark=acTempStr;

   // assert can't be used. checking made with 'checkRange'

   // set iHour

   ifs ( option & TM_Hour )
      hour( atoi(pcMark) );
      pcMark=strrchr(pcMark,0)+1;
   ife

   // set iMinute

   ifs ( option & TM_Minute )
      minute( atoi(pcMark) );
      pcMark=strchr(pcMark,0)+1;
   ife

   // set iSecond

   if ( option & TM_Second )
      second( atoi(pcMark) );

}

VOID TIME::setcur (VOID)
{
   struct tm *ptblock;
   time_t    timer;

   timer  =time(0L);
   ptblock=localtime(&timer);
   iHour  =ptblock->tm_hour;
   iMinute=ptblock->tm_min;
   iSecond=ptblock->tm_sec;
}

BYTE TIME::hour12 (VOID)
{
   ifs (Inside(iHour,1,12))  return iHour;
   eif (iHour==0)            return 1;
   els                       return iHour-12;
   ife
}

BYTE TIME::part(VOID)
{
   return iHour<12 ? TM_AM  : TM_PM;
}

                                                                                /*
-------------------------------------------------------------------------------
   calcuration  functions
------------------------------------------------------------------------------- */

VOID TIME::addHour(BYTE h)
{
   iHour+=h;
   iHour%=24;
}

VOID TIME::addMinute(BYTE m)
{
   iMinute+=m;
   addHour(iMinute/60);
   iMinute%=60;
}

VOID TIME::addSecond(BYTE s)
{
   iSecond+=s;
   addMinute(iSecond/60);
   iSecond%=60;
}

                                                                                /*
-------------------------------------------------------------------------------
   advanced functions
------------------------------------------------------------------------------- */

VOID TIME::convertTo(PSTRZ str ,WORD option)
{
   CHAR acHourStr  [4];
   CHAR acMinuteStr[4];
   CHAR acSecondStr[4];

   str[0]=0;

   ifs ( option & TM_Hour  )
      sprintf(acHourStr ,"%2u",  option & TM_PartConv ? hour12() : iHour );
      acHourStr[2]=0;
      strcat (str,acHourStr);
      strcat (str,":");
   ife

   ifs ( option & TM_Minute )
      sprintf( acMinuteStr ,"%2u",iMinute);
      acMinuteStr[2]=0;
      strcat ( str, acMinuteStr);
      strcat ( str, ":");
   ife

   ifs ( option & TM_Second )
      sprintf ( acSecondStr, "%2u", iSecond );
      acSecondStr[2]=0;
      strcat ( str, acSecondStr );
   ife

   if (strlen(str)>0 && str[strlen(str)-1]==AT_Colon)
      str [strlen(str)-1]=0;

   if ( option & TM_AppAMPM)
      strcat ( str, part()==TM_AM ? " AM": " PM");
}

FLAG TIME::checkRange(WORD option)
{
   if ( (option&TM_Hour   && Outside(iHour  ,0,23)) ||
        (option&TM_Minute && Outside(iMinute,0,59)) ||
        (option&TM_Second && Outside(iSecond,0,60))
       )
       return ERROR;

   return OK;
}

                                                                                /*
-------------------------------------------------------------------------------
   support
------------------------------------------------------------------------------- */

INT compare ( PTIME a , PTIME b , WORD option )
{
   INT it;

   if ( option & TM_Hour   && ( it = a->hour()   - b->hour()   )!=0 ) return it;
   if ( option & TM_Minute && ( it = a->minute() - b->minute() )!=0 ) return it;
   if ( option & TM_Second && ( it = a->second() - b->second() )!=0 ) return it;

   return 0;
}

*/
