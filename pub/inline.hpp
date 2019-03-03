																																								/*
--------------------------------------------------------------------------------
   pub/inline.hpp
   copyright(c) kyuhyun park
   1993.06.02
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_inline_hpp
#error  'pub/inline.hpp' duplicated.
#endif

#define def_pub_inline_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#if defined def_borlandc || defined def_watcomc || defined def_ibmc

   inline byte   get_u16_low      (uint16 u16)      { return (byte) (uint16) u16 ; }
   inline byte   get_u16_high     (uint16 u16)      { return (byte) ((uint16) u16 >> 8) ; }
   inline byte*  get_u16_low_pnt  (uint16* u16_pnt) { return (byte*)u16_pnt; }
   inline byte*  get_u16_high_pnt (uint16* u16_pnt) { return ((byte*)u16_pnt+1); }
   inline uint16 make_u16 (byte hi, byte lo)        { return uint16 (lo | ( (uint16)hi << 8 ) ) ; }

   inline void swap_u16(uint16* u16_pnt)
   {
      byte tmp = *get_u16_low_pnt(u16_pnt);
      *get_u16_low_pnt(u16_pnt) = *get_u16_high_pnt(u16_pnt);
      *get_u16_high_pnt(u16_pnt) = tmp;
   }

   inline void write_as_big_endian(void* p, uint16 n)
   {
      *(byte*)p = get_u16_high(n);
      *((byte*)p+1) = get_u16_low(n);
   }

   inline void write_as_little_endian(void* p, uint16 n)
   {
      *(uint16*)p = n;
   }

   inline uint16  get_u32_low      (uint32 val)      { return (uint16) val; }
   inline uint16  get_u32_high     (uint32 val)      { return val >> 16 ; }
   inline uint16* get_u32_low_pnt  (uint32* u32_pnt) { return (uint16*)u32_pnt; }
   inline uint16* get_u32_high_pnt (uint32* u32_pnt) { return (uint16*)u32_pnt+1; }
   inline uint32  make_u32         (uint16 hi, uint16 lo) { return lo | ( (uint32) hi << 16 ); }

   inline void swap_u32(uint32* u32_pnt)
   {
      uint16 tmp = *get_u32_low_pnt(u32_pnt);
      *get_u32_low_pnt(u32_pnt)  = *get_u32_high_pnt(u32_pnt);
      *get_u32_high_pnt(u32_pnt) = tmp;
   }
#else
   #error unsupported compiler.
#endif

#define mac_change_type_of(v,type) (*((type *)&v))
#define mac_offset_of(t,f) offsetof(t,f)
#define mac_cnt_of(arr) (sizeof (arr) / sizeof (arr[0]))

template<class cls_a, class cls_b> inline cls_a get_max(cls_a a, cls_b b) { return a > b ? a : b; }
template<class cls_a, class cls_b> inline cls_a get_min(cls_a a, cls_b b) { return a < b ? a : b; }

template <class V,class cls_a,class cls_b> inline bool is_inside      (V v,cls_a a,cls_b b) { return v >= a && v <= b; }
template <class V,class cls_a,class cls_b> inline bool is_inside_less (V v,cls_a a,cls_b b) { return v >= a && v < b; }
template <class V,class cls_a,class cls_b> inline bool is_inside_cnt  (V v,cls_a a,cls_b b) { return v >= a && v < a+b; }
template <class V,class cls_a,class cls_b> inline bool is_outside     (V v,cls_a a,cls_b b) { return v < a || v > b; }

template<class cls_t> inline bool is_odd(cls_t v)  { return byte(v) & 0x01; }
template<class cls_t> inline bool is_even(cls_t v) { return !odd(v); }

template<class cls_a,class cls_b> inline bool is_multiple(cls_a v1,cls_b v2) { return !(v1%v2); }
template<class cls_a,class cls_b> inline bool is_overflow(cls_a v1,cls_b v2) { return v1+v2 < v1 || v1+v2 < v2 ? def_true : def_false; }

template<class cls_v,class cls_u> inline cls_v get_prev_seg   (cls_v v, cls_u segsz) { return v/segsz*segsz; }
template<class cls_v,class cls_u> inline cls_v get_next_seg   (cls_v v, cls_u segsz) { return (v+segsz-1)/segsz*segsz; }
template<class cls_v,class cls_u> inline cls_v get_seg_cnt  (cls_v v, cls_u segsz) { return (v+segsz-1)/segsz; }
template<class cls_v,class cls_u> inline cls_v get_seg_num (cls_v v, cls_u segsz) { return (v >= 0 ? v : v + 1 - segsz) / segsz; }
template<class cls_v,class cls_u> inline cls_v get_offset     (cls_v v, cls_u segsz) { return v >= 0 ? v % segsz : segsz - 1 - (-v -1) % segsz; }

template <class cls_t> inline void turn(cls_t* var)
{
   *var =! *var;
}

template <class cls_v,class cls_a,class cls_b> inline void turn(cls_v* v, cls_a a, cls_b b)
{
   if (*v == a)
      *v = b;
   else
      *v = a;
}

template<class cls_t> inline cls_t shift (cls_t* old_val, cls_t new_val)
{
   cls_t tmp_val;
   tmp_val = *old_val;
   *old_val = new_val;
   return tmp_val;
}

template<class cls_t> inline void swap (cls_t* a, cls_t* b)
{
   cls_t tmp;
   tmp = *a;
   *a = *b;
   *b = tmp;
}

template<class cls_a, class cls_b, class cls_c> void masked_assign(cls_a* var, cls_b new_value, cls_c mask)
{
   *var = (*var & ~mask) | (new_value & mask);
}

template<class cls_a, class cls_b, class cls_c> cls_b binary_search(cls_a* pnt_base, cls_b cnt, cls_c key)
{
   int mid, low, high;

   low = 0;
   high = cnt - 1;

   while (low <= high)
   {
      mid =  ( high + low ) >> 1;
      if ( key < pnt_base[mid] ) high = mid - 1;
      ef ( key > pnt_base[mid] ) low = mid + 1;
      el return mid;
   }

   return -1;
}

