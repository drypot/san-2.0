                                                                                                                        /*
--------------------------------------------------------------------------------
   text/pick.cpp -- text pick information system
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/init.hpp>
#include <text/glb.hpp>

static void ctor()
{
   try
   {
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info("func: text/pick.cpp/ctor()\ninfo: error in initializing pick information.\n");
      throw;
   }
}

static void dtor()
{
   try
   {
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info("func: text/pick.cpp/ctor()\ninfo: error in saving pick information.\n");
      throw;
   }
}

static cls_infiniter infiniter(ctor,dtor,-1);
