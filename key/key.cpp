                                                                                                                        /*
--------------------------------------------------------------------------------
   key/key.cpp
   copyright(C) kyuhyun park
   1993.07.13
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/init.hpp>
#include <cnt/queue.hpp>
#include <key/key.hpp>

#if defined def_dos
#define def_key_dos
#define def_key_avail
#endif

#if defined def_os2 && !defined def_pm
#define def_key_os2
#define def_key_avail
#endif

#ifdef def_key_avail

#ifdef def_key_os2
#define INCL_KBD
#define INCL_NOPMAPI
#include <os2.h>
#endif

#ifdef def_key_dos
#include <pub/misc.hpp>
#endif

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
   def_key_sys_req          ,  /* 0x54 */
   0                        ,  /* 0x55 */
   0                        ,  /* 0x56 */
   def_key_f11              ,  /* 0x57 */
   def_key_f12                 /* 0x58 */
};

struct { uint16 u16_scan; uint16 u16_key_code; } e0_xtable [] =
{
   { 0x1c, def_key_pad_enter    },   // pad enter
   { 0x1d, def_key_rctrl        },   // right ctrl
   { 0x35, def_key_pad_slash    },   // pad/
   { 0x37, def_key_print_screen },   // printscreen
   { 0x38, def_key_ralt         },   // right alt
   { 0x46, def_key_pause        },   // pause
   { 0x47, def_key_home         },   // home
   { 0x48, def_key_up           },   // up
   { 0x49, def_key_page_up      },   // pgup
   { 0x4b, def_key_left         },   // left
   { 0x4d, def_key_right        },   // right
   { 0x4f, def_key_end          },   // end
   { 0x50, def_key_down         },   // down
   { 0x51, def_key_page_down    },   // pgdn
   { 0x52, def_key_insert       },   // insert
   { 0x53, def_key_delete       },   // delete
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

static tem_queue<cls_key_frame> key_frame_queue(32);
static bool on_flg;
static uint shifted_u16;
static uint toggled_u16;

static void fill_queue(uint arg_scan_code)
{
   static bool e0_flg;
   static bool e1_flg;

   cls_key_frame key_frame;
   uint scan_code_uint = arg_scan_code;
   uint make_code_uint = arg_scan_code & 0x7f;
   uint code_uint = 0xffff;
   uint make_flg = (arg_scan_code & 0x80) == 0;
   uint type_uint;

   if (e0_flg)
   {
      if (scan_code_uint == 0x2a || scan_code_uint == 0xaa)
      {
         nothing;
      }
      else
      {
         int i;
         forcnt(i,mac_cnt_of(e0_xtable))
         {
            if (e0_xtable[i].u16_scan == make_code_uint)
            {
               code_uint = e0_xtable[i].u16_key_code;
               break;
            }
         }
         mac_rtcheck(code_uint != 0xffff);
      }
      e0_flg = def_no;
   }
   else if (e1_flg)
   {
      if (make_code_uint == 0x45)
      {
         code_uint = def_key_pause;
         e1_flg = def_no;
      }
   }
   else
   {
      if (scan_code_uint == 0xf1)
      {
         code_uint = def_key_hanja;
      }
      ef (scan_code_uint == 0xf2)
      {
         code_uint = def_key_hangul;
      }
      ef (scan_code_uint == 0xe0)
      {
         e0_flg = def_yes;
      }
      ef (scan_code_uint == 0xe1)
      {
         e1_flg = def_yes;
      }
      else
      {
         mac_rtcheck(make_code_uint <= 0x58);
         code_uint = xtable[make_code_uint];
      }
   }

   type_uint = code_uint & def_key_mask_code_type;

   if (type_uint == def_key_type_shift)
   {
      uint make_uint = 1 << (code_uint & def_key_mask_code_offset);

      if (make_flg)
      {
         if (!(shifted_u16 & make_uint))
         {
            toggled_u16 ^= make_uint;
         }
         shifted_u16 |= make_uint;
      }
      else
      {
         shifted_u16 &= ~make_uint;
      }
   }
   ef (type_uint == def_key_type_pad_char)
   {
      if (!(toggled_u16 & def_key_mask_num_lock))
      {
         code_uint = pad_xtable[code_uint & def_key_mask_code_offset];
      }
   }

   if (code_uint != 0xffff)
   {
      key_frame.make_flg = make_flg;
      key_frame.code_u16 = code_uint;
      key_frame.shifted_u16 = shifted_u16;
      key_frame.toggled_u16 = toggled_u16;
      key_frame_queue.push_pnt(&key_frame);
   }
}

#ifdef def_key_os2

struct MonKeyPacket
{
   UCHAR uchFlags;
   UCHAR uchScanCode;
   KBDKEYINFO kbdKeyInfo;
   USHORT usKbdDFlags;
};

typedef USHORT HMONITOR;
typedef HMONITOR* PHMONITOR;

extern "C"
{
   APIRET16 APIENTRY16 DOS16MONOPEN  (PSZ devName, PHMONITOR pHandle);
   APIRET16 APIENTRY16 DOS16MONREG   (HMONITOR handle, PVOID bufI, PVOID bufO, USHORT posFlag, USHORT index);
   APIRET16 APIENTRY16 DOS16MONWRITE (PVOID bufO, PVOID dataBuf, USHORT byte_cnt);
   APIRET16 APIENTRY16 DOS16MONREAD  (PVOID bufI, USHORT waitFlag, PVOID dataBuf, PUSHORT pbyte_cnt);
   APIRET16 APIENTRY16 DOS16CLOSE    (HMONITOR);
}

#define DosMonOpen  DOS16MONOPEN
#define DosMonReg   DOS16MONREG
#define DosMonWrite DOS16MONWRITE
#define DosMonRead  DOS16MONREAD
#define DosMonClose DOS16CLOSE

static USHORT us_monitor;
static USHORT ary_us_init_mon_in[2];
static USHORT ary_us_init_mon_out[2];
static PBYTE pnt_byte_mon_buf;
static PBYTE pnt_byte_mon_in;
static PBYTE pnt_byte_mon_out;
static MonKeyPacket mon_key_packet;
static USHORT us_size_monkey_packet = sizeof(mon_key_packet);

static void set_toggled()
{
   KBDINFO kbd_info;

   kbd_info.cb = sizeof(kbd_info);
   KbdGetStatus(&kbd_info, 0);

   if (kbd_info.fsState & 0x40)
   {
      toggled_u16 |= def_key_mask_caps_lock;
   }
   if (kbd_info.fsState & 0x20)
   {
      toggled_u16 |= def_key_mask_num_lock;
   }
}

static void monitor_open()
{
   mac_rtcheck (DosMonOpen("KBD$",&us_monitor) == 0);

   //----------------------------------------------------------------------
   // Query the size of the needed monitor buffers
   //----------------------------------------------------------------------

   ary_us_init_mon_in[0]  = sizeof(ary_us_init_mon_in);
   ary_us_init_mon_out[0] = sizeof(ary_us_init_mon_out);

   mac_rtcheck
   (
      DosMonReg(us_monitor,(PBYTE)ary_us_init_mon_in,(PBYTE)ary_us_init_mon_out,0,-1) == 382
   );

   //----------------------------------------------------------------------
   // Allocate memory for the total size and specify the OBJ_TILE
   // attribute to force this to be 64K segment aligned.  This results
   // in both pnt_byte_mon_in and pnt_byte_mon_out to be in the same 16-bit segment
   // which is a requirement of DosMonReg().
   //----------------------------------------------------------------------

   mac_rtcheck
   (
      DosAllocMem ((PPVOID)&pnt_byte_mon_buf, ary_us_init_mon_in[1]+ary_us_init_mon_out[1], PAG_COMMIT|PAG_READ|PAG_WRITE|OBJ_TILE) == 0
   );

   pnt_byte_mon_in  = pnt_byte_mon_buf;
   pnt_byte_mon_out = pnt_byte_mon_buf+ary_us_init_mon_in[1];

   *(PUSHORT)pnt_byte_mon_in=ary_us_init_mon_in[1];
   *(PUSHORT)pnt_byte_mon_out=ary_us_init_mon_out[1];

   mac_rtcheck
   (
      DosMonReg (us_monitor, pnt_byte_mon_in, pnt_byte_mon_out, 0, -1) == 0
   );
}

static void monitor_close()
{
   DosMonClose(us_monitor);
   DosFreeMem(pnt_byte_mon_buf);
}

static void monitor_check()
{
   if (DosMonRead (pnt_byte_mon_in, 1, &mon_key_packet, &us_size_monkey_packet) == 0)
      if (mon_key_packet.uchFlags & 0x04)
         DosMonWrite (pnt_byte_mon_out, &mon_key_packet, us_size_monkey_packet);
      else
         fill_queue (mon_key_packet.uchScanCode);
}

#endif /* def_key_OS2 */

#ifdef def_key_dos

byte* real_mode_buf_byte_pnt;
int16* real_mode_buf_inx_i16_pnt;

void monitor_check()
{
   int cnt = *real_mode_buf_inx_i16_pnt;
   int i;

   if (cnt)
   {
      _disable();
      *real_mode_buf_inx_i16_pnt = 0;
      forcnt (i, cnt)
      {
         fill_queue(real_mode_buf_byte_pnt[i]);
      }
      _enable();
   }
}

static void set_toggled()
{
   _disable();

   uint16 bios_flag_u16 = *(uint16*) 0x0417;

   *real_mode_buf_inx_i16_pnt = 0;
   if (bios_flag_u16 & 0x40)
   {
      toggled_u16 |= def_key_mask_caps_lock;
   }
   if (bios_flag_u16 & 0x20)
   {
      toggled_u16 |= def_key_mask_num_lock;
   }

   _enable();
}

#endif  /* def_key_DOS */

void key_on()
{
   mac_assert(!on_flg);

#ifdef def_key_os2
   monitor_open();
#endif

   set_toggled();
   key_frame_queue.reset();
   on_flg = def_yes;
}

void key_off()
{
   mac_assert(on_flg);

#ifdef def_key_os2
   monitor_close();
#endif

   on_flg = def_no;
}

void key_reset()
{
   mac_assert(on_flg);
   key_frame_queue.reset();
}

bool key_pressed()
{
   mac_assert(on_flg);
   if (key_frame_queue.is_empty()) monitor_check();
   return !key_frame_queue.is_empty();
}

void key_get(cls_key_frame* key_frame)
{
   mac_assert(on_flg);
   while (!key_pressed());
   *key_frame = key_frame_queue.pop_val();

#ifdef def_key_dos
   while (_bios_keybrd(_NKEYBRD_READY)) _bios_keybrd(_NKEYBRD_READ);
#endif
}

static void ctor()
{
#ifdef def_key_dos
   real_mode_buf_byte_pnt = *(byte**)0xbfff0;
   real_mode_buf_inx_i16_pnt = *(int16**)0xbfff4;
#endif
}

static void dtor()
{
   if (on_flg) key_off();
}

static cls_infiniter infiniter(ctor, dtor);

#endif /* def_key_avail */
