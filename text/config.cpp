                                                                                                                        /*
--------------------------------------------------------------------------------
   text/config.cpp -- text configuration
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/ini.hpp>
#include <pub/init.hpp>

#include <fnt/hanfnt.hpp>
#include <fnt/engfnt.hpp>
#include <fnt/spcfnt.hpp>
#include <fnt/hnjfnt.hpp>

#include <key/mc.hpp>

#include <text/glb.hpp>

static cls_ini_item_desc desc_ary[] =
{
   {"hangul_font",          def_ini_path,      &han_fnt_fname_pch             },
   {"english_font",         def_ini_path,      &eng_fnt_fname_pch             },
   {"special1_font",        def_ini_path,      &sp1_fnt_fname_pch             },
   {"special2_font",        def_ini_path,      &sp2_fnt_fname_pch             },
   {"hanja_font",           def_ini_path,      &hnj_fnt_fname_pch             },

   {"meta_code_page",       def_ini_func_path,  mcp_add                       },

   {"pick_list_file",       def_ini_path,      &pick_list_fname_pch       },
   {"help_file",            def_ini_path,      &help_fname_pch            },

   {"insert",               def_ini_bool,      &insert_flg                },
   {"indent",               def_ini_bool,      &indent_flg                },
   {"unindent",             def_ini_bool,      &unindent_flg              },
   {"smart_tab",            def_ini_bool,      &smart_tab_flg             },
   {"make_backup",          def_ini_bool,      &make_backup_flg           },
   {"remove_trailing_space",def_ini_bool,      &remove_trailing_space_flg },

   {"tab_width",            def_ini_int,       &tab_width_int             },
   {"undo_steps",           def_ini_int,       &undo_step_cmax_int        },
   {"paragraph_left",       def_ini_int,       &para_begin_i32            },
   {"paragraph_right",      def_ini_int,       &para_end_i32              },
   {"pick_list_size",       def_ini_int,       &pick_list_cmax_int        },
   {"default_code_type",    def_ini_pch,       &default_code_type_pch     },
   {"init_find_option",     def_ini_pch,       &init_find_option_pch      },
   {"init_replace_option",  def_ini_pch,       &init_replace_option_pch   },
   {"shell_prompt",         def_ini_pch,       &shell_prompt_pch          },
   {"width",                def_ini_int,       &init_width                },
   {"height",               def_ini_int,       &init_height               },

   {"extention",            def_ini_ignore,    NULL                       },

   {"clr_sline_fg",       def_ini_int, &clr_sline_fg },
   {"clr_sline_bg",       def_ini_int, &clr_sline_bg },
   {"clr_mline_fg",       def_ini_int, &clr_mline_fg },
   {"clr_mline_bg",       def_ini_int, &clr_mline_bg },
   {"clr_normal_fg",      def_ini_int, &clr_normal_fg },
   {"clr_normal_bg",      def_ini_int, &clr_normal_bg },
   {"clr_blocked_fg",     def_ini_int, &clr_blocked_fg },
   {"clr_blocked_bg",     def_ini_int, &clr_blocked_bg },

   {NULL,                   def_ini_null,      NULL                       }
};

void parse_cmd_line()
{
}

static void parse_text_ini()
{
   parse_ini(cls_fname("@bindir/../etc/font.ini").get_path(), desc_ary);
   parse_ini(cls_fname("@bindir/../etc/mcp.ini") .get_path(), desc_ary);
   parse_ini(cls_fname("@bindir/../etc/text.ini").get_path(), desc_ary);

   parse_cmd_line();

   if (stricmp(default_code_type_pch, "johab") == 0) default_code_type_int = def_ct_johab;
   ef (stricmp(default_code_type_pch, "wansung") == 0) default_code_type_int = def_ct_wansung;
   el throw cls_xmsg("func: text/config.cpp/parse_text_ini()\ninfo: unknown code type\n");

   mac_rtcheck(is_inside(tab_width_int,1,64));
   mac_rtcheck(undo_step_cmax_int >= 0);
   mac_rtcheck(para_begin_i32 > 0);
   mac_rtcheck(para_end_i32 > 0);
   mac_rtcheck(pick_list_cmax_int >= 0);
}

static cls_initer initer(parse_text_ini);
