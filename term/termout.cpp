                                                                                                                        /*
--------------------------------------------------------------------------------
   term/termout.cpp
   copyright(c) kyuhyun park
   1995.12.13
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/charlist.hpp>
#include <pub/misc.hpp>

#include <term/glb.hpp>

enum
{
   def_cmd_esc,
   def_cmd_bracket,
   def_cmd_amp,
   def_cmd_equal
};

static bool parseing_es_flg;
static int  es_state_int;

static int  prev_x;
static int  prev_y;
static uint prev_attr;
static int  prev_fg = def_clr_pale_gray;
static int  prev_bg = def_clr_black;
static bool prev_bri;
static bool prev_bnk;

static int  stt_fg = def_clr_pale_gray;
static int  stt_bg = def_clr_black;
static bool stt_bri;
static bool stt_bnk;

static bool set_scroll_region_flg;
static int  scroll_top;
static int  scroll_bot;

static int  param_stack_int_ary[8];
static int  param_cnt;

static char es_buf_ach[32];
static int  es_cnt;

static int  cmd_type;
static bool reparse_flg;

static void set_color()
{
   term_brd_pnt->set_fg   (stt_fg | (stt_bri ? 0x08 : 0));
   term_brd_pnt->set_bg   (stt_bg | (stt_bnk ? 0x08 : 0));
}

inline bool is_param_stack_full()
{
   return param_cnt == mac_cnt_of(param_stack_int_ary);
}

void new_param()
{
   mac_assert(!is_param_stack_full());
   param_stack_int_ary[param_cnt++] = 0;
}

void update_param(char ch)
{
   mac_assert(is_inside(ch, '0', '9'));
   param_stack_int_ary[param_cnt-1] *= 10;
   param_stack_int_ary[param_cnt-1] += ch - '0';
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline bool is_es_buf_full()
{
   return es_cnt == mac_cnt_of(es_buf_ach);
}

void append_to_es_buf(char ch)
{
   mac_assert(!is_es_buf_full());
   es_buf_ach[es_cnt++] = ch;
}

void flush_es_buf()
{
   if (show_unknown_esc_seq_flg) term_write_scn(es_buf_ach,es_cnt);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline bool is_parsing()
{
   return parseing_es_flg;
}

void begin_parsing()
{
   parseing_es_flg = def_yes;
   es_state_int = 0;
   param_cnt = 0;
   es_cnt = 0;
   append_to_es_buf(def_c8_esc);
}

inline void end_parsing()
{
   parseing_es_flg = def_no;
}

void parsing_failed()
{
   parseing_es_flg = def_no;
   flush_es_buf();
}

void save_attr()
{
   prev_x    = term_brd_pnt->get_x();
   prev_y    = term_brd_pnt->get_y();
   prev_attr = term_brd_pnt->get_attr();
   prev_fg   = stt_fg;
   prev_bg   = stt_bg;
   prev_bri  = stt_bri;
   prev_bnk  = stt_bnk;
}

void restore_attr()
{
   term_brd_pnt->set_xy(prev_x, prev_y);
   term_brd_pnt->set_attr (prev_attr);
   stt_fg = prev_fg;
   stt_bg = prev_bg;
   stt_bri = prev_bri;
   stt_bnk = prev_bnk;
   set_color();
}

bool parse_cmd_esc(byte ch)
{
   bool done_flg = def_yes;

   switch (ch)
   {
      case '7':   save_attr();
                  break;

      case '8':   restore_attr();
                  break;

      default :   done_flg = def_no;
   }

   return done_flg;
}

bool parse_cmd_bracket(byte ch)
{
   bool done_flg = def_yes;
   int p1 = param_cnt > 0 ? param_stack_int_ary[0] : 0;
   int p2 = param_cnt > 1 ? param_stack_int_ary[1] : 0;
   int i;

   switch (ch)
   {
      case '@' :  if (!p1) p1 = 1;
                  term_brd_pnt->insert_char(p1);
                  break;

      case 'A' :  if (!p1) p1 = 1;
                  term_brd_pnt->set_y_rel(-p1);
                  break;

      case 'B' :  if (!p1) p1 = 1;
                  term_brd_pnt->set_y_rel(p1);
                  break;

      case 'C' :  if (!p1) p1 = 1;
                  term_brd_pnt->set_x_rel(p1);
                  break;

      case 'D' :  if (!p1) p1 = 1;
                  term_brd_pnt->set_x_rel(-p1);
                  break;

      case 'H' :  if (receive_txt_flg) rcv_txt_newline();
                  if (p1) p1--;
                  if (p2) p2--;
                  term_brd_pnt->set_xy(p2, p1);
                  break;

      case 'J' :  if (p1 == 0) term_brd_pnt->erase_to_eos();
                  ef (p1 == 1)
                  {
                     term_brd_pnt->write_space(1);
                     term_brd_pnt->set_x_rel(-1);
                     term_brd_pnt->erase_to_bos();
                  }
                  ef (p1 == 2) term_brd_pnt->erase();
                  else done_flg = def_no;
                  break;

      case 'K' :  if (p1 == 0) term_brd_pnt->erase_to_eol();
                  ef (p1 == 1)
                  {
                     term_brd_pnt->write_space(1);
                     term_brd_pnt->set_x_rel(-1);
                     term_brd_pnt->erase_to_bol();
                  }
                  ef (p1 == 2) term_brd_pnt->erase_line();
                  else done_flg = def_no;
                  break;

      case 'L' :  if (!p1) p1 = 1;
                  term_brd_pnt->insert_line(p1);
                  break;

      case 'M' :  if (!p1) p1 = 1;
                  term_brd_pnt->remove_line(p1);
                  break;

      case 'P' :  if (!p1) p1 = 1;
                  term_brd_pnt->remove_char(p1);
                  break;

      case 'X' :  if (!p1) p1 = 1;
                  {
                     int x = term_brd_pnt->get_x();
                     int y = term_brd_pnt->get_y();
                     term_brd_pnt->write_space(p1);
                     term_brd_pnt->set_x(x);
                     term_brd_pnt->set_y(y);
                  }
                  break;

      case 'f' :  if (receive_txt_flg) rcv_txt_newline();
                  if (p1) p1--;
                  if (p2) p2--;
                  term_brd_pnt->set_xy(p2, p1);
                  break;

      case 'm' :  if (!param_cnt)
                  {
                     param_cnt = 1;
                     param_stack_int_ary[0] = 0;
                  }
                  forcnt (i, param_cnt)
                  {
                     switch (param_stack_int_ary[i])
                     {
                        case 0 : term_brd_pnt->set_normal();
                                 stt_fg  = def_clr_pale_gray;
                                 stt_bg  = def_clr_black;
                                 stt_bri = 0;
                                 stt_bnk = 0;
                                 set_color();
                                 break;

                        case 1 : stt_bri = def_yes;
                                 set_color();
                                 break;

                        case 2 : stt_bri = def_no;
                                 set_color();
                                 break;

                        case 4 : term_brd_pnt->set_underline(def_yes);
                                 break;

                        case 5 : stt_bnk = def_yes;
                                 set_color();
                                 break;

                        case 7 : term_brd_pnt->set_inverse(def_yes);
                                 break;

                        case 8 : stt_fg  = stt_bg;
                                 stt_bri = stt_bnk;
                                 set_color();
                                 break;

                        case 22: stt_bri = def_no;
                                 set_color();
                                 break;

                        case 24: term_brd_pnt->set_underline(def_no);
                                 break;

                        case 25: stt_bnk = def_no;
                                 set_color();
                                 break;

                        case 27: term_brd_pnt->set_inverse(def_no);
                                 break;

                        case 30: stt_fg = def_clr_black;
                                 set_color();
                                 break;

                        case 31: stt_fg = def_clr_dark_red;
                                 set_color();
                                 break;

                        case 32: stt_fg = def_clr_dark_green;
                                 set_color();
                                 break;

                        case 33: stt_fg = def_clr_brown;
                                 set_color();
                                 break;

                        case 34: stt_fg = def_clr_dark_blue;
                                 set_color();
                                 break;

                        case 35: stt_fg = def_clr_dark_pink;
                                 set_color();
                                 break;

                        case 36: stt_fg = def_clr_dark_cyan;
                                 set_color();
                                 break;

                        case 37: stt_fg = def_clr_pale_gray;
                                 set_color();
                                 break;

                        case 40: stt_bg = def_clr_black;
                                 set_color();
                                 break;

                        case 41: stt_bg = def_clr_dark_red;
                                 set_color();
                                 break;

                        case 42: stt_bg = def_clr_dark_green;
                                 set_color();
                                 break;

                        case 43: stt_bg = def_clr_brown;
                                 set_color();
                                 break;

                        case 44: stt_bg = def_clr_dark_blue;
                                 set_color();
                                 break;

                        case 45: stt_bg = def_clr_dark_pink;
                                 set_color();
                                 break;

                        case 46: stt_bg = def_clr_dark_cyan;
                                 set_color();
                                 break;

                        case 47: stt_bg = def_clr_pale_gray;
                                 set_color();
                                 break;

                        default: done_flg = def_no;
                     }
                  }
                  break;

      case 'r' :  if (param_cnt==0)
                  {
                     set_scroll_region_flg = def_no;
                  }
                  else
                  {
                     if (param_cnt == 1) p2 = term_brd_pnt->get_height();
                     if (p1 < p2 && p1 > 0)
                     {
                        scroll_top = p1 - 1;
                        scroll_bot = p2 - 1;
                        set_scroll_region_flg = def_yes;
                     }
                  }
                  break;

      case 's':   save_attr();
                  break;

      case 'u':   restore_attr();
                  break;

      default :   done_flg = def_no;
   }

   return done_flg;
}

bool parse_cmd_equal(byte ch)
{
   bool done_flg = def_yes;
   int p1 = param_cnt > 0 ? param_stack_int_ary[0] : 0;

   switch (ch)
   {
      case 'F' :  if (!param_cnt) p1 = def_clr_pale_gray;
                  stt_fg = p1;
                  set_color();
                  break;

      case 'G' :  if (!param_cnt) p1 = def_clr_black;
                  stt_bg = p1;
                  set_color();
                  break;

      default :   done_flg = def_no;
   }

   return done_flg;
}

void parse_cmd(byte ch)
{
   bool done_flg;

   switch (cmd_type)
   {
      case def_cmd_esc:
         done_flg = parse_cmd_esc(ch);
         break;

      case def_cmd_bracket:
         done_flg = parse_cmd_bracket(ch);
         break;

      case def_cmd_equal:
         done_flg = parse_cmd_equal(ch);
         break;

      case def_cmd_amp:
         done_flg = def_no;
         break;

      default:
         done_flg = def_no;
   }

   if (done_flg) end_parsing();
   else parsing_failed();
}

void parse_head(byte ch)
{
   if (es_cnt == 2)
   {
      switch (ch)
      {
         case '[':   break;

         default:    cmd_type = def_cmd_esc;
                     parse_cmd(ch);
                     break;
      }
   }
   ef (es_cnt == 3)
   {
      es_state_int++;
      switch (ch)
      {
         case '=':   cmd_type = def_cmd_equal;
                     break;

         case '&':   cmd_type = def_cmd_amp;
                     es_state_int++;
                     break;

         default:    cmd_type = def_cmd_bracket;
                     reparse_flg = def_yes;
                     break;
      }
   }
   else mac_halt();
}

void parse_digit(byte ch)
{
   static bool begin_flg = def_yes;

   if (isdigit(ch))
   {
      if (begin_flg)
      {
         if (is_param_stack_full()) parsing_failed();
         else new_param();
         begin_flg = def_no;
      }
      update_param(ch);
   }
   ef (ch == ';')
   {
      begin_flg= def_yes;
   }
   else
   {
      begin_flg= def_yes;
      reparse_flg = def_yes;
      es_state_int++;
   }
}

void cont_parsing(byte ch)
{
   if (is_es_buf_full()) parsing_failed();
   else
   {
      append_to_es_buf(ch);
      do
      {
         reparse_flg = def_no;
         switch (es_state_int)
         {
            case 0 : parse_head(ch);
                     break;

            case 1 : parse_digit(ch);
                     break;

            case 2 : parse_cmd(ch);
         }
      } while (reparse_flg);
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void line_feed()
{
   if (set_scroll_region_flg && term_brd_pnt->get_y() == scroll_bot)
   {
      term_brd_pnt->scroll_up(0, scroll_top, term_brd_pnt->get_width(), scroll_bot - scroll_top + 1);
   }
   else
   {
      if (term_brd_pnt->get_y() == term_brd_pnt->get_height() - 1) term_brd_pnt->scroll_up();
      else term_brd_pnt->set_y_rel(1);
   }
}

void carriage_return()
{
   term_brd_pnt->set_x(0);
}

void new_line()
{
   line_feed();
   carriage_return();
}

void backspace()
{
   if (term_brd_pnt->get_x() > 0) term_brd_pnt->set_x_rel(-1);
}

void form_feed()
{
   term_brd_pnt->erase();
}

void htab()
{
   term_brd_pnt->write_space (8 - term_brd_pnt->get_x()%8);
   if (term_brd_pnt->get_x() >= term_brd_pnt->get_width()) new_line();
}

void parse_ctrl_code (byte ch)
{
   if (receive_txt_flg && ch != def_c8_esc) rcv_txt_loop(ch);

   switch (ch)
   {
      case def_c8_bel : beep();
                        break;

      case def_c8_bs:   backspace();
                        break;

      case def_c8_ht:   htab();
                        break;

      case def_c8_lf:   line_feed();
                        break;

      case def_c8_ff:   form_feed();
                        break;

      case def_c8_cr:   carriage_return();
                        break;

      case def_c8_esc:  begin_parsing();
                        break;
   }
}

void term_write_scn(char16 ch)
{
   int width = term_brd_pnt->get_width();

   if (receive_txt_flg) rcv_txt_loop(ch);

   if (term_brd_pnt->get_x() == width - 1 && get_c16_width (ch) == 2) new_line();
   term_brd_pnt->write(ch);
   if (term_brd_pnt->get_x() >= width) new_line();
}

void term_write_scn(char* p, int cnt)
{
   char* end_pch = p + cnt;
   while (p < end_pch) term_write_scn (read_c16(&p));
}

void term_write(byte ch)
{
   static byte prev_byte;
   char16 c16 = 0;

   if (is_parsing())
   {
      cont_parsing(ch);
   }
   ef (is_inside_less(ch, 0, 0x20))
   {
      parse_ctrl_code(ch);
      prev_byte = 0;
   }
   ef (prev_byte)
   {
      c16 = make_u16(prev_byte, ch);
      if (host_code_int == def_ct_wansung) c16 = get_johab(c16);
      prev_byte = 0;
   }
   ef (is_double(ch))
   {
      prev_byte = ch;
   }
   else
   {
      c16 = ch;
   }

   if (c16) term_write_scn(c16);
}

void term_write(byte* p)
{
   while (*p) term_write (*p++);
}

void term_write(byte* p, int cnt)
{
   while (cnt--) term_write (*p++);
}
