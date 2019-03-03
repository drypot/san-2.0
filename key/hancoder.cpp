                                                                                                                        /*
--------------------------------------------------------------------------------
   key/hancoder.cpp
   copyright(C) kyuhyun park
   1994.10.22
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/charlist.hpp>
#include <key/coder.hpp>
#include <key/hancoder.hpp>

enum // forward status list
{
   def_fs_null,
   def_fs_h1, def_fs_h1_aux,
   def_fs_h2, def_fs_h2_aux,
   def_fs_h3, def_fs_h3_aux,
   def_fs_h4, def_fs_h4_aux,
   def_fs_complete,
   def_fs_complete_h4
};

static uint16 h4_to_h3_ary[]=
{
   def_mc_offset_h3_null,
   def_mc_offset_h3_g,
   def_mc_offset_h3_gg,
   def_mc_offset_h3_n,
   def_mc_offset_h3_d,
   def_mc_offset_h3_null,
   def_mc_offset_h3_r,
   def_mc_offset_h3_m,
   def_mc_offset_h3_b,
   def_mc_offset_h3_null,
   def_mc_offset_h3_s,
   def_mc_offset_h3_ss,
   def_mc_offset_h3_y,
   def_mc_offset_h3_j,
   def_mc_offset_h3_null,
   def_mc_offset_h3_c,
   def_mc_offset_h3_k,
   def_mc_offset_h3_t,
   def_mc_offset_h3_p,
   def_mc_offset_h3_h
};

static uint32 h1_pair_ary[][3]=
{
   { def_mc_offset_h1_g, def_mc_offset_h1_g, def_mc_offset_h1_gg },
   { def_mc_offset_h1_d, def_mc_offset_h1_d, def_mc_offset_h1_dd },
   { def_mc_offset_h1_b, def_mc_offset_h1_b, def_mc_offset_h1_bb },
   { def_mc_offset_h1_s, def_mc_offset_h1_s, def_mc_offset_h1_ss },
   { def_mc_offset_h1_j, def_mc_offset_h1_j, def_mc_offset_h1_jj }
};

static uint32 h2_pair_ary[][3]=
{
   { def_mc_offset_h2_au, def_mc_offset_h2_ia,  def_mc_offset_h2_auia   },
   { def_mc_offset_h2_au, def_mc_offset_h2_iai, def_mc_offset_h2_auiai  },
   { def_mc_offset_h2_au, def_mc_offset_h2_i,   def_mc_offset_h2_aui    },
   { def_mc_offset_h2_ua, def_mc_offset_h2_ai,  def_mc_offset_h2_uaai   },
   { def_mc_offset_h2_ua, def_mc_offset_h2_aii, def_mc_offset_h2_uaaii  },
   { def_mc_offset_h2_ua, def_mc_offset_h2_i,   def_mc_offset_h2_uai    },
   { def_mc_offset_h2_u,  def_mc_offset_h2_i,   def_mc_offset_h2_ui     }
};

static uint32 h3_pair_ary[][3]=
{
   { def_mc_offset_h3_g, def_mc_offset_h3_g, def_mc_offset_h3_gg },
   { def_mc_offset_h3_g, def_mc_offset_h3_s, def_mc_offset_h3_gs },
   { def_mc_offset_h3_n, def_mc_offset_h3_j, def_mc_offset_h3_nj },
   { def_mc_offset_h3_n, def_mc_offset_h3_h, def_mc_offset_h3_nh },
   { def_mc_offset_h3_r, def_mc_offset_h3_g, def_mc_offset_h3_rg },
   { def_mc_offset_h3_r, def_mc_offset_h3_m, def_mc_offset_h3_rm },
   { def_mc_offset_h3_r, def_mc_offset_h3_b, def_mc_offset_h3_rb },
   { def_mc_offset_h3_r, def_mc_offset_h3_s, def_mc_offset_h3_rs },
   { def_mc_offset_h3_r, def_mc_offset_h3_t, def_mc_offset_h3_rt },
   { def_mc_offset_h3_r, def_mc_offset_h3_p, def_mc_offset_h3_rp },
   { def_mc_offset_h3_r, def_mc_offset_h3_h, def_mc_offset_h3_rh },
   { def_mc_offset_h3_b, def_mc_offset_h3_s, def_mc_offset_h3_bs },
   { def_mc_offset_h3_s, def_mc_offset_h3_s, def_mc_offset_h3_ss }
};

uint32 cls_han_coder::pairing ( uint32 table[][3], int table_cnt)
{
   int i;

   if ( ! (prev_mc_attr_u32 & def_mc_attr_no_combi) )
      forcnt ( i, table_cnt )
         if ( table[i][0] == prev_mc_offset_u32 && table[i][1] == cur_mc_offset_u32 ) return table[i][2];

   return 0;
}

uint32 cls_han_coder::h1_pairing ()
{
   return cur_mc_offset_u32 = pairing ( h1_pair_ary, mac_cnt_of(h1_pair_ary) );
}

uint32 cls_han_coder::h2_pairing ()
{
   return cur_mc_offset_u32 = pairing ( h2_pair_ary, mac_cnt_of(h2_pair_ary) );
}

uint32 cls_han_coder::h3_pairing ()
{
   return cur_mc_offset_u32 = pairing ( h3_pair_ary, mac_cnt_of(h3_pair_ary) );
}

void cls_han_coder::trans_cur_h4_to_h3 ()
{
   mac_assert ( cur_mc_offset_u32 < mac_cnt_of ( h4_to_h3_ary ) );
   cur_mc_offset_u32 = h4_to_h3_ary[ cur_mc_offset_u32 ];
}

void cls_han_coder::trans_prev_h4_to_h3 ()
{
   mac_assert ( prev_mc_offset_u32 < mac_cnt_of ( h4_to_h3_ary ) );
   prev_mc_offset_u32 = h4_to_h3_ary[ prev_mc_offset_u32 ];
}

void cls_han_coder::front_end()
{
   switch (cur_status_int)
   {
      case def_fs_null:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h4:
            case def_mc_type_h1: cur_status_int = def_fs_h1; break;
            case def_mc_type_h2: cur_status_int = def_fs_h2; break;
            case def_mc_type_h3: cur_status_int = def_fs_h3; break;
         }
         break;

      case def_fs_h1:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h4:
            case def_mc_type_h1: cur_status_int = h1_pairing () ?  def_fs_h1_aux : def_fs_complete ; break;
            case def_mc_type_h2: cur_status_int = def_fs_h2; break;
            case def_mc_type_h3: cur_status_int = def_fs_h3; break;
         }
         break;

      case def_fs_h1_aux:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h4:
            case def_mc_type_h1: cur_status_int = def_fs_complete; break;
            case def_mc_type_h2: cur_status_int = def_fs_h2; break;
            case def_mc_type_h3: cur_status_int = def_fs_h3; break;
         }
         break;

      case def_fs_h2:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h1: cur_status_int = def_fs_complete; break;
            case def_mc_type_h2: cur_status_int = h2_pairing() ? def_fs_h2_aux : def_fs_complete; break;
            case def_mc_type_h3: cur_status_int = def_fs_h3; break;
            case def_mc_type_h4: cur_status_int = def_fs_h4; trans_cur_h4_to_h3(); break;
         }
         break;

      case def_fs_h2_aux:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h1:
            case def_mc_type_h2: cur_status_int = def_fs_complete; break;
            case def_mc_type_h3: cur_status_int = def_fs_h3; break;
            case def_mc_type_h4: cur_status_int = def_fs_h4; trans_cur_h4_to_h3(); break;
         }
         break;

      case def_fs_h3:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h1:
            case def_mc_type_h2: cur_status_int = def_fs_complete; break;
            case def_mc_type_h3: cur_status_int = h3_pairing() ? def_fs_h3_aux : def_fs_complete; break;
            case def_mc_type_h4: trans_cur_h4_to_h3();
                                 cur_status_int = h3_pairing() ? def_fs_h4_aux : def_fs_complete;
                                 break;
         }
         break;

      case def_fs_h4:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h1: cur_status_int = def_fs_complete; break;
            case def_mc_type_h2: cur_status_int = def_fs_complete_h4; break;
            case def_mc_type_h3: trans_prev_h4_to_h3();
                                 cur_status_int = h3_pairing() ? def_fs_h3_aux : def_fs_complete;
                                 break;
            case def_mc_type_h4: trans_prev_h4_to_h3();
                                 trans_cur_h4_to_h3();
                                 cur_status_int = h3_pairing() ? def_fs_h4_aux : def_fs_complete;
                                 break;
         }
         break;

      case def_fs_h4_aux:
         switch ( cur_mc_type_u32 )
         {
            case def_mc_type_h1:
            case def_mc_type_h3:
            case def_mc_type_h4: cur_status_int = def_fs_complete; break;
            case def_mc_type_h2: cur_status_int = def_fs_complete_h4; break;
         }
         break;

      case def_fs_h3_aux:cur_status_int = def_fs_complete; break;
   }
}

void cls_han_coder::back_end()
{
   switch ( cur_status_int )
   {
      case def_fs_h1:
      case def_fs_h1_aux: cur_wch.parts.h1 = cardi_to_h1 ( cur_mc_offset_u32 ); break;

      case def_fs_h2:
      case def_fs_h2_aux: cur_wch.parts.h2 = cardi_to_h2 ( cur_mc_offset_u32 ); break;

      case def_fs_h3:
      case def_fs_h3_aux:
      case def_fs_h4:
      case def_fs_h4_aux: cur_wch.parts.h3 = cardi_to_h3 ( cur_mc_offset_u32 ); break;

      case def_fs_complete: mc_stack.push_pnt(&cur_mc); break;

      case def_fs_complete_h4:
      {
         mc_stack.push_pnt(&cur_mc);
         mc_stack.push_pnt(&prev_mc);
         frame_stack.discard();
         cur_wch = frame_stack.get_top_pnt()->wch;
      }
      break;
   }
}

cls_han_coder::cls_han_coder(cls_coder* arg_coder) :
   frame_stack (7),
   mc_stack (2),
   coder (arg_coder)
{
}

void cls_han_coder::reset()
{
   frame_stack.reset();
   mc_stack.reset();
}

void cls_han_coder::put(cls_mc* mc)
{
   mac_assert(mc->get_lang() == def_mc_lang_han);

   cls_frame forward_frame;
   int action_int;

   mc_stack.push_pnt(mc);

   while (mc_stack.is_holding())
   {
      cur_mc            = mc_stack.pop_val ();
      cur_mc_offset_u32 = cur_mc.get_offset ();
      cur_mc_type_u32   = cur_mc.get_type ();

      if (frame_stack.is_empty())
      {
         cur_status_int = def_fs_null;
         cur_wch        = def_c16_han_c_fill;
         action_int     = def_ca_open;
      }
      else
      {
         forward_frame      = *frame_stack.get_top_pnt();

         cur_status_int     = forward_frame.status_int;
         cur_wch            = forward_frame.wch;
         prev_mc            = forward_frame.mc;
         prev_mc_offset_u32 = prev_mc.get_offset();
         prev_mc_attr_u32   = prev_mc.get_attr();

         action_int         = def_ca_replace;
      }

      front_end();
      back_end();

      if (cur_status_int == def_fs_complete || cur_status_int == def_fs_complete_h4)
      {
         frame_stack.reset();
         action_int = def_ca_close;
      }
      else
      {
         forward_frame.wch        = cur_wch;
         forward_frame.mc         = cur_mc;
         forward_frame.status_int = cur_status_int;

         frame_stack.push_pnt(&forward_frame);
      }

      coder->put(action_int, cur_wch.c16);
   }
}

void cls_han_coder::complete()
{
   if (is_incomplete())
   {
      coder->put (def_ca_close, frame_stack.get_top_pnt()->wch.c16);
      frame_stack.reset();
   }
}

void cls_han_coder::discard()
{
   mac_assert (is_incomplete());

   frame_stack.discard();

   if (frame_stack.is_empty())
   {
      coder->put(def_ca_cancel, 0);
   }
   else
   {
      coder->put(def_ca_replace, frame_stack.get_top_pnt()->wch.c16);
   }
}

bool cls_han_coder::is_incomplete()
{
   return frame_stack.is_holding();
}

