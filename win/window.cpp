                                                                                                                        /*
--------------------------------------------------------------------------------
   win/window.cpp
   copyright(c) kyuhyun park
   1996.04.05
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <win/window.hpp>

#if defined def_owlpm

class cls_window_mac_runner : public cls_mac_runner
{
   private:
      cls_window* window;

   public:
      cls_window_mac_runner(cls_window*, cls_mac_bin*);
      int32 execute_pdf(int32);
};

cls_window_mac_runner::cls_window_mac_runner(cls_window* arg_window, cls_mac_bin* mac_bin) :
   cls_mac_runner(mac_bin),
   window(arg_window)
{
}

int32 cls_window_mac_runner::execute_pdf(int32 id)
{
   return window->ev_pdf(id);
}

cls_window::cls_window(TWindow* parent) :
   TWindow (parent), window_mac_runner(NULL), coder(NULL), mcp_list_iter(NULL)
{
   //EnableTransfer();
}

cls_window::~cls_window()
{
   delete window_mac_runner;
   delete coder;
   delete mcp_list_iter;
}

void cls_window::enable_mac(cls_mac_bin* mac_bin)
{
   if (window_mac_runner) delete window_mac_runner;
   window_mac_runner = new cls_window_mac_runner(this, mac_bin);
}

void cls_window::enable_char()
{
   if (coder == NULL) coder = new cls_coder();
   if (mcp_list_iter == NULL) mcp_list_iter = new cls_mcp_list_iter();
   coder->reset();
   mcp_list_iter->reset();
}

void cls_window::next_mcp()
{
   mac_assert (!mcp_list_iter);
   mcp_list_iter->next_mcp();
}

void cls_window::ev_key(cls_key_event* key_event)
{
   if (window_mac_runner && key_event->is_valid())
   {
      switch (window_mac_runner->scan(key_event))
      {
         case def_kb_scan_match :
            window_mac_runner->execute();
            break;

         case def_kb_scan_failed :
            if (coder && mcp_list_iter)
            {
               cls_mc mc(key_event, mcp_list_iter->get_mcp());
               coder->put (&mc);
               while (coder->is_holding())
               {
                  coder->get();
                  ev_char(coder->get_code(), coder->get_action());
               }
            }
            break;
      }
   }
}

int32 cls_window::ev_pdf(int32 /*id*/)
{
   /*
   switch(id)
   {
      case pdf_ :

      case pdf_ :

      default :
         throw cls_xmsg("");
   }
   */
   return 0;
}

void cls_window::ev_char(char16,int)
{
   /*
   switch ()
   {
      case def_ca_direct :
         break;

      case def_ca_open :
         break;

      case def_ca_replace :
         break;

      case def_ca_close:
         break;

      case def_ca_cancel:
         break;
   }
   */
}

void cls_window::ev_paint(HDC /*hps*/)
{
}

void cls_window::EvPaint()
{
   HPS hps = WinBeginPaint (HWindow, 0, 0);
   ev_paint(hps);
   WinEndPaint(hps);
}

LRESULT cls_window::EvKeyDown(WPARAM wParam, LPARAM lParam)
{
   if (IsWindowEnabled())
   {
      cls_key_event key_event((MPARAM)wParam, (MPARAM)lParam);
      ev_key(&key_event);
   }
   return (LRESULT) TRUE;
}

LRESULT cls_window::EvKeyUp(WPARAM wParam, LPARAM lParam)
{
   if (IsWindowEnabled())
   {
      cls_key_event key_event((MPARAM)wParam, (MPARAM)lParam);
      ev_key(&key_event);
   }
   return (LRESULT) TRUE;
}

LRESULT cls_window::EvMatchMnemonic(WPARAM, LPARAM)
{
   return TRUE;
}

DEFINE_RESPONSE_TABLE1(cls_window, TWindow)
   EV_WM_PAINT,
   EV_MESSAGE(WM_KEYDOWN, EvKeyDown),
   EV_MESSAGE(WM_KEYUP, EvKeyUp),
   EV_MESSAGE(WM_MATCHMNEMONIC, EvMatchMnemonic),
END_RESPONSE_TABLE;
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_frame_window::cls_frame_window(TWindow* parent, const char* title, TWindow* client, BOOL shirink_to_client) :
   TFrameWindow(parent, title, client, shirink_to_client)
{
}

LRESULT cls_frame_window::EvEraseBackground(WPARAM, LPARAM)
{
   return FALSE;
}

DEFINE_RESPONSE_TABLE1(cls_frame_window, TFrameWindow)
   EV_MESSAGE(WM_ERASEBACKGROUND, EvEraseBackground),
END_RESPONSE_TABLE;
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_text_frame_window::cls_text_frame_window(TWindow* parent, const char* title, TWindow* client, BOOL shirink_to_client) :
   cls_frame_window(parent, title, client, shirink_to_client)
{
}

LRESULT cls_text_frame_window::EvAdjustWindowPos(WPARAM mp1, LPARAM mp2)
{
   PSWP swp = (PSWP)mp1;

   if (swp->fl & SWP_SIZE)
   {
      RECTL rectl;

      rectl.xLeft   = 0;
      rectl.xRight  = swp->cx;
      rectl.yBottom = 0;
      rectl.yTop    = swp->cy;

      WinCalcFrameRect(HWindow, &rectl, TRUE);

      int client_width  = rectl.xRight - rectl.xLeft;
      int client_height = rectl.yTop - rectl.yBottom;

      rectl.xLeft   = 0;
      rectl.xRight  = client_width - client_width % 8;
      rectl.yBottom = 0;
      rectl.yTop    = client_height - client_height % 16;

      WinCalcFrameRect(HWindow, &rectl, FALSE);

      swp->cx = rectl.xRight - rectl.xLeft;
      swp->cy = rectl.yTop - rectl.yBottom;
   }

   return TFrameWindow::EvAdjustWindowPos(mp1,mp2);
}

DEFINE_RESPONSE_TABLE1(cls_text_frame_window, cls_text_window)
   EV_MESSAGE(WM_ADJUSTWINDOWPOS, EvAdjustWindowPos),
END_RESPONSE_TABLE;

#endif
