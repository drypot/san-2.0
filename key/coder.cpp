                                                                                                                        /*
--------------------------------------------------------------------------------
   key/coder.cpp
   copyright(C) kyuhyun park
   1994.12.20
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <key/hancoder.hpp>
#include <key/engcoder.hpp>
#include <key/coder.hpp>

cls_coder::cls_coder () :
   frame_queue (4),
   han_coder_pnt (NULL),
   eng_coder_pnt (NULL)
{
   han_coder_pnt = new cls_han_coder(this);
   eng_coder_pnt = new cls_eng_coder(this);
   prev_lang_u32 = 0;
}

cls_coder::~cls_coder ()
{
   delete han_coder_pnt;
   delete eng_coder_pnt;
}

void cls_coder::reset ()
{
   prev_lang_u32 = 0;
   frame_queue.reset ();
   han_coder_pnt->reset ();
}

void cls_coder::put (cls_mc* mc)
{
   if (mc->is_valid())
   {
      if (mc->get_lang() != prev_lang_u32) complete();
      switch (mc->get_lang())
      {
         case def_mc_lang_eng: eng_coder_pnt->put (mc); break;
         case def_mc_lang_han: han_coder_pnt->put (mc); break;
      }
      prev_lang_u32 = mc->get_lang();
   }
}

void cls_coder::put (int action_int, char16 code_c16)
{
   cls_frame frame;

   frame.action_int = action_int;
   frame.code_c16   = code_c16;
   frame_queue.push_pnt (&frame);
}

void cls_coder::discard ()
{
   switch (prev_lang_u32)
   {
      case def_mc_lang_han :
         han_coder_pnt->discard();
         break;
   }
}

void cls_coder::complete()
{
   switch(prev_lang_u32)
   {
      case def_mc_lang_han :
         han_coder_pnt->complete();
         break;
   }
}

void cls_coder::get ()
{
   output_frame = frame_queue.pop_val();
}

int cls_coder::get_action ()
{
   return output_frame.action_int;
}

char16 cls_coder::get_code ()
{
   return output_frame.code_c16;
}

bool cls_coder::is_incomplete ()
{
   bool rval = def_no;

   switch (prev_lang_u32)
   {
      case def_mc_lang_han :
         rval = han_coder_pnt->is_incomplete ();
         break;
   }

   return rval;
}

bool cls_coder::is_holding ()
{
   return frame_queue.is_holding ();
}

