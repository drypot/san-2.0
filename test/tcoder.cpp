
#include <pub\config.hpp>
#include <pub\process.hpp>
#include <stdpub\io.hpp>
#include <pub\inline.hpp>
#include <pub\metacode.hpp>
#include <pub\easyhan.hpp>

void tty_char(char16 ch)
{
   tty_output(ch);
}

void tty_new_line()
{
   int y = tty_cur_y() + 1;
   if ( y > crt_y_max() ) y = 0;

   tty_xy(0,y);
   tty_clear_rest();
   //tty_xy(0,y);
}

bool coder_hook(key_sig* p_sig)
{
   if (p_sig->code() == KEY_SPACE && p_sig->modify_l_shift())
   {
      coder_complete();
      meta_code_page_next();
      return YES;
   }
   ef (p_sig->code() == KEY_F10 )
   {
      sys_exit(0);
   }
   ef (p_sig->code() == KEY_F9 )
   {
      coder_complete();
      return YES;
   }
   return NO;
}

void main(void)
{

   easy_han_output_init();
   easy_han_output_on();

   easy_han_input_init();
   easy_han_input_on();

   forever
   {
      while ( ! key_signal() );
      coder(coder_hook);
      while (coder_avail())
      {
         coder_get();
         switch (coder_status())
         {

            case CODER_NULL :       tty_output("<NULL>  "); break;
            case CODER_DIRECT :     tty_output("<DIRECT>"); break;
            case CODER_MIX_START :  tty_output("<START> "); break;
            case CODER_MIX_ING :    tty_output("<ING>   "); break;
            case CODER_MIX_COMPLETE:tty_output("<END>   "); break;
            case CODER_MIX_CANCEL:  tty_output("<CANCEL>"); break;
            default: halt("default @do_han");
         }
         tty_char(coder_code());
         tty_new_line();
      }
   }
}
