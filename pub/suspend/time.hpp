                                                                                                                        /*
--------------------------------------------------------------------------------
   pub\time.hpp -- timer

   Copyright(C) Park, kyu hyun.

   1993.02.03  06.22
   1994.07.01
--------------------------------------------------------------------------------                                        */

#ifdef PUB_TIME_HPP
   #error 'pub\time.hpp' duplicated.
#endif

#define PUB_TIME_HPP

#include <time.h>

/*
enum enum_TIME_FIELD
{
   // value is linked with enum_TIME_CONVERT_METHOD

   TM_Hour   =0x01,
   TM_Second =0x02,
   TM_Minute =0x04
};

enum enum_TIME_CONVERT_METHOD
{
   // value is linked with enum_TIME_FIELD

   TM_PartConv    =0x08,
   TM_AppAMPM     =0x10
};

enum enum_HOUR_TYPE
{
   TM_AM,
   TM_PM
};

ClassDefine(TIME)
{
   INT  iHour;
   INT  iMinute;
   INT  iSecond;

   public:

        TIME       (BYTE h=0,BYTE m=0,BYTE s=0);

   VOID clear      (VOID);

   VOID set        (BYTE h=0,BYTE m=0,BYTE s=0);
   VOID set        (time_t t);
   VOID set        (PSTRZ  str,WORD option);
   VOID setcur	   (VOID);

   VOID hour       (BYTE h);
   VOID minute     (BYTE m);
   VOID second     (BYTE s);

   BYTE hour       (VOID);
   BYTE hour12     (VOID);
   BYTE minute     (VOID);
   BYTE second     (VOID);

   BYTE part       (VOID);

   VOID addHour    (BYTE h);
   VOID addMinute  (BYTE m);
   VOID addSecond  (BYTE s);

   VOID convertTo  (PSTRZ str, WORD option);
   FLAG checkRange (WORD option);
   INT  compareWith(PTIME b, WORD option);
};

// support funtions

INT compare ( PTIME a , PTIME b , WORD option );

// class TIME inlines

inline TIME::TIME (BYTE h,BYTE m,BYTE s) { set(h,m,s);     }

inline VOID TIME::clear  (VOID)          { set(0,0,0);     }

inline VOID TIME::hour   (BYTE h)        { iHour=h;        }
inline VOID TIME::minute (BYTE m)        { iMinute=m;      }
inline VOID TIME::second (BYTE s)        { iSecond=s;      }

inline BYTE TIME::hour   (VOID)          { return iHour;   }
inline BYTE TIME::minute (VOID)          { return iMinute; }
inline BYTE TIME::second (VOID)          { return iSecond; }

inline INT  TIME::compareWith ( PTIME b, WORD option )
{
   return compare(this,b,option);
}
*/
