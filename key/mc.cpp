                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mc.cpp
   copyright(C) kyuhyun park
   1994.10.25
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/charlist.hpp>
#include <key/mc.hpp>

void cls_mc::reset()
{
   val_u32 = 0;
}

void cls_mc::set(cls_key_event* key_event, cls_mcp* mcp)
{
   reset();

   switch (key_event->get_code_type())
   {
      case def_key_type_char :
         make_char(key_event, mcp);
         make_ctrl(key_event);
         break;

      case def_key_type_pad_char :
         make_pad_char(key_event);
         break;

      case def_key_type_action :
      case def_key_type_pad_action :
         make_action(key_event);
         break;
   }
}

void cls_mc::set (uint32 t, uint32 a, uint32 st, uint32 off)
{
   val_u32 = def_mc_mask_lang & t | def_mc_mask_attr & a | def_mc_mask_type & st | def_mc_mask_offset & off;
}

uint32 cls_mc::get_lang()
{
   return def_mc_mask_lang & val_u32;
}

uint32 cls_mc::get_attr()
{
   return def_mc_mask_attr & val_u32;
}

uint32 cls_mc::get_type()
{
   return def_mc_mask_type & val_u32;
}

uint32 cls_mc::get_offset()
{
   return def_mc_mask_offset & val_u32;
}

void cls_mc::set_lang(uint32 arg_val)
{
   masked_assign(&val_u32, arg_val, def_mc_mask_lang);
}

void cls_mc::set_attr(uint32 arg_val)
{
   masked_assign(&val_u32, arg_val, def_mc_mask_attr);
}

void cls_mc::set_type(uint32 arg_val)
{
   masked_assign(&val_u32, arg_val, def_mc_mask_type);
}

void cls_mc::set_offset(uint32 arg_val)
{
   masked_assign(&val_u32, arg_val, def_mc_mask_offset);
}

void cls_mc::make_char(cls_key_event* key_event, cls_mcp* mcp)
{
   mac_assert (key_event->get_code_type() == def_key_type_char);

   bool shifted     = key_event->is_shifted_shift();
   bool caps_locked = key_event->is_toggled_caps_lock();

   if (mcp->get_mc(0, key_event) & def_mc_attr_caps_lock)
   {
      val_u32 = mcp->get_mc ( shifted && !caps_locked || !shifted && caps_locked ? 1 : 0, key_event);
   }
   else
   {
      val_u32 = mcp->get_mc ( shifted ? 1 : 0 , key_event);
   }
}

void cls_mc::make_ctrl(cls_key_event* key_event)
{
   if (get_lang() == def_mc_lang_eng && key_event->is_shifted_ctrl())
   {
      char ch = (char) get_offset();
      if (isalpha(ch)) ch = toupper(ch);
      if (is_inside(ch,64,95)) set_offset(ch - 64);
   }
}

void cls_mc::make_pad_char(cls_key_event* key_event)
{
   static char xtable[] = { '0','1','2','3','4','5','6','7','8','9','/','*','-','+','.' };
   mac_assert (key_event->get_code_type() == def_key_type_pad_char);
   mac_assert (key_event->get_code_offset() < sizeof(xtable));
   set (def_mc_lang_eng, 0, 0, xtable[key_event->get_code_offset()]);
}

void cls_mc::make_action(cls_key_event* key_event)
{
   mac_assert (key_event->get_code_type() == def_key_type_action || key_event->get_code_type() == def_key_type_pad_action);

   static struct cls_frame_xtable { uint16 keycode; char16 ch; } xtable[] =
   {
      {def_key_esc,         def_c8_esc},
      {def_key_backspace,   def_c8_bs},
      {def_key_tab,         def_c8_ht},
      {def_key_enter,       def_c8_cr},
      {def_key_space,       def_c8_space},
      {def_key_pad_enter,   def_c8_cr},
      {def_key_delete,      def_c8_del},
      {def_key_pad_delete,  def_c8_del}
   };

   if (key_event->get_shifted())
   {
      reset();
   }
   else
   {
      cls_frame_xtable* end_frame_pnt = xtable + mac_cnt_of(xtable);
      cls_frame_xtable* mrx_frame_pnt = xtable;

      while (mrx_frame_pnt < end_frame_pnt)
      {
         if (mrx_frame_pnt->keycode == key_event->get_code())
         {
            set (def_mc_lang_eng, 0, 0, mrx_frame_pnt->ch);
            break;
         }
         mrx_frame_pnt++;
      }
   }
}

