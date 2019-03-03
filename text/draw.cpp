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

// �e�w�a�A�a. �e�s�s���a. �i�A�a. �����e ���s�w ���A..�b.

/*
char16 lineStyle[8][11]={
        {'��','��','Կ','��','��','Դ','��','��','��','��','Գ'},
        {'��','��','Ը','��','��','Ե','��','��','Ծ','��','Գ'},
        {'��','��','Է','��','��','Զ','��','��','Խ','��','Ժ'},
        {'��','��','Ի','��','��','Թ','��','��','Լ','��','Ժ'},
        {'ۣ','ۨ','ۤ','ۧ','۫','۩','ۦ','۪','ۥ','ۡ','ۢ'},
        {'��','۸','��','ۼ','ۻ','۾','��','ۺ','��','۬','ۢ'},
        {'��','۽','��','۷','��','۹','��','ۿ','��','ۡ','ۭ'},
        {'ۮ','۳','ۯ','۲','۶','۴','۱','۵','۰','۬','ۭ'}
     };
*/

char16 lineTable[8][3][3][3][3]=
   {
     /* BoxParty 0 */

     {
       {
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','Կ'},         
           {'Ը','��','��'},         
         },
         { {'Ժ','��','��'},         
           {'Է','��','��'},         
           {'Ի','��','��'}          
         }
       },
       {
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'Ծ','��','��'}
         },
         { {'Գ','��','��'},         
           {'Դ','��','Դ'},         
           {'Ե','��','��'}          
         },
         { {'Գ','��','Գ'},         
           {'��','��','��'},         
           {'Գ','��','��'}          
         }
       },
       {
         { {'Ժ','��','��'},         
           {'Խ','��','Խ'},         
           {'Ժ','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','Կ'},         
           {'Ը','��','��'}          
         },
         { {'Ժ','��','��'},         
           {'Զ','��','Զ'},         
           {'Թ','��','��'}          
         }
       }
     },

     /* BoxParty 1 */

     {
       {
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','��'},         
           {'Ը','Ը','��'}          
         },
         { {'Ժ','��','��'},         
           {'Է','��','��'},         
           {'Ի','Ի','��'}          
         }
       },
       {
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'Ծ','Ծ','��'}          
         },
         { {'Գ','��','��'},         
           {'Դ','��','��'},         
           {'Ե','Ե','��'}          
         },
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'Ծ','Ծ','��'}          
         }
       },
       {
         { {'Ժ','��','��'},         
           {'Խ','��','��'},         
           {'Լ','Լ','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','��'},         
           {'Ը','Ը','��'}          
         },
         { {'Ժ','��','��'},         
           {'Զ','��','Զ'},         
           {'Թ','Թ','��'}          
         }
       }
     },

     /* BoxParty 2 */

     {
       {
         { {'Ժ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','Կ'},         
           {'Ը','Ը','��'}          
         },
         { {'Ժ','��','��'},         
           {'Է','��','Է'},         
           {'Ի','��','��'}          
         }
       },
       {
         { {'Գ','��','��'},         
           {'��','��','��'},         
           {'Ծ','��','��'}          
         },
         { {'Գ','��','��'},
           {'Դ','��','Դ'},         
           {'Ե','��','��'}          
         },
         { {'Ժ','��','��'},         
           {'Է','��','Է'},         
           {'Ի','��','��'}          
         }
       },
       {
         { {'Ժ','��','��'},         
           {'Խ','��','Խ'},         
           {'Լ','��','��'}          
         },
         { {'Ժ','��','��'},         
           {'Խ','��','Խ'},         
           {'Լ','��','��'}          
         },
         { {'Ժ','��','��'},         
           {'Զ','��','Զ'},         
           {'Թ','��','��'}          
         }
       }
     },

     /* BoxParty 3 */

     {
       {
         { {'Ժ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Կ','��','��'},         
           {'Ը','Ը','��'}          
         },
         { {'Ժ','��','��'},         
           {'Է','��','��'},         
           {'Ի','Ի','��'}          
         }
       },
       {
         { {'Գ','��','��'},         
           {'Գ','��','��'},         
           {'Ժ','��','��'}          
         },
         { {'Գ','��','��'},         
           {'Դ','��','��'},         
           {'Ե','Ե','��'}          
         },
         { {'Ժ','��','��'},         
           {'Է','��','��'},         
           {'Ի','Ի','��'}          
         }
       },
       {
         { {'Ժ','��','��'},         
           {'Խ','��','��'},         
           {'Լ','Լ','��'}          
         },
         { {'Ժ','��','��'},         
           {'Խ','��','��'},         
           {'Լ','Լ','��'}          
         },
         { {'Ժ','��','��'},         
           {'Զ','��','��'},         
           {'Թ','Թ','��'}          
         }
       }
     },


     /* BoxParty 4 */

     {
       {
         { {'ۢ','ۡ','۬'},         
           {'ۡ','ۡ','ۡ'},         
           {'۬','ۡ','۬'}          
         },
         { {'ۢ','ۣ','��'},         
           {'ۤ','ۨ','��'},         
           {'��','��','۸'}          
         },
         { {'ۭ','��','ۮ'},         
           {'��','۽','��'},         
           {'ۯ','��','۳'}          
         }
       },
       {
         { {'ۢ','ۦ','��'},         
           {'ۥ','۪','��'},         
           {'��','��','ۺ'}          
         },
         { {'ۢ','ۧ','ۼ'},         
           {'۩','۫','��'},
           {'۾','��','ۻ'}          
         },
         { {'ۢ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         }
       },
       {
         { {'ۭ','��','۱'},         
           {'��','ۿ','��'},         
           {'۰','��','۵'}          
         },
         { {'ۢ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'ۭ','۷','۲'},         
           {'۹','��','��'},         
           {'۴','��','۶'}          
         }
       }
     },

     /* BoxParty 5 */

     {
       {
         { {'ۢ','ۡ','۬'},         
           {'ۡ','ۡ','۬'},         
           {'۬','۬','۬'}          
         },
         { {'ۢ','ۣ','��'},
           {'ۤ','ۨ','��'},         
           {'��','��','۸'}          
         },
         { {'ۭ','��','ۮ'},         
           {'��','۽','��'},         
           {'ۯ','��','۳'}          
         }
       },
       {
         { {'ۢ','ۦ','��'},         
           {'ۥ','۪','��'},         
           {'��','��','ۺ'}          
         },
         { {'ۢ','ۧ','ۼ'},         
           {'۩','۫','��'},         
           {'۾','��','ۻ'}          
         },
         { {'ۢ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         }
       },
       {
         { {'ۭ','��','۱'},         
           {'��','ۿ','��'},         
           {'۰','��','۵'}          
         },
         { {'ۢ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'ۭ','۷','۲'},
           {'۹','��','��'},         
           {'۴','��','۶'}          
         }
       }
     },

     /* BoxParty 6 */

     {
       {
         { {'ۢ','ۡ','۬'},         
           {'ۡ','ۡ','ۡ'},         
           {'۬','ۡ','۬'}          
         },
         { {'ۢ','ۣ','��'},         
           {'ۤ','ۨ','��'},         
           {'��','��','۸'}          
         },
         { {'ۭ','��','ۮ'},         
           {'��','۽','��'},         
           {'ۯ','��','۳'}          
         }
       },
       {
         { {'ۢ','ۦ','��'},         
           {'ۥ','۪','��'},         
           {'��','��','ۺ'}          
         },
         { {'ۢ','ۧ','ۼ'},         
           {'۩','۫','��'},         
           {'۾','��','ۻ'}          
         },
         { {'ۭ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         }
       },
       {
         { {'ۭ','��','۱'},         
           {'��','ۿ','��'},         
           {'۰','��','۵'}          
         },
         { {'ۭ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'ۭ','۷','۲'},         
           {'۹','��','��'},         
           {'۴','��','۶'}          
         }
       }
     },

     /* BoxParty 7 */

     {
       {
         { {'ۭ','ۡ','۬'},         
           {'ۡ','ۡ','۬'},         
           {'۬','۬','۬'}          
         },
         { {'ۢ','ۣ','��'},         
           {'ۤ','ۨ','��'},         
           {'��','��','۸'}          
         },
         { {'ۭ','��','ۮ'},         
           {'��','۽','��'},         
           {'ۯ','��','۳'}          
         }
       },
       {
         { {'ۢ','ۦ','��'},         
           {'ۥ','۪','��'},         
           {'��','��','ۺ'}          
         },
         { {'ۢ','ۧ','ۼ'},         
           {'۩','۫','��'},         
           {'۾','��','ۻ'}          
         },
         { {'ۭ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         }
       },
       {
         { {'ۭ','��','۱'},         
           {'��','ۿ','��'},         
           {'۰','��','۵'}          
         },
         { {'ۭ','��','��'},         
           {'��','��','��'},         
           {'��','��','��'}          
         },
         { {'ۭ','۷','۲'},         
           {'۹','��','��'},         
           {'۴','��','۶'}
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
   mline_write(" [D]�a����  [E]������  [G/A]�a�����a  [M/F]����  [L/S/1-8]��  [SPC]����/����");
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
               UpF= ExistCh("ԳԴԵԸԿ����������������",ch) ? Thin :
                    ExistCh("ԶԷԹԺԻ����������������",ch) ? Thick : Noline;
            }
            else
            {
               UpF= ExistCh("ۣۢۤۧۨ۩۫۸ۻۼ۾����������������������������",ch) ? Thin :
                    ExistCh("ۭۮۯ۲۳۴۶۷۹۽������������������������������",ch) ? Thick: Noline;
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
               DownF=(ExistCh("ԳԴԵԾ������������������",ch)) ? Thin :
                     (ExistCh("ԶԹԺԼԽ����������������",ch)) ? Thick: Noline;
            else
               DownF=(ExistCh("ۢۥۦۧ۩۪۫ۺۻۼ۾����������������������������",ch))? Thin :
                     (ExistCh("ۭ۰۱۲۴۵۶۷۹ۿ������������������������������",ch))? Thick: Noline;
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
           LeftF=(ExistCh("��������������������������",ch)) ? Thin :
                 (ExistCh("��������������������������",ch)) ? Thick: Noline;
         else
           LeftF=(ExistCh("ۣۡۦ۪ۧۨ۫۷۽ۿ������������������������������",ch)) ? Thin :
                 (ExistCh("۬ۮ۱۲۳۵۶۸ۺۻۼ����������������������������",ch)) ? Thick: Noline;
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
             RightF=ExistCh("ԴԶԷԽԿ����������������",ch) ? Thin :
                    ExistCh("ԵԸԹԻԼԾ��������������",ch) ? Thick: Noline;
          else
             RightF=ExistCh("ۡۤۥۨ۩۪۫۹۽ۿ������������������������������",ch) ? Thin :
                    ExistCh("۬ۯ۰۳۴۵۶۸ۺۻ۾����������������������������",ch) ? Thick: Noline;

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
   tty_xy(WX+1,4); tty_output("����Կ����Ը����Է����Իۣۨۤ��۸����۽��ۮ۳ۯ");
   tty_xy(WX+1,5); tty_output("����Դ����Ե����Զ����Թۧ۫۩ۼۻ۾۷��۹۲۶۴");
   tty_xy(WX+1,6); tty_output("����������Ծ����Խ����Լۦ۪ۥ��ۺ����ۿ��۱۵۰");
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

