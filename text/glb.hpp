                                                                                                                        /*
--------------------------------------------------------------------------------
   text/glb.hpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#ifdef def_text_glb_hpp
#error 'text/glb.hpp' duplicated.
#endif

#define def_text_glb_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_dir_hpp
#include <pub/dir.hpp>
#endif

#ifndef def_pub_point_hpp
#include <pub/point.hpp>
#endif

#ifndef def_pub_res_hpp
#include <pub/res.hpp>
#endif

#ifndef def_cnt_paper_hpp
#include <cnt/paper.hpp>
#endif

#ifndef def_vio_textbrd_hpp
#include <vio/textbrd.hpp>
#endif

#ifndef def_key_keyevent_hpp
#include <key/keyevent.hpp>
#endif

#ifndef def_key_coder_hpp
#include <key/coder.hpp>
#endif

#ifndef def_key_mac_hpp
#include <key/mac.hpp>
#endif

#include <text/pdf.hpp>

enum
{
   def_mark_prev = 10,
   def_mark_tmp,
   def_mark_block_begin,
   def_mark_block_end,
   def_mark_block_anchor,
   def_mark_hiden_block_begin,
   def_mark_hiden_block_end,
   def_mark_internal_tmp,
   def_mark_list_cmax
};

enum
{
   def_block_type_char,
   def_block_type_line,
   def_block_type_column
};

class cls_mark
{
   public:
      int32 y;
      int32 x;
      bool  ignore_x_flg;

   public:
      cls_mark(int32 arg_x, int32 arg_y) : y(arg_y) , x(arg_x), ignore_x_flg(def_no) {}
      cls_mark(int32 arg_x, int32 arg_y, bool f) : y(arg_y) , x(arg_x), ignore_x_flg(f) {}
      cls_mark() : y(-1), ignore_x_flg(def_no) {}

      void make_null() { y=-1; }
      bool is_null()   { return y==-1; }
      void set_ignore_x(bool flg)  { ignore_x_flg = flg; }

      bool operator <  (cls_mark& second);
      bool operator == (cls_mark& second);
      bool operator <= (cls_mark& second);
};

class cls_log_frame
{
   public:
      byte type;
      byte new_group_flg;
      int32 index;
      int32 cnt;
      int32 dary_cnt;

   public:
      cls_log_frame();
};

typedef tem_dynamic_array<cls_log_frame,256> cls_log_frame_dary;

class cls_doc
{
   public:

      #define block_begin       mark_ary[def_mark_block_begin]
      #define block_end         mark_ary[def_mark_block_end]
      #define block_anchor      mark_ary[def_mark_block_anchor]
      #define hiden_block_begin mark_ary[def_mark_hiden_block_begin]
      #define hiden_block_end   mark_ary[def_mark_hiden_block_end]

      static int32 id_seed;
      static cls_paper buffer;
      static int buffer_type;

      int32 id;
      cls_fname fname;
      cls_paper paper;
      cls_paper_iter iter;
      int code_type;
      int32 prev_vx;
      bool modified_flg;
      cls_point cursor;
      cls_point window;
      int  block_type;
      bool block_marking_flg;
      bool block_enabled_flg;

      cls_mark mark_ary[def_mark_list_cmax];

      bool in_undo_process_flg;
      bool in_redo_process_flg;
      bool new_group_flg;
      int log_cnt;
      cls_log_frame_dary* log_frame_dary;
      cls_paper_char_dary* log_char_dary;

      cls_log_frame_dary undo_frame_dary;
      cls_paper_char_dary undo_char_dary;

      cls_log_frame_dary redo_frame_dary;
      cls_paper_char_dary redo_char_dary;

   public:

      cls_doc();
     ~cls_doc();

      void reset();

      void load(char* fname_pch, int option = def_ct_auto);
      void save();

      void set_modified(bool f);
      bool is_modified() { return modified_flg; }

      void mark_reset();
      void mark_reset(int);

      void mark_insert_line(int32);
      void mark_remove_line(int32);

      void mark_insert(int32,int32);
      void mark_remove(int32,int32);
      void mark_separate(int32);
      void mark_join(int32);

      void mark_set(int);
      void mark_set(int,int32,int32);
      bool mark_get(int,int32*,int32*);

      void focus_set_prev_vx();

      bool focus_set_x (int32);
      void focus_set_x (int32,int32);
      bool focus_set_x_rel (int32);
      bool focus_set_vx (int32);
      void focus_reset_vx();

      bool focus_set_y (int32);
      bool focus_set_y_rel (int32);

      bool focus_set_xy (int32, int32);
      bool focus_set_xy_rel (int32, int32);
      bool focus_mark (int);

      bool focus_skip_prev(bool (*fn)(char16));
      bool focus_skip_next(bool (*fn)(char16));

      bool focus_is_in_block();

      void cursor_adjust_x();
      void cursor_adjust_y();
      void cursor_adjust_xy();

      void window_adjust_x();
      void window_adjust_y();
      void window_adjust_xy();

      void paper_insert_line();
      void paper_insert_line_below();
      void paper_remove_line();
      void paper_remove_line_below();

      void paper_insert(int32 inx, int32 cnt);

      void paper_insert(int32 dst_inx, cls_paper* src_paper, int32 src_inx, int32 cnt);
      void paper_insert(int32 inx, cls_paper_char_dary* src_char_dary, int32 cnt);

      void paper_remove(int32 inx, int32 cnt);

      void paper_replace(int32 inx, int32 ins_ch_cnt, int32 vis_ins_ch_cnt);

      void paper_fill(int32,char16,int32);

      void paper_separate();
      void paper_separate(int32);
      void paper_join();
      void paper_join(int32);

      void paper_write(char16);
      void paper_write(int32 inx, cls_paper_char_dary* src_char_dary, int32 cnt);

      bool paper_is_space (int32 inx, int32 end);
      bool paper_is_space_from(int32);
      bool paper_is_space_till(int32);

      cls_mark block_get_mark();
      void block_save_focus();
      void block_restore_focus();
      bool block_mark_is_ok(cls_mark* begin, cls_mark* end, int type);
      bool block_mark_is_ok();
      void block_set_marking(bool flg);
      void block_continue_marking();
      void block_set_enabled(bool enable_flg);
      void block_set_type(int new_type);
      void block_set_begin();
      void block_set_end();
      void block_expand();
      bool block_remove(cls_mark* bp, cls_mark* ep, int type);
      bool block_remove();
      bool block_insert_head(char16 ch);
      bool block_remove_head_space(int32 cnt);

      void hiden_block_set_begin();
      void hiden_block_set_end();
      void hiden_block_remove();

      void focus_block_begin();
      void focus_block_end();

      void buffer_reset();
      bool buffer_read_char_block();
      bool buffer_read_line_block();
      bool buffer_read_block();
      bool buffer_read_block_arranging();
      bool buffer_write_char_block();
      bool buffer_write_line_block();
      bool buffer_write_block();
      void buffer_read_file(char* fname_pch);
      void buffer_write_file(char* fname_pch);

      void log_new_group();

      void log_append_frame(cls_log_frame*);
      bool log_common();

      void log_focus_set_x();
      void log_focus_set_y();

      void log_paper_insert_line();
      void log_paper_insert_line_below();
      void log_paper_remove_line();
      void log_paper_remove_line_below();

      void log_paper_insert(int32,int32);
      void log_paper_insert_paper(int32,int32);
      void log_paper_insert_char_dary(int32,int32);
      void log_paper_remove(int32,int32);
      void log_paper_fill(int32,int32);
      void log_paper_separate(int32);
      void log_paper_join(int32);
      void log_paper_write_char16();
      void log_paper_write_char_dary(int32,int32);

      void log_mark(cls_mark*);
      void log_block_set_enabled();
      void log_block_set_type();
      void log_block_set_marking();
      void log_block_begin();
      void log_block_end();
      void log_view_invalidate();

      void log_replay(cls_log_frame_dary*, cls_paper_char_dary*);
      void log_undo();
      void log_redo();
      void log_reset();
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

extern CHAR client_class_ach[];

extern CHAR* title_pch;
extern CHAR* copyright_eng_pch;
extern CHAR* copyright_han_pch;

extern HWND frame_hwnd;
extern HWND client_hwnd;

extern cls_text_brd* ebrd;
extern cls_text_brd* sline;
extern cls_text_brd* mline;

extern cls_mac_runner*    mac_runner;
extern cls_mcp_list_iter* mcp_list_iter;
extern cls_coder*         coder;

extern cls_doc* cdoc; // current doc
extern cls_doc* bdoc; // blocked doc

extern char* help_fname_pch;

extern char* pick_list_fname_pch;
extern int pick_list_cmax_int;

extern int32 undo_step_cmax_int;

extern bool insert_flg;
extern bool indent_flg;
extern bool unindent_flg;
extern bool smart_tab_flg;
extern bool wrap_flg;
extern bool show_match_flg;
extern bool literal_flg;
extern bool remove_trailing_space_flg;
extern bool make_backup_flg;
extern bool coder_flushed_flg;

extern int32 para_begin_i32;
extern int32 para_end_i32;

extern int default_code_type_int;

extern char* default_code_type_pch;
extern char* init_find_option_pch;
extern char* init_replace_option_pch;
extern char* shell_prompt_pch;

extern int clr_sline_fg;
extern int clr_sline_bg;
extern int clr_mline_fg;
extern int clr_mline_bg;
extern int clr_normal_fg;
extern int clr_normal_bg;
extern int clr_blocked_fg;
extern int clr_blocked_bg;

extern int init_width;
extern int init_height;

extern cls_msg_xlator* msg_xlator;
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void client_char();
void client_update();
void client_draw(HPS);
void client_draw();
MRESULT EXPENTRY client_win_proc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

void frame_create();
void frame_destroy();

char* msg_get(int num);

void sline_invalidate();
void sline_update();
void sline_draw(HPS hps);
void sline_draw();

void mline_clear();
void mline_write(char* pch, bool arg_auto_erase_flg = def_yes);
void mline_write(int msg_num, bool arg_auto_erase_flg = def_yes);
void mline_write_error();
void mline_update();
void mline_draw(HPS);
void mline_draw();
void mline_wm_timer();

void view_invalidate();
void view_invalidate_line();
void view_update();
void view_draw(HPS hps);
void view_draw();
bool view_is_invalid();
bool view_is_line_invalid();

void ca_direct(char16 ch);
void ca_open(char16 ch);
void ca_replace(char16 ch);
void ca_close(char16 ch);
void ca_cancel();

void doc_init();
bool doc_open(char* fname_pch, int option);

void paper_line_edit_common();
void paper_remove_trailing_space();
