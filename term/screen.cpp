                                                                                                                        /*
--------------------------------------------------------------------------------
   term/screen.cpp
   copyright(C) kyuhyun park
   1995.11.14
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <term/glb.hpp>

void draw_state_brd()
{
   stat_brd_pnt->set_fg(def_clr_pale_gray);

   stat_brd_pnt->set_x(0);
   stat_brd_pnt->write(mcp_list_iter.get_mcp()->get_name());

   stat_brd_pnt->set_x(8);

   stat_brd_pnt->write(host_code_int == def_ct_johab ? "¹¡Ðs" : "µÅ¬÷");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->write(local_code_int == def_ct_johab ? "¹¡Ðs" : "µÅ¬÷");
   stat_brd_pnt->set_x_rel(4);


   stat_brd_pnt->set_fg(dtr_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("DTR");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(rts_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("RTS");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(dsr_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("DSR");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(cts_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("CTS");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(dcd_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("DCD");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(ri_flg  ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("RI");
   stat_brd_pnt->set_x_rel(4);


   stat_brd_pnt->set_fg(send_txt_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("ST");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(send_zmd_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("SZ");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(receive_zmd_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("RZ");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(receive_txt_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("LT");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->set_fg(receive_bin_flg ? def_clr_pale_gray : def_clr_black);
   stat_brd_pnt->write("LP");
   stat_brd_pnt->set_x_rel(2);

   stat_brd_pnt->erase_to_eol();
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void draw_term()
{
   HPS hps = WinGetPS(client_hwnd);
   term_brd_pnt->draw(hps, 0, 16*2);
   WinReleasePS(hps);
}

void draw_chat()
{
   HPS hps = WinGetPS(client_hwnd);
   char_brd_pnt->draw(hps, 0, 16*1);
   WinReleasePS(hps);
}

void draw_state()
{
   HPS hps = WinGetPS(client_hwnd);
   stat_brd_pnt->draw(hps, 0, 16*0);
   WinReleasePS(hps);
}

void draw_client(HPS hps)
{
   term_brd_pnt ->draw(hps, 0, 16*2);
   char_brd_pnt ->draw(hps, 0, 16*1);
   stat_brd_pnt->draw(hps, 0, 16*0);
}

void draw_client()
{
   HPS hps = WinGetPS(client_hwnd);
   draw_client(hps);
   WinReleasePS(hps);
}

void invalidate_client()
{
   term_brd_pnt ->invalidate();
   char_brd_pnt ->invalidate();
   stat_brd_pnt->invalidate();
}

void update_state()
{
   draw_state_brd();
   draw_state();
}
