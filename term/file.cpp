                                                                                                                        /*
--------------------------------------------------------------------------------
   term/file.cpp
   copyright(C) kyuhyun park
   1995.12.13
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <pub/dir.hpp>
#include <pub/init.hpp>

#include <term/glb.hpp>

static FILE* snd_txt_fh;
static FILE* rcv_txt_fh;
static FILE* rcv_bin_fh;

static FILEDLG snd_txt_fdlg;
static FILEDLG rcv_bin_fdlg;
static FILEDLG rcv_txt_fdlg;

static void snd_txt_loop(void*)
{
   static byte send1;
   static byte send2;
   static byte prev_byte;
   int ch;

   while (ch = fgetc (snd_txt_fh), ch != EOF && send_txt_flg)
   {
      if (is_inside_less(ch, 0, 0x20))
      {
         prev_byte = 0;
         send1 = ch;
      }
      ef (prev_byte)
      {
         if (host_code_int == local_code_int)
         {
            send1 = prev_byte;
            send2 = ch;
         }
         else
         {
            char16 c16 = make_u16(prev_byte, ch);
            c16 = host_code_int == def_ct_wansung ? get_wansung(c16) : get_johab(c16);
            send1 = get_u16_high(c16);
            send2 = get_u16_low(c16);
         }
         prev_byte = 0;
      }
      ef (is_double((byte)ch))
      {
         prev_byte = ch;
      }
      else
      {
         send1 = ch;
      }

      if (send1)
      {
         port_write(send1);
         send1 = 0;
      }

      if (send2)
      {
         port_write(send2);
         send2 = 0;
      }
   }

   if (send_txt_flg)
   {
      snd_txt_end();
      port_write((byte)26);
   }
}

void snd_txt()
{
   if (send_txt_flg)
   {
      snd_txt_end();
   }
   else
   {
      WinFileDlg(HWND_DESKTOP, client_hwnd, &snd_txt_fdlg);
      if (snd_txt_fdlg.lReturn == DID_OK)
      {
         if (snd_txt_fh = fopen (snd_txt_fdlg.szFullFile,"rt"), snd_txt_fh != NULL)
         {
            send_txt_flg = def_yes;
            begin_thread(snd_txt_loop, 16384, NULL);
            update_state();
         }
      }
   }
}

void snd_txt_end()
{
   send_txt_flg = def_no;
   fclose(snd_txt_fh);
   update_state();
}

void snd_bin()
{
   //put_msg("send bin");
}

void snd_zmd()
{
   //put_msg("send zmd");
}

void rcv_txt()
{
   if (receive_txt_flg)
   {
      rcv_txt_end();
   }
   else
   {
      WinFileDlg(HWND_DESKTOP, client_hwnd, &rcv_txt_fdlg);
      if (rcv_txt_fdlg.lReturn == DID_OK)
      {
         if (rcv_txt_fh = fopen (rcv_txt_fdlg.szFullFile,"ab"), rcv_txt_fh != NULL)
         {
            receive_txt_flg = def_yes;
            update_state();
         }
      }
   }
}

void rcv_txt_end()
{
   receive_txt_flg = def_no;
   fclose(rcv_txt_fh);
   update_state();
}

void rcv_txt_loop(char16 c16)
{
   if (is_double(c16))
   {
      if (local_code_int == def_ct_wansung) c16 = get_wansung(c16);

      byte ch1 = get_u16_high(c16);
      byte ch2 = get_u16_low(c16);

      if (ch1) if (fputc(ch1, rcv_txt_fh) == EOF) rcv_txt_end();
      if (ch2) if (fputc(ch2, rcv_txt_fh) == EOF) rcv_txt_end();
   }
   else
   {
      if (fputc(c16, rcv_txt_fh) == EOF) rcv_txt_end();
   }
}

void rcv_txt_newline()
{
   rcv_txt_loop('\r');
   rcv_txt_loop('\n');
}

void rcv_bin()
{
   if (receive_bin_flg)
   {
      rcv_bin_end();
   }
   else
   {
      WinFileDlg(HWND_DESKTOP, client_hwnd, &rcv_bin_fdlg);
      if (rcv_bin_fdlg.lReturn == DID_OK)
      {
         if (rcv_bin_fh = fopen (rcv_bin_fdlg.szFullFile,"ab"), rcv_bin_fh != NULL)
         {
            receive_bin_flg = def_yes;
            update_state();
         }
      }
   }
}

void rcv_bin_end()
{
   receive_bin_flg = def_no;
   fclose(rcv_bin_fh);
   update_state();
}

void rcv_bin_loop(byte ch)
{
   if (fputc(ch, rcv_bin_fh) == EOF) rcv_bin_end();
}

void rcv_zmd()
{
   //put_msg ("receive zmd");
}

void ctor()
{
   snd_txt_fdlg.cbSize = sizeof (FILEDLG);
   snd_txt_fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_OPEN_DIALOG;
   strcpy (snd_txt_fdlg.szFullFile, cls_fname(send_txt_dir_pch).get_path());

   rcv_bin_fdlg.cbSize = sizeof (FILEDLG);
   rcv_bin_fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_SAVEAS_DIALOG;
   strcpy (rcv_bin_fdlg.szFullFile, cls_fname(receive_bin_dir_pch).get_path());

   rcv_txt_fdlg.cbSize = sizeof (FILEDLG);
   rcv_txt_fdlg.fl = FDS_CENTER | FDS_HELPBUTTON | FDS_SAVEAS_DIALOG;
   strcpy (rcv_txt_fdlg.szFullFile, cls_fname(receive_txt_dir_pch).get_path());
}

static cls_initer initer(ctor,-1);
