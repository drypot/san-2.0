                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/env.hpp
   copyright(c) kyuhyun park
   1994.06.01
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_env_hpp
#error 'pub/env.hpp' duplicated.
#endif

#define def_pub_env_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

char* get_bin_dir();


