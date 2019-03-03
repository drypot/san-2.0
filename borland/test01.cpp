/*
   scan.cpp
*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/misc.hpp>
#include <vio/textbrd.hpp>
#include <win/window.hpp>
#include <win/spcdlg.hpp>

class cls_test_window : public cls_window
{
   private:

      cls_text_brd* txb;
      flag flg_txb_invalid;

   public:

      cls_test_window(TWindow* parent = 0);
      ~cls_test_window();

      void redraw();
      void pcs_key_event(cls_key_event&);
      void paint (HDC);
      void SetupWindow();

      void EvLButtonDown(uint, TPoint&);
      void EvSize(uint sizeType, TSize& size);

      DECLARE_RESPONSE_TABLE(cls_test_window);
};

cls_test_window::cls_test_window (TWindow* parent) :
   cls_window(parent), flg_txb_invalid(def_no)
{
   txb = new cls_text_brd(60,20);
   Attr.W = 60*8;
   Attr.H = 20*16;
   Attr.Style &= ~WS_VISIBLE;
}

cls_test_window::~cls_test_window ()
{
   delete txb;
}

void cls_test_window::redraw()
{
   int i,j;
   static char ch = 'A';

   if (!flg_txb_invalid)
   {
      forcnt(i, txb->get_height())
      {
         txb->set_xy(0,i);
         forcnt(j, txb->get_width()) txb->write(ch);
      }
      ch++;
      if (ch==127) ch = 'A';
   }
   Invalidate(FALSE);
}

void cls_test_window::pcs_key_event(cls_key_event& key_event)
{
   redraw();
/*   if (key_event.get_code() == def_key_f4)
   {
      int i;

      cls_spc_dlg dlg;
      dlg.exec();
      txb->set_x(0);
      forcnt (i, dlg.spc_page.cnt) txb->write(dlg.spc_page.ary_c16_contents[i]);
      txb->set_y_rel(1);
      if (txb->get_y() == txb->get_height()) txb->set_y(0);
      UpdateWindow();
   } */
}

void cls_test_window::paint (HDC hdc)
{
   txb->invalidate();
   txb->draw(hdc);
}

void cls_test_window::SetupWindow()
{
   cls_window::SetupWindow();
   set_frame_size_from_client(Parent->HWindow, txb->get_width()*8, txb->get_height()*16);
   set_frame_pos_center(Parent->HWindow);
}

void cls_test_window::EvLButtonDown(uint, TPoint&)
{
}

void cls_test_window::EvSize(uint sizeType, TSize& size)
{
   if (sizeType != SIZE_MINIMIZED)
   {
      int cx = size.cx / 8;
      int cy = size.cy / 16;

      flg_txb_invalid = cx < 10 || cy < 3;
      if (flg_txb_invalid)
      {
         txb = new cls_text_brd(5,3);
         txb->write("Invlid Size");
      }
      else
      {
         txb = new cls_text_brd(cx, cy);
      }
   }
}

DEFINE_RESPONSE_TABLE1(cls_test_window, cls_window)
   EV_WM_LBUTTONDOWN,
   EV_WM_SIZE,
END_RESPONSE_TABLE;

class cls_app : public TApplication
{
   public:

      cls_app() {}

      void InitMainWindow()
      {
         TFrameWindow* frame = new cls_text_frame_window(0, "test_bitmap", new cls_test_window);
         frame->Attr.Style &= ~WS_VISIBLE;
         SetMainWindow(frame);
      }
};

int pcs_main()
{
   return cls_app().Run();
}

