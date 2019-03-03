                                                                                                                        /*
--------------------------------------------------------------------------------
   text/msg.cpp -- text messaging system
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

char* msg_pch_ary[]=
{
   "���� ���w ���A �i��",
   "�A���� ����",
   "���� �១ ���A �i��",

   "�� ����",
   "���� ��w",
   "���� ����",

   "���� ����:",
   "���� ��w:",
   "���� ���q:",

   "�����i",

   "���� ��w? (def_yes/no)",
   "���� ��w? (yes/def_no)",

   "line:",
   "column:",
   "literal",

   "�i�� ����:",
   "�i�� �a��:",
   "������ ���� �����s���a. ���� �i�a�a? (def_yes/no)",
   "�i�� ��w"
};


char* msg_get(int num)
{
   mac_assert(num < mac_cnt_of(msg_pch_ary));
   return msg_pch_ary[num];
}
