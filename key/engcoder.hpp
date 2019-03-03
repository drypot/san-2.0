                                                                                                                        /*
--------------------------------------------------------------------------------
   key/engcoder.hpp
   copyright(C) kyuhyun park
   1994.12.20
--------------------------------------------------------------------------------                                        */

#ifdef def_key_codereng_HPP
#error 'key/engcoder.hpp' duplicated.
#endif

#define def_key_codereng_HPP

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_mc_hpp
#include <key/mc.hpp>
#endif

class cls_coder;

class cls_eng_coder
{
   public:

      cls_coder* coder;

   public:

      cls_eng_coder(cls_coder*);

      void put (cls_mc*);
};
