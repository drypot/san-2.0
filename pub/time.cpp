                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/time.hpp
   copyright(c) kyuhyun park
   1995.08.26
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/time.hpp>

char* get_converted_date(char* arg_str)
{
   static char* month_pch_ary[] =
   {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
   };

   static char converted_ach[11];

   char month_ach[16];
   int day_int;
   int year_int;
   int month_int;

   sscanf(arg_str,"%s %d %d", month_ach, &day_int, &year_int);
   forcnt (month_int, 12) if (strcmp(month_ach, month_pch_ary[month_int])==0) break;
   mac_assert(month_int<12);

   sprintf(converted_ach, "%04d/%02d/%02d", year_int, month_int+1, day_int);
   mac_assert(strlen(converted_ach) == sizeof (converted_ach)-1);

   return converted_ach;
}

