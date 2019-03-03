                                                                                                                        /*
--------------------------------------------------------------------------------
   text/pdf.hpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#ifdef def_text_pdf_hpp
#error 'text/glb.hpp' duplicated.
#endif

#define def_text_pdf_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

void pdf_quit();

void pdf_doc_new();
int32 pdf_doc_open();
int32 pdf_doc_open_johab();
int32 pdf_doc_open_wansung();
int32 pdf_doc_save();
int32 pdf_doc_save_as();
int32 pdf_doc_close();
int32 pdf_doc_close_all();
int32 pdf_doc_discard();
int32 pdf_doc_discard_all();
int32 pdf_doc_prev();
int32 pdf_doc_next();
void pdf_doc_list();
void pdf_doc_iterate();

void pdf_doc_pick_list();
void pdf_doc_print();
int32 pdf_doc_is_modifed();

void pdf_fork();
void pdf_fork_shell();

int32 pdf_focus_prev_char();
int32 pdf_focus_next_char();

int32 pdf_focus_prev_line();
int32 pdf_focus_next_line();

int32 pdf_focus_prev_page();
int32 pdf_focus_next_page();

int32 pdf_focus_line_begin();
int32 pdf_focus_line_end();

int32 pdf_focus_doc_begin();
int32 pdf_focus_doc_end();

void pdf_focus_block_begin();
void pdf_focus_block_end();

int32 pdf_focus_window_top();
int32 pdf_focus_window_mid();
int32 pdf_focus_window_bottom();

int32 pdf_focus_skip_prev_word();
int32 pdf_focus_skip_next_word();

int32 pdf_focus_skip_prev_non_word();
int32 pdf_focus_skip_next_non_word();

int32 pdf_focus_skip_prev_space();
int32 pdf_focus_skip_next_space();

int32 pdf_focus_mark();
int32 pdf_focus_prev_mark();
int32 pdf_focus_tmp_mark();

int32 pdf_focus_line();
int32 pdf_focus_column();

int32 pdf_focus_match();

int32 pdf_window_scroll_left();
int32 pdf_window_scroll_right();
int32 pdf_window_scroll_up();
int32 pdf_window_scroll_down();

void pdf_cursor_adjust();
void pdf_window_adjust();

int32 pdf_focus_is_column_one();
int32 pdf_focus_is_line_head();
int32 pdf_focus_is_line_out();
int32 pdf_focus_is_first_line();
int32 pdf_focus_is_last_line();
int32 pdf_focus_is_window_top();
int32 pdf_focus_is_window_bottom();
int32 pdf_focus_is_in_block();

int32 pdf_focus_get_line_num();
int32 pdf_focus_get_column_num();

void pdf_mark();
void pdf_mark_prev();
void pdf_mark_tmp();

void pdf_write_date();
void pdf_write_time();
void pdf_write_string();
void pdf_write_literal();
void pdf_write_special();
void pdf_write_hanja();

void pdf_char_remove();
void pdf_char_erase();

void pdf_char_flip();
void pdf_char_lower();
void pdf_char_upper();

void pdf_line_insert();
void pdf_line_insert_below();

void pdf_line_remove();
void pdf_line_remove_below();

void pdf_line_split();
void pdf_line_join();

void pdf_line_indent();
void pdf_line_unindent();

void pdf_line_align_prev();
void pdf_line_align_left();
void pdf_line_align_right();
void pdf_line_align_center();

int32 pdf_line_is_empty();
int32 pdf_line_is_space_from();
int32 pdf_line_is_space_till();

void pdf_block_set_char_type();
void pdf_block_set_line_type();
void pdf_block_set_column_type();

void pdf_block_set_marking();
int32 pdf_block_is_marking();

void pdf_block_set_enabled();
int32 pdf_block_is_enabled();
int32 pdf_block_is_enabled_existent();

void pdf_block_set_begin();
void pdf_block_set_end();
void pdf_block_expand();

int32 pdf_block_remove();

void pdf_block_erase();
void pdf_block_erase_line();
void pdf_block_erase_char();

void pdf_block_fill();

void pdf_block_flip();
void pdf_block_lower();
void pdf_block_upper();

void pdf_block_align_left();
void pdf_block_align_right();
void pdf_block_align_center();

int32 pdf_block_indent();
int32 pdf_block_unindent();

int32 pdf_block_shift_left();
int32 pdf_block_shift_right();

void pdf_hiden_block_set_begin();
void pdf_hiden_block_set_end();
void pdf_hiden_block_remove();
void pdf_hiden_block_set_find_string();

void pdf_buffer_reset();
int32 pdf_buffer_read_block();
int32 pdf_buffer_read_block_arranging();
int32 pdf_buffer_write_block();
int32 pdf_buffer_read_file();
int32 pdf_buffer_write_file();

void pdf_clipboard_reset();
void pdf_clipboard_read_block();
void pdf_clipboard_write_block();

void pdf_find();
void pdf_find_replace();
void pdf_find_repeat();
void pdf_find_repeat_backward();

void pdf_draw();

void pdf_mcp_next();

int32 pdf_coder_is_flushed();

void pdf_code_set_wansung();
void pdf_code_set_johab();
int32 pdf_code_is_johab();

void pdf_mode_set_insert();
int32 pdf_mode_is_insert();

void pdf_mode_set_indent();
int32 pdf_mode_is_indent();

void pdf_mode_set_unindent();
int32 pdf_mode_is_unindent();

void pdf_mode_set_wrap();
int32 pdf_mode_is_wrap();

void pdf_mode_set_show_match();
int32 pdf_mode_is_show_match();

void pdf_mode_set_smart_tab();
int32 pdf_mode_is_smart_tab();

void pdf_info_quick_help();
void pdf_info_char();

void pdf_log_undo();
void pdf_log_redo();
void pdf_log_reset();
void pdf_log_continue_group();

void pdf_key_macro_record();
void pdf_key_macro_replay();

void pdf_no_operation();
void pdf_test1();
void pdf_test2();
void pdf_test3();
void pdf_test4();
void pdf_test5();

