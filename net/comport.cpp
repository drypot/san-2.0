                                                                                                                        /*
--------------------------------------------------------------------------------
   net/comport.cpp
   copyright(C) kyuhyun park
   1995.11.19
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#include <net/comport.hpp>

cls_com_port::cls_com_port(int arg_int_size_buf) :
   bool_opened(def_no),
   int_size_buf(arg_int_size_buf),
   array_byte_buf(arg_int_size_buf)
{
   pnt_byte_rd_pnt = pnt_byte_end_pnt = array_byte_buf.get_base();
}

cls_com_port::~cls_com_port()
{
   close();
}

void cls_com_port::open(int n)
{
   mac_assert(is_inside(n,1,4));
   mac_assert(!bool_opened);

   static char dev_name[] = "COMX";

   APIRET rc;
   ULONG  ul_action_taken;

   dev_name[3] = '0' + n;
   rc = DosOpen(dev_name,
                &hfile,
                &ul_action_taken,
                0,
                FILE_NORMAL,
                FILE_OPEN,
                OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                NULL);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::open\n");

   DCBINFO dcb_info;

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_GETDCBINFO,
                     NULL, 0, NULL,
                     &dcb_info, sizeof(dcb_info), NULL);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::open (GETDCBINFO)\n");

   dcb_info.fbCtlHndShake = MODE_DTR_CONTROL | MODE_CTS_HANDSHAKE;
   dcb_info.fbFlowReplace = MODE_RTS_CONTROL ;
   dcb_info.fbTimeout     = MODE_NO_WRITE_TIMEOUT | MODE_NOWAIT_READ_TIMEOUT;

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_SETDCBINFO,
                     &dcb_info, sizeof(dcb_info), NULL,
                     NULL, 0, NULL);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::open (SETDCBINFO)\n");

   bool_opened = def_yes;
}

void cls_com_port::close()
{
   if (bool_opened) DosClose(hfile);
}

void cls_com_port::set_bit_rate(int n)
{
   APIRET rc;
   USHORT us_bps = n;

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_SETBAUDRATE,
                     &us_bps, sizeof(us_bps), NULL,
                     NULL, 0, NULL);

   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::set_BitRate\n");
}

void cls_com_port::set_line_ctrl(int data_bits, int parity, int stop_bits)
{
   APIRET rc;
   LINECONTROL line_ctrl = {data_bits, parity, stop_bits, 0};

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_SETLINECTRL,
                     &line_ctrl, sizeof(line_ctrl), NULL,
                     NULL, 0, NULL);

   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::set_line_ctrl\n");
}

byte cls_com_port::get_output_state()
{
   APIRET rc;
   BYTE ret_val;

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_GETMODEMOUTPUT,
                     NULL, 0, NULL,
                     &ret_val, sizeof(ret_val), NULL);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::get_output_state\n");
   return ret_val;
}

byte cls_com_port::get_input_state()
{
   APIRET rc;
   BYTE ret_val;

   rc = DosDevIOCtl (hfile, IOCTL_ASYNC, ASYNC_GETMODEMINPUT,
                     NULL, 0, NULL,
                     &ret_val, sizeof(ret_val), NULL);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::get_input_state\n");
   return ret_val;
}

void cls_com_port::fill_buf()
{
   mac_assert (pnt_byte_rd_pnt == pnt_byte_end_pnt);

   ULONG  ulong_bytes_read;
   APIRET rc;

   pnt_byte_rd_pnt  = array_byte_buf.get_base();
   rc = DosRead (hfile, pnt_byte_rd_pnt, int_size_buf, &ulong_bytes_read);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::read\n");
   pnt_byte_end_pnt = pnt_byte_rd_pnt + ulong_bytes_read;
}

void cls_com_port::put_byte (uint8 val)
{
   ULONG  ul_bytes_written;
   APIRET rc;

   rc = DosWrite (hfile, &val, 1, &ul_bytes_written);
   if (rc != 0) throw cls_xmsg_com_port("func: net/comport.cpp/com_port::put_byte\n");
}

