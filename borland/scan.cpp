/*
   scan.cpp
*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <vio/textbrd.hpp>
#include <win/window.hpp>

class cls_window_test : public cls_window
{
   private:

      cls_text_brd txb;
      char ch;

   public:

      cls_window_test (TWindow* parent = 0);

      void redraw();
      void pcs_key_event(cls_key_event&);
      void paint (HDC);

      void EvLButtonDown(uint, TPoint&);

      DECLARE_RESPONSE_TABLE(cls_window_test);
};

cls_window_test::cls_window_test (TWindow* parent) :
   cls_window(parent), txb(60,20), ch('A')
{
   Attr.W = 60*8;
   Attr.H = 20*16;
}

void cls_window_test::redraw()
{
   int i,j;

   forcnt(i, txb.get_height())
   {
      txb.set_xy(0,i);
      forcnt(j, txb.get_width()) txb.write(ch);
   }
   ch++;
   if (ch == 127) ch = 'A';
   Invalidate(FALSE);
}

void cls_window_test::pcs_key_event(cls_key_event& key_event)
{
   redraw();
}

void cls_window_test::paint (HDC hdc)
{
   txb.invalidate();
   txb.draw(hdc);
}

DEFINE_RESPONSE_TABLE1(cls_window_test, cls_window)
   EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;

void cls_window_test::EvLButtonDown(uint, TPoint&)
{
   if (IsWindowEnabled())
   {
      EnableWindow(FALSE);
   }
   else
   {
      EnableWindow(TRUE);
   }
}

class cls_app : public TApplication
{
   public:

      cls_app() {}

      void InitMainWindow()
      {
         TFrameWindow* frame = new TFrameWindow(0, "test_bitmap", new cls_window_test);
         frame->Attr.W = 60*8;
         frame->Attr.H = 10*16;
         SetMainWindow(frame);
      }
};

int pcs_main()
{
   return cls_app().Run();
}

