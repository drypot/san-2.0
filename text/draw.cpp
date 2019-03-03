                                                                                                                        /*
--------------------------------------------------------------------------------
   text/draw.cpp
   copyright(c) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

//#include <pub/charlist.hpp>
//#include <pub/inline.hpp>
//#include <vio/window.hpp>
//#include <vio/easyhan.hpp>

#include <text/glb.hpp>

/*

  not fully arranged.

*/

#define Noline      0
#define Thin        1
#define Thick       2

#define DrawMode  0
#define MoveMode  1
#define EraseMode 2
#define GrfMode   3

#define Up 0
#define Down 1
#define Right 2
#define Left 3

// ´e‘wÐa­A¶a. ¤eˆs¯s“¡”a. ‹i±A¶a. ·¡ˆõ·e ¹¡ÐsÑw ·¥•A..Ób.

/*
char16 lineStyle[8][11]={
        {'ÔÚ','ÔÂ','Ô¿','ÔÃ','ÔÅ','Ô´','ÔÀ','ÔÁ','ÔÙ','ÔÄ','Ô³'},
        {'ÔÕ','ÔÑ','Ô¸','ÔÆ','ÔØ','Ôµ','ÔÔ','ÔÏ','Ô¾','ÔÍ','Ô³'},
        {'ÔÖ','ÔÒ','Ô·','ÔÇ','Ô×','Ô¶','ÔÓ','ÔÐ','Ô½','ÔÄ','Ôº'},
        {'ÔÉ','ÔË','Ô»','ÔÌ','ÔÎ','Ô¹','ÔÈ','ÔÊ','Ô¼','ÔÍ','Ôº'},
        {'Û£','Û¨','Û¤','Û§','Û«','Û©','Û¦','Ûª','Û¥','Û¡','Û¢'},
        {'ÛÈ','Û¸','ÛÂ','Û¼','Û»','Û¾','ÛÆ','Ûº','ÛÄ','Û¬','Û¢'},
        {'ÛÇ','Û½','ÛÁ','Û·','ÛÀ','Û¹','ÛÅ','Û¿','ÛÃ','Û¡','Û­'},
        {'Û®','Û³','Û¯','Û²','Û¶','Û´','Û±','Ûµ','Û°','Û¬','Û­'}
     };
*/

char16 lineTable[8][3][3][3][3]=
   {
     /* BoxParty 0 */

     {
       {
         { {'Ô³','ÔÄ','ÔÍ'},         
           {'ÔÄ','ÔÄ','ÔÄ'},         
           {'ÔÍ','ÔÄ','ÔÍ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','Ô¿'},         
           {'Ô¸','ÔÚ','ÔÑ'},         
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','ÔÄ'},         
           {'Ô»','ÔÖ','ÔË'}          
         }
       },
       {
         { {'Ô³','ÔÀ','ÔÔ'},         
           {'ÔÙ','ÔÁ','ÔÙ'},         
           {'Ô¾','ÔÀ','ÔÏ'}
         },
         { {'Ô³','ÔÃ','ÔÆ'},         
           {'Ô´','ÔÅ','Ô´'},         
           {'Ôµ','ÔÃ','ÔØ'}          
         },
         { {'Ô³','ÔÀ','Ô³'},         
           {'ÔÙ','ÔÁ','ÔÙ'},         
           {'Ô³','ÔÀ','ÔÏ'}          
         }
       },
       {
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','Ô½'},         
           {'Ôº','ÔÇ','ÔÌ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','Ô¿'},         
           {'Ô¸','ÔÚ','ÔÑ'}          
         },
         { {'Ôº','ÔÇ','ÔÌ'},         
           {'Ô¶','Ô×','Ô¶'},         
           {'Ô¹','ÔÇ','ÔÎ'}          
         }
       }
     },

     /* BoxParty 1 */

     {
       {
         { {'Ô³','ÔÄ','ÔÍ'},         
           {'ÔÄ','ÔÄ','ÔÍ'},         
           {'ÔÍ','ÔÍ','ÔÍ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','ÔÕ'},         
           {'Ô¸','Ô¸','ÔÑ'}          
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','ÔÉ'},         
           {'Ô»','Ô»','ÔË'}          
         }
       },
       {
         { {'Ô³','ÔÀ','ÔÔ'},         
           {'ÔÙ','ÔÁ','ÔÔ'},         
           {'Ô¾','Ô¾','ÔÏ'}          
         },
         { {'Ô³','ÔÃ','ÔÆ'},         
           {'Ô´','ÔÅ','ÔÆ'},         
           {'Ôµ','Ôµ','ÔØ'}          
         },
         { {'Ô³','ÔÀ','ÔÔ'},         
           {'ÔÙ','ÔÁ','ÔÔ'},         
           {'Ô¾','Ô¾','ÔÏ'}          
         }
       },
       {
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','ÔÈ'},         
           {'Ô¼','Ô¼','ÔÊ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','ÔÕ'},         
           {'Ô¸','Ô¸','ÔÑ'}          
         },
         { {'Ôº','ÔÇ','ÔÌ'},         
           {'Ô¶','Ô×','Ô¶'},         
           {'Ô¹','Ô¹','ÔÎ'}          
         }
       }
     },

     /* BoxParty 2 */

     {
       {
         { {'Ôº','ÔÄ','ÔÍ'},         
           {'ÔÄ','ÔÄ','ÔÄ'},         
           {'ÔÍ','ÔÄ','ÔÍ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','Ô¿'},         
           {'Ô¸','Ô¸','ÔÑ'}          
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','Ô·'},         
           {'Ô»','ÔÖ','ÔË'}          
         }
       },
       {
         { {'Ô³','ÔÀ','ÔÔ'},         
           {'ÔÙ','ÔÁ','ÔÙ'},         
           {'Ô¾','ÔÀ','ÔÏ'}          
         },
         { {'Ô³','ÔÃ','ÔÆ'},
           {'Ô´','ÔÅ','Ô´'},         
           {'Ôµ','ÔÃ','ÔØ'}          
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','Ô·'},         
           {'Ô»','ÔÖ','ÔË'}          
         }
       },
       {
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','Ô½'},         
           {'Ô¼','ÔÓ','ÔÊ'}          
         },
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','Ô½'},         
           {'Ô¼','ÔÓ','ÔÊ'}          
         },
         { {'Ôº','ÔÇ','ÔÌ'},         
           {'Ô¶','Ô×','Ô¶'},         
           {'Ô¹','ÔÇ','ÔÎ'}          
         }
       }
     },

     /* BoxParty 3 */

     {
       {
         { {'Ôº','ÔÄ','ÔÍ'},         
           {'ÔÄ','ÔÄ','ÔÍ'},         
           {'ÔÍ','ÔÍ','ÔÍ'}          
         },
         { {'Ô³','ÔÚ','ÔÕ'},         
           {'Ô¿','ÔÂ','ÔÕ'},         
           {'Ô¸','Ô¸','ÔÑ'}          
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','ÔÉ'},         
           {'Ô»','Ô»','ÔË'}          
         }
       },
       {
         { {'Ô³','ÔÀ','ÔÔ'},         
           {'Ô³','ÔÃ','ÔÆ'},         
           {'Ôº','ÔÖ','ÔÉ'}          
         },
         { {'Ô³','ÔÃ','ÔÆ'},         
           {'Ô´','ÔÅ','ÔÆ'},         
           {'Ôµ','Ôµ','ÔØ'}          
         },
         { {'Ôº','ÔÖ','ÔÉ'},         
           {'Ô·','ÔÒ','ÔÉ'},         
           {'Ô»','Ô»','ÔË'}          
         }
       },
       {
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','ÔÈ'},         
           {'Ô¼','Ô¼','ÔÊ'}          
         },
         { {'Ôº','ÔÓ','ÔÈ'},         
           {'Ô½','ÔÐ','ÔÈ'},         
           {'Ô¼','Ô¼','ÔÊ'}          
         },
         { {'Ôº','ÔÇ','ÔÌ'},         
           {'Ô¶','Ô×','ÔÌ'},         
           {'Ô¹','Ô¹','ÔÎ'}          
         }
       }
     },


     /* BoxParty 4 */

     {
       {
         { {'Û¢','Û¡','Û¬'},         
           {'Û¡','Û¡','Û¡'},         
           {'Û¬','Û¡','Û¬'}          
         },
         { {'Û¢','Û£','ÛÈ'},         
           {'Û¤','Û¨','ÛÒ'},         
           {'ÛÂ','ÛÑ','Û¸'}          
         },
         { {'Û­','ÛÇ','Û®'},         
           {'ÛÁ','Û½','ÛÔ'},         
           {'Û¯','ÛÓ','Û³'}          
         }
       },
       {
         { {'Û¢','Û¦','ÛÆ'},         
           {'Û¥','Ûª','ÛÖ'},         
           {'ÛÄ','ÛÕ','Ûº'}          
         },
         { {'Û¢','Û§','Û¼'},         
           {'Û©','Û«','ÛÚ'},
           {'Û¾','ÛÙ','Û»'}          
         },
         { {'Û¢','ÛÊ','ÛÌ'},         
           {'ÛÎ','ÛÜ','Ûà'},         
           {'ÛÐ','Ûß','Ûâ'}          
         }
       },
       {
         { {'Û­','ÛÅ','Û±'},         
           {'ÛÃ','Û¿','ÛØ'},         
           {'Û°','Û×','Ûµ'}          
         },
         { {'Û¢','ÛÉ','ÛË'},         
           {'ÛÍ','ÛÛ','ÛÞ'},         
           {'ÛÏ','ÛÝ','Ûá'}          
         },
         { {'Û­','Û·','Û²'},         
           {'Û¹','ÛÀ','Ûä'},         
           {'Û´','Ûã','Û¶'}          
         }
       }
     },

     /* BoxParty 5 */

     {
       {
         { {'Û¢','Û¡','Û¬'},         
           {'Û¡','Û¡','Û¬'},         
           {'Û¬','Û¬','Û¬'}          
         },
         { {'Û¢','Û£','ÛÈ'},
           {'Û¤','Û¨','ÛÒ'},         
           {'ÛÂ','ÛÑ','Û¸'}          
         },
         { {'Û­','ÛÇ','Û®'},         
           {'ÛÁ','Û½','ÛÔ'},         
           {'Û¯','ÛÓ','Û³'}          
         }
       },
       {
         { {'Û¢','Û¦','ÛÆ'},         
           {'Û¥','Ûª','ÛÖ'},         
           {'ÛÄ','ÛÕ','Ûº'}          
         },
         { {'Û¢','Û§','Û¼'},         
           {'Û©','Û«','ÛÚ'},         
           {'Û¾','ÛÙ','Û»'}          
         },
         { {'Û¢','ÛÊ','ÛÌ'},         
           {'ÛÎ','ÛÜ','Ûà'},         
           {'ÛÐ','Ûß','Ûâ'}          
         }
       },
       {
         { {'Û­','ÛÅ','Û±'},         
           {'ÛÃ','Û¿','ÛØ'},         
           {'Û°','Û×','Ûµ'}          
         },
         { {'Û¢','ÛÉ','ÛË'},         
           {'ÛÍ','ÛÛ','ÛÞ'},         
           {'ÛÏ','ÛÝ','Ûá'}          
         },
         { {'Û­','Û·','Û²'},
           {'Û¹','ÛÀ','Ûä'},         
           {'Û´','Ûã','Û¶'}          
         }
       }
     },

     /* BoxParty 6 */

     {
       {
         { {'Û¢','Û¡','Û¬'},         
           {'Û¡','Û¡','Û¡'},         
           {'Û¬','Û¡','Û¬'}          
         },
         { {'Û¢','Û£','ÛÈ'},         
           {'Û¤','Û¨','ÛÒ'},         
           {'ÛÂ','ÛÑ','Û¸'}          
         },
         { {'Û­','ÛÇ','Û®'},         
           {'ÛÁ','Û½','ÛÔ'},         
           {'Û¯','ÛÓ','Û³'}          
         }
       },
       {
         { {'Û¢','Û¦','ÛÆ'},         
           {'Û¥','Ûª','ÛÖ'},         
           {'ÛÄ','ÛÕ','Ûº'}          
         },
         { {'Û¢','Û§','Û¼'},         
           {'Û©','Û«','ÛÚ'},         
           {'Û¾','ÛÙ','Û»'}          
         },
         { {'Û­','ÛÊ','ÛÌ'},         
           {'ÛÎ','ÛÜ','Ûà'},         
           {'ÛÐ','Ûß','Ûâ'}          
         }
       },
       {
         { {'Û­','ÛÅ','Û±'},         
           {'ÛÃ','Û¿','ÛØ'},         
           {'Û°','Û×','Ûµ'}          
         },
         { {'Û­','ÛÉ','ÛË'},         
           {'ÛÍ','ÛÛ','ÛÞ'},         
           {'ÛÏ','ÛÝ','Ûá'}          
         },
         { {'Û­','Û·','Û²'},         
           {'Û¹','ÛÀ','Ûä'},         
           {'Û´','Ûã','Û¶'}          
         }
       }
     },

     /* BoxParty 7 */

     {
       {
         { {'Û­','Û¡','Û¬'},         
           {'Û¡','Û¡','Û¬'},         
           {'Û¬','Û¬','Û¬'}          
         },
         { {'Û¢','Û£','ÛÈ'},         
           {'Û¤','Û¨','ÛÒ'},         
           {'ÛÂ','ÛÑ','Û¸'}          
         },
         { {'Û­','ÛÇ','Û®'},         
           {'ÛÁ','Û½','ÛÔ'},         
           {'Û¯','ÛÓ','Û³'}          
         }
       },
       {
         { {'Û¢','Û¦','ÛÆ'},         
           {'Û¥','Ûª','ÛÖ'},         
           {'ÛÄ','ÛÕ','Ûº'}          
         },
         { {'Û¢','Û§','Û¼'},         
           {'Û©','Û«','ÛÚ'},         
           {'Û¾','ÛÙ','Û»'}          
         },
         { {'Û­','ÛÊ','ÛÌ'},         
           {'ÛÎ','ÛÜ','Ûà'},         
           {'ÛÐ','Ûß','Ûâ'}          
         }
       },
       {
         { {'Û­','ÛÅ','Û±'},         
           {'ÛÃ','Û¿','ÛØ'},         
           {'Û°','Û×','Ûµ'}          
         },
         { {'Û­','ÛÉ','ÛË'},         
           {'ÛÍ','ÛÛ','ÛÞ'},         
           {'ÛÏ','ÛÝ','Ûá'}          
         },
         { {'Û­','Û·','Û²'},         
           {'Û¹','ÛÀ','Ûä'},         
           {'Û´','Ûã','Û¶'}
         }
       }
     }
   };

/*
static int BoxStyle,BoxParty;
static bool UpF,DownF,RightF,LeftF;
static int Dicls_rection;
static uint16 Mode,*/ /*Class,*/ /*lineCharF,GrfCharF;
static char16  GrfChar = 0xD480;
static int LastDrawMode=DrawMode;
static int ScrollCommand;
static line aux_line(*p_cur_paper_);
static paper_iter_ aux_iter(aux_line);
static paper_iter_ aux_iter_cur(cur_line);

static void set_MenuItem()
{
   scn_global();
   switch (Mode)
   {
     case DrawMode   :crt_inverse(0,global_win.y2,10,global_win.y2);  break;
     case EraseMode  :crt_inverse(11,global_win.y2,21,global_win.y2); break;
     case GrfMode    :crt_inverse(22,global_win.y2,36,global_win.y2); break;
     case MoveMode   :crt_inverse(37,global_win.y2,47,global_win.y2); break;
   }
}

static void set_lineMenu(void)
{
   mline_write(" [D]‹aŸ¡‹¡  [E]»¡¶‹¡  [G/A]‹aŸ±¢…¸a  [M/F]·¡•·  [L/S/1-8]¬å  [SPC]®¸÷/·¡•·");
   Mode=MoveMode;
   set_MenuItem();
}

static bool ExistCh ( char* str,char16 ch)
{
   big_endian(ch);
   while (*str!=0)
     if (*(char16*)str==ch) return def_ok;
     else str+=2;
   return def_false;
}

static void set_UpF(void)
{
   UpF=Noline;
   if (cdoc->iter.pos_y()>1)
   {
      aux_line.get(cdoc->iter.pos_y()-1);
      aux_iter.reset();
      aux_iter.move_visual( cdoc->iter.pos_visual() );
      if ( aux_iter.pos_visual() == cdoc->iter.pos_visual() )
      {
         char16 ch = aux_iter.code();
         if ( is_Spc ( ch ) )
         {
            if (BoxParty==0)
            {
               UpF= ExistCh("Ô³Ô´ÔµÔ¸Ô¿ÔÂÔÃÔÅÔÆÔÑÔØÔÕÔÚ",ch) ? Thin :
                    ExistCh("Ô¶Ô·Ô¹ÔºÔ»ÔÇÔÉÔËÔÌÔÎÔÒÔ×ÔÖ",ch) ? Thick : Noline;
            }
            else
            {
               UpF= ExistCh("Û¢Û£Û¤Û§Û¨Û©Û«Û¸Û»Û¼Û¾ÛÂÛÈÛÉÛËÛÍÛÏÛÑÛÒÛÙÛÚÛÛÛÝÛÞÛá",ch) ? Thin :
                    ExistCh("Û­Û®Û¯Û²Û³Û´Û¶Û·Û¹Û½ÛÀÛÁÛÇÛÊÛÌÛÎÛÐÛÓÛÔÛÜÛßÛàÛâÛãÛä",ch) ? Thick: Noline;
            }
         }
      }
   }
}

static void set_DownF(void)
{
   DownF=Noline;
   if (cdoc->iter.pos_y()<cdoc->paper_.line_cnt()-1)
   {
      aux_line.get(cdoc->iter.pos_y()+1);
      aux_iter.reset();
      aux_iter.move_visual( cdoc->iter.pos_visual() );
      if ( aux_iter.pos_visual() == cdoc->iter.pos_visual() )
      {
         Hangul ch = aux_iter.code();
         if ( is_Spc ( (char16) ch ) )
         {
            if (BoxParty==0)
               DownF=(ExistCh("Ô³Ô´ÔµÔ¾ÔÀÔÁÔÃÔÅÔÆÔÏÔÔÔØÔÙ",ch)) ? Thin :
                     (ExistCh("Ô¶Ô¹ÔºÔ¼Ô½ÔÇÔÈÔÊÔÌÔÎÔÐÔÓÔ×",ch)) ? Thick: Noline;
            else
               DownF=(ExistCh("Û¢Û¥Û¦Û§Û©ÛªÛ«ÛºÛ»Û¼Û¾ÛÄÛÆÛÊÛÌÛÎÛÐÛÕÛÖÛÙÛÚÛÜÛßÛàÛâ",ch))? Thin :
                     (ExistCh("Û­Û°Û±Û²Û´ÛµÛ¶Û·Û¹Û¿ÛÀÛÃÛÅÛÉÛËÛÍÛÏÛ×ÛØÛÛÛÝÛÞÛáÛãÛä",ch))? Thick: Noline;
         }
      }
   }
}

static void set_LeftF(void)
{
   LeftF=Noline;
   if ( cdoc->iter.pos() )
   {
      aux_iter_cur.reset();
      aux_iter_cur.move( cdoc->iter.pos() - 1 );
      Hangul ch = aux_iter_cur.code();
      if ( is_line(ch) )
         if (BoxParty==0)
           LeftF=(ExistCh("ÔÀÔÁÔÂÔÃÔÄÔÅÔÇÔÐÔÒÔÓÔÖÔ×ÔÚ",ch)) ? Thin :
                 (ExistCh("ÔÆÔÈÔÉÔÊÔËÔÌÔÍÔÎÔÏÔÑÔÔÔÕÔØ",ch)) ? Thick: Noline;
         else
           LeftF=(ExistCh("Û¡Û£Û¦Û§Û¨ÛªÛ«Û·Û½Û¿ÛÀÛÅÛÇÛÉÛÊÛÑÛÓÛÕÛ×ÛÙÛÛÛÜÛÝÛßÛã",ch)) ? Thin :
                 (ExistCh("Û¬Û®Û±Û²Û³ÛµÛ¶Û¸ÛºÛ»Û¼ÛÆÛÈÛËÛÌÛÒÛÔÛÖÛØÛÚÛÞÛàÛáÛâÛä",ch)) ? Thick: Noline;
   }
}

static void set_RightF(void)
{
   RightF=Noline;
   {
      aux_iter_cur.reset();
      aux_iter_cur.move( cdoc->iter.pos() + 1 );
      Hangul ch = aux_iter_cur.code();
      if ( is_line(ch) )
          if (BoxParty==0)
             RightF=ExistCh("Ô´Ô¶Ô·Ô½Ô¿ÔÁÔÂÔÄÔÅÔÐÔÒÔ×ÔÙ",ch) ? Thin :
                    ExistCh("ÔµÔ¸Ô¹Ô»Ô¼Ô¾ÔÊÔËÔÍÔÎÔÏÔÑÔØ",ch) ? Thick: Noline;
          else
             RightF=ExistCh("Û¡Û¤Û¥Û¨Û©ÛªÛ«Û¹Û½Û¿ÛÀÛÁÛÃÛÍÛÎÛÒÛÔÛÖÛØÛÚÛÛÛÜÛÞÛàÛä",ch) ? Thin :
                    ExistCh("Û¬Û¯Û°Û³Û´ÛµÛ¶Û¸ÛºÛ»Û¾ÛÂÛÄÛÏÛÐÛÑÛÓÛÕÛ×ÛÙÛÝÛßÛáÛâÛã",ch) ? Thick: Noline;

   }
}

static void set_branch_f()
{
   set_UpF();
   set_DownF();
   set_LeftF();
   set_RightF();
}

static void EraseGrf(void)
{
   line_replace( cdoc->iter.pos() , cdoc->iter.width() , cdoc->iter.width());
}

static void DrawGrf(void)
{
   line_replace( cdoc->iter.pos() , 1 , 2 );
   cdoc->iter.code(GrfChar);
}

static void DrawNewPosition(void)
{
   set_branch_f();
   line_replace( cdoc->iter.pos() , 1 , 2 );
   Hangul hc = lineTable[BoxStyle][UpF][DownF][LeftF][RightF];
   hc.swap();
   cdoc->iter.code ( hc.word );
}

static void DrawOldPosition(void)
{
   switch (Dicls_rection) {
     case Up    : switch (BoxStyle) {
                    case 0 :
                    case 1 :
                    case 4 :
                    case 5 : UpF=Thin;  break;
                    case 2 :
                    case 3 :
                    case 6 :
                    case 7 : UpF=Thick; break;
                  }
                  break;
     case Down  : switch (BoxStyle) {
                    case 0 :
                    case 1 :
                    case 4 :
                    case 5 : DownF=Thin;  break;
                    case 2 :
                    case 3 :
                    case 6 :
                    case 7 : DownF=Thick; break;
                  }
                  break;
     case Left  : switch (BoxStyle) {
                    case 0 :
                    case 2 :
                    case 4 :
                    case 6 : LeftF=Thin; break;
                    case 1 :
                    case 3 :
                    case 5 :
                    case 7 : LeftF=Thick; break;
                  }
                  break;
     case Right : switch (BoxStyle) {
                    case 0 :
                    case 2 :
                    case 4 :
                    case 6 : RightF=Thin; break;
                    case 1 :
                    case 3 :
                    case 5 :
                    case 7 : RightF=Thick; break;
                  }
                  break;
   }

   line_replace( cdoc->iter.pos() , 1 , 2 );
   Hangul hc = lineTable[BoxStyle][UpF][DownF][LeftF][RightF];
   hc.swap();
   cdoc->iter.code ( hc.word );
   //if (Y!=cdoc->iter.pos_y()) cur_line.put();
}

static void EraseNewPosition(void)
{
    DrawNewPosition();
}

static void EraseOldPosition(void)
{
   if (!lineCharF) return;

   switch (Dicls_rection) {
     case Up    : switch (BoxStyle) {
                    case 0 :
                    case 1 :
                    case 4 :
                    case 5 : UpF=Noline;  break;
                    case 2 :
                    case 3 :
                    case 6 :
                    case 7 : UpF=Noline; break;
                  }
                  if (!LeftF && !RightF) DownF=Noline;
                  break;
     case Down  : switch (BoxStyle) {
                    case 0 :
                    case 1 :
                    case 4 :
                    case 5 : DownF=Noline;  break;
                    case 2 :
                    case 3 :
                    case 6 :
                    case 7 : DownF=Noline; break;
                  }
                  if (!LeftF && !RightF) UpF=Noline;
                  break;
     case Left  : switch (BoxStyle) {
                    case 0 :
                    case 2 :
                    case 4 :
                    case 6 : LeftF=Noline; break;
                    case 1 :
                    case 3 :
                    case 5 :
                    case 7 : LeftF=Noline; break;
                  }
                  if (!UpF && !DownF) RightF=Noline;
                  break;
     case Right : switch (BoxStyle) {
                    case 0 :
                    case 2 :
                    case 4 :
                    case 6 : RightF=Noline; break;
                    case 1 :
                    case 3 :
                    case 5 :
                    case 7 : RightF=Noline; break;
                  }
                  if (!UpF && !DownF) LeftF=Noline;
                  break;
   }

   //if ( cdoc->iter.pos() != X || cdoc->iter.pos_y() != Y)
   //{
      if (RightF || LeftF || UpF || DownF)
      {
         if ( ( cdoc->iter.code() & 0xff00) == 0xd400 )
         {
            Hangul hc = lineTable[0][UpF][DownF][LeftF][RightF];
            hc.swap();
            cdoc->iter.code( hc.word );
         }
         else
         {
            Hangul hc = lineTable[4][UpF][DownF][LeftF][RightF];
            hc.swap();
            cdoc->iter.code( hc.word );
         }
      }
      else
      {
         int sz = cdoc->iter.width();
         line_replace( cdoc->iter.pos() , sz , sz );
      }
   //}
   //if (OldY!=Y)  Writeline(SY,EditBuf+1);
}

static void SelectlineStyle(void)
{
   window win;
   uint16 j,WX;

   scn_global();
   WX=global_win.x2-52;
   win.open(WX,3,WX+49,7);
   crt_inverse();
   tty_xy(WX+1,4); tty_output("ÔÚÔÂÔ¿ÔÕÔÑÔ¸ÔÖÔÒÔ·ÔÉÔËÔ»Û£Û¨Û¤ÛÈÛ¸ÛÂÛÇÛ½ÛÁÛ®Û³Û¯");
   tty_xy(WX+1,5); tty_output("ÔÃÔÅÔ´ÔÆÔØÔµÔÇÔ×Ô¶ÔÌÔÎÔ¹Û§Û«Û©Û¼Û»Û¾Û·ÛÀÛ¹Û²Û¶Û´");
   tty_xy(WX+1,6); tty_output("ÔÀÔÁÔÙÔÔÔÏÔ¾ÔÓÔÐÔ½ÔÈÔÊÔ¼Û¦ÛªÛ¥ÛÆÛºÛÄÛÅÛ¿ÛÃÛ±ÛµÛ°");
   j=BoxStyle;

   do
   {
      crt_inverse(WX+j*6+1,4,WX+j*6+6,6);
      bios_key_get();
      crt_inverse(WX+j*6+1,4,WX+j*6+6,6);
      switch (bios_key_code())
      {
         case BK_LEFT   :
         case BK_CTRL_S :
         case BK_UP     :
         case BK_CTRL_E : if (j==0) j=7;
                          else      j--;
                          break;
         case BK_RIGHT  :
         case BK_CTRL_D :
         case BK_DOWN   :
         case BK_CTRL_X : if (j==7) j=0;
                          else      j++;
                          break;
         case BK_END    :
         case BK_PGDN   :
         case BK_CTRL_C : j=7;
                          break;
         case BK_HOME   :
         case BK_PGUP   :
         case BK_CTRL_R : j=0;
                          break;
         case BK_ENTER  : BoxStyle=j;
                          break;
         default        : if ( bios_key_ascii() >= '1' && bios_key_ascii() <='8')
                          {
                             BoxStyle=bios_key_ascii()-'1';
                             bios_key_set(BK_ENTER);
                           }
      }
   } while (bios_key_code()!=BK_ENTER && bios_key_code()!=BK_ESC );
   BoxParty= BoxStyle>3;
}

static void set_GrfChar(void)
{
   set_spc_page();
   if ( spc_page_cnt )
   {
      GrfChar = spc_page[0];
      set_MenuItem();
      Mode=LastDrawMode=GrfMode;
      set_MenuItem();
   }
}
*/

/*
static void arrange_vx (int32 nx)
{
   move_pos_vx(nx);
   if ( nx > cdoc->iter.pos_visual() )
   {
      line_replace ( cdoc->iter.pos(),1,2 );
      move_pos_vx(nx);
   }
}
*/

void pdf_draw()
{
   /*
   //arrange_vx ( cdoc->iter.pos_visual() /2 *2 );
   set_lineMenu();

   //X = cdoc->iter.pos();
   //Y = cdoc->iter.pos_y();

   do
   {
   */

/*..................................................set_ Position............*/

/*
      if ( in(Mode,DrawMode,GrfMode  */ /*,EraseMode*/  /*) )
      {
         //arrange_vx ( prev_vx /2 *2 );
         int32 column_save = prev_vx ;
         move_pos_vx( prev_vx /2 *2);
         line_replace_visual ( column_save /2 *2 , 1 , 2 );
         move_pos_vx( column_save /2 *2);
         cdoc->iter.code(C16_HAN_C_FILL);
      }
      scn_xy_pos();
      if ( ! edited_flg && ( Mode==DrawMode|| Mode==GrfMode ) ) paper_edited_flg_set();
*/
/*..................................................Ready...................*/
/*
      lineCharF = is_line ( cdoc->iter.code() );
      GrfCharF  = ! lineCharF && is_Spc( cdoc->iter.code() ) ;
      if      (Mode==DrawMode) DrawNewPosition();
      else if (Mode==GrfMode ) DrawGrf();
      else if (Mode==EraseMode && (lineCharF || GrfCharF   ))
      {
              if (GrfCharF)
                 EraseGrf();
              else
                 EraseNewPosition();
      }
      move_pos_adjust();
*/

/*..................................................get_ Order...............*/
/*
      scn_update();
      scn_line_cursor();
      //if (Mode==MoveMode) EngCur2(SX-1,SY-1);
      //else                HanCur2(SX-1,SY-1);
      bios_key_get();
      //OldX=X;
      //OldY=Y;
      ScrollCommand=def_error;
      Dicls_rection=def_error;
      uint16 kc = bios_key_code();
      if ( kc ==BK_ESC) break;
      switch (kc) {
         case BK_UP   :
         case BK_CTRL_E:Dicls_rection=Up;      break;
         case BK_DOWN :
         case BK_CTRL_X:Dicls_rection=Down;    break;
         case BK_RIGHT:
         case BK_CTRL_D:Dicls_rection=Right;  break;
         case BK_LEFT :
         case BK_CTRL_S:Dicls_rection=Left;   break;
         */
         /*
         case CtrlZ:if (HY+SY-Scnto_p!=paper_Len || SY!=Scnto_p) {
                       if (SY>Scnto_p) HY=HY+1,SY=SY-1;
                       else           {
                          ScrollCommand=CtrlZ;
                          Y++;
                          Dicls_rection=Down;
                       }
                       set_ScnF=ON;
                    }
                    break;
         case CtrlW:if (HY>1) {
                       if (SY<ScnBot) HY=HY-1,SY=SY+1;
                       else {
                         ScrollCommand=CtrlW;
                         Y--;
                         Dicls_rection=Up;
                       }
                       set_ScnF=ON;
                    }
                    break;
         */
         /*
         case BK_SPACE :set_MenuItem();
                    if (Mode==MoveMode)  Mode=LastDrawMode;
                    else                 Mode=MoveMode;
                    set_MenuItem();
                    break;
         case BK_d  :
         case BK_D  :set_MenuItem();
                   Mode=LastDrawMode=DrawMode;
                   set_MenuItem();
                   break;
         case BK_f  :
         case BK_F  :
         case BK_m  :
         case BK_M  :set_MenuItem();
                  Mode=MoveMode;
                  set_MenuItem();
                  break;
         case BK_e  :
         case BK_E  :set_MenuItem();
                  Mode=LastDrawMode=EraseMode;
                  set_MenuItem();
                  break;
         case BK_s  :
         case BK_S  :
         case BK_l  :
         case BK_L  :SelectlineStyle();
                   set_MenuItem();
                   Mode=LastDrawMode=DrawMode;
                    set_MenuItem();
                    break;
         case BK_F4   :
         case BK_a  :
         case BK_A  :
         case BK_g  :
         case BK_ALT_G :
         case BK_G  :set_GrfChar();                  break;
         default   :if (bios_key_ascii()>='1' && bios_key_ascii()<='8')
                    {
                       BoxStyle=bios_key_ascii()-'1';
                       BoxParty=BoxStyle>3;
                       set_MenuItem();
                       Mode=LastDrawMode=DrawMode;
                       set_MenuItem();
                    }
                    break;
      }
*/
/* ..........................................................Access.........*/
/*
      switch (Mode) {
         case DrawMode :DrawOldPosition();
         case GrfMode  :if ( cdoc->iter.pos_y() == cdoc->paper_.line_cnt() -1 ) paper_append_blank();
                        break;

         case EraseMode:if (lineCharF) EraseOldPosition();
      }

      scn_update();

      switch (kc) {
         case BK_UP   :
         case BK_CTRL_E: pdf_go_prev_line(); break;
         case BK_DOWN :
         case BK_CTRL_X: pdf_go_next_line();
                         break;
         case BK_RIGHT:
         case BK_CTRL_D: if ( in ( Mode , DrawMode , GrfMode ) )  prev_vx+=2;
                         else pdf_go_next_char();
                         break;
         case BK_LEFT :
         case BK_CTRL_S: if ( in ( Mode , DrawMode , GrfMode ) )  prev_vx-=2;
                         else pdf_go_prev_char();
                         break;
      }
      */
      /*
      if (ScrollCommand==CtrlZ) {
         if (put_EditBuf()!=def_ok) return;
         HY++;
         cdoc->iter.pos_y()++;
         set_EditBuf();
         if (SelectingBlockF) set_BlockPos();
      } else if (ScrollCommand==CtrlW) {
           if (put_EditBuf()!=def_ok) return;
           HY--;
           cdoc->iter.pos_y()--;
           set_EditBuf();
           if (SelectingBlockF) set_BlockPos();
      }
      */
      /*
   } while (bios_key_code()!=BK_ESC);

   mline_clear();
*/
}

