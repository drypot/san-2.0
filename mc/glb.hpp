                                                                                                                        /*
--------------------------------------------------------------------------------
   mc/glb.hpp
   copyright(c) kyuhyun park
   1994.11.06
--------------------------------------------------------------------------------                                        */

#ifdef def_mc_glb_hpp
#error 'mc/glb.hpp' duplicated.
#endif

#define def_mc_glb_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

/* main */

#ifdef __cplusplus
extern "C" {
#endif

extern char key_name_fname_ach[];
extern char mac_fname_ach[];
extern char bin_fname_ach[];

void open_error(char* name);

#ifdef __cplusplus
}
#endif

#define def_id_size 64

/* keyname */

uint16 scan_key_name();
void read_key_name_file();

/* func */

uint32 scan_func(char*);
void regi_func(char*,uint32);

/* compiler */

#ifdef __cplusplus
extern "C" {
#endif

void bifunc();

void func_name();
void func_body_end();

void statement_return();

void if_exp_end();
void else_begin();
void else_end();
void else_null();

void while_begin();
void while_exp_end();
void while_end();

void call_name();
void call_arg_end();
void call_arg_str();
void call_arg_exp();

void exp_discard();
void exp_logical_or();
void exp_logical_and();
void exp_equal();
void exp_not_equal();
void exp_above();
void exp_below();
void exp_above_equal();
void exp_below_equal();
void exp_plus();
void exp_minus();
void exp_mul();
void exp_div();
void exp_not();
void exp_int();
void exp_char();
void exp_func_result();
void exp_func_ptr();

void new_mode();
void mode_end();
void new_bind();
void new_keyseq_list();
void new_keyseq();
void new_key();
void not_modify();
void modify_s();
void modify_ls();
void modify_rs();
void modify_c();
void modify_lc();
void modify_rc();
void modify_a();
void modify_la();
void modify_ra();
void modify_m();
void modify_lm();
void modify_rm();
void not_key();
void key_name();
void key_name_str();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
void compile_mac_file();
#endif

/* scanner */

#ifdef __cplusplus
extern "C" {
#endif

void scanner_key_name_mode();
void scanner_mac_mode();

#ifdef __cplusplus
}
#endif



