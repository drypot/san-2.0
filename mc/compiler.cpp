                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/compiler.cpp
   copyright(c) kyuhyun park
   1994.11.07
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <pub/lex.hpp>
#include <cnt/stack.hpp>
#include <cnt/array.hpp>
#include <key/mac.hpp>

#include <mc/glb.hpp>
#include <mc/tmp/parser.h>

#define def_data_seg_smax    (4*1024)
#define def_code_seg_smax    (16*1024)
#define def_mode_stack_cmax  (16)
#define def_key_stack_cmax   (4*1024)
#define def_func_stack_cmax  (2*1024)

tem_stack<byte>         mac_data_stack(def_data_seg_smax);
tem_stack<cls_mac_mode> mac_mode_stack(def_mode_stack_cmax);
tem_stack<cls_mac_key>  mac_key_stack (def_key_stack_cmax);
tem_stack<int32>        mac_func_stack(def_func_stack_cmax);

tem_static_array<int32,def_code_seg_smax> mac_code;
tem_stack<int32> jmp_stack(128);

void bifunc()
{
   static int32 addr;

   if (!scan_func(lex_val_ach)) regi_func(lex_val_ach, --addr);
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   user defined function process
--------------------------------------------------------------------------------                                        */

int  ip=1;
char call_name_ach[def_id_size];
int  arg_cnt;

inline void add_code(int32 code)
{
   *mac_code.get_pnt(ip++) = code;
}

inline void dummy_code()
{
   ip++;
}

void jmp_stack_push()
{
   jmp_stack.push_val(ip);
}

int32 jmp_stack_pop()
{
   return jmp_stack.pop_val();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void func_name()
{
   regi_func(lex_val_ach,ip);
}

void func_body_end()
{
   add_code(def_pc_ret);
}

void statement_return()
{
   add_code(def_pc_ret);
}

void if_exp_end()
{
   add_code(def_pc_jmp_false);
   jmp_stack_push();
   dummy_code();
}

void else_begin()
{
   int32 tmp_addr = jmp_stack_pop();

   add_code(def_pc_jump);
   jmp_stack_push();
   dummy_code();
   *mac_code.get_pnt(tmp_addr) = ip;
}

void else_end()
{
   *mac_code.get_pnt(jmp_stack_pop()) = ip;
}

void else_null()
{
   *mac_code.get_pnt(jmp_stack_pop()) = ip;
}

void while_begin()
{
   jmp_stack_push();
}

void while_exp_end()
{
   add_code(def_pc_jmp_false);
   jmp_stack_push();
   dummy_code();
}

void while_end()
{
   add_code(def_pc_jump);
   *mac_code.get_pnt(jmp_stack_pop()) = ip+1;
   add_code(jmp_stack_pop());
}

void call_name()
{
   mac_rtcheck(strlen(lex_val_ach) < sizeof(call_name_ach));
   strcpy(call_name_ach,lex_val_ach);
   arg_cnt=0;
}

/*
if macro call nested in another macro call's argment list,
  problem arise because of arg_cnt
*/

void call_arg_end()
{
   int32 id;

   
   if (id = scan_func(call_name_ach), id)
   {
      add_code(def_pc_call);
      add_code(id);
   }
   else
   {
      throw cls_xmsg("func: mc/compiler.cpp/call_arg_end()\ninfo: undefined function\n");
   }

   if (arg_cnt)
   {
      add_code(def_pc_arg_stack_discard);
      add_code(arg_cnt);
   }
}

void call_arg_str()
{
   add_code(def_pc_arg_stack_push);
   add_code(mac_data_stack.get_cnt());
   mac_data_stack.push_ary((byte*)lex_val_ach,strlen(lex_val_ach)+1);
   arg_cnt++;
}

void call_arg_exp()
{
   add_code(def_pc_arg_stack_push_val);
   arg_cnt++;
}

void exp_discard()
{
   add_code(def_pc_val_stack_discard_one);
}

void exp_logical_or()
{
   add_code(def_pc_logical_or);
}

void exp_logical_and()
{
   add_code(def_pc_logical_and);
}

void exp_equal()
{
   add_code(def_pc_equal);
}

void exp_not_equal()
{
   add_code(def_pc_not_equal);
}

void exp_above()
{
   add_code(def_pc_above);
}

void exp_below()
{
   add_code(def_pc_below);
}

void exp_above_equal()
{
   add_code(def_pc_above_equal);
}

void exp_below_equal()
{
   add_code(def_pc_below_equal);
}

void exp_plus()
{
   add_code(def_pc_plus);
}

void exp_minus()
{
   add_code(def_pc_minus);
}

void exp_mul()
{
   add_code(def_pc_mul);
}

void exp_div()
{
   add_code(def_pc_div);
}

void exp_not()
{
   add_code(def_pc_not);
}

void exp_int()
{
   add_code(def_pc_val_stack_push_int);
   add_code(lex_val_int);
}

void exp_char()
{
   add_code(def_pc_val_stack_push_int);
   add_code(lex_val_char);
}

void exp_func_result()
{
   add_code(def_pc_val_stack_push_func_result);
}

void exp_func_ptr()
{
   int32 func_id = scan_func(lex_val_ach);
   if (!func_id) throw cls_xmsg("func: mc/compiler.hpp/exp_func_ptr()\ninfo: undefined function\n");
   add_code(def_pc_val_stack_push_int);
   add_code(func_id);
}

                                                                                                                        /*
--------------------------------------------------------------------------------
   keybind process
--------------------------------------------------------------------------------                                        */

cls_mac_mode mac_mode;
cls_mac_key  mac_key;
flag new_key_seq_list_flg;
flag new_key_seq_flg;
flag not_modify_flg;
flag not_key_flg;

void new_mode()
{
   mac_fill_zero(mac_mode);
   mac_mode.name_inx       = mac_data_stack.get_cnt();
   mac_mode.func_begin_inx = mac_func_stack.get_cnt();
   mac_mode.key_begin_inx  = mac_key_stack.get_cnt();
   mac_data_stack.push_ary((byte*)lex_val_ach,strlen(lex_val_ach)+1);
}

void mode_end()
{
   mac_mode.key_end_inx = mac_key_stack.get_cnt();
   mac_mode_stack.push_pnt(&mac_mode);
}

void new_bind()
{
   int32 id = scan_func(lex_val_ach);
   if (!id) throw cls_xmsg("func: mc/compiler.hpp/new_bin\ninfo: undefined function\n");
   mac_func_stack.push_val(id);
}

void new_keyseq_list()
{
   new_key_seq_list_flg = def_yes;
}

void new_keyseq()
{
   new_key_seq_flg = def_yes;
}

void new_key()
{
   mac_fill_zero(mac_key);
   if (new_key_seq_list_flg) { mac_key.on_u16 = 0x8000U;  new_key_seq_list_flg = def_no; }
   if (new_key_seq_flg) { mac_key.off_u16 = 0x8000U; new_key_seq_flg = def_no ; }
   not_modify_flg = def_no;
   not_key_flg = def_no;
}

void not_modify()
{
   not_modify_flg = def_yes;
}

static
void set_modify_st(uint16 val)
{
   if ( not_modify_flg )
   {
      mac_key.off_u16 |= val;
   }
   else mac_key.on_u16 |= val;
}

void modify_s()
{
   set_modify_st(def_mk_mask_s);
}

void modify_ls()
{
   set_modify_st(def_mk_mask_ls);
}

void modify_rs()
{
   set_modify_st(def_mk_mask_rs);
}

void modify_c()
{
   set_modify_st(def_mk_mask_c);
}

void modify_lc()
{
   set_modify_st(def_mk_mask_lc);
}

void modify_rc()
{
   set_modify_st(def_mk_mask_rc);
}

void modify_a()
{
   set_modify_st(def_mk_mask_a);
}

void modify_la()
{
   set_modify_st(def_mk_mask_la);
}

void modify_ra()
{
   set_modify_st(def_mk_mask_ra);
}

void modify_m()
{
   set_modify_st(def_mk_mask_m);
}

void modify_lm()
{
   set_modify_st(def_mk_mask_lm);
}

void modify_rm()
{
   set_modify_st(def_mk_mask_rm);
}

static void keyseq_end()
{
   uint16 id = scan_key_name();
   if (!id) throw cls_xmsg("func: mc/compiler.cpp/keyseq_end()\ninfo: unknown key name\n");
   mac_key.code_u16 = not_key_flg ? ( not_key_flg = def_no , 0x8000 | id ) : id ;
   mac_key_stack.push_pnt(&mac_key);
}

void not_key()
{
   not_key_flg = def_yes;
}

void key_name()
{
   keyseq_end();
}

void key_name_str()
{
   keyseq_end();
}
                                                                                                                        /*
--------------------------------------------------------------------------------
   main
--------------------------------------------------------------------------------                                        */

void save_bin()
{
   try
   {
      cls_wfile bin_file(bin_fname_ach);

      int32 mac_data_off;
      int32 mac_code_off;
      int32 mac_mode_off;
      int32 mac_func_off;
      int32 mac_key_off;

      bin_file.set_offset(sizeof(int32)*5);

      mac_data_off = bin_file.get_offset();
      bin_file.write(mac_data_stack.get_base_pnt(), mac_data_stack.get_cnt_in_byte());

      mac_code_off = bin_file.get_offset();
      bin_file.write(mac_code.get_base_pnt(), sizeof(int32)*ip);

      mac_mode_off = bin_file.get_offset();
      bin_file.write(mac_mode_stack.get_base_pnt(), mac_mode_stack.get_cnt_in_byte());

      mac_func_off = bin_file.get_offset();
      bin_file.write(mac_func_stack.get_base_pnt(), mac_func_stack.get_cnt_in_byte());

      mac_key_off = bin_file.get_offset();
      bin_file.write(mac_key_stack.get_base_pnt(), mac_key_stack.get_cnt_in_byte());

      bin_file.set_offset(0);
      bin_file.write(&mac_data_off, sizeof(int32));
      bin_file.write(&mac_code_off, sizeof(int32));
      bin_file.write(&mac_mode_off, sizeof(int32));
      bin_file.write(&mac_func_off, sizeof(int32));
      bin_file.write(&mac_key_off,  sizeof(int32));
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info("func: mc/compiler.cpp/save_bin()\ninfo: binary output error\n");
      throw;
   }
}

void compile_mac_file()
{
   mac_data_stack.push_val(0);

   scanner_mac_mode();
   yyparse();

   while (mac_data_stack.get_cnt_in_byte() % 4) mac_data_stack.push_val(0);

   save_bin();
}

