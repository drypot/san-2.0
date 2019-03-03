                                                                                                                        /*
--------------------------------------------------------------------------------
   text/mark.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

bool cls_mark::operator < (cls_mark& second)
{
   return !is_null() && !second.is_null() && (ignore_x_flg ? y < second.y : y < second.y || y == second.y && x < second.x);
}

bool cls_mark::operator == (cls_mark& second)
{
   return !is_null() && !second.is_null() && y == second.y && (ignore_x_flg || x == second.x);
}

bool cls_mark::operator <= (cls_mark& second)
{
   return !is_null() && !second.is_null() && (ignore_x_flg ? y <= second.y : y < second.y || y == second.y && x <= second.x);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void cls_doc::mark_reset()
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);
   while (pnt < end_pnt) (pnt++)->make_null();
}

void cls_doc::mark_reset(int inx)
{
   mac_assert (inx < mac_cnt_of(mark_ary));
   if (!mark_ary[inx].is_null())
   {
      log_mark(mark_ary + inx);
      mark_ary[inx].make_null();
   }
}

void cls_doc::mark_insert_line(int32 num)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);

   while (pnt < end_pnt)
   {
      if (!pnt->is_null() && pnt->y >= num)
      {
         log_mark(pnt);
         pnt->y++;
      }
      pnt++;
   }
}

void cls_doc::mark_remove_line(int32 num)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);

   while (pnt < end_pnt)
   {
      if (!pnt->is_null())
      {
         if (pnt->y > num)
         {
            log_mark(pnt);
            pnt->y--;
         }
         ef (pnt->y == num && !pnt->ignore_x_flg)
         {
            log_mark(pnt);
            pnt->x = 0;
         }
      }
      pnt++;
   }
}

void cls_doc::mark_insert(int32 index, int32 cnt)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);
   int32 y = iter.get_y();

   while (pnt < end_pnt)
   {
      if (!pnt->is_null() && pnt->y == y && pnt->x >= index && !pnt->ignore_x_flg)
      {
         log_mark(pnt);
         pnt->x += cnt;
      }
      pnt++;
   }
}

void cls_doc::mark_remove(int32 index, int32 cnt)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);
   int32 y = iter.get_y();
   int32 index2 = index + cnt;

   while (pnt < end_pnt)
   {
      if (!pnt->is_null() && pnt->y == y && !pnt->ignore_x_flg)
      {
         if (is_inside_less(pnt->x, index, index2))
         {
            log_mark(pnt);
            pnt->x = index;
         }
         ef (pnt->x >= index2)
         {
            log_mark(pnt);
            pnt->x -= cnt;
         }
      }
      pnt++;
   }
}

void cls_doc::mark_separate(int32 index)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);
   int32 y = iter.get_y();

   while (pnt < end_pnt)
   {
      if (!pnt->is_null())
         if (pnt->y == y)
         {
            if (pnt->x >= index && !pnt->ignore_x_flg)
            {
               log_mark(pnt);
               pnt->y++;
               pnt->x-=index;
            }
         }
         ef (pnt->y > y)
         {
            log_mark(pnt);
            pnt->y++;
         }
      pnt++;
   }
}

void cls_doc::mark_join(int32 index)
{
   cls_mark* pnt = mark_ary;
   cls_mark* end_pnt = pnt + mac_cnt_of(mark_ary);
   int32 y = iter.get_y();

   while (pnt < end_pnt)
   {
      if (!pnt->is_null())
      {
         if (pnt->y == y)
         {
            if (pnt->x > index && !pnt->ignore_x_flg)
            {
               log_mark(pnt);
               pnt->x = index;
            }
         }
         ef (pnt->y == y+1)
         {
            log_mark(pnt);
            pnt->y--;
            if (!pnt->ignore_x_flg)
            {
               pnt->x += index;
            }
         }
         ef (pnt->y > y+1)
         {
            log_mark(pnt);
            pnt->y--;
         }
      }
      pnt++;
   }
}

void cls_doc::mark_set(int index)
{
   mark_set(index, iter.get_x(), iter.get_y());
}

void cls_doc::mark_set(int index, int32 x, int32 y)
{
   mac_assert (index < mac_cnt_of(mark_ary));
   log_mark(mark_ary + index);
   mark_ary[index].y = y;
   mark_ary[index].x = x;
}

bool cls_doc::mark_get(int inx, int32* px, int32* py)
{
   mac_assert (inx < mac_cnt_of(mark_ary));
   bool result = !mark_ary[inx].is_null();
   if (result)
   {
      *py = mark_ary[inx].y;
      *px = mark_ary[inx].x;
   }
   return result;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_mark()
{
   int inx = mac_runner->get_arg_i32(0);
   mac_rtcheck(inx < 10);
   cdoc->mark_set(inx);
}

void pdf_mark_prev()
{
   cdoc->mark_set(def_mark_prev);
}

void pdf_mark_tmp()
{
   cdoc->mark_set(def_mark_tmp);
}
