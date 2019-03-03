																																								/*
--------------------------------------------------------------------------------
   fnt/hanfnt.cpp
	copyright(C) kyuhyun park
	1991.
-------------------------------------------------------------------------------- 													*/

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/io.hpp>
#include <pub/dir.hpp>
#include <pub/init.hpp>
#include <cnt/array.hpp>
#include <fnt/hanfnt.hpp>
																																								/*
--------------------------------------------------------------------------------

	�a��

      hanfnt �a �a�w�a�e �a���i�e �a�q�� �{�a.

		�����e ���� 19 �a�����a.
		�����e ���� 21 �a�����a.
		�����e ���� 27 �a�����a.

	10.4.4 �a�w�� ����

		�a�A ���� �a�w��, ���� �a�w��, ���� �a�w�� 3 �����a�� �a��a.

		����, ����, ���� �i�� �b�b 10, 4, 4 �鷁 �a�w�i�i �{�e�a.
		�b �鷁 ��q�A�e ���� ���a�a �s���E�a.

		����

			__ �A �A �A �A �A ... �A �A  --+
													 |
			__ �A �A �A �A �A ... �A �A	 |
													 |
			__ �A �A �A �A �A ... �A �A	 +-- �hñ ���e �i�a�w 5 ��
													 |
			__ �A �A �A �A �A ... �A �A	 |   ��e �����A �a�q
													 |
			__ �A �A �A �A �A ... �A �A  --+


			__ �A �A �A �A �A ... �A �A  --+
													 |
			__ �A �A �A �A �A ... �A �A	 |
													 |
			__ �A �A �A �A �A ... �A �A	 +-- �hñ ���e �i�a�w 5 ��
													 |
			__ �A �A �A �A �A ... �A �A	 |   ��e �����A �a�q
													 |
			__ �A �A �A �A �A ... �A �A  --+

			|								 |
			+------------+-----------+
							 |
						  20 �a


		����

			__ �a �� �� �� �� ... �� ��  --+-- �hñ ���e �i�a�w 2 ��
													 |
			__ �a �� �� �� �� ... �� ��  --+   ��e �����A �a�q


			__ �a �� �� �� �� ... �� ��  --+-- �hñ ���e �i�a�w 2 ��
													 |
			__ �a �� �� �� �� ... �� ��  --+   ��e �����A �a�q

			|								 |
			+------------+-----------+
							 |
						  22 �a

		����

			__ �B �C �D �E �F ... �\ �]  --+
													 |
			__ �B �C �D �E �F ... �\ �]	 |
													 +-- ���� 4 ��
			__ �B �C �D �E �F ... �\ �]	 |
													 |   ��e �����A �a�q
			__ �B �C �D �E �F ... �\ �]  --+

			|								 |
			+------------+-----------+
							 |
						  27 �a

	2.4 �a�w

      hanfnt ������ �����A�� �a�w�A�e �a�w �������a.
		�b���e ������ �����i �i�s���a ���� �a�w�q�a����
		���e �b �����i �w�a ��ǥ�a.

		����+����

			�� �����e ������ ���e ���A �a�w�I ������
			���e ���A �a�w�I 2 �����a�� �a��a.
			�b ������ �|�A�e ���� �a�w�� ͡�q�E�a.


			������ ���e �i�a�A �a�w�I �a�w


				�a �� �� �� �� ... �� ��  --+
													 |
			�A �a �� �� �� �� ... �� ��	 |
													 |
			�A �a �� �� �� �� ... �� ��	 |
													 |
			.										 +-- �����w 20 �a�w
													 |
			.										 |
													 |
			.										 |
													 |
			�A �a Ё С Ё �� ... Ӂ ӡ  --+

			|								 |
			+------------+-----------+
							 |
					  �����w 22 �a�w


			������ ���e �i�a�A �a�w�I �a�w


				�a �� �� �� �� ... �� ��  --+
													 |
			�A �a �� �� �� �� ... �� ��	 |
													 |
			�A �a �� �� �� �� ... �� ��	 |
													 |
			.										 +-- �����w 20 �a�w
													 |
			.										 |
													 |
			.										 |
													 |
			�A �a Ё С Ё �� ... Ӂ ӡ  --+

			|								 |
			+------------+-----------+
							 |
					  �����w 22 �a�w



		����

			4 �鷡�a. �����a�w �����A�e �a�� ������ ���a.


			�B �C �D �E �F �G ... �\ �]  --+
													 |
			�B �C �D �E �F �G ... �\ �]	 |
													 +-- 4
			�B �C �D �E �F �G ... �\ �]	 |
													 |
			�B �C �D �E �F �G ... �\ �]  --+

			|								  |
			+-------------+-----------+
							 |
							27 �a

-------------------------------------------------------------------------------- 													*/
																																								/*
--------------------------------------------------------------------------------
   fnt spec - 10*4*4
-------------------------------------------------------------------------------- 													*/

#define def_fnt_h1_cnt 20  // fnt num 19 real fnt plus 1 space fnt
#define def_fnt_h2_cnt 22  //         21 real fnt plus 1 space fnt
#define def_fnt_h3_cnt 28  //         27 real fnt plus 1 space fnt

#define def_suit_h1_cnt 10  // suit cnt
#define def_suit_h2_cnt 4
#define def_suit_h3_cnt 4

#define def_fnt_size sizeof(type_fnt16)
																																								/*
--------------------------------------------------------------------------------
   fnt file spec
-------------------------------------------------------------------------------- 													*/

#define def_mbk_fnt_cnt 400  // magic book    fnt specification
#define def_dkb_fnt_cnt 360  // dkb2 normal   fnt specification
#define def_mix_fnt_cnt 988  // def_fnt_h1_cnt * def_fnt_h2_cnt * 2 + (def_fnt_h3_cnt-1) * def_suit_h3_cnt

#define def_mbk_size_file (def_mbk_fnt_cnt * def_fnt_size)
#define def_dkb_size_file (def_dkb_fnt_cnt * def_fnt_size)
#define def_mix_size_file (def_mix_fnt_cnt * def_fnt_size)

void expand_mbk (char*);
void expand_dkb (char*);

struct cls_fnt_file_type
{
   off_t size;
   void (*func_pnt)(char*) ;
};

static cls_fnt_file_type fnt_file_type_ary[]=
{
   { def_mbk_size_file, expand_mbk },
   { def_dkb_size_file, expand_dkb },
	{ 0 , NULL	}
};

static type_fnt16 han_fnt16_ary[def_mix_fnt_cnt];
char* han_fnt_fname_pch;

void make_mix_fnt (type_fnt16* arg_fnt16_pnt)
{
   static byte h1_suit_ary [def_fnt_h2_cnt] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 3, 3, 3, 1, 2, 4,
		4, 4, 2, 1, 3, 0
	};

   static byte h2_suit_ary [def_fnt_h1_cnt] =
	{
		0, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1
	};

   int h1, h2, h3;
   int cnt = 0;

	//
   // h1|h2 part 1
	//

   forcnt (h1, def_fnt_h1_cnt)
	{
      forcnt (h2, def_fnt_h2_cnt)
		{
			memcpy
			(
            han_fnt16_ary + cnt,
            arg_fnt16_pnt + h1_suit_ary[h2]*def_fnt_h1_cnt + h1 ,
            def_fnt_size
			);
         mem_or
			(
            han_fnt16_ary + cnt,
            arg_fnt16_pnt + h2_suit_ary[h1]*def_fnt_h2_cnt + h2 + def_fnt_h1_cnt*def_suit_h1_cnt,
            def_fnt_size
			);
         cnt++;
		}
	}

	//
   // h1|h2 part 2
	//

   forcnt (h1, def_fnt_h1_cnt)
	{
      forcnt (h2, def_fnt_h2_cnt)
		{
			memcpy
			(
            han_fnt16_ary + cnt ,
            arg_fnt16_pnt + (h1_suit_ary[h2]+def_suit_h1_cnt/2)*def_fnt_h1_cnt + h1 ,
            def_fnt_size
			);
         mem_or
			(
            han_fnt16_ary + cnt ,
            arg_fnt16_pnt  + (h2_suit_ary[h1]+def_suit_h2_cnt/2)*def_fnt_h2_cnt + h2 + def_fnt_h1_cnt*def_suit_h1_cnt,
            def_fnt_size
			);
         cnt++;
		}
	}

	//
   // h3
	//

   forcnt(h3, def_suit_h3_cnt)
	{
		memcpy
		(
         han_fnt16_ary + cnt,
         arg_fnt16_pnt + h3*def_fnt_h3_cnt + 1 + def_fnt_h1_cnt*def_suit_h1_cnt + def_fnt_h2_cnt*def_suit_h2_cnt,
         (def_fnt_h3_cnt-1)*def_fnt_size
		);
      cnt += def_fnt_h3_cnt - 1;
	}
}

void expand_mbk(char* arg_fname)
{
   cls_rfile rfile(arg_fname);
   tem_array<byte> byte_array (def_mbk_size_file);

   rfile.read (byte_array.get_base(), def_mbk_size_file);
   mac_assert (byte_array.check());
   make_mix_fnt ((type_fnt16*)byte_array.get_base());
}

void expand_dkb(char* arg_fname)
{
   cls_rfile rfile(arg_fname);
   tem_array<byte> byte_array(def_mbk_size_file);
   type_fnt16* fnt16_pnt = (type_fnt16*)byte_array.get_base();

   rfile.read (byte_array.get_base(), def_dkb_size_file);
   mac_assert (byte_array.check ());

   {  // make def_mbk format

      //
      // move up h2,jong
      //

      memmove
      (
         fnt16_pnt+def_fnt_h1_cnt*10 ,
         fnt16_pnt+def_fnt_h1_cnt*8,
         (def_fnt_h2_cnt*4+def_fnt_h3_cnt*4)*def_fnt_size
      );

      // move up h1
      // def_dkbN han_fnt16_ary consists of 5 suits of han_fnt16_ary needing jong ,
      // and 3 suit of han_fnt16_ary not needing jong.

      memcpy
      (
         fnt16_pnt+def_fnt_h1_cnt*8,
         fnt16_pnt+def_fnt_h1_cnt*7,
         def_fnt_h1_cnt*def_fnt_size
      );

      memcpy
      (
         fnt16_pnt+def_fnt_h1_cnt*9,
         fnt16_pnt+def_fnt_h1_cnt*7,
         def_fnt_h1_cnt*def_fnt_size
      );

      memmove
      (
         fnt16_pnt+def_fnt_h1_cnt*7,
         fnt16_pnt+def_fnt_h1_cnt*6,
         def_fnt_h1_cnt*def_fnt_size
      );
      mac_assert(byte_array.check());
   }
   make_mix_fnt (fnt16_pnt);
}

void load_han_fnt (char* arg_fname)
{
   cls_rfile rfile(arg_fname);
   off_t fsz = rfile.get_size();
   rfile.close();

	int i=0;
   while (fnt_file_type_ary[i].size)
	{
      if (fnt_file_type_ary[i].size == fsz)
		{
         fnt_file_type_ary[i].func_pnt (arg_fname);
         return;
		}
		i++;
	}
   throw cls_xmsg("func: fnt/hanfnt.cpp/load_han_fnt\ninfo: unknown file type\n");
}

type_fnt16* get_han_fnt(cls_wchar wch)
{
   static uint part1_uint_ary [def_fnt_h1_cnt]=
	{
      def_fnt_h2_cnt * 0 ,
      def_fnt_h2_cnt * 1 ,
      def_fnt_h2_cnt * 2 ,
      def_fnt_h2_cnt * 3 ,
      def_fnt_h2_cnt * 4 ,
      def_fnt_h2_cnt * 5 ,
      def_fnt_h2_cnt * 6 ,
      def_fnt_h2_cnt * 7 ,
      def_fnt_h2_cnt * 8 ,
      def_fnt_h2_cnt * 9 ,
      def_fnt_h2_cnt * 10,
      def_fnt_h2_cnt * 11,
      def_fnt_h2_cnt * 12,
      def_fnt_h2_cnt * 13,
      def_fnt_h2_cnt * 14,
      def_fnt_h2_cnt * 15,
      def_fnt_h2_cnt * 16,
      def_fnt_h2_cnt * 17,
      def_fnt_h2_cnt * 18,
      def_fnt_h2_cnt * 19
	};

   static uint part2_uint_ary [def_fnt_h1_cnt]=
	{
      def_fnt_h2_cnt * 0  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 1  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 2  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 3  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 4  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 5  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 6  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 7  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 8  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 9  + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 10 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 11 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 12 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 13 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 14 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 15 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 16 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 17 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 18 + def_fnt_h1_cnt*def_fnt_h2_cnt ,
      def_fnt_h2_cnt * 19 + def_fnt_h1_cnt*def_fnt_h2_cnt
	};

   static uint part3_uint_ary [def_fnt_h2_cnt]=
	{
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 0,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 0,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 0,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 3,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 0,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 3,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 3,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 2,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 3,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 3,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1,
      def_fnt_h1_cnt * def_fnt_h2_cnt * 2  +  (def_fnt_h3_cnt - 1) * 1
	};

   uint h1, h2, h3;

   h1= h1_to_cardi(wch.parts.h1);
   h2= h2_to_cardi(wch.parts.h2);
   h3= h3_to_cardi(wch.parts.h3);

   if (h3)
	{
      static uint16 fnt_buf[16];
      register uint16* dst_pnt = fnt_buf;
      register uint16* fnt1_pnt = (uint16*)(han_fnt16_ary + part2_uint_ary[h1] + h2);
      register uint16* fnt2_pnt = (uint16*)(han_fnt16_ary + part3_uint_ary[h2] + h3 - 1) + 8;

      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;

      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;
      *dst_pnt++ = *fnt1_pnt++;

      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;

      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;
      *dst_pnt++ = *fnt1_pnt++ | *fnt2_pnt++;

      return (type_fnt16*) &fnt_buf;
	}
	else
	{
      return han_fnt16_ary + part1_uint_ary[h1] + h2;
	}
}

static void ctor()
{
   cls_fname fname;

   try
   {
      fname.set_path(han_fnt_fname_pch != NULL ? han_fnt_fname_pch : "@bindir/../font/sanigj.han");
      load_han_fnt(fname.get_path());
   }
   catch(cls_xmsg xmsg)
   {
      xmsg.add_info(cls_form_expander("func: fnt/hanfnt.cpp/ctor()\ninfo: font loading error\nfile: %s\n",fname.get_path()).get_pch());
      throw;
   }
}

static cls_initer initer(ctor, def_init_pri_fnt_hanfnt);
