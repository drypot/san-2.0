                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mac.cpp
   copyright(C) kyuhyun park
   1994.11.08
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <key/keyevent.hpp>

#include <key/mac.hpp>

typedef int32 (*type_func_ret_i32)();

cls_mac_bin::cls_mac_bin() : img_byte_pnt(NULL)
{
}

cls_mac_bin::cls_mac_bin(char* arg_fname) : img_byte_pnt(NULL)
{
   init(arg_fname);
}

cls_mac_bin::~cls_mac_bin()
{
   if (img_byte_pnt) mem_free(img_byte_pnt);
}

void cls_mac_bin::init(char* arg_fname)
{
   mac_rtcheck (!img_byte_pnt);

   try
   {
      cls_rfile bin_file(arg_fname);
      size_t file_sz = (size_t) bin_file.get_size();

      img_byte_pnt = (byte*) mem_alloc(file_sz);
      bin_file.read(img_byte_pnt, file_sz);
      mac_assert(mem_check(img_byte_pnt));
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info(cls_form_expander("func: key/mac.cpp/cls_mac_bin::init\ninfo: file read error\nfile: %s\n", arg_fname).get_pch());
      throw;
   }
}

byte* cls_mac_bin::get_pnt()
{
   mac_rtcheck (img_byte_pnt);
   return img_byte_pnt;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_mac_runner::cls_mac_runner(cls_mac_bin* mac_bin, cls_mac_mapper* arg_mapper) :
   img_byte_pnt(NULL),
   key_event_cnt(0),
   ret_addr_stack(16),
   val_stack(16),
   arg_stack(16),
   arg_stack_push_cnt_stack(16),
   mac_mapper(NULL)
{
   if (mac_bin) init(mac_bin, arg_mapper);
}

cls_mac_runner::~cls_mac_runner()
{
}

void cls_mac_runner::init(cls_mac_bin* mac_bin, cls_mac_mapper* arg_mapper)
{
   img_byte_pnt = (byte*) mac_bin->get_pnt();

   mac_change_type_of(mac_data_base_byte_pnt, byte*) = img_byte_pnt + *(int32*)(img_byte_pnt + 0*sizeof(int32));
   mac_change_type_of(mac_code_base_byte_pnt, byte*) = img_byte_pnt + *(int32*)(img_byte_pnt + 1*sizeof(int32));
   mac_change_type_of(mac_mode_base_pnt, byte*)      = img_byte_pnt + *(int32*)(img_byte_pnt + 2*sizeof(int32));
   mac_change_type_of(mac_func_base_i32_pnt, byte*)  = img_byte_pnt + *(int32*)(img_byte_pnt + 3*sizeof(int32));
   mac_change_type_of(mac_key_base_pnt,  byte*)      = img_byte_pnt + *(int32*)(img_byte_pnt + 4*sizeof(int32));

   mac_mode_end_pnt = (cls_mac_mode*) mac_func_base_i32_pnt;
   mac_rtcheck (mac_mode_base_pnt != mac_mode_end_pnt);

   mac_key_begin_pnt  = mac_key_base_pnt  + mac_mode_base_pnt->key_begin_inx;
   mac_key_end_pnt    = mac_key_base_pnt  + mac_mode_base_pnt->key_end_inx;
   mac_func_begin_i32_pnt = mac_func_base_i32_pnt + mac_mode_base_pnt->func_begin_inx;

   mac_mapper = arg_mapper;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline void cls_mac_runner::key_stack_reset()
{
   key_event_cnt=0;
}

inline void cls_mac_runner::key_stack_discard()
{
   mac_assert(key_event_cnt);
   key_event_cnt--;
}

inline void cls_mac_runner::key_stack_push(cls_key_event* pnt_key_event)
{
   mac_rtcheck(key_event_cnt < mac_cnt_of(key_event_ary));
   key_event_ary[key_event_cnt++] = *pnt_key_event;
}

inline bool cls_mac_runner::is_key_seq_list_head(cls_mac_key* pnt_mac_key)
{
   return pnt_mac_key->on_u16 & 0x8000U;
}

inline bool cls_mac_runner::is_key_seq_head(cls_mac_key* pnt_mac_key)
{
   return pnt_mac_key == mac_key_end_pnt || pnt_mac_key->off_u16 & 0x8000U;
}

bool cls_mac_runner::compare_key(cls_mac_key* pnt_mac_key, cls_key_event* pnt_key_event)
{
   return
      ( pnt_key_event->get_code() == (pnt_mac_key->code_u16 & 0x7fff)) &&
      ( !!(pnt_key_event->is_make_event()) == !(pnt_mac_key->code_u16 & 0x8000)) &&

      ( pnt_mac_key->on_u16 & def_mk_mask_s   ?   pnt_key_event->is_shifted_shift()    : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_ls  ?   pnt_key_event->is_shifted_lshift()   : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_rs  ?   pnt_key_event->is_shifted_rshift()   : def_true ) &&

      ( pnt_mac_key->on_u16 & def_mk_mask_c   ?   pnt_key_event->is_shifted_ctrl()     : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_lc  ?   pnt_key_event->is_shifted_lctrl()    : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_rc  ?   pnt_key_event->is_shifted_rctrl()    : def_true ) &&

      ( pnt_mac_key->on_u16 & def_mk_mask_a   ?   pnt_key_event->is_shifted_alt()      : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_la  ?   pnt_key_event->is_shifted_lalt()     : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_ra  ?   pnt_key_event->is_shifted_ralt()     : def_true ) &&

      ( pnt_mac_key->on_u16 & def_mk_mask_m   ?   pnt_key_event->is_shifted_machine()  : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_lm  ?   pnt_key_event->is_shifted_lmachine() : def_true ) &&
      ( pnt_mac_key->on_u16 & def_mk_mask_rm  ?   pnt_key_event->is_shifted_rmachine() : def_true ) &&

      ( pnt_mac_key->off_u16 & def_mk_mask_s  ? ! pnt_key_event->is_shifted_shift()    : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_ls ? ! pnt_key_event->is_shifted_lshift()   : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_rs ? ! pnt_key_event->is_shifted_rshift()   : def_true ) &&

      ( pnt_mac_key->off_u16 & def_mk_mask_c  ? ! pnt_key_event->is_shifted_ctrl()     : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_lc ? ! pnt_key_event->is_shifted_lctrl()    : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_rc ? ! pnt_key_event->is_shifted_rctrl()    : def_true ) &&

      ( pnt_mac_key->off_u16 & def_mk_mask_a  ? ! pnt_key_event->is_shifted_alt()      : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_la ? ! pnt_key_event->is_shifted_lalt()     : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_ra ? ! pnt_key_event->is_shifted_ralt()     : def_true ) &&

      ( pnt_mac_key->off_u16 & def_mk_mask_m  ? ! pnt_key_event->is_shifted_machine()  : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_lm ? ! pnt_key_event->is_shifted_lmachine() : def_true ) &&
      ( pnt_mac_key->off_u16 & def_mk_mask_rm ? ! pnt_key_event->is_shifted_rmachine() : def_true )
      ;
}

#define def_cmp_keyseq_ok    0
#define def_cmp_keyseq_no    1
#define def_cmp_keyseq_cont  2

int cls_mac_runner::compare_key_seq(cls_mac_key* pnt_mac_key)
{
   mac_assert (is_key_seq_head(pnt_mac_key));

   int sp = 0;
   while ( sp < key_event_cnt && (sp == 0 || !is_key_seq_head(pnt_mac_key)) )
   {
      if ( ! compare_key(pnt_mac_key, key_event_ary + sp) ) break;
      sp++;
      pnt_mac_key++;
   }

   if ( sp == key_event_cnt )
   {
      if ( is_key_seq_head(pnt_mac_key) ) return def_cmp_keyseq_ok;
      else return def_cmp_keyseq_cont;
   }
   return def_cmp_keyseq_no;
}

int cls_mac_runner::scan(cls_key_event* key_event)
{
   mac_assert(img_byte_pnt);

   cls_mac_key* iter_mac_key_pnt = mac_key_begin_pnt;
   int32* func_iter_pnt = mac_func_begin_i32_pnt;
   int rc;

   key_stack_push(key_event);

   while (iter_mac_key_pnt < mac_key_end_pnt)
   {
      rc = compare_key_seq(iter_mac_key_pnt);
      if (rc == def_cmp_keyseq_ok)
      {
         key_stack_reset();
         scaned_func_addr_i32 = *func_iter_pnt;
         return def_kb_scan_match;
      }
      ef (rc == def_cmp_keyseq_cont)
      {
         return def_kb_scan_continue;
      }
      iter_mac_key_pnt++;
      while (!is_key_seq_head(iter_mac_key_pnt)) iter_mac_key_pnt++;
      if (is_key_seq_list_head(iter_mac_key_pnt)) func_iter_pnt++;
   }

   if (key_event->is_break_event())
   {
      key_stack_discard();
      return def_kb_scan_ignore;
   }
   key_stack_reset();
   return def_kb_scan_failed;
}

void cls_mac_runner::set_mode(char* pch_mode_name)
{
   cls_mac_mode* iter_mac_mode_pnt = mac_mode_base_pnt;
   while (iter_mac_mode_pnt < mac_mode_end_pnt)
   {
      if (strcmp((char*)(mac_data_base_byte_pnt + iter_mac_mode_pnt->name_inx), pch_mode_name) == 0)
      {
         mac_key_begin_pnt      = mac_key_base_pnt  + iter_mac_mode_pnt->key_begin_inx;
         mac_key_end_pnt        = mac_key_base_pnt  + iter_mac_mode_pnt->key_end_inx;
         mac_func_begin_i32_pnt = mac_func_base_i32_pnt + iter_mac_mode_pnt->func_begin_inx;
         return;
      }
      iter_mac_mode_pnt++;
   }
   put_msg("\nfunc : cls_mac_runner::set_mode\ninfo : mode not found\n");
   pcs_exit(1);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

inline int32 cls_mac_runner::fetch_code()
{
   return mac_code_base_byte_pnt[ip_i32++];
}

void cls_mac_runner::pcode_intp(int32 arg_i32_ip)
{
   int32 code_i32;
   int32 tmp_ip_i32;
   int32 val1_i32;
   int32 val2_i32;
   int   call_cnt;
   int32 rc;

   ret_addr_stack.push_val(ip_i32);
   arg_stack_push_cnt_stack.push_val(arg_stack_push_cnt);
   ip_i32 = arg_i32_ip;
   arg_stack_push_cnt = 0;
   call_cnt = 1;
   while (call_cnt)
   {
      code_i32 = fetch_code();
      switch (code_i32)
      {
         case def_pc_jump :
            ip_i32 = fetch_code();
            break;

         case def_pc_jmp_false :
            tmp_ip_i32 = fetch_code();
            if (!val_stack.pop_val()) ip_i32 = tmp_ip_i32;
            break;

         case def_pc_jmp_true :
            tmp_ip_i32 = fetch_code();
            if (val_stack.pop_val()) ip_i32 = tmp_ip_i32;
            break;

         case def_pc_call :
            tmp_ip_i32 = fetch_code();
            if (tmp_ip_i32<0)
            {
               rc = cb_pdf(tmp_ip_i32);
            }
            else
            {
               ret_addr_stack.push_val(ip_i32);
               arg_stack_push_cnt_stack.push_val(arg_stack_push_cnt);
               ip_i32=tmp_ip_i32;
               call_cnt++;
            }
            break;

         case def_pc_ret :
            ip_i32=ret_addr_stack.pop_val();
            arg_stack_push_cnt = arg_stack_push_cnt_stack.pop_val();
            call_cnt--;
            break;

         case def_pc_arg_stack_push :
            arg_stack.push_val( fetch_code() );
            arg_stack_push_cnt++;
            break;

         case def_pc_arg_stack_push_val :
            arg_stack.push_val( val_stack.pop_val() );
            arg_stack_push_cnt++;
            break;

         case def_pc_arg_stack_discard :
            arg_stack.discard( (int)fetch_code() );
            arg_stack_push_cnt = 0;
            break;

         case def_pc_val_stack_push_func_result:
            val_stack.push_val(rc);
            break;

         case def_pc_val_stack_push_int:
            val_stack.push_val(fetch_code());
            break;

         case def_pc_val_stack_discard_one:
            val_stack.pop_val();
            break;

         case def_pc_logical_and:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32 && val2_i32);
            break;

         case def_pc_logical_or:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32 || val2_i32);
            break;

         case def_pc_equal:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32 == val2_i32);
            break;

         case def_pc_not_equal: val2_i32 = val_stack.pop_val(); val1_i32
            = val_stack.pop_val(); val_stack.push_val(val1_i32 !=
            val2_i32); break;

         case def_pc_above:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32>val2_i32);
            break;

         case def_pc_below:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32<val2_i32);
            break;

         case def_pc_above_equal:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32>=val2_i32);
            break;

         case def_pc_below_equal:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32<=val2_i32);
            break;

         case def_pc_plus:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32+val2_i32);
            break;

         case def_pc_minus:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32-val2_i32);
            break;

         case def_pc_mul:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32 * val2_i32);
            break;

         case def_pc_div:
            val2_i32 = val_stack.pop_val();
            val1_i32 = val_stack.pop_val();
            val_stack.push_val(val1_i32 / val2_i32);
            break;

         case def_pc_not :
            val_stack.push_val( !val_stack.pop_val() );
            break;

         default:
            mac_halt();
      }
   }
}

void cls_mac_runner::execute (int32 addr)
{
   mac_assert(img_byte_pnt);
   if (addr == 0) addr = scaned_func_addr_i32;
   if (addr < 0) cb_pdf(addr);
   else pcode_intp (addr);
}

int32 cls_mac_runner::cb_pdf(int32 id_i32)
{
   if (mac_mapper)
   {
      cls_mac_mapper* mrx_mapper = mac_mapper;
      while (mrx_mapper->func != NULL)
      {
         if (mrx_mapper->id_i32 == id_i32) return ((type_func_ret_i32)mrx_mapper->func)();
         mrx_mapper++;
      }
      mac_halt();
   }
   return 0;
}

