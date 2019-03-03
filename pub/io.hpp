                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/io.hpp
   copyright(c) kyuhyun park
   1993.02.06
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_file_hpp
#error 'pub/io.hpp' duplicated.
#endif

#define def_pub_file_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

#if defined def_gnuc
#include <unistd.h>
#endif

#if defined def_watcomc
#include <io.h>
#endif

#if defined def_borlandc
#include <io.h>
#endif

#if defined def_ibmc
#include <io.h>
#endif

#include <fcntl.h>
#include <sys\stat.h>

mac_define_xmsg1(io);

class cls_file
{
   protected:

      int fd;

      cls_file ();
     ~cls_file ();

   public:

      void open (char*, int = O_RDWR | O_CREAT);
      void close ();
      bool is_opened ();

      void  set_offset (off_t);
      off_t get_offset ();
      off_t get_size ();

      void read (void*, size_t);
      void write (void*, size_t);

      void truncate (off_t);
};

inline bool cls_file::is_opened()
{
   return fd != -1;
}

class cls_rfile : public cls_file
{
   public:

      cls_rfile ();
      cls_rfile (char*);
     ~cls_rfile ();

      void open (char*);
};

class cls_wfile : public cls_file
{
   public:

      cls_wfile ();
      cls_wfile (char*);
     ~cls_wfile ();

      void open (char*);
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void make_backup(char* name);
