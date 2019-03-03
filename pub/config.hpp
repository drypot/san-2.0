																																								/*
--------------------------------------------------------------------------------
   pub/config.hpp
   copyright(c) kyuhyun park
   1990.11.04
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_config_hpp
#error 'pub/config.hpp' duplicated.
#endif

#define def_pub_config_hpp

#include <stddef.h>
#include <limits.h>
#include <sys\types.h>
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */
/*
   def_debug    [manual]

   def_gnuc     [auto]
   def_borlandc [auto]
   def_watcomc  [auto]
   def_ibmc     [auto]

   def_os2      [auto]
   def_dos      [auto]
   def_win      [auto]

   def_pm       [manual]
   def_vio      [manual]
   def_novio    [manual]

   def_owl      [manual]

   def_owlpm    [auto]
   def_owlwin   [auto]
*/

#if defined __GNUC__
#define def_gnuc
#endif

#if defined __BORLANDC__
#define def_borlandc
#endif

#if defined __WATCOMC__
#define def_watcomc
#endif

#if defined __IBMC__ || defined __IBMCPP__
#define def_ibmc
#endif

#if defined __OS2__
#define def_os2
#endif

#if defined __WINDOWS__
#define def_win
#endif

#if defined __MSDOS__ || defined __DOS__
#define def_dos
#endif

#if defined def_owl && defined def_os2
#define def_pm
#endif

#if defined def_owl && defined def_pm
#define def_owlpm
#endif

#if defined def_owl && defined def_win
#define def_owlwin
#endif

#if   defined def_owlwin
   #define _OWLPCH
   #include <owl\owlpch.h>
#elif defined def_owlpm
   #define INCL_OS2
   #define _OWLPCH
   #include <owl\owlpch.h>
#elif defined def_pm
   #define INCL_BASE
   #define INCL_DOSDEVIOCTL
   #define INCL_PM
   #include <os2.h>
#elif defined def_os2
   #define INCL_BASE
   #define INCL_DOSDEVIOCTL
   #define INCL_NOPMAPI
   #include <os2.h>
#elif defined def_win
   #define STRICT
	#include <windows.h>
   #include <windowsx.h>
#endif
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#define def_false      0
#define def_true       1
#define def_no         0
#define def_yes        1
#define def_error      0
#define def_ok         1
#define def_off        0
#define def_on         1
#define def_not_exist  0
#define def_exist      1
#define def_fail       0
#define def_success    1
#define def_exit       0
#define def_stop       0
#define def_continue   1

#define def_ok_null    NULL
#define def_error_null NULL

#define def_ok_zero    0
#define def_error_zero 0

#define def_ok_minus    -1
#define def_error_minus -1
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

typedef unsigned int uint;

#if SCHAR_MAX == 127 && SCHAR_MIN == -128 && UCHAR_MAX == 255
	typedef unsigned char byte;
	typedef signed char int8;
	typedef unsigned char uint8;
#else
	#error can not resolve 'int8' type.
#endif

#if SHRT_MAX == 0x7FFF
	typedef short int16;
	typedef unsigned short uint16;
#else
	#error can not resolve 'int16' type.
#endif

#if LONG_MAX == 0x7FFFFFFFL
	typedef long int32;
	typedef unsigned long uint32;
#elif INT_MAX == 0x7FFFFFFFL
	typedef int int32;
	typedef unsigned int uint32;
#else
	#error can not resolve 'int32' type.
#endif

#if CHAR_BIT != 8
	#error char_bit must be 8.
#endif

#if defined def_borlandc
   typedef long off_t;
#endif

typedef int bool;
typedef uint16 char16;

#define def_int_max 0x7FFFFFFFL
#define def_int16_max 0x7FFF
#define def_int32_max 0x7FFFFFFFL
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#define nothing (void)0
#define touch(id) ((void)(id))

#define el else
#define ef(val) else if (val)

#define forcnt(var,cnt)        for( (var)=0 ; (var)<(cnt) ; (var)++ )
#define fordecnt(var,cnt)      for( (var)=(cnt) ; (var)-->0 ; )
#define forinc(var,from,to)    for( var=(from) ; var<=(to) ; var++ )
#define fordec(var,from,to)    for( var=(from) ; var>=(to) ; var-- )
#define forever                for(;;)

#if defined def_watcomc || defined def_ibmc
#define mac_declare_copy_ctor(class_name)
#else
#define mac_declare_copy_ctor(class_name) class_name (const class_name&); class_name& operator= (const class_name&)
#endif

