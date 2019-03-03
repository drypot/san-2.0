                                                                                                                        /*
--------------------------------------------------------------------------------
   win/window.hpp
   copyright(c) kyuhyun park
   1996.04.05
--------------------------------------------------------------------------------                                        */

#ifdef def_win_window_hpp
#error 'win/window.hpp' duplicated.
#endif

#define def_win_window_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_keyevent_hpp
#include <key/keyevent.hpp>
#endif

#ifndef def_key_coder_hpp
#include <key/coder.hpp>
#endif

#ifndef def_mac_keybind_hpp
#include <key/mac.hpp>
#endif

#if defined def_owlpm

class cls_window_mac_runner;

class cls_window : public TWindow
{
   private:

      cls_window_mac_runner* window_mac_runner;
      cls_mcp_list_iter* mcp_list_iter;
      cls_coder* coder;

   public:
      cls_window(TWindow* parent = 0);
      ~cls_window();

      void enable_mac(cls_mac_bin*);
      void enable_char();
      void next_mcp();

      virtual void ev_key(cls_key_event*);
      virtual int32 ev_pdf(int32 pdf_id);
      virtual void ev_char(char16 code, int action);
      virtual void ev_paint(HDC);

   protected:

      void    EvPaint(void);
      LRESULT EvKeyDown(WPARAM, LPARAM);
      LRESULT EvKeyUp(WPARAM, LPARAM);
      LRESULT EvMatchMnemonic(WPARAM, LPARAM);

      DECLARE_RESPONSE_TABLE(cls_window);
};

class cls_frame_window : public TFrameWindow
{
   public:

      cls_text_frame_window(TWindow* parent, const char* title = 0, TWindow* client = 0, BOOL shirink_to_client = FALSE);

   protected:

      LRESULT EvEraseBackground(WPARAM, LPARAM);

      DECLARE_RESPONSE_TABLE(cls_frame_window);
};

class cls_text_frame_window : public cls_frame_window
{
   public:

      cls_text_frame_window(TWindow* parent, const char* title = 0, TWindow* client = 0, BOOL shirink_to_client = FALSE);

   protected:

      LRESULT EvAdjustWindowPos(WPARAM, LPARAM);

      DECLARE_RESPONSE_TABLE(cls_text_frame_window);
};

#endif
