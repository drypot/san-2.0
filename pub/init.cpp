                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/init.cpp
   copyright(c) kyuhyun park
   1994.05.10
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop
#include <pub/init.hpp>

int cls_initer::stt_min_pri;
int cls_initer::stt_max_pri;
cls_initer* cls_initer::stt_prev;

cls_initer::cls_initer (void (*arg_func)(), int arg_pri) :
   pri(arg_pri),
   func(arg_func),
   prev(stt_prev)
{
   if (pri < stt_min_pri) stt_min_pri = pri;
   if (pri > stt_max_pri) stt_max_pri = pri;
   stt_prev = this;
}

void cls_initer::execute()
{
   int cur_pri = stt_max_pri;
   cls_initer* cur_pnt;

   while (cur_pri >= stt_min_pri)
   {
      cur_pnt = stt_prev;

      while (cur_pnt)
      {
         if (cur_pnt->pri == cur_pri)
         {
            cur_pnt->func();
         }
         cur_pnt = cur_pnt->prev;
      }

      cur_pri--;
   }
}

int cls_finiter::stt_min_pri;
int cls_finiter::stt_max_pri;
cls_finiter* cls_finiter::stt_prev;

cls_finiter::cls_finiter(void (*arg_func)(), int arg_pri) :
   pri(arg_pri),
   func(arg_func),
   prev(stt_prev)
{
   if (pri < stt_min_pri) stt_min_pri = pri;
   if (pri > stt_max_pri) stt_max_pri = pri;
   stt_prev = this;
}

void cls_finiter::execute()
{
   int cur_pri = stt_min_pri;
   cls_finiter* cur_pnt;

   while (cur_pri <= stt_max_pri)
   {
      cur_pnt = stt_prev;

      while (cur_pnt)
      {
         if (cur_pnt->pri == cur_pri)
         {
            cur_pnt->func();
         }
         cur_pnt = cur_pnt->prev;
      }

      cur_pri++;
   }
}

cls_infiniter::cls_infiniter(void (*inf)(), void (*finf)(), int pri) :
   cls_initer(inf,pri),
   cls_finiter(finf,pri)
{
}
