                                                                                                                        /*
--------------------------------------------------------------------------------
   win\spcdlg.cpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/dir.hpp>
#include <pub/point.hpp>
#include <pub/init.hpp>
#include <pub/misc.hpp>
#include <cnt/array.hpp>
#include <vio/textbrd.hpp>
#include <key/mac.hpp>
#include <win/spcdlg.hpp>

#define def_sel_brd_width   ( 16 )
#define def_sel_brd_height  ( 12 )
#define def_sel_brd_size    ( def_sel_brd_width * def_sel_brd_height )

#define def_win_width       ( 1+ 1+8+1 +def_sel_brd_width*2 + 1 +1 )
#define def_win_height      ( 1+ 1+def_sel_brd_height +1 + 1 )

#define def_page_x          ( 1+8+1 +1 )
#define def_page_y          ( 1 )

#define def_inp_line_x      ( 1+8+1 +1 )
#define def_inp_line_y      ( 1 + def_sel_brd_height + 1 )
#define def_inp_line_width  ( 16 )

#define def_menu_x          ( 2 )
#define def_menu_y          ( 1 )
#define def_menu_width      ( 8 )

#define def_null_char 0

struct cls_extent
{
   char* name_pch;
   int char_list_cnt;
   int char_list_inx;
};

static cls_extent extent_ary[]=
{
   { "�q����ѡ"  , 1, 0 },
   { "��ѡ"      , 2, 1 },
   { "�e��"      , 1, 3 },
   { "��ѡ"      ,10, 4 },
   { "���"      , 1,14 },
   { "�e�i"      , 5,15 },
   { "�i�a�U"    , 4,20 },
   { "����"      , 2,24 },
   { "���a"      , 2,26 },
   { "�a���a"    , 2,28 },
   { "�a˥"      , 2,30 },
   { "�ᯡ�a"    , 2,32 }
};

static char* char_list_ach_ary[]=
{
   "ԁԂԃԄԅԆԇԈԉԊԋԌԍԎԏԐԑԒԓԔԕԖԗԘԙԚԛԜԝԞԟԠԡԢԣԤԥԦԧԨԩԪԫԬԭԮԯ԰ԱԲԳԴԵԶԷԸԹԺԻԼԽԾԿ������������������������������������������������������������������������������������������������������������������������������",
   "�1�2�3�4�5�6�7�8�9�:�;�<�=�>�?�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\\�]�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~ّْٕٖٜٟٓٔٗ٘ٙٚٛٝٞ٠",
   "١٢٣٤٥٦٧٨٩٪٫٬٭ٮٯٰٱٲٳٴٵٶٷٸٹٺٻټٽپٿ����������������������������������������������������������������������������",
   "�1�2�3�4�5�6�7�8�9�:�;�<�=�>�?�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\\�]�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~ܑ",
   "ܱܴܷܸܹܻܼܾܲܳܵܶܺܽ",
   "ܿ��������������������������",
   "����������������������������������������������������",
   "������������������������������",
   "�A�B�C�D�E�F�G�H�I�J�K�L�M�N",
   "�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\\",
   "�]�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v",
   "�w�x�y�z�{�|�}�~ݑݒݓݔݕݖݗ",
   "������������������",
   "ݘݙݚݛݜݝݞݟݠ",
   "ۣۡۢۤۥۦۧۨ۩۪ۭ۫۬ۮۯ۰۱۲۳۴۵۶۷۸۹ۺۻۼ۽۾ۿ��������������������������������������������������������������������������",
   "ڡڢڣڤڥڦڧڨکڪګڬڭڮگڰڱڲڳڴڵڶڷڸڹںڻڼڽھ",
   "ڿ����������������������������������������",
   "��",
   "��������������������������������������������������������������������",
   "����������������",
   "�1�2�3�4�5�6�7�8�9�:�;�<�=�>�?�J�K�L�M�N�O�P�k�l�m�n�o�pڝڞڟڠ",
   "�@�A�B�C�D�E�F�G�H�I",
   "�Q�R�S�T�U�V�W�X�Y�Z�[�\\�]�^�_�`�a�b�c�d�e�f�g�h�i�j",
   "�q�r�s�t�u�v�w�x�y�z�{�|�}�~ڑڒړڔڕږڗژڙښڛڜ",
   "ݡݢݣݤݥݦݧݨݩݪݫݬݭݮݯݰݱݲݳݴݵݶݷݸݹݺݻݼݽݾݿ��������������������������������������������������������������������������������������������������������",
   "�1�2�3�4�5�6�7�8�9�:�;�<�=�>�?�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\\�]�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~ޑޒޓޔޕޖޗޘ",
   "�1�2�3�4�5�6�7�8�9�:",
   "�@�A�B�C�D�E�F�G�H�I",
   "�Q�R�S�T�U�V�W�X�Y�Z�[�\\�]�^�_�`�a�b�c�d�e�f�g�h",
   "�q�r�s�t�u�v�w�x�y�z�{�|�}�~ۑےۓ۔ەۖۗۘۙۚ",
   "ܡܢܣܤܥܦܧܨܩܪܫܬܭܮܯܰ",
   "�1�2�3�4�5�6�7�8�9�:�;�<�=�>�?�@",
   "ޡޢޣޤޥަާިީުޫެޭޮޯްޱ޲޳޴޵޶޷޸޹޺޻޼޽޾޿����",
   "������������������������������������������������������������������"
};

static tem_static_array<char16,def_sel_brd_size> cur_char_list;
static cls_boxed_point iter (def_sel_brd_width, def_sel_brd_size);
static cls_boxed_point extent (1, mac_cnt_of(extent_ary));
static bool exit_flg;

static tem_static_array<char16,def_spc_page_cmax> contents;
static int cnt;

static HWND frame;
static HWND client;

static cls_mac_runner* mac_runner;
static cls_mac_bin* mac_bin;
static cls_text_brd* brd;

static cls_spc_dlg* dlg;

inline char16 get_cur_char()
{
   return *cur_char_list.get_pnt(iter.get_index());
}

static void inverse_extent()
{
   brd->inverse_rect (def_menu_x , def_menu_y + extent.get_index(), def_menu_width, 1);
}

static void set_cur_char_list(int arg_inx)
{
   inverse_extent();
   extent.set_index(arg_inx);

   int inx = 0;
   int i;
   char* src;

   forcnt (i, extent_ary[extent.get_index()].char_list_cnt)
   {
      src = char_list_ach_ary [ extent_ary [ extent.get_index() ] . char_list_inx + i ];
      while ( *src )
      {
         cls_wchar wch = read_c16(&src);
         mac_assert (inx < def_sel_brd_size);
         *cur_char_list.get_pnt(inx++) = wch.c16;
      }
      while (inx % def_sel_brd_width)
      {
         mac_assert (inx < def_sel_brd_size);
         *cur_char_list.get_pnt(inx++) = def_null_char;
      }
   }

   while (inx < def_sel_brd_size)
   {
      *cur_char_list.get_pnt(inx++) = def_null_char;
   }

   int x;
   int y;
   forcnt (y, def_sel_brd_height)
   {
      brd->set_xy (def_page_x , def_page_y + y );
      forcnt (x, def_sel_brd_width)
      {
         char16 ch = *cur_char_list.get_pnt(y * def_sel_brd_width + x);
         if (ch) brd->write (ch);
         else brd->write_space(2);
      }
   }

   inverse_extent();
}

static void set_cur_char_list_rel(int inx_rel)
{
   set_cur_char_list (extent.get_index() + inx_rel);
}

static void first_char_list()
{
   set_cur_char_list (0);
}

static void last_char_list()
{
   set_cur_char_list (mac_cnt_of(extent_ary) - 1);
}

static void update_stock_line()
{
   brd->set_xy(def_inp_line_x , def_inp_line_y);

   int index = get_max (0, cnt - (def_inp_line_width-1));
   int i=0;

   while (i < def_inp_line_width-1 && index < cnt)
   {
      brd->write(*contents.get_pnt(index));
      index++;
      i++;
   }
   brd->write('<');
   brd->write_space((def_inp_line_width - i) * 2 - 1);
}

static bool append_to()
{
   bool rc = def_error;

   if (get_cur_char() != def_null_char)
   {
      *contents.get_pnt(cnt++) = get_cur_char();
      rc = def_ok;
   }

   return rc;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_ok()
{
   if (!cnt) append_to();
   exit_flg = def_yes;
}

void pdf_cancel()
{
   exit_flg = def_yes;
}

void pdf_left()
{
   iter.set_x_rel(-1);
}

void pdf_right()
{
   iter.set_x_rel(1);
}

void pdf_up()
{
   iter.set_y_rel(-1);
}

void pdf_down()
{
   iter.set_y_rel(1);
}

void pdf_home()
{
   if (iter.is_x_first()) iter.set_first();
   else iter.set_x_first();
}

void pdf_end()
{
   if (iter.is_x_last()) iter.set_last();
   else iter.set_x_last();
}

void pdf_page_up()
{
   set_cur_char_list_rel(-1);
}

void pdf_page_down()
{
   set_cur_char_list_rel(1);
}

void pdf_left_acc()
{
   iter.set_x_rel(-4);
}

void pdf_right_acc()
{
   iter.set_x_rel(4);
}

void pdf_up_acc()
{
   iter.set_y_first();
}

void pdf_down_acc()
{
   iter.set_y_last();
}

void pdf_home_acc()
{
   iter.set_y_first();
}

void pdf_end_acc()
{
   iter.set_y_last();
}

void pdf_page_up_acc()
{
   first_char_list();
}

void pdf_page_down_acc()
{
   last_char_list();
}

int32 pdf_stock_add()
{
   return cnt < def_spc_page_cmax ? append_to() : def_error;
}

int32 pdf_stock_discard()
{
   return cnt ? (cnt--, def_ok) : def_error;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void client_update()
{
   update_stock_line();
   brd->set_xy(def_page_x + iter.get_x()*2 , def_page_y + iter.get_y());
}

static void client_draw(HPS hps)
{
   brd->draw(hps);
}

static void client_draw()
{
   HPS hps = WinGetPS(client);
   client_draw(hps);
   WinReleasePS(hps);
}

static void client_key(cls_key_event* key_event)
{
   mac_assert(mac_runner);

   if (key_event->is_valid())
   {
      //int cnt = key_event->cnt;
      //while (cnt--)
      //{
         if (mac_runner->scan(key_event) == def_kb_scan_match)
         {
            mac_runner->execute();
            client_update();
            client_draw();
         }
      //}
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static MRESULT client_wm_char(MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event((MPARAM)mp1, (MPARAM)mp2);
   client_key(&key_event);
   return (MRESULT) TRUE; // processed
}

static MRESULT client_wm_create(HWND /*hwnd*/)
{
   int i;

   brd = new cls_text_brd(def_win_width, def_win_height);

   brd->set_fg(def_clr_black);
   brd->set_bg(def_clr_white);
   brd->erase();
   brd->set_wide_cursor(def_yes);
   brd->show_cursor(def_yes);

   forcnt (i, mac_cnt_of(extent_ary))
   {
      brd->set_xy(def_menu_x, def_menu_y+i);
      brd->write(extent_ary[i].name_pch);
   }

   brd->set_fg(def_clr_white);
   brd->set_bg(def_clr_black);

   inverse_extent();

   cnt = 0;
   set_cur_char_list_rel(0);

   client_update();

   return 0; // continue creation
}

static MRESULT client_wm_destroy()
{
   delete brd;

   dlg->cnt = cnt;
   memcpy (dlg->contents, contents.get_base_pnt(), cnt * sizeof(char16));

   return 0; // reserved
}

static MRESULT client_wm_paint(HPS hps)
{
   brd->invalidate();
   client_draw(hps);
   return 0; // reserved
}

static MRESULT EXPENTRY client_proc(HWND hwnd, ULONG mline, MPARAM mp1, MPARAM mp2)
{
   MRESULT rc;

   switch (mline)
   {
      case WM_CHAR :    return client_wm_char(mp1, mp2);
      case WM_CREATE :  return client_wm_create(hwnd);
      case WM_DESTROY : return client_wm_destroy();
      case WM_PAINT :
         {
            HPS hps = WinBeginPaint (hwnd, 0, 0);
            rc = client_wm_paint(hps);
            WinEndPaint(hps);
         }
         return rc;
   }

   return WinDefWindowProc(hwnd, mline, mp1, mp2);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void frame_create()
{
   static bool registered_flg;
   static char client_cname[] = "spc_dlg_class";

   if (!registered_flg)
   {
      registered_flg = def_yes;
      WinRegisterClass (
         hab,
         client_cname,
         client_proc,
         CS_HITTEST,
         0
      );
   }

   ULONG flFrameFlags =
      //FCF_ICON |
      //FCF_MENU |
      FCF_SYSMODAL |
      FCF_NOBYTEALIGN |
      FCF_TITLEBAR |
      //FCF_SYSMENU |
      FCF_DLGBORDER
      //FCF_MINMAX |
      //FCF_HIDEBUTTON |
      //FCF_TASKLIST
      ;

   frame = WinCreateStdWindow (
      dlg->parent,
      /*WS_VISIBLE*/ 0,
      &flFrameFlags,
      client_cname,
      "Special Character Selector",
      WS_VISIBLE,
      0,
      0,
      &client
   );

   LONG cx_screen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
   //LONG cy_screen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

   RECTL rectl;

   rectl.xLeft   = 0;
   rectl.xRight  = def_win_width*8;
   rectl.yBottom = 0;
   rectl.yTop    = def_win_height*16;

   WinCalcFrameRect(frame, &rectl, FALSE);

   int frame_width  = rectl.xRight - rectl.xLeft;
   int frame_height = rectl.yTop - rectl.yBottom;

   int x = get_min(dlg->x + frame_width, cx_screen) - frame_width;
   int y = get_max(0, dlg->y - 1 - frame_height);

   WinSetWindowPos(
      frame,
      0,
      x, y,
      frame_width, frame_height,
      SWP_MOVE | SWP_SIZE
   );

   set_frame_activate(frame);
}

static void frame_destroy()
{
   WinDestroyWindow(frame);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_spc_dlg::cls_spc_dlg(HWND arg_parent, int arg_x, int arg_y, HWND arg_owner) :
   parent(arg_parent),
   x(arg_x),
   y(arg_y),
   owner(arg_owner),
   cnt(0)
{
}

void cls_spc_dlg::execute ()
{
   BOOL rc;

   dlg = this;
   exit_flg = def_no;

   rc = owner ? WinIsWindowEnabled(owner) : FALSE;
   if (rc) WinEnableWindow(owner, FALSE);

   frame_create();
   while (!exit_flg && WinGetMsg (hab, &qmsg, 0, 0, 0)) WinDispatchMsg (hab, &qmsg);
   frame_destroy();

   if (rc) WinEnableWindow(owner, TRUE);
}

#include <macro/tmp/spcdlg.def>
#include <macro/tmp/spcdlg.map>

static void ctor()
{
   try
   {
      mac_bin = new cls_mac_bin(cls_fname("@bindir/../macro/spcdlg.bin").get_path());
      mac_runner = new cls_mac_runner(mac_bin, mac_mapper);
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info("func: win/spcdlg.cpp/ctor()\ninfo: macro loading error\n");
      throw;
   }
}

static cls_initer initer(ctor);
