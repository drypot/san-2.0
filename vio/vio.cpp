                                                                                                                        /*
--------------------------------------------------------------------------------
   vio/vio.cpp
   copyright(C) kyuhyun park.
	1991.03.26
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/init.hpp>
#include <vio/vio.hpp>

#if defined def_os2 && !defined def_pm
#define VIO_OS2
#define VIO_AVAIL
#endif

#if defined def_dos
#define VIO_DOS
#define VIO_AVAIL
#endif

#ifdef VIO_AVAIL

#ifdef VIO_OS2
#define INCL_VIO
#define INCL_def_noPMAPI
#include <os2.h>
#endif

#ifdef VIO_DOS
#include <pub/misc.hpp>
#endif

#define def_width 80
#define def_height 30
#define def_map_size (def_width * def_height * 16)

#ifdef VIO_OS2
static byte* map_byte_pnt;
static VIOMODEINFO vio_text_mode_info;
static VIOMODEINFO vio_graf_mode_info;
#endif

#ifdef VIO_DOS
#define map_byte_pnt ((byte*)0xA0000)
static int real_mode_server_inter_num;
static int prev_mode_num;
#endif

static int on_flg;

#ifdef VIO_OS2
static void set_video_map_base()
{
   VIOPHYSBUF vio_phys_buf;

   vio_phys_buf.pBuf = (CHAR*)(ULONG)0x000A0000;
   vio_phys_buf.cb = def_width * def_height * 16;

   VioGetPhysBuf(&vio_phys_buf,0);
   map_byte_pnt = (byte __far16*) ((ULONG)vio_phys_buf.asel[0] << 16);
}

static void set_vio_mode_info()
{
   vio_graf_mode_info.cb = sizeof(VIOMODEINFO);
   VioGetMode(&vio_graf_mode_info,0);
   vio_text_mode_info = vio_graf_mode_info;

   vio_graf_mode_info.fbType = 3;
   vio_graf_mode_info.color  = 4;
   vio_graf_mode_info.col    = 80;
   vio_graf_mode_info.row    = 30;
   vio_graf_mode_info.hres   = 640;
   vio_graf_mode_info.vres   = 480;
}

/*
byte color_table[] =
{
    0, 0, 0,0 ,
    0, 0,42,0 ,
    0,42, 0,0 ,
    0,42,42,0 ,
   42, 0, 0,0 ,
   42, 0,42,0 ,
   42,21, 0,0 ,
   42,42,42,0 ,
   21,21,21,0 ,
   21,21,63,0 ,
   21,63,21,0 ,
   21,63,63,0 ,
   63,21,21,0 ,
   63,21,63,0 ,
   63,63,21,0 ,
    0, 42,0,0
};
*/

/*
static void set_color_table()
{

   VIOCOLORREG vio_color_reg;

   vio_color_reg.cb = sizeof(VIOCOLORREG);
   vio_color_reg.type = 3;

   vio_color_reg.firstcolorreg = 63;
   vio_color_reg.numcolorregs = 1;
   mac_change_type_of(vio_color_reg.colorregaddr,byte __far16*) = color_table;
   VioSetState(&vio_color_reg,0);

}
*/

/*
static void set_palette()
{
   PVIOPALSTATE pnt_palette;
   int sz = sizeof(VIOPALSTATE)+30;

   pnt_palette = (PVIOPALSTATE) mem_alloc(sz);

   pnt_palette->cb     = sz;
   pnt_palette->type   = 0;
   pnt_palette->iFirst = 0;

   pnt_palette->acolor[0] = 0;
   pnt_palette->acolor[1] = 1;
   pnt_palette->acolor[2] = 1;
   pnt_palette->acolor[3] = 1;
   pnt_palette->acolor[4] = 1;
   pnt_palette->acolor[5] = 1;
   pnt_palette->acolor[6] = 1;
   pnt_palette->acolor[7] = 1;
   pnt_palette->acolor[8] = 1;
   pnt_palette->acolor[9] = 1;
   pnt_palette->acolor[10] = 1;
   pnt_palette->acolor[11] = 1;
   pnt_palette->acolor[12] = 1;
   pnt_palette->acolor[13] = 1;
   pnt_palette->acolor[14] = 1;
   pnt_palette->acolor[15] = 1;

   Vioset_State(pnt_palette,0);
   mem_free (pnt_palette);
}
*/

static void save_redraw_thread(void*)
{
   VIOMODEINFO vio_mode_info;
   USHORT  us_save_redraw_cmd;
   int cnt;
   void* pnt_map_buf = mem_alloc (def_map_size);

   forever
   {
      VioSavRedrawWait(VSRWI_SAVEANDREDRAW,&us_save_redraw_cmd,0);

      if (us_save_redraw_cmd == VSRWN_SAVE)
      {
         vio_mode_info.cb = sizeof(VIOMODEINFO);
         VioGetMode(&vio_mode_info,0);
         memcpy (pnt_map_buf, map_byte_pnt, def_map_size);
      }
      else
      {
         PVIOPALSTATE pnt_save_palette;
         PVIOPALSTATE pnt_tmp_palette;

         VioSetMode(&vio_mode_info,0);

         pnt_save_palette = (PVIOPALSTATE) mem_alloc(sizeof(VIOPALSTATE)+30);
         pnt_tmp_palette  = (PVIOPALSTATE) mem_alloc(sizeof(VIOPALSTATE)+30);

         pnt_save_palette->cb     = sizeof(VIOPALSTATE)+30;
         pnt_save_palette->type   = 0;   /* get palette registers    */
         pnt_save_palette->iFirst = 0;   /* starting with register 0 */

         VioGetState(pnt_save_palette,0);

         memcpy(pnt_tmp_palette,pnt_save_palette,pnt_save_palette->cb);

         forcnt (cnt,16) pnt_tmp_palette->acolor[cnt] = 0;

         VioSetState(pnt_tmp_palette,0);

         memcpy (map_byte_pnt, pnt_map_buf, def_map_size);

         VioSetState(pnt_save_palette,0);

         mem_free (pnt_save_palette);
         mem_free (pnt_tmp_palette);
      }
   }
}

/*
static void mode_thread(void*)
{
   USHORT us_mode_cmd;

   forever
   {
      VioModeWait(0,&us_mode_cmd,0);
      set_graf_mode();
   }
}
*/

#endif /* VIO_OS2 */

static void set_graf_mode()
{
#ifdef VIO_OS2
   VioSetMode(&vio_graf_mode_info,0);
   //set_color_table();
   //set_palette();
#endif

#ifdef VIO_DOS
   REGS regs;
   regs.w.ax = 0x0000 + 0x0012;
   int386 (0x10, &regs, &regs);
   regs.w.ax = 0;
   int386 (real_mode_server_inter_num, &regs, &regs);
#endif
}

static void set_text_mode()
{
#ifdef VIO_OS2
   VioSetMode(&vio_text_mode_info,0);
#endif

#ifdef VIO_DOS
   REGS regs;
   regs.w.ax = 0x0000 + prev_mode_num;
   int386 (0x10, &regs, &regs);
#endif
}

void vio_on()
{
   mac_assert(!on_flg);
   set_graf_mode();
   vio_fill(0);
   on_flg=def_yes;
}

void vio_off()
{
   mac_assert(on_flg);
   set_text_mode();
   on_flg=def_no;
}

void vio_fill(byte c)
{
   memset (map_byte_pnt, c, def_map_size);
}

void vio_get_img (int x1, int y1, int x2, int y2, void* pnt_tar)
{
   mac_assert (on_flg);

   mac_assert (x1 >= 0);
   mac_assert (y1 >= 0);
   mac_assert (x1 <= x2);
   mac_assert (y1 <= y2);
   mac_assert (x2 <  def_width);
   mac_assert (y2 <  def_height);

   register byte* pnt_byte_src = map_byte_pnt + def_width*16*y1 + x1;
   register int width = x2 - x1 + 1;
   register int cnt = (y2 - y1 + 1) * 16;

   while (cnt--)
   {
      memcpy(pnt_tar, pnt_byte_src, width);
      mac_change_type_of(pnt_tar,byte*) += width;
      pnt_byte_src += def_width;
   }
}

void vio_put_img (int x1, int y1, int x2, int y2, void* pnt_src)
{
   mac_assert (on_flg);

   mac_assert (x1 >= 0);
   mac_assert (y1 >= 0);
   mac_assert (x1 <= x2);
   mac_assert (y1 <= y2);
   mac_assert (x2 <  def_width);
   mac_assert (y2 <  def_height);

   register byte* pnt_byte_tar = map_byte_pnt + def_width*16*y1 + x1;
   register int width = x2 - x1 + 1;
   register int cnt = (y2 - y1 + 1) * 16;

   while (cnt--)
   {
      memcpy(pnt_byte_tar, pnt_src, width);
      mac_change_type_of(pnt_src,byte*) += width;
      pnt_byte_tar += def_width;
   }
}

int vio_get_width()
{
   return def_width;
}

int vio_get_height()
{
   return def_height;
}

static void ctor()
{
#ifdef VIO_OS2
   set_video_map_base();
   set_vio_mode_info();

   begin_thread (save_redraw_thread,16384,NULL);
   //begin_thread (mode_thread,16384,NULL);
#endif

#ifdef VIO_DOS
   REGS regs;

   real_mode_server_inter_num = *(byte*)(0xbfff8);

   regs.w.ax = 0x0f00;
   int386 (0x10, &regs, &regs);
   prev_mode_num = regs.h.al;
#endif
}

static void dtor()
{
   if (on_flg) vio_off();
}

static cls_infiniter infiniter(ctor, dtor);

#endif  /* VIO_AVAIL */
