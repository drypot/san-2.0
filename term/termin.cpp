                                                                                                                        /*
--------------------------------------------------------------------------------
   term/termin.cpp
   copyright(C) kyuhyun park
   1995.11.14
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/charlist.hpp>
#include <pub/dir.hpp>
#include <pub/misc.hpp>
#include <pub/init.hpp>
#include <key/mac.hpp>

#include <term/glb.hpp>

#define def_size_chat_buf 256

static cls_mac_runner* mac_runner;

static bool    chat_flg;
static char16  char_buf_c16_ary[def_size_chat_buf];
static int     chat_x;
static int     chat_xvis_base;
static int     chat_len;
static bool    chat_insert_flg = def_yes;

void chat_reset()
{
   chat_x = 0;
   chat_xvis_base = 0;
   chat_len = 0;
   char_brd_pnt->set_x(0);
}

void chat_update_chat()
{
   int inx = 0;
   int inx_vis = 0;
   int prev_x = char_brd_pnt->get_x();

   char_brd_pnt->calc_cursor_width(chat_x < chat_len ? char_buf_c16_ary[chat_x] : ' ');

   while (inx_vis + get_c16_width(char_buf_c16_ary[inx]) < chat_xvis_base)
   {
      inx_vis += get_c16_width(char_buf_c16_ary[inx]);
      inx++;
   }

   char_brd_pnt->set_x(inx_vis - chat_xvis_base);
   while (inx < chat_len && char_brd_pnt->get_x() < def_term_width) char_brd_pnt->write(char_buf_c16_ary[inx++]);
   char_brd_pnt->erase_to_eol();
   char_brd_pnt->set_x(prev_x);
   draw_chat();
}

void chat_set_x(int x)
{
   int inx = 0;
   int inx_vis = 0;

   chat_x = x;

   if (chat_x < 0) chat_x = 0;
   if (chat_x > chat_len) chat_x = chat_len;

   while (inx < chat_x)
   {
      inx_vis += get_c16_width(char_buf_c16_ary[inx]);
      inx++;
   }

   if (inx_vis < chat_xvis_base)
   {
      chat_xvis_base = inx_vis;
   }
   else
   {
      int width = chat_x < chat_len ? get_c16_width(char_buf_c16_ary[chat_x]) : 1;
      if (chat_xvis_base + def_term_width < inx_vis + width)
      {
         chat_xvis_base = inx_vis + width - def_term_width;
      }
   }
   char_brd_pnt->set_x (inx_vis - chat_xvis_base);
}

void chat_set_x_rel(int dx)
{
   chat_set_x(chat_x + dx);
}

bool chat_char_insert()
{
   if (chat_insert_flg)
   {
      if (chat_len == def_size_chat_buf)
      {
         beep();
         return def_error;
      }
      else
      {
         memmove(char_buf_c16_ary + chat_x + 1, char_buf_c16_ary + chat_x, (chat_len - chat_x)*2);
         chat_len++;
         return def_ok;
      }
   }
   else
   {
      if (chat_x == def_size_chat_buf)
      {
         beep();
         return def_error;
      }
      else
      {
         if (chat_x == chat_len) chat_len++;
         return def_ok;
      }
   }
}

void chat_char_delete()
{
   if (chat_x == chat_len)
   {
      beep();
   }
   else
   {
      memmove(char_buf_c16_ary + chat_x, char_buf_c16_ary + chat_x + 1, (chat_len - chat_x)*2);
      chat_len--;
   }
}

inline
void chat_char_replace(char16 ch)
{
   char_buf_c16_ary[chat_x] = ch;
}

void coder_loop()
{
   if (chat_flg)
   {
      while (coder.is_holding())
      {
         coder.get();
         char16 c16 = coder.get_code();

         switch (coder.get_action())
         {
            case def_ca_direct :
               if (chat_char_insert())
               {
                  chat_char_replace(c16);
                  chat_set_x_rel(1);
               }
               break;

            case def_ca_open :
               if (chat_char_insert())
               {
                  chat_char_replace(c16);
                  chat_set_x_rel(0);
               }
               break;

            case def_ca_replace :
               chat_char_replace(c16);
               break;

            case def_ca_close:
               chat_char_replace(c16);
               chat_set_x_rel(1);
               break;

            case def_ca_cancel:
               chat_char_delete();
               break;
         }
      }
   }
   else
   {
      while (coder.is_holding())
      {
         coder.get();
         char16 c16 = coder.get_code();

         switch (coder.get_action())
         {
            case def_ca_direct :
               port_write (c16);
               break;

            case def_ca_open :
               term_brd_pnt->set_img_cursor(c16);
               draw_term();
               break;

            case def_ca_replace :
               term_brd_pnt->set_img_cursor(c16);
               draw_term();
               break;

            case def_ca_close:
               term_brd_pnt->set_img_cursor(0);
               if (host_code_int == def_ct_wansung) c16 = get_wansung (c16);
               if (c16)
               {
                  port_write (get_u16_high(c16));
                  port_write (get_u16_low(c16));
               }
               draw_term();
               break;

            case def_ca_cancel:
               term_brd_pnt->set_img_cursor(0);
               draw_term();
               break;
         }
      }
   }
}

void pdf_next_mcp()
{
   mcp_list_iter.next_mcp();
   update_state();
}

void pdf_coder_discard()
{
   coder.discard();
   coder_loop();
}

void pdf_coder_complete()
{
   coder.complete();
   coder_loop();
}

int32 pdf_coder_is_incomplete()
{
   return coder.is_incomplete();
}

void pdf_port_write_byte()
{
   port_write((byte)mac_runner->get_arg_i32(0));
}

void pdf_port_write_string()
{
   port_write_str((char*)mac_runner->get_arg_pnt(0));
}

void pdf_send_text()
{
   snd_txt();
}

void pdf_send_binary()
{
   snd_bin();
}

void pdf_send_zmodem()
{
   snd_zmd();
}

void pdf_receive_text()
{
   rcv_txt();
}

void pdf_receive_binary()
{
   rcv_bin();
}

void pdf_receive_zmodem()
{
   rcv_zmd();
}

void pdf_exit()
{
   WinPostMsg(frame_hwnd, WM_CLOSE, 0, 0);
}

void pdf_chat_mode()
{
   mac_runner->set_mode("chat");
   chat_flg = def_yes;
   term_brd_pnt->set_outline_cursor(def_yes);
   char_brd_pnt->show_cursor(def_yes);
   draw_term();
}

void pdf_term_mode()
{
   mac_runner->set_mode("term");
   chat_flg = def_no;
   term_brd_pnt->set_outline_cursor(def_no);
   char_brd_pnt->show_cursor(def_no);

   chat_reset();
   chat_update_chat();
   draw_term();
}

void pdf_change_host_code()
{
   turn(&host_code_int, def_ct_johab, def_ct_wansung);
   update_state();
}

void pdf_change_local_code()
{
   turn(&local_code_int, def_ct_johab, def_ct_wansung);
   update_state();
}

void pdf_chat_cursor_left()
{
   chat_set_x_rel(-1);
}

void pdf_chat_cursor_right()
{
   chat_set_x_rel(1);
}

void pdf_chat_cursor_home()
{
   chat_set_x(0);
}

void pdf_chat_cursor_end()
{
   chat_set_x(chat_len);
}

void pdf_chat_cursor_left_acc()
{
   int inx = chat_x;

   while (inx > 0 && !is_word(char_buf_c16_ary[inx-1])) inx--;
   while (inx > 0 && is_word(char_buf_c16_ary[inx-1])) inx--;
   chat_set_x(inx);
}

void pdf_chat_cursor_right_acc()
{
   int inx = chat_x;
   while (inx < chat_len && is_word(char_buf_c16_ary[inx])) inx++;
   while (inx < chat_len && !is_word(char_buf_c16_ary[inx])) inx++;
   chat_set_x(inx);
}

void pdf_chat_insert_on()
{
}

void pdf_chat_insert_off()
{
}

int32 pdf_chat_is_insert_on()
{
   return chat_insert_flg;
}

void pdf_chat_char_delete()
{
   chat_char_delete();
}

void pdf_chat_char_erase()
{
}

void pdf_chat_word_delete()
{
   int inx1 = chat_x;
   int inx2;

   pdf_chat_cursor_right_acc();
   inx2 = chat_x;
   memmove (char_buf_c16_ary + inx1 , char_buf_c16_ary + inx2, (chat_len - inx2)*2);
   chat_len -= inx2 - inx1;
   chat_set_x(inx1);
}

void pdf_chat_line_delete()
{
   chat_len = 0;
   chat_set_x(0);
}

void pdf_chat_line_delete_rest()
{
   chat_len = chat_x;
}

int32 pdf_chat_is_bol()
{
   return chat_x == 0;
}

void pdf_chat_flush()
{
   int inx = 0;
   char16 c16;

   while (inx < chat_len)
   {
      c16 = char_buf_c16_ary[inx];
      if (is_double(c16))
      {
         if (host_code_int == def_ct_wansung) c16 = get_wansung(c16);
         port_write((byte)get_u16_high(c16));
         port_write((byte)get_u16_low(c16));
      }
      else
      {
         port_write((byte)c16);
      }
      inx++;
   }

   chat_reset();
}

void pdf_test_func1()
{
   /*
   #include <pub/io.hpp>
   #include <term/termout.hpp>

   readfiletype file("h:\\cap\\test3.cap");
   off_t sz = file.get_size();

   byte* p = (byte*) mem_alloc(sz);
   file.read(p,sz);
   while (sz)
   {
      term_write(p,get_min(sz,32));
      draw_term();
      p += get_min(sz,32);
      sz -= get_min(sz,32);
   }
   */
}

void pdf_test_func2()
{
}

void pdf_test_func3()
{
}

void pcs_key_event (cls_key_event* key_event)
{
   if (key_event->is_valid())
   {
      if (send_txt_flg)
      {
         if (key_event->is_make_event() && key_event->get_code() == def_key_esc) snd_txt_end();
      }
      else
      {
         switch (mac_runner->scan(key_event))
         {
            case def_kb_scan_match :
               mac_runner->execute();
               if (chat_flg) chat_update_chat();
               break;

            case def_kb_scan_failed :
               {
                  cls_mc mc(key_event, mcp_list_iter.get_mcp());
                  coder.put (&mc);
                  coder_loop ();
                  if (chat_flg) chat_update_chat();
               }
               break;
         }
      }
   }
}

#include <macro/tmp/term.def>
#include <macro/tmp/term.map>

static void ctor()
{
   try
   {
      cls_mac_bin* mac_bin = new cls_mac_bin(cls_fname("@bindir/../macro/term.bin").get_path());
      mac_runner = new cls_mac_runner(mac_bin, mac_mapper);
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info("func: term/termin.cpp/ctor()\ninfo: error in loading macro\n");
      throw;
   }
}

static cls_initer initer(ctor);
