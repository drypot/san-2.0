                                                                                                                        /*
--------------------------------------------------------------------------------
   key/mcp.hpp
   copyright(C) kyuhyun park
   1994.10.22
--------------------------------------------------------------------------------                                        */

#ifdef def_key_mcp_hpp
#error 'key/mcp.hpp' duplicated.
#endif

#define def_key_mcp_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_key_keyevent_hpp
#include <key/keyevent.hpp>
#endif

#define def_mcp_line_cnt  4
#define def_mcp_name_size 16

class cls_mcp
{
   private:

      struct cls_line
      {
         uint32  cnt;
         uint32* page0_u32_pnt;
         uint32* page1_u32_pnt;
      };

      cls_line line_ary[def_mcp_line_cnt];
      uint32*  file_img_u32_pnt;
      char*    name_pch;
      uint32   lang_u32;

   public:

      cls_mcp();
     ~cls_mcp();

      void   load(char*);

      char*  get_name();
      uint32 get_lang();
      uint32 get_mc (int num_page, cls_key_event*);
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

class cls_mcp_list_iter
{
   private:

      cls_mcp* mcp_pnt;

   public:

      cls_mcp_list_iter();

      void reset();

      void next_mcp ();
      bool locate_mcp (uint32 lang_u32);

      cls_mcp* get_mcp()
      {
         return mcp_pnt;
      }
};

void  mcp_add (char*);
