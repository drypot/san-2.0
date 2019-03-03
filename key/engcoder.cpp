                                                                                                                        /*
--------------------------------------------------------------------------------
   key/engcoder.cpp
   copyright(C) kyuhyun park
   1994.12.20
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <key/coder.hpp>
#include <key/engcoder.hpp>

cls_eng_coder::cls_eng_coder (cls_coder* arg_coder) : coder (arg_coder)
{
}

void cls_eng_coder::put (cls_mc* mc)
{
   coder->put (def_ca_direct, mc->get_offset());
}

