                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mac.hpp
   copyright(C) kyuhyun park
   1994.11.08
--------------------------------------------------------------------------------                                        */

#ifdef def_key_mac_hpp
#error 'key/mac.hpp' duplicated.
#endif

#define def_key_mac_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_cnt_stack_hpp
#include <cnt/stack.hpp>
#endif

#ifndef def_key_keyevent_hpp
#include <key/keyevent.hpp>
#endif

//
// macro pseudo code
//

enum
{
   def_pc_jump,
   def_pc_jmp_false,
   def_pc_jmp_true,
   def_pc_call,
   def_pc_ret,

   def_pc_arg_stack_push,
   def_pc_arg_stack_push_val,
   def_pc_arg_stack_discard,

   def_pc_val_stack_push_func_result,
   def_pc_val_stack_push_int,
   def_pc_val_stack_discard_one,

   def_pc_logical_and,
   def_pc_logical_or,
   def_pc_equal,
   def_pc_not_equal,
   def_pc_above,
   def_pc_below,
   def_pc_above_equal,
   def_pc_below_equal,
   def_pc_plus,
   def_pc_minus,
   def_pc_mul,
   def_pc_div,
   def_pc_not
};

//
// keybind modify flags
//

#define def_mk_mask_s    0x0001u
#define def_mk_mask_ls   0x0002u
#define def_mk_mask_rs   0x0004u

#define def_mk_mask_c    0x0008u
#define def_mk_mask_lc   0x0010u
#define def_mk_mask_rc   0x0020u

#define def_mk_mask_a    0x0040u
#define def_mk_mask_la   0x0080u
#define def_mk_mask_ra   0x0100u

#define def_mk_mask_m    0x0200u
#define def_mk_mask_lm   0x0400u
#define def_mk_mask_rm   0x0800u

struct cls_mac_key
{
   uint16 on_u16;
   uint16 off_u16;
   uint16 code_u16;
};

struct cls_mac_mode
{
   uint32 name_inx;
   uint32 func_begin_inx;
   uint32 key_begin_inx;
   uint32 key_end_inx;
};

struct cls_mac_mapper
{
   int32 id_i32;
   void* func;
};

class cls_mac_bin
{
   private:

      byte* img_byte_pnt;

   public:

      cls_mac_bin();
      cls_mac_bin(char*);
     ~cls_mac_bin();

      void init(char*);
      byte* get_pnt();
};

enum
{
   def_kb_scan_failed,
   def_kb_scan_continue,
   def_kb_scan_ignore,
   def_kb_scan_match
};

class cls_mac_runner
{
   private:

      byte*         img_byte_pnt;

      byte*         mac_data_base_byte_pnt;
      int32*        mac_code_base_byte_pnt;

      cls_mac_mode* mac_mode_base_pnt;
      cls_mac_mode* mac_mode_end_pnt;

      int32*        mac_func_base_i32_pnt;
      int32*        mac_func_begin_i32_pnt;

      cls_mac_key*  mac_key_base_pnt;
      cls_mac_key*  mac_key_begin_pnt;
      cls_mac_key*  mac_key_end_pnt;

      cls_key_event key_event_ary[4];
      int           key_event_cnt;

      int32         scaned_func_addr_i32;

   private:

      void key_stack_reset();
      void key_stack_discard();
      void key_stack_push(cls_key_event*);

      bool is_key_seq_list_head(cls_mac_key*);
      bool is_key_seq_head(cls_mac_key*);

      bool compare_key(cls_mac_key*, cls_key_event*);
      int  compare_key_seq(cls_mac_key*);

   private:

      int32 ip_i32;
      int32 arg_stack_push_cnt;
      tem_stack<int32> ret_addr_stack;
      tem_stack<int32> val_stack;
      tem_stack<int32> arg_stack;
      tem_stack<int32> arg_stack_push_cnt_stack;
      cls_mac_mapper* mac_mapper;

   private:

      int32 fetch_code();
      void  pcode_intp (int32);

   public:

      cls_mac_runner(cls_mac_bin* = NULL, cls_mac_mapper* = NULL);
     ~cls_mac_runner();

      void  init(cls_mac_bin*, cls_mac_mapper*);

      void  set_mode(char*);
      int   scan(cls_key_event*);

      int32 get_func();
      int   get_arg_cnt ();
      int32 get_arg_i32 (int);
      void* get_arg_pnt (int);

      void  execute (int32 addr = 0);

      virtual int32 cb_pdf(int32);
};

inline int32 cls_mac_runner::get_func()
{
   return scaned_func_addr_i32;
}

inline int cls_mac_runner::get_arg_cnt ()
{
   return arg_stack_push_cnt;
}

inline int32 cls_mac_runner::get_arg_i32 (int inx)
{
   return *arg_stack.get_pnt(arg_stack_push_cnt - inx - 1);
}

inline void* cls_mac_runner::get_arg_pnt (int inx)
{
   return mac_data_base_byte_pnt + *arg_stack.get_pnt(arg_stack_push_cnt - inx - 1);
}

