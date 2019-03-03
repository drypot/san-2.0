                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/ipc.hpp
   copyright(c) kyuhyun park
   1996
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_ipc_hpp
#error 'pub/ipc.hpp' duplicated.
#endif

#define def_pub_ipc_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif


#ifdef def_os2

class cls_mutex_sem
{
   private:

      HMTX hmtx;

   public:

      void create  (bool state = def_false);
      void close   ();
      void request ();
      void release ();
};

void cls_mutex_sem::create(bool state)
{
   DosCreateMutexSem (NULL, &hmtx, NULL, state);
}

void cls_mutex_sem::close()
{
   DosCloseMutexSem (hmtx);
}

void cls_mutex_sem::request()
{
   DosRequestMutexSem (hmtx, SEM_INDEFINITE_WAIT);
}

void cls_mutex_sem::release()
{
   DosReleaseMutexSem (hmtx);
}

#endif
