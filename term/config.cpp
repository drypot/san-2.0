                                                                                                                        /*
--------------------------------------------------------------------------------
   term/config.cpp
   copyright(c) kyuhyun park
   1995.11.26
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/lex.hpp>
#include <pub/dir.hpp>
#include <pub/ini.hpp>
#include <pub/init.hpp>

#include <key/mc.hpp>

#include <fnt/hanfnt.hpp>
#include <fnt/engfnt.hpp>
#include <fnt/spcfnt.hpp>
#include <fnt/hnjfnt.hpp>

#include <term/glb.hpp>

static cls_ini_item_desc ary_ini_item_desc[] =
{
   {"hangul_font",          def_ini_path,      &han_fnt_fname_pch       },
   {"english_font",         def_ini_path,      &eng_fnt_fname_pch       },
   {"special1_font",        def_ini_path,      &sp1_fnt_fname_pch       },
   {"special2_font",        def_ini_path,      &sp2_fnt_fname_pch       },
   {"hanja_font",           def_ini_path,      &hnj_fnt_fname_pch       },

   {"meta_code_page",       def_ini_func_path,  mcp_add                 },

   {"macro_image",          def_ini_path,      &mac_fname_pch       },
   {"com_port_auto_detect", def_ini_bool,      &com_port_auto_detect_flg},
   {"com_port",             def_ini_int,       &com_port_num_int    },
   {"modem_init_string",    def_ini_pch,       &modem_init_str_pch  },
   {"term_height",          def_ini_int,       &term_height_int     },
   {"show_unknown_esc_seq", def_ini_bool,      &show_unknown_esc_seq_flg },
   {"send_text_dir",        def_ini_path,      &send_txt_dir_pch    },
   {"send_binary_dir",      def_ini_path,      &send_bin_dir_pch    },
   {"send_zmodem_dir",      def_ini_path,      &send_zmd_dir_pch    },
   {"receive_text_dir",     def_ini_path,      &receive_txt_dir_pch },
   {"receive_binary_dir",   def_ini_path,      &receive_bin_dir_pch },
   {"receive_zmodem_dir",   def_ini_path,      &receive_zmd_dir_pch },
   {NULL,                   def_ini_null,      NULL                     }
};

static void parse_term_ini()
{
   parse_ini(cls_fname("@bindir/../etc/font.ini").get_path(), ary_ini_item_desc);
   parse_ini(cls_fname("@bindir/../etc/mcp.ini") .get_path(), ary_ini_item_desc);
   parse_ini(cls_fname("@bindir/../etc/term.ini").get_path(), ary_ini_item_desc);
   mac_rtcheck(is_inside(com_port_num_int, 1, 4));
   mac_rtcheck(term_height_int > 10);
}

static cls_initer initer(parse_term_ini);

