                                                                                                                        /*
--------------------------------------------------------------------------------
   key/keyevent.hpp
   copyright(C) kyuhyun park
   1993.07.13
--------------------------------------------------------------------------------                                        */

#ifdef def_key_keyevent_hpp
#error 'key/keyevent.hpp' duplicated.
#endif

#define def_key_keyevent_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_key_hpp
#include <key/key.hpp>
#endif

class cls_key_event
{
   public:

      bool   make_flg;
      uint16 code_u16;
      uint16 shifted_u16;
      uint16 toggled_u16;
      uint16 cnt;

   public:

      cls_key_event () : code_u16 (0)
      {
      }

      bool is_valid ()
      {
         return code_u16 != 0;
      }

#if defined def_pm
      cls_key_event (MPARAM mp1, MPARAM mp2)
      {
         set(mp1, mp2);
      }

      void set(MPARAM, MPARAM);
#endif

#if defined def_dos || (defined def_os2 && !defined def_pm)
      void set();
#endif

      void set (cls_key_frame*);

      uint16 get_shifted          ();
      uint16 get_toggled          ();

      uint16 is_shifted_rshift   ();
      uint16 is_shifted_lshift   ();
      uint16 is_shifted_rctrl    ();
      uint16 is_shifted_lctrl    ();
      uint16 is_shifted_ralt     ();
      uint16 is_shifted_lalt     ();
      uint16 is_shifted_rmachine ();
      uint16 is_shifted_lmachine ();

      uint16 is_shifted_num_lock  ();
      uint16 is_shifted_caps_lock ();

      uint16 is_shifted_shift     ();
      uint16 is_shifted_ctrl      ();
      uint16 is_shifted_alt       ();
      uint16 is_shifted_machine   ();

      uint16 is_toggled_rshift   ();
      uint16 is_toggled_lshift   ();
      uint16 is_toggled_rctrl    ();
      uint16 is_toggled_lctrl    ();
      uint16 is_toggled_ralt     ();
      uint16 is_toggled_lalt     ();
      uint16 is_toggled_rmachine ();
      uint16 is_toggled_lmachine ();

      uint16 is_toggled_num_lock  ();
      uint16 is_toggled_caps_lock ();

      uint16 is_toggled_shift     ();
      uint16 is_toggled_ctrl      ();
      uint16 is_toggled_alt       ();
      uint16 is_toggled_machine   ();

      uint16 is_make_event        ();
      uint16 is_break_event       ();

      uint16 get_code           ();
      uint16 get_code_type      ();
      uint16 get_code_offset    ();
      uint16 get_char_code_line ();
      uint16 get_char_code_col  ();
};

inline uint16 cls_key_event::get_shifted()           { return shifted_u16; }
inline uint16 cls_key_event::get_toggled()           { return toggled_u16; }

inline uint16 cls_key_event::is_shifted_rshift    () { return shifted_u16 & def_key_mask_rshift;   }
inline uint16 cls_key_event::is_shifted_lshift    () { return shifted_u16 & def_key_mask_lshift;   }
inline uint16 cls_key_event::is_shifted_rctrl     () { return shifted_u16 & def_key_mask_rctrl;    }
inline uint16 cls_key_event::is_shifted_lctrl     () { return shifted_u16 & def_key_mask_lctrl;    }
inline uint16 cls_key_event::is_shifted_ralt      () { return shifted_u16 & def_key_mask_ralt;     }
inline uint16 cls_key_event::is_shifted_lalt      () { return shifted_u16 & def_key_mask_lalt;     }
inline uint16 cls_key_event::is_shifted_rmachine  () { return shifted_u16 & def_key_mask_rmachine; }
inline uint16 cls_key_event::is_shifted_lmachine  () { return shifted_u16 & def_key_mask_lmachine; }

inline uint16 cls_key_event::is_shifted_num_lock  () { return shifted_u16 & def_key_mask_num_lock;  }
inline uint16 cls_key_event::is_shifted_caps_lock () { return shifted_u16 & def_key_mask_caps_lock; }

inline uint16 cls_key_event::is_shifted_shift     () { return shifted_u16 & def_key_mask_shift  ; }
inline uint16 cls_key_event::is_shifted_ctrl      () { return shifted_u16 & def_key_mask_ctrl   ; }
inline uint16 cls_kgy_event::is_shifted_alt       () { return shifted_u16 & def_key_mask_alt    ; }
inline uint16 cls_key_event::is_shifted_machine   () { return shifted_u16 & def_key_mask_machine; }

inline uint16 cls_key_event::is_toggled_rshift    () { return toggled_u16 & def_key_mask_rshift;   }
inline uint16 cls_key_event::is_toggled_lshift    () { return toggled_u16 & def_key_mask_lshift;   }
inline uint16 cls_key_event::is_toggled_rctrl     () { return toggled_u16 & def_key_mask_rctrl;    }
inline uint16 cls_key_event::is_toggled_lctrl     () { return toggled_u16 & def_key_mask_lctrl;    }
inline uint16 cls_key_event::is_toggled_ralt      () { return toggled_u16 & def_key_mask_ralt;     }
inline uint16 cls_key_event::is_toggled_lalt      () { return toggled_u16 & def_key_mask_lalt;     }
inline uint16 cls_key_event::is_toggled_rmachine  () { return toggled_u16 & def_key_mask_rmachine; }
inline uint16 cls_key_event::is_toggled_lmachine  () { return toggled_u16 & def_key_mask_lmachine; }

inline uint16 cls_key_event::is_toggled_num_lock  () { return toggled_u16 & def_key_mask_num_lock;  }
inline uint16 cls_key_event::is_toggled_caps_lock () { return toggled_u16 & def_key_mask_caps_lock; }

inline uint16 cls_key_event::is_toggled_shift     () { return toggled_u16 & def_key_mask_shift   ; }
inline uint16 cls_key_event::is_toggled_ctrl      () { return toggled_u16 & def_key_mask_ctrl    ; }
inline uint16 cls_key_event::is_toggled_alt       () { return toggled_u16 & def_key_mask_alt     ; }
inline uint16 cls_key_event::is_toggled_machine   () { return toggled_u16 & def_key_mask_machine ; }

inline uint16 cls_key_event::is_make_event        () { return make_flg; }
inline uint16 cls_key_event::is_break_event       () { return !make_flg; }

inline uint16 cls_key_event::get_code             () { return code_u16; }
inline uint16 cls_key_event::get_code_type        () { return code_u16 & def_key_mask_code_type; }
inline uint16 cls_key_event::get_code_offset      () { return code_u16 & def_key_mask_code_offset; }

inline uint16 cls_key_event::get_char_code_line   () { return (get_code_offset() & 0x00f0u) / 0x20; }
inline uint16 cls_key_event::get_char_code_col    () { return get_code_offset() & 0x000fu; }

