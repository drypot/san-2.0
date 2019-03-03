                                                                                                                        /*
--------------------------------------------------------------------------------
   text/textinst.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#define def_inst_cnt_list

#include <cnt/list.hpp>
#include <text/glb.hpp>

static tem_obj_list<cls_doc> __doc_list;
static tem_obj_list_iter<cls_doc> __doc_iter(&__doc_list);
