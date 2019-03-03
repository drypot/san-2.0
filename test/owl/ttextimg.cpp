/*
   11.04
*/

#include <pub\common.hpp>
#include <vio\textwin.hpp>
#include <fnt\engfont.hpp>

class TestWindow : public TWindow
{
   private:
      TextImage* pImage;
      char ch;

   private:
      void Paint(TDC&,BOOL,TRect&);

      void EvLButtonDown(UINT, TPoint&);
      void EvRButtonDown(UINT, TPoint&);
      void EvChar(UINT, UINT, UINT);


      void DrawImage();

   public:
      TestWindow(TWindow* = 0);

      DECLARE_RESPONSE_TABLE(TestWindow);
};

DEFINE_RESPONSE_TABLE1(TestWindow, TWindow)
   EV_WM_CHAR,
   EV_WM_LBUTTONDOWN,
   EV_WM_RBUTTONDOWN,
END_RESPONSE_TABLE;

TestWindow::TestWindow(TWindow* parent) : pImage(NULL), ch('0')
{
   Init(parent,0,0);
   pImage = new TextImage(40,20);
   DrawImage();
}

void TestWindow::DrawImage()
{
   int x,y,w,h;
   void* pFont;

   w = pImage->GetWidth();
   h = pImage->GetHeight();


   forcnt (y,h)
   {
      pFont = EngFont(ch);
      ch = (ch + 1) % 128;
      forcnt (x,w)
         pImage->Put8(x, y, pFont);
   }
}

void TestWindow::Paint(TDC& dc, BOOL, TRect&)
{
   int w = pImage->GetWidth()*8;
   int h = pImage->GetHeight()*16;

   TMemoryDC memoryDC(dc);
   TBitmap bitmap(w, h, 1, 1, (void*)pImage->GetImageBase());

   memoryDC.SelectObject(bitmap);
   dc.SetStretchBltMode(COLORONCOLOR);
   //dc.SetROP2(R2_COPYPEN);
   dc.SelectObject(TBrush(TColor(255,0,0)));
   //dc.SetTextColor(TColor(255,0,0));
   //dc.SetBkColor(TColor(0,0,255));
   dc.BitBlt(0, 0, w, h, memoryDC, 0, 0, SRCCOPY);
   //dc.StretchBlt(0, 0, w, h, memoryDC, 0, 0, w, h,SRCCOPY);
}

void TestWindow::EvChar(UINT , UINT , UINT)
{
   DrawImage();
   Invalidate();
}

void TestWindow::EvLButtonDown(UINT, TPoint&)
{
   DrawImage();
   Invalidate();
}

void TestWindow::EvRButtonDown(UINT, TPoint&)
{
}

/*
void TestBase()
{
}


void TestScroll()
{
   TextWindow textwin;
   TextImage textimg(40,20);

   textimg.Fill(0xAA);
   textimg.Inverse();
   textimg.ClearRect(1,1,38,18);
   textimg.Normal();
   textimg.ClearRect(2,2,36,16);
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollUp();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollUp();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollDown();
   textwin.Draw(textimg);
   Pause();

   textimg.ScrollDown();
   textwin.Draw(textimg);
}

*/

class App : public TApplication
{
   public:

      App() : TApplication() {}

      void InitMainWindow()
      {
         SetMainWindow(new TFrameWindow(0, "Test TextImage", new TestWindow));
      }
};

void Main()
{
   App().Run();
}
