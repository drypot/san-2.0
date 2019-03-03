                                                                                                                        /*
--------------------------------------------------------------------------------
   key/keyevent.cpp
   copyright(C) kyuhyun park
   1993.07.13
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <key/keyevent.hpp>

#if defined def_pm

static uint16 xtable[] =
{
   0                        ,  /* 0x00 */
   def_key_esc              ,  /* 0x01 */
   def_key_a01              ,  /* 0x02 */
   def_key_a02              ,  /* 0x03 */
   def_key_a03              ,  /* 0x04 */
   def_key_a04              ,  /* 0x05 */
   def_key_a05              ,  /* 0x06 */
   def_key_a06              ,  /* 0x07 */
   def_key_a07              ,  /* 0x08 */
   def_key_a08              ,  /* 0x09 */
   def_key_a09              ,  /* 0x0a */
   def_key_a10              ,  /* 0x0b */
   def_key_a11              ,  /* 0x0c */
   def_key_a12              ,  /* 0x0d */
   def_key_backspace        ,  /* 0x0e */
   def_key_tab              ,  /* 0x0f */
   def_key_b00              ,  /* 0x10 */
   def_key_b01              ,  /* 0x11 */
   def_key_b02              ,  /* 0x12 */
   def_key_b03              ,  /* 0x13 */
   def_key_b04              ,  /* 0x14 */
   def_key_b05              ,  /* 0x15 */
   def_key_b06              ,  /* 0x16 */
   def_key_b07              ,  /* 0x17 */
   def_key_b08              ,  /* 0x18 */
   def_key_b09              ,  /* 0x19 */
   def_key_b10              ,  /* 0x1a */
   def_key_b11              ,  /* 0x1b */
   def_key_enter            ,  /* 0x1c */
   def_key_lctrl            ,  /* 0x1d */
   def_key_c00              ,  /* 0x1e */
   def_key_c01              ,  /* 0x1f */
   def_key_c02              ,  /* 0x20 */
   def_key_c03              ,  /* 0x21 */
   def_key_c04              ,  /* 0x22 */
   def_key_c05              ,  /* 0x23 */
   def_key_c06              ,  /* 0x24 */
   def_key_c07              ,  /* 0x25 */
   def_key_c08              ,  /* 0x26 */
   def_key_c09              ,  /* 0x27 */
   def_key_c10              ,  /* 0x28 */
   def_key_a00              ,  /* 0x29 */
   def_key_lshift           ,  /* 0x2a */
   def_key_a13              ,  /* 0x2b */
   def_key_d00              ,  /* 0x2c */
   def_key_d01              ,  /* 0x2d */
   def_key_d02              ,  /* 0x2e */
   def_key_d03              ,  /* 0x2f */
   def_key_d04              ,  /* 0x30 */
   def_key_d05              ,  /* 0x31 */
   def_key_d06              ,  /* 0x32 */
   def_key_d07              ,  /* 0x33 */
   def_key_d08              ,  /* 0x34 */
   def_key_d09              ,  /* 0x35 */
   def_key_rshift           ,  /* 0x36 */
   def_key_pad_asterisk     ,  /* 0x37 */
   def_key_lalt             ,  /* 0x38 */
   def_key_space            ,  /* 0x39 */
   def_key_caps_lock        ,  /* 0x3a */
   def_key_f1               ,  /* 0x3b */
   def_key_f2               ,  /* 0x3c */
   def_key_f3               ,  /* 0x3d */
   def_key_f4               ,  /* 0x3e */
   def_key_f5               ,  /* 0x3f */
   def_key_f6               ,  /* 0x40 */
   def_key_f7               ,  /* 0x41 */
   def_key_f8               ,  /* 0x42 */
   def_key_f9               ,  /* 0x43 */
   def_key_f10              ,  /* 0x44 */
   def_key_num_lock         ,  /* 0x45 */
   def_key_scroll_lock      ,  /* 0x46 */
   def_key_pad_7            ,  /* 0x47 */
   def_key_pad_8            ,  /* 0x48 */
   def_key_pad_9            ,  /* 0x49 */
   def_key_pad_minus        ,  /* 0x4a */
   def_key_pad_4            ,  /* 0x4b */
   def_key_pad_5            ,  /* 0x4c */
   def_key_pad_6            ,  /* 0x4d */
   def_key_pad_plus         ,  /* 0x4e */
   def_key_pad_1            ,  /* 0x4f */
   def_key_pad_2            ,  /* 0x50 */
   def_key_pad_3            ,  /* 0x51 */
   def_key_pad_0            ,  /* 0x52 */
   def_key_pad_period       ,  /* 0x53 */
   0                        ,  /* 0x54 */
   0                        ,  /* 0x55 */
   0                        ,  /* 0x56 */
   def_key_f11              ,  /* 0x57 */
   def_key_f12              ,  /* 0x58 */
   0                        ,  /* 0x59 */
   def_key_pad_enter        ,  /* 0x5a */
   def_key_rctrl            ,  /* 0x5b */
   def_key_pad_slash        ,  /* 0x5c */
   def_key_print_screen     ,  /* 0x5d */
   def_key_ralt             ,  /* 0x5e */
   def_key_pause            ,  /* 0x5f */
   def_key_home             ,  /* 0x60 */
   def_key_up               ,  /* 0x61 */
   def_key_page_up          ,  /* 0x62 */
   def_key_left             ,  /* 0x63 */
   def_key_right            ,  /* 0x64 */
   def_key_end              ,  /* 0x65 */
   def_key_down             ,  /* 0x66 */
   def_key_page_down        ,  /* 0x67 */
   def_key_insert           ,  /* 0x68 */
   def_key_delete              /* 0x69 */
};

static uint16 pad_xtable[] =
{
   def_key_pad_insert       ,  // 0 ---> pad_insert
   def_key_pad_end          ,  // 1 ---> pad_end
   def_key_pad_down         ,  // 2 ---> pad_down
   def_key_pad_page_down    ,  // 3 ---> pad_page_down
   def_key_pad_left         ,  // 4 ---> pad_left
   def_key_pad_clear        ,  // 5 ---> pad_clear
   def_key_pad_right        ,  // 6 ---> pad_right
   def_key_pad_home         ,  // 7 ---> pad_home
   def_key_pad_up           ,  // 8 ---> pad_up
   def_key_pad_page_up      ,  // 9 ---> pad_page_up
   def_key_pad_slash        ,  // / ---> /
   def_key_pad_asterisk     ,  // * ---> *
   def_key_pad_minus        ,  // - ---> -
   def_key_pad_plus         ,  // + ---> +
   def_key_pad_period          // . ---> pad_delete
};

#endif

#ifdef def_pm

void cls_key_event::set(MPARAM mp1, MPARAM /*mp2*/)
{
   USHORT fsflags = SHORT1FROMMP(mp1);
   UCHAR  ucscan  = CHAR4FROMMP(mp1);
   UCHAR  repeat_cnt = CHAR3FROMMP(mp1);

   if ((fsflags & KC_SCANCODE) && (ucscan < mac_cnt_of(xtable)))
   {
      make_flg = !(fsflags & KC_KEYUP);

      shifted_u16 = 0;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x36) & 0x8000) shifted_u16 |= def_key_mask_rshift;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x2A) & 0x8000) shifted_u16 |= def_key_mask_lshift;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x5B) & 0x8000) shifted_u16 |= def_key_mask_rctrl;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x1D) & 0x8000) shifted_u16 |= def_key_mask_lctrl;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x5E) & 0x8000) shifted_u16 |= def_key_mask_ralt;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x38) & 0x8000) shifted_u16 |= def_key_mask_lalt;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x45) & 0x8000) shifted_u16 |= def_key_mask_num_lock;
      if (WinGetPhysKeyState(HWND_DESKTOP,0x3A) & 0x8000) shifted_u16 |= def_key_mask_caps_lock;

      toggled_u16 = 0;
      if (WinGetKeyState(HWND_DESKTOP,VK_SHIFT)    & 0x0001L) toggled_u16 |= def_key_mask_shift ;
      if (WinGetKeyState(HWND_DESKTOP,VK_CTRL)     & 0x0001L) toggled_u16 |= def_key_mask_ctrl ;
      if (WinGetKeyState(HWND_DESKTOP,VK_ALT)      & 0x0001L) toggled_u16 |= def_key_mask_alt ;
      if (WinGetKeyState(HWND_DESKTOP,VK_NUMLOCK)  & 0x0001L) toggled_u16 |= def_key_mask_num_lock ;
      if (WinGetKeyState(HWND_DESKTOP,VK_CAPSLOCK) & 0x0001L) toggled_u16 |= def_key_mask_caps_lock ;

      code_u16 = xtable[ucscan];

      if ((code_u16 & def_key_mask_code_type) == def_key_type_pad_char)
      {
         if (!(toggled_u16 & def_key_mask_num_lock))
         {
            code_u16 = pad_xtable[code_u16 & def_key_mask_code_offset];
         }
      }

      cnt = repeat_cnt;
   }
   else
   {
      code_u16 = 0;
   }
}

#endif /* def_pm */

#if defined def_dos || (defined def_os2 && !defined def_pm)

void cls_key_event::set()
{
   cls_key_frame key_frame;

   key_get (&key_frame);
   set (&key_frame);
}

#endif /* def_dos || def_os2 */

void cls_key_event::set(cls_key_frame* key_frame)
{
   make_flg    = key_frame->make_flg;
   code_u16    = key_frame->code_u16;
   shifted_u16 = key_frame->shifted_u16;
   toggled_u16 = key_frame->toggled_u16;
}
