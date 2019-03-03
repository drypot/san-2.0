                                                                                                                        /*
--------------------------------------------------------------------------------
   term/port.cpp
   copyright(C) kyuhyun park
   1995.12.14
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop


#include <term/glb.hpp>

cls_com_port com_port;

void port_open()
{
   if (com_port_auto_detect_flg)
   {
      com_port_num_int = 1;
      while (com_port_num_int <= 4)
      {
         try
         {
            com_port.open (com_port_num_int);
            break;
         }
         catch (...)
         {
            com_port_num_int++;
         }
      }
      if (com_port_num_int == 5)
      {
         throw cls_xmsg ("func: term/port.cpp/port_open\ninfo: com port auto detection failed\n");
      }
   }
   else
   {
      com_port.open (com_port_num_int);
   }

   com_port.set_bit_rate  (38400);
   com_port.set_line_ctrl (8, def_cp_no_parity, def_cp_stop_bit1);

   port_check_state();
   if (!dcd_flg)
   {
      port_write_str (modem_init_str_pch);
      port_write ((byte)'\r');
   }
}

byte port_read()
{
   byte ch = com_port.get_byte();
   if (receive_bin_flg) rcv_bin_loop(ch);
   return ch;
}

void port_write_str(char* p)
{
   while (*p) port_write((byte)*p++);
}

bool port_check_state()
{
   bool changed = def_no;
   byte output_state = com_port.get_output_state();
   byte input_state  = com_port.get_input_state();

   if (dtr_flg != (output_state & def_cp_dtr))
   {
      dtr_flg = output_state & def_cp_dtr;
      changed = def_yes;
   }

   if (rts_flg != (output_state & def_cp_rts))
   {
      rts_flg = output_state & def_cp_rts;
      changed = def_yes;
   }

   if (cts_flg != (input_state & def_cp_cts))
   {
      cts_flg = input_state & def_cp_cts;
      changed = def_yes;
   }

   if (dsr_flg != (input_state & def_cp_dsr))
   {
      dsr_flg = input_state & def_cp_dsr;
      changed = def_yes;
   }

   if (ri_flg != (input_state & def_cp_ri))
   {
      ri_flg = input_state & def_cp_ri;
      changed = def_yes;
   }

   if (dcd_flg != (input_state & def_cp_dcd))
   {
      dcd_flg = input_state & def_cp_dcd;
      changed = def_yes;
   }

   return changed;
}
