                                                                                                                        /*
--------------------------------------------------------------------------------
   key/key.hpp
   copyright(C) kyuhyun park
   1993.07.13
--------------------------------------------------------------------------------                                        */

#ifdef def_key_key_hpp
#error 'key/key.hpp' duplicated.
#endif

#define def_key_key_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif
                                                                                                                        /*
--------------------------------------------------------------------------------
   shift keys
--------------------------------------------------------------------------------                                        */

#define def_key_rshift            0x0100
#define def_key_lshift            0x0101
#define def_key_rctrl             0x0102
#define def_key_lctrl             0x0103
#define def_key_ralt              0x0104
#define def_key_lalt              0x0105
#define def_key_rmachine          0x0106
#define def_key_lmachine          0x0107
#define def_key_num_lock          0x0108
#define def_key_caps_lock         0x0109
                                                                                                                        /*
--------------------------------------------------------------------------------
   character keys
--------------------------------------------------------------------------------                                        */

#define def_key_a00               0x0200
#define def_key_a01               0x0201
#define def_key_a02               0x0202
#define def_key_a03               0x0203
#define def_key_a04               0x0204
#define def_key_a05               0x0205
#define def_key_a06               0x0206
#define def_key_a07               0x0207
#define def_key_a08               0x0208
#define def_key_a09               0x0209
#define def_key_a10               0x020a
#define def_key_a11               0x020b
#define def_key_a12               0x020c
#define def_key_a13               0x020d
#define def_key_a14               0x020e
#define def_key_a15               0x020f

#define def_key_b00               0x0220
#define def_key_b01               0x0221
#define def_key_b02               0x0222
#define def_key_b03               0x0223
#define def_key_b04               0x0224
#define def_key_b05               0x0225
#define def_key_b06               0x0226
#define def_key_b07               0x0227
#define def_key_b08               0x0228
#define def_key_b09               0x0229
#define def_key_b10               0x022a
#define def_key_b11               0x022b
#define def_key_b12               0x022c
#define def_key_b13               0x022d
#define def_key_b14               0x022e
#define def_key_b15               0x022f

#define def_key_c00               0x0240
#define def_key_c01               0x0241
#define def_key_c02               0x0242
#define def_key_c03               0x0243
#define def_key_c04               0x0244
#define def_key_c05               0x0245
#define def_key_c06               0x0246
#define def_key_c07               0x0247
#define def_key_c08               0x0248
#define def_key_c09               0x0249
#define def_key_c10               0x024a
#define def_key_c11               0x024b
#define def_key_c12               0x024c
#define def_key_c13               0x024d
#define def_key_c14               0x024e
#define def_key_c15               0x024f

#define def_key_d00               0x0260
#define def_key_d01               0x0261
#define def_key_d02               0x0262
#define def_key_d03               0x0263
#define def_key_d04               0x0264
#define def_key_d05               0x0265
#define def_key_d06               0x0266
#define def_key_d07               0x0267
#define def_key_d08               0x0268
#define def_key_d09               0x0269
#define def_key_d10               0x026a
#define def_key_d11               0x026b
#define def_key_d12               0x026c
#define def_key_d13               0x026d
#define def_key_d14               0x026e
#define def_key_d15               0x026f

#define def_key_qwt_q             0x0220
#define def_key_qwt_w             0x0221
#define def_key_qwt_e             0x0222
#define def_key_qwt_r             0x0223
#define def_key_qwt_t             0x0224
#define def_key_qwt_y             0x0225
#define def_key_qwt_u             0x0226
#define def_key_qwt_i             0x0227
#define def_key_qwt_o             0x0228
#define def_key_qwt_p             0x0229

#define def_key_qwt_a             0x0240
#define def_key_qwt_s             0x0241
#define def_key_qwt_d             0x0242
#define def_key_qwt_f             0x0243
#define def_key_qwt_g             0x0244
#define def_key_qwt_h             0x0245
#define def_key_qwt_j             0x0246
#define def_key_qwt_k             0x0247
#define def_key_qwt_l             0x0248

#define def_key_qwt_z             0x0260
#define def_key_qwt_x             0x0261
#define def_key_qwt_c             0x0262
#define def_key_qwt_v             0x0263
#define def_key_qwt_b             0x0264
#define def_key_qwt_n             0x0265
#define def_key_qwt_m             0x0266
                                                                                                                        /*
--------------------------------------------------------------------------------
   character keys on keypad
--------------------------------------------------------------------------------                                        */

#define def_key_pad_0             0x0300
#define def_key_pad_1             0x0301
#define def_key_pad_2             0x0302
#define def_key_pad_3             0x0303
#define def_key_pad_4             0x0304
#define def_key_pad_5             0x0305
#define def_key_pad_6             0x0306
#define def_key_pad_7             0x0307
#define def_key_pad_8             0x0308
#define def_key_pad_9             0x0309
#define def_key_pad_slash         0x030a
#define def_key_pad_asterisk      0x030b
#define def_key_pad_minus         0x030c
#define def_key_pad_plus          0x030d
#define def_key_pad_period        0x030e
                                                                                                                        /*
--------------------------------------------------------------------------------
   special keys
--------------------------------------------------------------------------------                                        */

#define def_key_esc               0x0400
#define def_key_backspace         0x0401
#define def_key_tab               0x0402
#define def_key_enter             0x0403
#define def_key_space             0x0404
#define def_key_insert            0x0405
#define def_key_delete            0x0406
#define def_key_print_screen      0x0407
#define def_key_scroll_lock       0x0408
#define def_key_pause             0x0409
#define def_key_sys_req           0x040a
#define def_key_break             0x040b
                              //  0x040c  reserved for clear key
#define def_key_hangul            0x040d
#define def_key_hanja             0x040e
                                                                                                                        /*
--------------------------------------------------------------------------------
   special keys on keypad
--------------------------------------------------------------------------------                                        */

#define def_key_pad_enter         0x0503
#define def_key_pad_insert        0x0505
#define def_key_pad_delete        0x0506
#define def_key_pad_clear         0x050c
                                                                                                                        /*
--------------------------------------------------------------------------------
   movement keys
--------------------------------------------------------------------------------                                        */

#define def_key_up                0x0600
#define def_key_down              0x0601
#define def_key_left              0x0602
#define def_key_right             0x0603
#define def_key_page_up           0x0604
#define def_key_page_down         0x0605
#define def_key_home              0x0606
#define def_key_end               0x0607
                                                                                                                        /*
--------------------------------------------------------------------------------
   movement keys on keypad
--------------------------------------------------------------------------------                                        */

#define def_key_pad_up            0x0700
#define def_key_pad_down          0x0701
#define def_key_pad_left          0x0702
#define def_key_pad_right         0x0703
#define def_key_pad_page_up       0x0704
#define def_key_pad_page_down     0x0705
#define def_key_pad_home          0x0706
#define def_key_pad_end           0x0707
                                                                                                                        /*
--------------------------------------------------------------------------------
   function keys
--------------------------------------------------------------------------------                                        */

#define def_key_f1                0x0800
#define def_key_f2                0x0801
#define def_key_f3                0x0802
#define def_key_f4                0x0803
#define def_key_f5                0x0804
#define def_key_f6                0x0805
#define def_key_f7                0x0806
#define def_key_f8                0x0807
#define def_key_f9                0x0808
#define def_key_f10               0x0809
#define def_key_f11               0x080a
#define def_key_f12               0x080b
                                                                                                                        /*
--------------------------------------------------------------------------------
   function keys on keypad
--------------------------------------------------------------------------------                                        */

                                                                                                                        /*
--------------------------------------------------------------------------------
   additonal defines
--------------------------------------------------------------------------------                                        */

#define def_key_type_null            0x0000u
#define def_key_type_shift           0x0100u
#define def_key_type_char            0x0200u
#define def_key_type_pad_char        0x0300u
#define def_key_type_action          0x0400u
#define def_key_type_pad_action      0x0500u
#define def_key_type_cursor          0x0600u
#define def_key_type_pad_cursor      0x0700u
#define def_key_type_function        0x0800u
#define def_key_type_pad_function    0x0900u

#define def_key_mask_rshift         0x0001u
#define def_key_mask_lshift         0x0002u
#define def_key_mask_rctrl          0x0004u
#define def_key_mask_lctrl          0x0008u
#define def_key_mask_ralt           0x0010u
#define def_key_mask_lalt           0x0020u
#define def_key_mask_rmachine       0x0040u
#define def_key_mask_lmachine       0x0080u
#define def_key_mask_num_lock        0x0100u
#define def_key_mask_caps_lock       0x0200u

#define def_key_mask_shift           (def_key_mask_rshift   | def_key_mask_lshift)
#define def_key_mask_ctrl            (def_key_mask_rctrl    | def_key_mask_lctrl)
#define def_key_mask_alt             (def_key_mask_ralt     | def_key_mask_lalt)
#define def_key_mask_machine         (def_key_mask_rmachine | def_key_mask_lmachine)

#define def_key_mask_code_type       0xff00u
#define def_key_mask_code_offset     0x00ffu
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

struct cls_key_frame
{
   bool   make_flg;
   uint16 code_u16;
   uint16 shifted_u16;
   uint16 toggled_u16;
};

#if (defined def_dos) || (defined def_os2 && !defined def_pm)
   void key_on();
   void key_off();
   void key_reset();
   bool key_pressed();
   void key_get(cls_key_frame*);
#endif
