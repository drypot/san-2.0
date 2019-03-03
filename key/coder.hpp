                                                                                                                        /*
--------------------------------------------------------------------------------
   key/coder.hpp
   copyright(C) kyuhyun park
   1994.12.20
--------------------------------------------------------------------------------                                        */

#ifdef def_key_coder_hpp
#error 'key/coder.hpp' duplicated.
#endif

#define def_key_coder_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_mc_hpp
#include <key/mc.hpp>
#endif

#ifndef def_cnt_queue_hpp
#include <cnt/queue.hpp>
#endif

class cls_han_coder;
class cls_eng_coder;

enum
{
   def_ca_direct,
   def_ca_open,
   def_ca_replace,
   def_ca_close,
   def_ca_cancel
};

class cls_coder
{
   private:

      struct cls_frame
      {
         int    action_int;
         char16 code_c16;
      };

      cls_han_coder* han_coder_pnt;
      cls_eng_coder* eng_coder_pnt;

      tem_queue<cls_frame> frame_queue;
      cls_frame output_frame;
      uint32 prev_lang_u32;

   public:

      cls_coder           ();
     ~cls_coder           ();

      void   reset        ();

      void   put          (cls_mc*);
      void   put          (int action, char16 code);
      void   discard      ();
      void   complete     ();

      void   get          ();
      int    get_action    ();
      char16 get_code      ();

      bool   is_incomplete ();
      bool   is_holding    ();
};
