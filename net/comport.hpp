                                                                                                                        /*
--------------------------------------------------------------------------------
   net/comport.hpp
   copyright(C) kyuhyun park
   1995.11.19
--------------------------------------------------------------------------------                                        */

#ifdef def_net_comport_hpp
#error 'net/comport.hpp' duplicated.
#endif

#define def_net_comport_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif

#ifndef def_pub_char_hpp
#include <pub/char.hpp>
#endif

#ifndef def_cnt_array_hpp
#include <cnt/array.hpp>
#endif

mac_define_xmsg1(com_port);

enum
{
   def_cp_no_parity,
   def_cp_odd_parity,
   def_cp_even_parity,
   def_cp_mark_parity,
   def_cp_space_parity
};

enum
{
   def_cp_stop_bit1,
   def_cp_stop_bit15,
   def_cp_stop_bit2
};

enum
{
   def_cp_dtr = 0x01,
   def_cp_rts = 0x02,

   def_cp_cts = 0x10,
   def_cp_dsr = 0x20,
   def_cp_ri  = 0x40,
   def_cp_dcd = 0x80
};

class cls_com_port
{
   private:
      bool  bool_opened;
      HFILE hfile;
      int   int_size_buf;
      tem_array<byte> array_byte_buf;
      byte* pnt_byte_rd_pnt;
      byte* pnt_byte_end_pnt;

   public:

      cls_com_port   (int = 512);
     ~cls_com_port   ();

      void open      (int);
      void close     ();

      void set_bit_rate (int);
      void set_line_ctrl (int data_bits, int parity, int stop_bits);

      byte get_output_state();
      byte get_input_state();

      bool is_readable ();

      byte get_byte ();
      void put_byte (byte);

   private:

      void fill_buf ();
};

inline bool cls_com_port::is_readable()
{
   if (pnt_byte_rd_pnt == pnt_byte_end_pnt) fill_buf();
   return pnt_byte_rd_pnt < pnt_byte_end_pnt;
}

inline uint8 cls_com_port::get_byte()
{
   mac_assert (pnt_byte_rd_pnt < pnt_byte_end_pnt);
   return *pnt_byte_rd_pnt++;
}
