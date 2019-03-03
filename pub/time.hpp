                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/time.hpp
   copyright(c) kyuhyun park
   1995.08.26
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_time_hpp
#error 'pub/time.hpp' duplicated.
#endif

#define def_pub_time_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#include <time.h>

class cls_stop_watch
{
   private:

      clock_t start_mark;
      clock_t stop_mark;

   public:

      cls_stop_watch() : start_mark(0), stop_mark(0)
      {
      }

      void start()
      {
         start_mark = clock();
      }

      void stop()
      {
         stop_mark = clock();
      }

      clock_t get_diff()
      {
         return stop_mark - start_mark;
      }
};

char* get_converted_date(char*);
