                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/res.hpp
   copyright(c) kyuhyun park
   1996.04.28
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_res_hpp
#error 'pub/res.hpp' duplicated.
#endif

#define def_pub_res_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

class cls_msg_xlator
{
   public:
      char* xlate(char* msg) { return msg; }
};

