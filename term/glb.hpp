                                                                                                                        /*
--------------------------------------------------------------------------------
   term/glb.hpp
   copyright(C) kyuhyun park
   1995.11.14
--------------------------------------------------------------------------------                                        */

#ifdef def_term_glb_hpp
#error 'term/glb.hpp' duplicated.
#endif

#define def_term_glb_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_net_comport_hpp
#include <net/comport.hpp>
#endif

#ifndef def_vio_textbrd_hpp
#include <vio/textbrd.hpp>
#endif

#ifndef def_key_coder_hpp
#include <key/coder.hpp>
#endif

#define def_term_width 80
#define def_client_width 80
#define def_client_height (term_height_int + 2)

extern int   term_height_int;
extern bool  show_unknown_esc_seq_flg;
extern char* mac_fname_pch;

extern bool  com_port_auto_detect_flg;
extern int   com_port_num_int;
extern char* modem_init_str_pch;

extern char* send_txt_dir_pch;
extern char* send_bin_dir_pch;
extern char* send_zmd_dir_pch;
extern char* receive_txt_dir_pch;
extern char* receive_bin_dir_pch;
extern char* receive_zmd_dir_pch;

extern bool send_txt_flg;
extern bool send_bin_flg;
extern bool send_zmd_flg;
extern bool receive_txt_flg;
extern bool receive_bin_flg;
extern bool receive_zmd_flg;

extern bool dtr_flg;
extern bool rts_flg;
extern bool cts_flg;
extern bool dsr_flg;
extern bool ri_flg;
extern bool dcd_flg;

extern int host_code_int;
extern int local_code_int;

extern cls_mcp_list_iter mcp_list_iter;
extern cls_coder coder;

extern cls_text_brd* term_brd_pnt;
extern cls_text_brd* char_brd_pnt;
extern cls_text_brd* stat_brd_pnt;

extern HWND frame_hwnd;
extern HWND client_hwnd;

/* file */

void snd_txt();
void snd_txt_end();

void snd_bin();

void snd_zmd();

void rcv_txt();
void rcv_txt_end();
void rcv_txt_loop(char16);
void rcv_txt_newline();

void rcv_bin();
void rcv_bin_end();
void rcv_bin_loop(byte ch);

void rcv_zmd();

/* port */

extern cls_com_port com_port;

void port_open();

inline bool port_is_readable()
{
   return com_port.is_readable();
}

inline void port_write(byte ch)
{
   com_port.put_byte(ch);
}

byte port_read();
void port_write_str(char*);
bool port_check_state();

/* screen */

void draw_state_brd();

void draw_term();
void draw_state();
void draw_chat();

void draw_client(HPS);
void draw_client();
void invalidate_client();

void update_state();

/* termin */

void pcs_key_event (cls_key_event* key_event);

/* termout */

void term_write_scn(char16 ch);
void term_write_scn(char*, int);

void term_write(byte);
void term_write(byte*);
void term_write(byte*, int);

