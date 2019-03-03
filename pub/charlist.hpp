                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/charlist.hpp
   copyright(c) kyuhyun park
   1990.11.04
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_charlist_hpp
#error 'pub/charlist.hpp' duplicated.
#endif

#define def_pub_charlist_hpp
                                                                                                                        /*
--------------------------------------------------------------------------------

   Ðe‹i ¸a­¡

   Á¡¬÷      ˆAŒAA”A˜AœA A¤A¨A¬A°A´A¸A¼AÀAÄAÈAÌAÐA
   º—¬÷     „a„„¡„Á„á…A…a……¡…Á…á†A†a††¡†Á†á‡A‡a‡‡¡
   ¹·¬÷      „B„C„D„E„F„G„H„I„J„K„L„M„N„O„P„Q„S„T„U„V„W„X„Y„Z„[„\„]

--------------------------------------------------------------------------------                                        */
                                                                                                                        /*
--------------------------------------------------------------------------------
   Á¡¬÷                                                  ¬w¶w ¹¡Ðs Ðe‹i ¸a­¡
--------------------------------------------------------------------------------                                        */

                                              //  00  00000
#define def_h1_fill                   0x01    //  01  00001                À¶‘
#define def_h1_g                      0x02    //  02  00010                [ˆA ]
#define def_h1_gg                     0x03    //  03  00011                [ŒA ]
#define def_h1_n                      0x04    //  04  00100                [A ]
#define def_h1_d                      0x05    //  05  00101                [”A ]
#define def_h1_dd                     0x06    //  06  00110                [˜A ]
#define def_h1_r                      0x07    //  07  00111                [œA ]
#define def_h1_m                      0x08    //  08  01000                [ A ]
#define def_h1_b                      0x09    //  09  01001                [¤A ]
#define def_h1_bb                     0x0a    //  10  01010                [¨A ]
#define def_h1_s                      0x0b    //  11  01011                [¬A ]
#define def_h1_ss                     0x0c    //  12  01100                [°A ]
#define def_h1_y                      0x0d    //  13  01101                [´A ]
#define def_h1_j                      0x0e    //  14  01110                [¸A ]
#define def_h1_jj                     0x0f    //  15  01111                [¼A ]
#define def_h1_c                      0x10    //  16  10000                [ÀA ]
#define def_h1_k                      0x11    //  17  10001                [ÄA ]
#define def_h1_t                      0x12    //  18  10010                [ÈA ]
#define def_h1_p                      0x13    //  19  10011                [ÌA ]
#define def_h1_h                      0x14    //  20  10100                [ÐA ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   º—¬÷                                                  ¬w¶w ¹¡Ðs Ðe‹i ¸a­¡
--------------------------------------------------------------------------------                                        */

                                              //  00  00000
                                              //  01  00001
#define def_h2_fill                   0x02    //  02  00010                À¶‘
#define def_h2_ia                     0x03    //  03  00011                [„a ]
#define def_h2_iai                    0x04    //  04  00100                [„ ]
#define def_h2_iaa                    0x05    //  05  00101                [„¡ ]
#define def_h2_iaai                   0x06    //  06  00110                [„Á ]
#define def_h2_ai                     0x07    //  07  00111                [„á ]
                                              //  08  01000
                                              //  09  01001
#define def_h2_aii                    0x0a    //  10  01010                […A ]
#define def_h2_aai                    0x0b    //  11  01011                […a ]
#define def_h2_aaii                   0x0c    //  12  01100                [… ]
#define def_h2_au                     0x0d    //  13  01101                […¡ ]
#define def_h2_auia                   0x0e    //  14  01110                […Á ]
#define def_h2_auiai                  0x0f    //  15  01111                […á ]
                                              //  16  10000
                                              //  17  10001
#define def_h2_aui                    0x12    //  18  10010                [†A ]
#define def_h2_aau                    0x13    //  19  10011                [†a ]
#define def_h2_ua                     0x14    //  20  10100                [† ]
#define def_h2_uaai                   0x15    //  21  10101                [†¡ ]
#define def_h2_uaaii                  0x16    //  22  10110                [†Á ]
#define def_h2_uai                    0x17    //  23  10111                [†á ]
                                              //  24  11000
                                              //  25  11001
#define def_h2_uaa                    0x1a    //  26  11010                [‡A ]
#define def_h2_u                      0x1b    //  27  11011                [‡a ]
#define def_h2_ui                     0x1c    //  28  11100                [‡ ]
#define def_h2_i                      0x1d    //  29  11101                [‡¡ ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   ¹·¬÷                                                  ¬w¶w ¹¡Ðs Ðe‹i ¸a­¡
--------------------------------------------------------------------------------                                        */

                                              //  00  00000
#define def_h3_fill                   0x01    //  01  00001                À¶‘
#define def_h3_g                      0x02    //  02  00010                [„B ]
#define def_h3_gg                     0x03    //  03  00011                [„C ]
#define def_h3_gs                     0x04    //  04  00100                [„D ]
#define def_h3_n                      0x05    //  05  00101                [„E ]
#define def_h3_nj                     0x06    //  06  00110                [„F ]
#define def_h3_nh                     0x07    //  07  00111                [„G ]
#define def_h3_d                      0x08    //  08  01000                [„H ]
#define def_h3_r                      0x09    //  09  01001                [„I ]
#define def_h3_rg                     0x0a    //  10  01010                [„J ]
#define def_h3_rm                     0x0b    //  11  01011                [„K ]
#define def_h3_rb                     0x0c    //  12  01100                [„L ]
#define def_h3_rs                     0x0d    //  13  01101                [„M ]
#define def_h3_rp                     0x0e    //  14  01110                [„O ]
#define def_h3_rt                     0x0f    //  15  01111                [„N ]
#define def_h3_rh                     0x10    //  16  10000                [„P ]
#define def_h3_m                      0x11    //  17  10001                [„Q ]
                                              //  18  10010
#define def_h3_b                      0x13    //  19  10011                [„S ]
#define def_h3_bs                     0x14    //  20  10100                [„T ]
#define def_h3_s                      0x15    //  21  10101                [„U ]
#define def_h3_ss                     0x16    //  22  10110                [„V ]
#define def_h3_y                      0x17    //  23  10111                [„W ]
#define def_h3_j                      0x18    //  24  11000                [„X ]
#define def_h3_c                      0x19    //  25  11001                [„Y ]
#define def_h3_k                      0x1a    //  26  11010                [„Z ]
#define def_h3_t                      0x1b    //  27  11011                [„[ ]
#define def_h3_p                      0x1c    //  28  11100                [„\ ]
#define def_h3_h                      0x1d    //  29  11101                [„] ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   control characters                                            ascii table
--------------------------------------------------------------------------------                                        */

#define def_c8_nul                    0x00    //  000  null character
#define def_c8_soh                    0x01    //  001  start of header
#define def_c8_stx                    0x02    //  002  start of text
#define def_c8_etx                    0x03    //  003  end of text
#define def_c8_eot                    0x04    //  004  end of transmission
#define def_c8_enq                    0x05    //  005  enquire
#define def_c8_ack                    0x06    //  006  acknowledge
#define def_c8_bel                    0x07    //  007  bell
#define def_c8_bs                     0x08    //  008  backspace
#define def_c8_ht                     0x09    //  009  horizontal tab
#define def_c8_lf                     0x0a    //  010  line feed
#define def_c8_vt                     0x0b    //  011  vertical tab
#define def_c8_ff                     0x0c    //  012  form feed
#define def_c8_cr                     0x0d    //  013  carriage return
#define def_c8_so                     0x0e    //  014  shift out
#define def_c8_si                     0x0f    //  015  shift in
#define def_c8_dle                    0x10    //  016  data link escape
#define def_c8_dc1                    0x11    //  017  device control 1
#define def_c8_dc2                    0x12    //  018  device control 2
#define def_c8_dc3                    0x13    //  019  device control 3
#define def_c8_dc4                    0x14    //  020  device control 4
#define def_c8_nak                    0x15    //  021  negative acknowledge
#define def_c8_syn                    0x16    //  022  synchronize
#define def_c8_etb                    0x17    //  023  end of text block
#define def_c8_can                    0x18    //  024  cancel
#define def_c8_em                     0x19    //  025  end of medium
#define def_c8_sub                    0x1a    //  026  substitute
#define def_c8_esc                    0x1b    //  027  escape
#define def_c8_fs                     0x1c    //  028  file separator
#define def_c8_gs                     0x1d    //  029  group separator
#define def_c8_rs                     0x1e    //  030  record separator
#define def_c8_us                     0x1f    //  031  unit separator
#define def_c8_del                    0x7f    //  127  delete
                                                                                                                        /*
--------------------------------------------------------------------------------
   control characters concerned with keys                        ascii table
--------------------------------------------------------------------------------                                        */

#define def_c8_ctrl_a                 0x01    //  001  SOH
#define def_c8_ctrl_b                 0x02    //  002  STX
#define def_c8_ctrl_c                 0x03    //  003  ETX
#define def_c8_ctrl_d                 0x04    //  004  EOT
#define def_c8_ctrl_e                 0x05    //  005  ENQ
#define def_c8_ctrl_f                 0x06    //  006  ACK
#define def_c8_ctrl_g                 0x07    //  007  BEL
#define def_c8_ctrl_h                 0x08    //  008  BS
#define def_c8_ctrl_i                 0x09    //  009  HT
#define def_c8_ctrl_j                 0x0a    //  010  LF
#define def_c8_ctrl_k                 0x0b    //  011  VT
#define def_c8_ctrl_l                 0x0c    //  012  FF
#define def_c8_ctrl_m                 0x0d    //  013  CR
#define def_c8_ctrl_n                 0x0e    //  014  SO
#define def_c8_ctrl_o                 0x0f    //  015  SI
#define def_c8_ctrl_p                 0x10    //  016  DLE
#define def_c8_ctrl_q                 0x11    //  017  DC1
#define def_c8_ctrl_r                 0x12    //  018  DC2
#define def_c8_ctrl_s                 0x13    //  019  DC3
#define def_c8_ctrl_t                 0x14    //  020  DC4
#define def_c8_ctrl_u                 0x15    //  021  NAK
#define def_c8_ctrl_v                 0x16    //  022  SYN
#define def_c8_ctrl_w                 0x17    //  023  ETB
#define def_c8_ctrl_x                 0x18    //  024  CAN
#define def_c8_ctrl_y                 0x19    //  025  EM
#define def_c8_ctrl_z                 0x1a    //  026  SUB
                                                                                                                        /*
--------------------------------------------------------------------------------
   digit characters                                              ascii table
--------------------------------------------------------------------------------                                        */

#define def_c8_0                      0x30    //  048                      [ 0 ]
#define def_c8_1                      0x31    //  049                      [ 1 ]
#define def_c8_2                      0x32    //  050                      [ 2 ]
#define def_c8_3                      0x33    //  051                      [ 3 ]
#define def_c8_4                      0x34    //  052                      [ 4 ]
#define def_c8_5                      0x35    //  053                      [ 5 ]
#define def_c8_6                      0x36    //  054                      [ 6 ]
#define def_c8_7                      0x37    //  055                      [ 7 ]
#define def_c8_8                      0x38    //  056                      [ 8 ]
#define def_c8_9                      0x39    //  057                      [ 9 ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   control characters concerned with keys                        ascii table
--------------------------------------------------------------------------------                                        */

#define def_c8_A                      0x41    //  065                      [ A ]
#define def_c8_B                      0x42    //  066                      [ B ]
#define def_c8_C                      0x43    //  067                      [ C ]
#define def_c8_D                      0x44    //  068                      [ D ]
#define def_c8_E                      0x45    //  069                      [ E ]
#define def_c8_F                      0x46    //  070                      [ F ]
#define def_c8_G                      0x47    //  071                      [ G ]
#define def_c8_H                      0x48    //  072                      [ H ]
#define def_c8_I                      0x49    //  073                      [ I ]
#define def_c8_J                      0x4a    //  074                      [ J ]
#define def_c8_K                      0x4b    //  075                      [ K ]
#define def_c8_L                      0x4c    //  076                      [ L ]
#define def_c8_M                      0x4d    //  077                      [ M ]
#define def_c8_N                      0x4e    //  078                      [ N ]
#define def_c8_O                      0x4f    //  079                      [ O ]
#define def_c8_P                      0x50    //  080                      [ P ]
#define def_c8_Q                      0x51    //  081                      [ Q ]
#define def_c8_R                      0x52    //  082                      [ R ]
#define def_c8_S                      0x53    //  083                      [ S ]
#define def_c8_T                      0x54    //  084                      [ T ]
#define def_c8_U                      0x55    //  085                      [ U ]
#define def_c8_V                      0x56    //  086                      [ V ]
#define def_c8_W                      0x57    //  087                      [ W ]
#define def_c8_X                      0x58    //  088                      [ X ]
#define def_c8_Y                      0x59    //  089                      [ Y ]
#define def_c8_Z                      0x5a    //  090                      [ Z ]

#define def_c8_a                      0x61    //  097                      [ a ]
#define def_c8_b                      0x62    //  098                      [ b ]
#define def_c8_c                      0x63    //  099                      [ c ]
#define def_c8_d                      0x64    //  100                      [ d ]
#define def_c8_e                      0x65    //  101                      [ e ]
#define def_c8_f                      0x66    //  102                      [ f ]
#define def_c8_g                      0x67    //  103                      [ g ]
#define def_c8_h                      0x68    //  104                      [ h ]
#define def_c8_i                      0x69    //  105                      [ i ]
#define def_c8_j                      0x6a    //  106                      [ j ]
#define def_c8_k                      0x6b    //  107                      [ k ]
#define def_c8_l                      0x6c    //  108                      [ l ]
#define def_c8_m                      0x6d    //  109                      [ m ]
#define def_c8_n                      0x6e    //  110                      [ n ]
#define def_c8_o                      0x6f    //  111                      [ o ]
#define def_c8_p                      0x70    //  112                      [ p ]
#define def_c8_q                      0x71    //  113                      [ q ]
#define def_c8_r                      0x72    //  114                      [ r ]
#define def_c8_s                      0x73    //  115                      [ s ]
#define def_c8_t                      0x74    //  116                      [ t ]
#define def_c8_u                      0x75    //  117                      [ u ]
#define def_c8_v                      0x76    //  118                      [ v ]
#define def_c8_w                      0x77    //  119                      [ w ]
#define def_c8_x                      0x78    //  120                      [ x ]
#define def_c8_y                      0x79    //  121                      [ y ]
#define def_c8_z                      0x7a    //  122                      [ z ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   punctuation characters                                        ascii table
--------------------------------------------------------------------------------                                        */

#define def_c8_space                  0x20    //  032                      [   ]
#define def_c8_exclamation_point      0x21    //  033                      [ ! ]
#define def_c8_quotation_mark         0x22    //  034                      [ " ]
#define def_c8_num                 0x23    //  035                      [ # ]
#define def_c8_dollar                 0x24    //  036                      [ $ ]
#define def_c8_percent                0x25    //  037                      [ % ]
#define def_c8_ampersand              0x26    //  038                      [ & ]
#define def_c8_apostrophe             0x27    //  039                      [ ' ]
#define def_c8_opening_parenthesis    0x28    //  040                      [ ( ]
#define def_c8_closing_parenthesis    0x29    //  041                      [ ) ]
#define def_c8_asterisk               0x2a    //  042                      [ * ]
#define def_c8_plus                   0x2b    //  043                      [ + ]
#define def_c8_comma                  0x2c    //  044                      [ , ]
#define def_c8_minus                  0x2d    //  045 ***                  [ - ]
#define def_c8_hyphen                 0x2d    //  045                      [ - ]
#define def_c8_period                 0x2e    //  046                      [ . ]
#define def_c8_slash                  0x2f    //  047                      [ / ]

                                              //  digit characters gap

#define def_c8_colon                  0x3a    //  058                      [ : ]
#define def_c8_semicolon              0x3b    //  059                      [ ; ]
#define def_c8_less_than              0x3c    //  060                      [ < ]
#define def_c8_equal                  0x3d    //  061                      [ = ]
#define def_c8_greater_than           0x3e    //  062                      [ > ]
#define def_c8_question               0x3f    //  063                      [ ? ]
#define def_c8_at                     0x40    //  064                      [ @ ]

                                              //  upper characters gap

#define def_c8_opening_bracket        0x5b    //  091                      [ [ ]
#define def_c8_backward_slash         0x5c    //  092                      [ \ ]
#define def_c8_closing_bracket        0x5d    //  093                      [ ] ]
#define def_c8_caret                  0x5e    //  094                      [ ^ ]
#define def_c8_circum                 0x5e    //  094 ***                  [ ^ ]
#define def_c8_underscore             0x5f    //  095                      [ _ ]
#define def_c8_grave                  0x60    //  096                      [ ` ]

                                              //  lower characters gap

#define def_c8_opening_brace          0x7b    //  123                      [ { ]
#define def_c8_vertical_line          0x7c    //  124                      [ | ]
#define def_c8_closing_brace          0x7d    //  125                      [ } ]
#define def_c8_tilde                  0x7e    //  126                      [ ~ ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   ¹A´á¢…¸a                                                2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_nul                   0x0000  //  Null
#define def_c16_soh                   0x0001  //  Start of header
#define def_c16_stx                   0x0002  //  Start of text
#define def_c16_etx                   0x0003  //  End of text
#define def_c16_eot                   0x0004  //  End of transmission
#define def_c16_enq                   0x0005  //  Enquiry
#define def_c16_ack                   0x0006  //  Acknowledgement
#define def_c16_bel                   0x0007  //  Bell
#define def_c16_bs                    0x0008  //  Backspace
#define def_c16_ht                    0x0009  //  Horizontal tab
#define def_c16_lf                    0x000a  //  Line feed
#define def_c16_vt                    0x000b  //  Vertical tab
#define def_c16_ff                    0x000c  //  Form feed
#define def_c16_cr                    0x000d  //  Carriage return
#define def_c16_so                    0x000e  //  Shift out
#define def_c16_si                    0x000f  //  Shift in
#define def_c16_dle                   0x0010  //  Data link escape
#define def_c16_dc1                   0x0011  //  Device control 1
#define def_c16_dc2                   0x0012  //  Device control 2
#define def_c16_dc3                   0x0013  //  Device control 3
#define def_c16_dc4                   0x0014  //  Device control 4
#define def_c16_nak                   0x0015  //  Negative acknowledgment
#define def_c16_syn                   0x0016  //  Synchronous idle
#define def_c16_etb                   0x0017  //  End of transmission block
#define def_c16_can                   0x0018  //  Cancel
#define def_c16_em                    0x0019  //  End of medium
#define def_c16_sub                   0x001a  //  Substitute
#define def_c16_esc                   0x001b  //  Escape
#define def_c16_fs                    0x001c  //  File separator
#define def_c16_gs                    0x001d  //  Group separator
#define def_c16_rs                    0x001e  //  Record separator
#define def_c16_us                    0x001f  //  Unit separator
                                                                                                                        /*
--------------------------------------------------------------------------------
   ‹i®A ·³bµA ·Ðe ¹A´á¢…¸a                                  2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_ctrl_2                0x0000

#define def_c16_ctrl_a                0x0001
#define def_c16_ctrl_b                0x0002
#define def_c16_ctrl_c                0x0003
#define def_c16_ctrl_d                0x0004
#define def_c16_ctrl_e                0x0005
#define def_c16_ctrl_f                0x0006
#define def_c16_ctrl_g                0x0007
#define def_c16_ctrl_h                0x0008
#define def_c16_ctrl_i                0x0009
#define def_c16_ctrl_j                0x000a
#define def_c16_ctrl_k                0x000b
#define def_c16_ctrl_l                0x000c
#define def_c16_ctrl_m                0x000d
#define def_c16_ctrl_n                0x000e
#define def_c16_ctrl_o                0x000f
#define def_c16_ctrl_p                0x0010
#define def_c16_ctrl_q                0x0011
#define def_c16_ctrl_r                0x0012
#define def_c16_ctrl_s                0x0013
#define def_c16_ctrl_t                0x0014
#define def_c16_ctrl_u                0x0015
#define def_c16_ctrl_v                0x0016
#define def_c16_ctrl_w                0x0017
#define def_c16_ctrl_x                0x0018
#define def_c16_ctrl_y                0x0019
#define def_c16_ctrl_z                0x001a

#define def_c16_ctrl_opening_bracket  0x001b  //  CTRL-[
#define def_c16_ctrl_backword_slash   0x001c  //  CTRL-\
#define def_c16_ctrl_closing_bracket  0x001d  //  CTRL-]
#define def_c16_ctrl_6                0x001e
#define def_c16_ctrl_minus            0x001f
                                                                                                                        /*
--------------------------------------------------------------------------------
   ®•¸a                                                       2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_0                     0x0030  //                           [ 0 ]
#define def_c16_1                     0x0031  //                           [ 1 ]
#define def_c16_2                     0x0032  //                           [ 2 ]
#define def_c16_3                     0x0033  //                           [ 3 ]
#define def_c16_4                     0x0034  //                           [ 4 ]
#define def_c16_5                     0x0035  //                           [ 5 ]
#define def_c16_6                     0x0036  //                           [ 6 ]
#define def_c16_7                     0x0037  //                           [ 7 ]
#define def_c16_8                     0x0038  //                           [ 8 ]
#define def_c16_9                     0x0039  //                           [ 9 ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   ´iÌa¥u                                                     2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_A                     0x0041  //                           [ A ]
#define def_c16_B                     0x0042  //                           [ B ]
#define def_c16_C                     0x0043  //                           [ C ]
#define def_c16_D                     0x0044  //                           [ D ]
#define def_c16_E                     0x0045  //                           [ E ]
#define def_c16_F                     0x0046  //                           [ F ]
#define def_c16_G                     0x0047  //                           [ G ]
#define def_c16_H                     0x0048  //                           [ H ]
#define def_c16_I                     0x0049  //                           [ I ]
#define def_c16_J                     0x004a  //                           [ J ]
#define def_c16_K                     0x004b  //                           [ K ]
#define def_c16_L                     0x004c  //                           [ L ]
#define def_c16_M                     0x004d  //                           [ M ]
#define def_c16_N                     0x004e  //                           [ N ]
#define def_c16_O                     0x004f  //                           [ O ]
#define def_c16_P                     0x0050  //                           [ P ]
#define def_c16_Q                     0x0051  //                           [ Q ]
#define def_c16_R                     0x0052  //                           [ R ]
#define def_c16_S                     0x0053  //                           [ S ]
#define def_c16_T                     0x0054  //                           [ T ]
#define def_c16_U                     0x0055  //                           [ U ]
#define def_c16_V                     0x0056  //                           [ V ]
#define def_c16_W                     0x0057  //                           [ W ]
#define def_c16_X                     0x0058  //                           [ X ]
#define def_c16_Y                     0x0059  //                           [ Y ]
#define def_c16_Z                     0x005a  //                           [ Z ]

#define def_c16_a                     0x0061  //                           [ a ]
#define def_c16_b                     0x0062  //                           [ b ]
#define def_c16_c                     0x0063  //                           [ c ]
#define def_c16_d                     0x0064  //                           [ d ]
#define def_c16_e                     0x0065  //                           [ e ]
#define def_c16_f                     0x0066  //                           [ f ]
#define def_c16_g                     0x0067  //                           [ g ]
#define def_c16_h                     0x0068  //                           [ h ]
#define def_c16_i                     0x0069  //                           [ i ]
#define def_c16_j                     0x006a  //                           [ j ]
#define def_c16_k                     0x006b  //                           [ k ]
#define def_c16_l                     0x006c  //                           [ l ]
#define def_c16_m                     0x006d  //                           [ m ]
#define def_c16_n                     0x006e  //                           [ n ]
#define def_c16_o                     0x006f  //                           [ o ]
#define def_c16_p                     0x0070  //                           [ p ]
#define def_c16_q                     0x0071  //                           [ q ]
#define def_c16_r                     0x0072  //                           [ r ]
#define def_c16_s                     0x0073  //                           [ s ]
#define def_c16_t                     0x0074  //                           [ t ]
#define def_c16_u                     0x0075  //                           [ u ]
#define def_c16_v                     0x0076  //                           [ v ]
#define def_c16_w                     0x0077  //                           [ w ]
#define def_c16_x                     0x0078  //                           [ x ]
#define def_c16_y                     0x0079  //                           [ y ]
#define def_c16_z                     0x007a  //                           [ z ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   ¡AÈa¢…¸a                                                   2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_space                 0x0020  //                           [   ]
#define def_c16_exclamation_point     0x0021  //                           [ ! ]
#define def_c16_quotation_mark        0x0022  //                           [ " ]
#define def_c16_num_sign           0x0023  //                           [ # ]
#define def_c16_dollor_sign           0x0024  //                           [ $ ]
#define def_c16_percent_sign          0x0025  //                           [ % ]
#define def_c16_ampersand             0x0026  //                           [ & ]
#define def_c16_apostrophe            0x0027  //                           [ ' ]
#define def_c16_opening_parenthesis   0x0028  //                           [ ( ]
#define def_c16_closing_paranthesis   0x0029  //                           [ ) ]
#define def_c16_asterisk              0x002a  //                           [ * ]
#define def_c16_plus_sign             0x002b  //                           [ + ]
#define def_c16_comma                 0x002c  //                           [ , ]
#define def_c16_minus_sign            0x002d  //                           [ - ]
#define def_c16_hyphen                0x002d  //                           [ - ]
#define def_c16_period                0x002e  //                           [ . ]
#define def_c16_slash                 0x002f  //                           [ / ]

                                         //  digit characters gap

#define def_c16_colon                 0x003a  //                           [ : ]
#define def_c16_semicolon             0x003b  //                           [ ; ]
#define def_c16_less_than_sign        0x003c  //                           [ < ]
#define def_c16_equal_sign            0x003d  //                           [ = ]
#define def_c16_greater_than_sign     0x003e  //                           [ > ]
#define def_c16_question_mark         0x003f  //                           [ ? ]
#define def_c16_atsign                0x0040  //                           [ @ ]

                                         //  upper characters gap

#define def_c16_opening_bracket       0x005b  //                           [ [ ]
#define def_c16_backward_slash        0x005c  //                           [ \ ]
#define def_c16_closing_bracket       0x005d  //                           [ ] ]
#define def_c16_caret                 0x005e  //                           [ ^ ]
#define def_c16_circum                0x005e  //                           [ ^ ]
#define def_c16_underscore            0x005f  //                           [ _ ]
#define def_c16_grave                 0x0060  //                           [ ` ]

                                         //  lower characters gap

#define def_c16_opening_brace         0x007b  //                           [ { ]
#define def_c16_vertical_line         0x007c  //                           [ | ]
#define def_c16_closing_brace         0x007d  //                           [ } ]
#define def_c16_tilde                 0x007e  //                           [ ~ ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   Ðe‹i ¸a­¡ ( ‰iÐs¶w)                                        2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_han_sign              0x8000  //  1-xxxxx-xxxxx-xxxxx      [   ]

#define def_c16_h1_fill               0x0400  //  x-00001-xxxxx-xxxxx      [   ]
#define def_c16_h1_g                  0x0800  //  x-00010-xxxxx-xxxxx      [ˆA ]
#define def_c16_h1_gg                 0x0c00  //  x-00011-xxxxx-xxxxx      [ŒA ]
#define def_c16_h1_n                  0x1000  //  x-00100-xxxxx-xxxxx      [A ]
#define def_c16_h1_d                  0x1400  //  x-00101-xxxxx-xxxxx      [”A ]
#define def_c16_h1_dd                 0x1800  //  x-00110-xxxxx-xxxxx      [˜A ]
#define def_c16_h1_r                  0x1c00  //  x-00111-xxxxx-xxxxx      [œA ]
#define def_c16_h1_m                  0x2000  //  x-01000-xxxxx-xxxxx      [ A ]
#define def_c16_h1_b                  0x2400  //  x-01001-xxxxx-xxxxx      [¤A ]
#define def_c16_h1_bb                 0x2800  //  x-01010-xxxxx-xxxxx      [¨A ]
#define def_c16_h1_s                  0x2c00  //  x-01011-xxxxx-xxxxx      [¬A ]
#define def_c16_h1_ss                 0x3000  //  x-01100-xxxxx-xxxxx      [°A ]
#define def_c16_h1_y                  0x3400  //  x-01101-xxxxx-xxxxx      [´A ]
#define def_c16_h1_j                  0x3800  //  x-01110-xxxxx-xxxxx      [¸A ]
#define def_c16_h1_jj                 0x3c00  //  x-01111-xxxxx-xxxxx      [¼A ]
#define def_c16_h1_c                  0x4000  //  x-10000-xxxxx-xxxxx      [ÀA ]
#define def_c16_h1_k                  0x4400  //  x-10001-xxxxx-xxxxx      [ÄA ]
#define def_c16_h1_t                  0x4800  //  x-10010-xxxxx-xxxxx      [ÈA ]
#define def_c16_h1_p                  0x4c00  //  x-10011-xxxxx-xxxxx      [ÌA ]
#define def_c16_h1_h                  0x5000  //  x-10100-xxxxx-xxxxx      [ÐA ]

#define def_c16_h2_fill               0x0040  //  x-xxxxx-00010-xxxxx      [   ]
#define def_c16_h2_ia                 0x0060  //  x-xxxxx-00011-xxxxx      [„a ]
#define def_c16_h2_iai                0x0080  //  x-xxxxx-00100-xxxxx      [„ ]
#define def_c16_h2_iaa                0x00a0  //  x-xxxxx-00101-xxxxx      [„¡ ]
#define def_c16_h2_iaai               0x00c0  //  x-xxxxx-00110-xxxxx      [„Á ]
#define def_c16_h2_ai                 0x00e0  //  x-xxxxx-00111-xxxxx      [„á ]
#define def_c16_h2_aii                0x0140  //  x-xxxxx-01010-xxxxx      […A ]
#define def_c16_h2_aai                0x0160  //  x-xxxxx-01011-xxxxx      […a ]
#define def_c16_h2_aaii               0x0180  //  x-xxxxx-01100-xxxxx      [… ]
#define def_c16_h2_au                 0x01a0  //  x-xxxxx-01101-xxxxx      […¡ ]
#define def_c16_h2_auia               0x01c0  //  x-xxxxx-01110-xxxxx      […Á ]
#define def_c16_h2_auiai              0x01e0  //  x-xxxxx-01111-xxxxx      […á ]
#define def_c16_h2_aui                0x0240  //  x-xxxxx-10010-xxxxx      [†A ]
#define def_c16_h2_aau                0x0260  //  x-xxxxx-10011-xxxxx      [†a ]
#define def_c16_h2_ua                 0x0280  //  x-xxxxx-10100-xxxxx      [† ]
#define def_c16_h2_uaai               0x02a0  //  x-xxxxx-10101-xxxxx      [†¡ ]
#define def_c16_h2_uaaii              0x02c0  //  x-xxxxx-10110-xxxxx      [†Á ]
#define def_c16_h2_uai                0x02e0  //  x-xxxxx-10111-xxxxx      [†á ]
#define def_c16_h2_uaa                0x0340  //  x-xxxxx-11010-xxxxx      [‡A ]
#define def_c16_h2_u                  0x0360  //  x-xxxxx-11011-xxxxx      [‡a ]
#define def_c16_h2_ui                 0x0380  //  x-xxxxx-11100-xxxxx      [‡ ]
#define def_c16_h2_i                  0x03a0  //  x-xxxxx-11101-xxxxx      [‡¡ ]

#define def_c16_h3_fill               0x0001  //  x-xxxxx-xxxxx-00001      [   ]
#define def_c16_h3_g                  0x0002  //  x-xxxxx-xxxxx-00010      [„B ]
#define def_c16_h3_gg                 0x0003  //  x-xxxxx-xxxxx-00011      [„C ]
#define def_c16_h3_gs                 0x0004  //  x-xxxxx-xxxxx-00100      [„D ]
#define def_c16_h3_n                  0x0005  //  x-xxxxx-xxxxx-00101      [„E ]
#define def_c16_h3_nj                 0x0006  //  x-xxxxx-xxxxx-00110      [„F ]
#define def_c16_h3_nh                 0x0007  //  x-xxxxx-xxxxx-00111      [„G ]
#define def_c16_h3_d                  0x0008  //  x-xxxxx-xxxxx-01000      [„H ]
#define def_c16_h3_r                  0x0009  //  x-xxxxx-xxxxx-01001      [„I ]
#define def_c16_h3_rg                 0x000a  //  x-xxxxx-xxxxx-01010      [„J ]
#define def_c16_h3_rm                 0x000b  //  x-xxxxx-xxxxx-01011      [„K ]
#define def_c16_h3_rb                 0x000c  //  x-xxxxx-xxxxx-01100      [„L ]
#define def_c16_h3_rs                 0x000d  //  x-xxxxx-xxxxx-01101      [„M ]
#define def_c16_h3_rt                 0x000e  //  x-xxxxx-xxxxx-01110      [„N ]
#define def_c16_h3_rp                 0x000f  //  x-xxxxx-xxxxx-01111      [„O ]
#define def_c16_h3_rh                 0x0010  //  x-xxxxx-xxxxx-10000      [„P ]
#define def_c16_h3_m                  0x0011  //  x-xxxxx-xxxxx-10001      [„Q ]
#define def_c16_h3_b                  0x0013  //  x-xxxxx-xxxxx-10011      [„S ]
#define def_c16_h3_bs                 0x0014  //  x-xxxxx-xxxxx-10100      [„T ]
#define def_c16_h3_s                  0x0015  //  x-xxxxx-xxxxx-10101      [„U ]
#define def_c16_h3_ss                 0x0016  //  x-xxxxx-xxxxx-10110      [„V ]
#define def_c16_h3_y                  0x0017  //  x-xxxxx-xxxxx-10111      [„W ]
#define def_c16_h3_j                  0x0018  //  x-xxxxx-xxxxx-11000      [„X ]
#define def_c16_h3_c                  0x0019  //  x-xxxxx-xxxxx-11001      [„Y ]
#define def_c16_h3_k                  0x001a  //  x-xxxxx-xxxxx-11010      [„Z ]
#define def_c16_h3_t                  0x001b  //  x-xxxxx-xxxxx-11011      [„[ ]
#define def_c16_h3_p                  0x001c  //  x-xxxxx-xxxxx-11100      [„\ ]
#define def_c16_h3_h                  0x001d  //  x-xxxxx-xxxxx-11101      [„] ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   Ðe‹i ¸a­¡ ( {¸a¶w)                                        2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

                                              //  _C_ : complete

#define def_c16_han_c_fill            0x8441  //  1-00001-00010-00001      [   ]

#define def_c16_h1_c_g                0x8841  //  1-00010-00010-00001      [ˆA ]
#define def_c16_h1_c_gg               0x8c41  //  1-00011-00010-00001      [ŒA ]
#define def_c16_h1_c_n                0x9041  //  1-00100-00010-00001      [A ]
#define def_c16_h1_c_d                0x9441  //  1-00101-00010-00001      [”A ]
#define def_c16_h1_c_dd               0x9841  //  1-00110-00010-00001      [˜A ]
#define def_c16_h1_c_r                0x9c41  //  1-00111-00010-00001      [œA ]
#define def_c16_h1_c_m                0xa041  //  1-01000-00010-00001      [ A ]
#define def_c16_h1_c_b                0xa441  //  1-01001-00010-00001      [¤A ]
#define def_c16_h1_c_bb               0xa841  //  1-01010-00010-00001      [¨A ]
#define def_c16_h1_c_s                0xac41  //  1-01011-00010-00001      [¬A ]
#define def_c16_h1_c_ss               0xb041  //  1-01100-00010-00001      [°A ]
#define def_c16_h1_c_y                0xb441  //  1-01101-00010-00001      [´A ]
#define def_c16_h1_c_j                0xb841  //  1-01110-00010-00001      [¸A ]
#define def_c16_h1_c_jj               0xbc41  //  1-01111-00010-00001      [¼A ]
#define def_c16_h1_c_c                0xc041  //  1-10000-00010-00001      [ÀA ]
#define def_c16_h1_c_k                0xc441  //  1-10001-00010-00001      [ÄA ]
#define def_c16_h1_c_t                0xc841  //  1-10010-00010-00001      [ÈA ]
#define def_c16_h1_c_p                0xcc41  //  1-10011-00010-00001      [ÌA ]
#define def_c16_h1_c_h                0xd041  //  1-10100-00010-00001      [ÐA ]

#define def_c16_h2_c_ia               0x8461  //  1-00001-00011-00001      [„a ]
#define def_c16_h2_c_iai              0x8481  //  1-00001-00100-00001      [„ ]
#define def_c16_h2_c_iaa              0x84a1  //  1-00001-00101-00001      [„¡ ]
#define def_c16_h2_c_iaai             0x84c1  //  1-00001-00110-00001      [„Á ]
#define def_c16_h2_c_ai               0x84e1  //  1-00001-00111-00001      [„á ]
#define def_c16_h2_c_aii              0x8541  //  1-00001-01010-00001      […A ]
#define def_c16_h2_c_aai              0x8561  //  1-00001-01011-00001      […a ]
#define def_c16_h2_c_aaii             0x8581  //  1-00001-01100-00001      [… ]
#define def_c16_h2_c_au               0x85a1  //  1-00001-01101-00001      […¡ ]
#define def_c16_h2_c_auia             0x85c1  //  1-00001-01110-00001      […Á ]
#define def_c16_h2_c_auiai            0x85e1  //  1-00001-01111-00001      […á ]
#define def_c16_h2_c_aui              0x8641  //  1-00001-10010-00001      [†A ]
#define def_c16_h2_c_aau              0x8661  //  1-00001-10011-00001      [†a ]
#define def_c16_h2_c_ua               0x8681  //  1-00001-10100-00001      [† ]
#define def_c16_h2_c_uaai             0x86a1  //  1-00001-10101-00001      [†¡ ]
#define def_c16_h2_c_uaaii            0x86c1  //  1-00001-10110-00001      [†Á ]
#define def_c16_h2_c_uai              0x86e1  //  1-00001-10111-00001      [†á ]
#define def_c16_h2_c_uaa              0x8741  //  1-00001-11010-00001      [‡A ]
#define def_c16_h2_c_u                0x8761  //  1-00001-11011-00001      [‡a ]
#define def_c16_h2_c_ui               0x8781  //  1-00001-11100-00001      [‡ ]
#define def_c16_h2_c_i                0x87a1  //  1-00001-11101-00001      [‡¡ ]

#define def_c16_h3_c_g                0x8442  //  1-00001-00010-00010      [„B ]
#define def_c16_h3_c_gg               0x8443  //  1-00001-00010-00011      [„C ]
#define def_c16_h3_c_gs               0x8444  //  1-00001-00010-00100      [„D ]
#define def_c16_h3_c_n                0x8445  //  1-00001-00010-00101      [„E ]
#define def_c16_h3_c_nj               0x8446  //  1-00001-00010-00110      [„F ]
#define def_c16_h3_c_nh               0x8447  //  1-00001-00010-00111      [„G ]
#define def_c16_h3_c_d                0x8448  //  1-00001-00010-01000      [„H ]
#define def_c16_h3_c_r                0x8449  //  1-00001-00010-01001      [„I ]
#define def_c16_h3_c_rg               0x844a  //  1-00001-00010-01010      [„J ]
#define def_c16_h3_c_rm               0x844b  //  1-00001-00010-01011      [„K ]
#define def_c16_h3_c_rb               0x844c  //  1-00001-00010-01100      [„L ]
#define def_c16_h3_c_rs               0x844d  //  1-00001-00010-01101      [„M ]
#define def_c16_h3_c_rt               0x844e  //  1-00001-00010-01110      [„N ]
#define def_c16_h3_c_rp               0x844f  //  1-00001-00010-01111      [„O ]
#define def_c16_h3_c_rh               0x8450  //  1-00001-00010-10000      [„P ]
#define def_c16_h3_c_m                0x8451  //  1-00001-00010-10001      [„Q ]
#define def_c16_h3_c_b                0x8453  //  1-00001-00010-10011      [„S ]
#define def_c16_h3_c_bs               0x8454  //  1-00001-00010-10100      [„T ]
#define def_c16_h3_c_s                0x8455  //  1-00001-00010-10101      [„U ]
#define def_c16_h3_c_ss               0x8456  //  1-00001-00010-10110      [„V ]
#define def_c16_h3_c_y                0x8457  //  1-00001-00010-10111      [„W ]
#define def_c16_h3_c_j                0x8458  //  1-00001-00010-11000      [„X ]
#define def_c16_h3_c_c                0x8459  //  1-00001-00010-11001      [„Y ]
#define def_c16_h3_c_k                0x845a  //  1-00001-00010-11010      [„Z ]
#define def_c16_h3_c_t                0x845b  //  1-00001-00010-11011      [„[ ]
#define def_c16_h3_c_p                0x845c  //  1-00001-00010-11100      [„\ ]
#define def_c16_h3_c_h                0x845d  //  1-00001-00010-11101      [„] ]
                                                                                                                        /*
--------------------------------------------------------------------------------
   ‹¡¥¥ ·q¸é ¸÷·                                             2 ¤a·¡Ëa Å¡—a
--------------------------------------------------------------------------------                                        */

#define def_c16_ga                    0x8861  //  1-00010-00011-00001      [ˆa ]
#define def_c16_na                    0x9061  //  1-00100-00011-00001      [a ]
#define def_c16_da                    0x9461  //  1-00101-00011-00001      [”a ]
#define def_c16_ra                    0x9c61  //  1-00111-00011-00001      [œa ]
#define def_c16_ma                    0xa061  //  1-01000-00011-00001      [ a ]
#define def_c16_ba                    0xa461  //  1-01001-00011-00001      [¤a ]
#define def_c16_sa                    0xac61  //  1-01011-00011-00001      [¬a ]
#define def_c16_xa                    0xb461  //  1-01101-00011-00001      [´a ]
#define def_c16_ja                    0xb861  //  1-01110-00011-00001      [¸a ]
#define def_c16_ca                    0xc061  //  1-10000-00011-00001      [Àa ]
#define def_c16_ka                    0xc461  //  1-10001-00011-00001      [Äa ]
#define def_c16_ta                    0xc861  //  1-10010-00011-00001      [Èa ]
#define def_c16_pa                    0xcc61  //  1-10011-00011-00001      [Ìa ]
#define def_c16_ha                    0xd061  //  1-10100-00011-00001      [Ða ]

