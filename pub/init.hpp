                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/init.hpp
   copyright(c) kyuhyun park
   1994.5.10
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_init_hpp
#error 'pub/init.hpp' duplicated.
#endif

#define def_pub_init_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

class cls_initer
{
   private:
      static int         stt_min_pri;
      static int         stt_max_pri;
      static cls_initer* stt_prev;

      int pri;
      void (*func)();
      cls_initer* prev;

   public:
      cls_initer (void (*)(), int = 0);

      static void execute();
};

class cls_finiter
{
   private:
      static int          stt_min_pri;
      static int          stt_max_pri;
      static cls_finiter* stt_prev;

      int pri;
      void (*func)();
      cls_finiter* prev;

   public:
      cls_finiter(void (*)(), int = 0);

      static void execute();
};

class cls_infiniter : public cls_initer , public cls_finiter
{
   public:
      cls_infiniter(void (*)(), void (*)(), int = 0);
};

enum
{
   def_init_pri_pub_env    =  3,
   def_init_pri_normal     =  0,
   def_init_pri_key_mcp    = -3,
   def_init_pri_fnt_hanfnt = -5,
   def_init_pri_fnt_engfnt = -5,
   def_init_pri_fnt_spcfnt = -5,
   def_init_pri_fnt_hnjfnt = -5
};
