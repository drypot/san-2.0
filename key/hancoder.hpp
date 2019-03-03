                                                                                                                        /*
--------------------------------------------------------------------------------
   key/hancoder.hpp
   copyright(C) kyuhyun park
   1994.10.22
--------------------------------------------------------------------------------                                        */

#ifdef def_key_coderhan_hpp
#error 'key/hancoder.hpp' duplicated.
#endif

#define def_key_coderhan_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_char_hpp
#include <pub/char.hpp>
#endif

#ifndef def_key_mc_hpp
#include <key/mc.hpp>
#endif

#ifndef def_cnt_stack_hpp
#include <cnt/stack.hpp>
#endif

class cls_coder;

class cls_han_coder
{
   private:

      struct cls_frame
      {
         int       status_int;
         cls_wchar wch;
         cls_mc    mc;
      };

      tem_stack<cls_frame> frame_stack;
      tem_stack<cls_mc>    mc_stack;

      int       cur_status_int;
      cls_wchar cur_wch;

      cls_mc    cur_mc;
      uint32    cur_mc_offset_u32;
      uint32    cur_mc_type_u32;

      cls_mc    prev_mc;
      uint32    prev_mc_offset_u32;
      uint32    prev_mc_attr_u32;

      cls_coder* coder;

   public:

      cls_han_coder(cls_coder*);

      void reset ();
      void put (cls_mc*);
      void complete ();
      void discard ();
      bool is_incomplete ();

   private:

      uint32 pairing (uint32 table[][3], int table_cnt);
      uint32 h1_pairing ();
      uint32 h2_pairing ();
      uint32 h3_pairing ();
      void   trans_cur_h4_to_h3 ();
      void   trans_prev_h4_to_h3 ();
      void   front_end ();
      void   back_end  ();
};

