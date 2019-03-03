                                                                                                                        /*
--------------------------------------------------------------------------------
   text/glb.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/init.hpp>
#include <pub/time.hpp>

#include <text/glb.hpp>

CHAR client_class_ach[]="text_service_client";

CHAR* title_pch;
CHAR* copyright_eng_pch = "Copyright(C) Kyuhyun Park";
CHAR* copyright_han_pch = "Copyright(C) ¤b ‹A Ñe";

HWND frame_hwnd;
HWND client_hwnd;

cls_text_brd* ebrd;
cls_text_brd* sline;
cls_text_brd* mline;

cls_mac_runner*    mac_runner;
cls_mcp_list_iter* mcp_list_iter;
cls_coder*         coder;

cls_doc* cdoc;
cls_doc* bdoc;

char* help_fname_pch;

char* pick_list_fname_pch;
int pick_list_cmax_int;

int32 undo_step_cmax_int;

bool insert_flg;
bool indent_flg;
bool unindent_flg;
bool smart_tab_flg;
bool wrap_flg;
bool show_match_flg;
bool literal_flg;
bool remove_trailing_space_flg;
bool make_backup_flg;
bool coder_flushed_flg;

int32 para_begin_i32;
int32 para_end_i32;
int default_code_type_int;

char* default_code_type_pch;
char* init_find_option_pch;
char* init_replace_option_pch;
char* shell_prompt_pch;

int clr_sline_fg;
int clr_sline_bg;
int clr_mline_fg;
int clr_mline_bg;
int clr_normal_fg;
int clr_normal_bg;
int clr_blocked_fg;
int clr_blocked_bg;

int init_width = 70;
int init_height = 25;

cls_msg_xlator* msg_xlator;

#include <macro/tmp/text.def>
#include <macro/tmp/text.map>

static void ctor()
{
   cls_mac_bin* mac_bin = new cls_mac_bin(cls_fname("@bindir/../macro/text.bin").get_path());

   mac_runner    = new cls_mac_runner(mac_bin, mac_mapper);
   coder         = new cls_coder();
   mcp_list_iter = new cls_mcp_list_iter();

   title_pch = dup_msg("TextService %s",get_converted_date(__DATE__));

   msg_xlator = new cls_msg_xlator();
}

static cls_initer initer(ctor);
