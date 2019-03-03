                                                                                                                        /*
--------------------------------------------------------------------------------
   term/glb.cpp
   copyright(C) kyuhyun park
   1995.11.14
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <vio/textimg.hpp>
#include <key/coder.hpp>

#include <term/glb.hpp>

int   term_height_int = 25;
bool  show_unknown_esc_seq_flg;

char* mac_fname_pch;

bool  com_port_auto_detect_flg;
int   com_port_num_int = 2;
char* modem_init_str_pch;

char* send_txt_dir_pch;
char* send_bin_dir_pch;
char* send_zmd_dir_pch;
char* receive_txt_dir_pch;
char* receive_bin_dir_pch;
char* receive_zmd_dir_pch;

bool send_txt_flg;
bool send_bin_flg;
bool send_zmd_flg;
bool receive_txt_flg;
bool receive_bin_flg;
bool receive_zmd_flg;

bool dtr_flg;
bool rts_flg;
bool cts_flg;
bool dsr_flg;
bool ri_flg;
bool dcd_flg;

int host_code_int  = def_ct_wansung;
int local_code_int = def_ct_johab;

cls_mcp_list_iter mcp_list_iter;
cls_coder coder;

cls_text_brd* term_brd_pnt;
cls_text_brd* char_brd_pnt;
cls_text_brd* stat_brd_pnt;

HWND  frame_hwnd;
HWND  client_hwnd;

