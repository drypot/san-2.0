																																								/*
--------------------------------------------------------------------------------
   pub/io.cpp
	copyright(C) kyuhyun park
   1993.02.06
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/dir.hpp>
#include <pub/io.hpp>

#define mac_throw_xmsg_io(func) throw cls_xmsg_io(cls_form_expander("%sinfo: %s",func,strerror(errno)).get_pch())

cls_file::cls_file() : fd(-1)
{
}

cls_file::~cls_file()
{
   if (is_opened()) close();
}

void cls_file::open(char* arg_fname, int arg_mode)
{
   mac_assert(!is_opened());

   if (arg_mode & O_CREAT)
	{
      fd = ::open (arg_fname, arg_mode|O_BINARY, S_IREAD|S_IWRITE);
      if (fd == -1) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::open\n");
	}
	else
	{
      fd = ::open (arg_fname, arg_mode|O_BINARY);
      if (fd == -1) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::open\n");
	}
}

void cls_file::close()
{
   if (is_opened())
   {
      if(::close(fd) != 0) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::close\n");
      fd = -1;
   }
}

void cls_file::set_offset(off_t off)
{
   mac_assert(is_opened());
   if (lseek(fd, off, SEEK_SET) == def_error_minus) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::set_offset\n");
}

off_t cls_file::get_offset()
{
   mac_assert(is_opened());

   off_t off = tell(fd);
   if (off == def_error_minus) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::get_offset\n");
	return off;
}

off_t cls_file::get_size()
{
   mac_assert(is_opened());

   off_t sz = filelength(fd);
   if (sz==def_error_minus) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::get_size\n");
   return sz;
}

void cls_file::read (void* p, size_t sz)
{
   mac_assert(is_opened());
   if (::read(fd, p, sz)!=sz) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::read\n");
}

void cls_file::write(void* p, size_t sz)
{
   mac_assert(is_opened());
   if (::write(fd, p, sz) != sz) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::write\n");
}

void cls_file::truncate (off_t fs)
{
   mac_assert(is_opened());
   if (chsize(fd, fs) == def_error_minus) mac_throw_xmsg_io("func: pub/io.cpp/cls_file::truncate\n");
   set_offset(0);
}

cls_rfile::cls_rfile()
{
}

cls_rfile::cls_rfile(char* arg_fname)
{
   open(arg_fname);
}

cls_rfile::~cls_rfile()
{
}

void cls_rfile::open(char* arg_fname)
{
   cls_file::open(arg_fname, O_RDONLY);
}

cls_wfile::cls_wfile()
{
}

cls_wfile::cls_wfile(char* arg_fname)
{
   open(arg_fname);
}

cls_wfile::~cls_wfile()
{
}

void cls_wfile::open(char* arg_fname)
{
   cls_file::open(arg_fname, O_WRONLY|O_CREAT|O_TRUNC);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void make_backup(char* name)
{
   cls_fname fname(name);

   if (stricmp(fname.get_ext(),".bak")!=0)
   {
      fname.set_ext(".bak");
      remove(fname.get_path());
      rename(name, fname.get_path());
   }
}

