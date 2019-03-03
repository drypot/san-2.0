                                                                                                                        /*
--------------------------------------------------------------------------------
   text/sline.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <text/glb.hpp>

#define def_gap_size 2

#define def_row_digit_size 5
#define def_col_digit_size 4

#define def_mcp_info_size 6 //MCPAGE_NAME_SIZE
#define def_row_info_size (2+def_row_digit_size)
#define def_col_info_size (2+def_col_digit_size)

#define def_insert "I"
#define def_smart_tab "S"
#define def_indent "I"
#define def_unindent "U"

static bool invalid_flg;

static void sline_write_switch_info(bool f, char* lamp)
{
   if (f) sline->write(lamp);
   else sline->write_space(strlen(lamp));
   //sline->write_space(def_gap_size);
}

static void sline_write_string (char* str, int width)
{
   int l = strlen(str);
   if (l > width)
   {
      sline->write_space(width);
   }
   else
   {
      sline->write(str);
      sline->write_space(width - l);
   }
   sline->write_space(def_gap_size);
}

static void sline_write_long(char* pre, char*, long val, int width)
{
   char buf[64];

   int pre_len;
   int len;

   pre_len = strlen(pre);
   if (pre_len)
   {
      sprintf(buf,"%s %ld", pre, val);
   }
   else
   {
      sprintf(buf,"%ld", val);
   }
   len = strlen(buf);

   if (len <= width + pre_len)
   {
      str_expand(buf, width + pre_len);
   }
   else
   {
      char* p = buf + pre_len;
      char* p_end = p + width;
      while (p<p_end) *(p++) = '-';
      *p = 0;
   }

   sline->write(buf);
   sline->write_space(def_gap_size);
}

static void sline_write_fname()
{
   if (!cdoc->fname.is_null())
   {
      int avail;
      char* str = cdoc->fname.get_path();
      size_t len = strlen(str);

      avail = get_min(sline->get_width() - sline->get_x(), len);
      if (avail > 0) sline->write(str + len - avail);
   }
}

void sline_update()
{
   sline->set_x(0);

   if (invalid_flg)
   {
      sline_write_string(mcp_list_iter->get_mcp()->get_name(), def_mcp_info_size);
   }
   else
   {
      sline->set_x_rel(def_mcp_info_size + def_gap_size);
   }

   sline_write_long("L ", "", cdoc->iter.get_y() + 1, def_row_digit_size);
   sline_write_long("C ", "", cdoc->iter.get_vx() + 1, def_col_digit_size);

   if (invalid_flg)
   {
      sline_write_switch_info(insert_flg, def_insert);
      sline_write_switch_info(smart_tab_flg, def_smart_tab);
      sline_write_switch_info(indent_flg, def_indent);
      sline_write_switch_info(unindent_flg, def_unindent);
      sline->write_space(def_gap_size);

      switch (cdoc->code_type)
      {
         case def_ct_johab   : sline->write("¹¡Ðs"); break;
         case def_ct_wansung : sline->write("µÅ¬÷"); break;
      }
      sline->write_space(def_gap_size);

      if (cdoc->modified_flg) sline->write("*");
      else sline->write_space(1);

      sline_write_fname();

      sline->erase_to_eol();
      invalid_flg = def_no;
   }
}

void sline_invalidate()
{
   invalid_flg = def_yes;
}

void sline_draw(HPS hps)
{
   sline->draw(hps, 0, 16);
}

void sline_draw()
{
   HPS hps = WinGetPS(client_hwnd);
   sline_draw(hps);
   WinReleasePS(hps);
}

