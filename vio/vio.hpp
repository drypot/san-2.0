																																								/*
--------------------------------------------------------------------------------
   vio/vio.hpp
	copyright(C) kyuhyun park
	1991.03.26
-------------------------------------------------------------------------------- 													*/

#ifdef vio_vio_hpp
#error 'vio/vio.hpp' duplicated.
#endif

#define vio_vio_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#if (defined def_dos) || (defined def_os2 && !defined def_pm)
   void vio_on ();
   void vio_off ();

   void vio_fill (byte);
   void vio_get_img (int, int, int, int, void*);
   void vio_put_img (int, int, int, int, void*);

   int vio_get_width ();
   int vio_get_height ();
#endif
