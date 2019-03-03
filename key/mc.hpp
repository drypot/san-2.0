                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mc.hpp -- meta code
   copyright(C) kyuhyun park
   1994.10.22
--------------------------------------------------------------------------------                                        */

#ifdef def_key_mc_hpp
#error 'key/mc.hpp' duplicated.
#endif

#define def_key_mc_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_keyevent_hpp
#include <key/keyevent.hpp>
#endif

#ifndef def_key_mcp_hpp
#include <key/mcp.hpp>
#endif

#define def_mc_mask_lang       0xff000000u
#define def_mc_mask_attr       0x00ff0000u
#define def_mc_mask_type       0x0000ff00u
#define def_mc_mask_offset     0x000000ffu

#define def_mc_lang_eng        0x01000000u
#define def_mc_lang_han        0x02000000u

#define def_mc_attr_no_combi   0x00010000u
#define def_mc_attr_caps_lock  0x00020000u

#define def_mc_type_h1         0x00000100u
#define def_mc_type_h2         0x00000200u
#define def_mc_type_h3         0x00000300u
#define def_mc_type_h4         0x00000400u

enum
{
   def_mc_offset_h1_null,
   def_mc_offset_h1_g,
   def_mc_offset_h1_gg,
   def_mc_offset_h1_n,
   def_mc_offset_h1_d,
   def_mc_offset_h1_dd,
   def_mc_offset_h1_r,
   def_mc_offset_h1_m,
   def_mc_offset_h1_b,
   def_mc_offset_h1_bb,
   def_mc_offset_h1_s,
   def_mc_offset_h1_ss,
   def_mc_offset_h1_y,
   def_mc_offset_h1_j,
   def_mc_offset_h1_jj,
   def_mc_offset_h1_c,
   def_mc_offset_h1_k,
   def_mc_offset_h1_t,
   def_mc_offset_h1_p,
   def_mc_offset_h1_h
};

enum
{
   def_mc_offset_h2_null,
   def_mc_offset_h2_ia,
   def_mc_offset_h2_iai,
   def_mc_offset_h2_iaa,
   def_mc_offset_h2_iaai,
   def_mc_offset_h2_ai,
   def_mc_offset_h2_aii,
   def_mc_offset_h2_aai,
   def_mc_offset_h2_aaii,
   def_mc_offset_h2_au,
   def_mc_offset_h2_auia,
   def_mc_offset_h2_auiai,
   def_mc_offset_h2_aui,
   def_mc_offset_h2_aau,
   def_mc_offset_h2_ua,
   def_mc_offset_h2_uaai,
   def_mc_offset_h2_uaaii,
   def_mc_offset_h2_uai,
   def_mc_offset_h2_uaa,
   def_mc_offset_h2_u,
   def_mc_offset_h2_ui,
   def_mc_offset_h2_i,
};

enum
{
   def_mc_offset_h3_null,
   def_mc_offset_h3_g,
   def_mc_offset_h3_gg,
   def_mc_offset_h3_gs,
   def_mc_offset_h3_n,
   def_mc_offset_h3_nj,
   def_mc_offset_h3_nh,
   def_mc_offset_h3_d,
   def_mc_offset_h3_r,
   def_mc_offset_h3_rg,
   def_mc_offset_h3_rm,
   def_mc_offset_h3_rb,
   def_mc_offset_h3_rs,
   def_mc_offset_h3_rt,
   def_mc_offset_h3_rp,
   def_mc_offset_h3_rh,
   def_mc_offset_h3_m,
   def_mc_offset_h3_b,
   def_mc_offset_h3_bs,
   def_mc_offset_h3_s,
   def_mc_offset_h3_ss,
   def_mc_offset_h3_y,
   def_mc_offset_h3_j,
   def_mc_offset_h3_c,
   def_mc_offset_h3_k,
   def_mc_offset_h3_t,
   def_mc_offset_h3_p,
   def_mc_offset_h3_h
};

enum
{
   def_mc_offset_h4_null,
   def_mc_offset_h4_g,
   def_mc_offset_h4_gg,
   def_mc_offset_h4_n,
   def_mc_offset_h4_d,
   def_mc_offset_h4_garbage_00,
   def_mc_offset_h4_r,
   def_mc_offset_h4_m,
   def_mc_offset_h4_b,
   def_mc_offset_h4_garbage_01,
   def_mc_offset_h4_s,
   def_mc_offset_h4_ss,
   def_mc_offset_h4_y,
   def_mc_offset_h4_j,
   def_mc_offset_h4_garbage_02,
   def_mc_offset_h4_c,
   def_mc_offset_h4_k,
   def_mc_offset_h4_t,
   def_mc_offset_h4_p,
   def_mc_offset_h4_h
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

class cls_mc
{
   private:

      uint32 val_u32;

   public:

      cls_mc (uint32 arg_val = 0) : val_u32 (arg_val)
      {
      }

      cls_mc (cls_key_event* key_event, cls_mcp* mcp)
      {
         set(key_event, mcp);
      }

      void   reset ();

      void   set (cls_key_event*, cls_mcp* mcp);
      void   set (uint32, uint32, uint32, uint32);

      uint32 get_lang   ();
      uint32 get_attr   ();
      uint32 get_type   ();
      uint32 get_offset ();

      void   set_lang   (uint32);
      void   set_attr   (uint32);
      void   set_type   (uint32);
      void   set_offset (uint32);

      bool   is_valid   ()
      {
         return val_u32 != 0;
      }

   private:

      void   make_char     (cls_key_event*, cls_mcp* mcp);
      void   make_ctrl     (cls_key_event*);
      void   make_pad_char (cls_key_event*);
      void   make_action   (cls_key_event*);
};
