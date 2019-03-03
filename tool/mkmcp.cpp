                                                                                                                        /*
--------------------------------------------------------------------------------
   mkmcp.cpp -- make meta-code-page

   copyright(C) kyuhyun park

   1993.09.04
   1994.10.25
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#include <pub/io.hpp>
#include <key/mc.hpp>

char qwertyName[MCP_NAME_SIZE] = "qwt";
char dvorakName[MCP_NAME_SIZE] = "DVORAK";
char han390Name[MCP_NAME_SIZE] = "≠A§ÈØ¢";
char han2Name[MCP_NAME_SIZE] = "ñÅ§ÈØ¢";

uint32 qwertyTable[]={

   14,     // A line Size
   12,     // B line Size
   11,     // C line Size
   10,     // D line Size

   MC_LANG_ENGLISH | '`',
   MC_LANG_ENGLISH | '1',
   MC_LANG_ENGLISH | '2',
   MC_LANG_ENGLISH | '3',
   MC_LANG_ENGLISH | '4',
   MC_LANG_ENGLISH | '5',
   MC_LANG_ENGLISH | '6',
   MC_LANG_ENGLISH | '7',
   MC_LANG_ENGLISH | '8',
   MC_LANG_ENGLISH | '9',
   MC_LANG_ENGLISH | '0',
   MC_LANG_ENGLISH | '-',
   MC_LANG_ENGLISH | '=',
   MC_LANG_ENGLISH | '\\',

   MC_LANG_ENGLISH | 'q'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'w'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'e'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'r'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 't'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'y'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'u'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'i'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'o'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'p'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | '[',
   MC_LANG_ENGLISH | ']',

   MC_LANG_ENGLISH | 'a'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 's'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'd'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'f'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'g'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'h'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'j'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'k'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'l'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | ';',
   MC_LANG_ENGLISH | '\'',

   MC_LANG_ENGLISH | 'z'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'x'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'c'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'v'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'b'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'n'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'm'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | ',',
   MC_LANG_ENGLISH | '.',
   MC_LANG_ENGLISH | '/',


   MC_LANG_ENGLISH | '~',
   MC_LANG_ENGLISH | '!',
   MC_LANG_ENGLISH | '@',
   MC_LANG_ENGLISH | '#',
   MC_LANG_ENGLISH | '$',
   MC_LANG_ENGLISH | '%',
   MC_LANG_ENGLISH | '^',
   MC_LANG_ENGLISH | '&',
   MC_LANG_ENGLISH | '*',
   MC_LANG_ENGLISH | '(',
   MC_LANG_ENGLISH | ')',
   MC_LANG_ENGLISH | '_',
   MC_LANG_ENGLISH | '+',
   MC_LANG_ENGLISH | '|',

   MC_LANG_ENGLISH | 'Q',
   MC_LANG_ENGLISH | 'W',
   MC_LANG_ENGLISH | 'E',
   MC_LANG_ENGLISH | 'R',
   MC_LANG_ENGLISH | 'T',
   MC_LANG_ENGLISH | 'Y',
   MC_LANG_ENGLISH | 'U',
   MC_LANG_ENGLISH | 'I',
   MC_LANG_ENGLISH | 'O',
   MC_LANG_ENGLISH | 'P',
   MC_LANG_ENGLISH | '{',
   MC_LANG_ENGLISH | '}',

   MC_LANG_ENGLISH | 'A',
   MC_LANG_ENGLISH | 'S',
   MC_LANG_ENGLISH | 'D',
   MC_LANG_ENGLISH | 'F',
   MC_LANG_ENGLISH | 'G',
   MC_LANG_ENGLISH | 'H',
   MC_LANG_ENGLISH | 'J',
   MC_LANG_ENGLISH | 'K',
   MC_LANG_ENGLISH | 'L',
   MC_LANG_ENGLISH | ':',
   MC_LANG_ENGLISH | '\"',

   MC_LANG_ENGLISH | 'Z',
   MC_LANG_ENGLISH | 'X',
   MC_LANG_ENGLISH | 'C',
   MC_LANG_ENGLISH | 'V',
   MC_LANG_ENGLISH | 'B',
   MC_LANG_ENGLISH | 'N',
   MC_LANG_ENGLISH | 'M',
   MC_LANG_ENGLISH | '<',
   MC_LANG_ENGLISH | '>',
   MC_LANG_ENGLISH | '?'
};

uint32 dvorakTable[]={

   14,     // A line Size
   12,     // B line Size
   11,     // C line Size
   10,     // D line Size

   MC_LANG_ENGLISH | '`',
   MC_LANG_ENGLISH | '1',
   MC_LANG_ENGLISH | '2',
   MC_LANG_ENGLISH | '3',
   MC_LANG_ENGLISH | '4',
   MC_LANG_ENGLISH | '5',
   MC_LANG_ENGLISH | '6',
   MC_LANG_ENGLISH | '7',
   MC_LANG_ENGLISH | '8',
   MC_LANG_ENGLISH | '9',
   MC_LANG_ENGLISH | '0',
   MC_LANG_ENGLISH | '[',
   MC_LANG_ENGLISH | '=',
   MC_LANG_ENGLISH | '\\',

   MC_LANG_ENGLISH | '\'',
   MC_LANG_ENGLISH | ',',
   MC_LANG_ENGLISH | '.',
   MC_LANG_ENGLISH | 'p'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'y'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'f'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'g'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'c'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'r'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'l'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | '/',
   MC_LANG_ENGLISH | ']',

   MC_LANG_ENGLISH | 'a'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'o'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'e'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'u'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'i'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'd'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'h'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 't'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'n'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 's'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | '-',

   MC_LANG_ENGLISH | ';',
   MC_LANG_ENGLISH | 'q'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'j'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'k'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'x'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'b'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'm'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'w'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'v'  | MC_ATTR_CAPS_LOCK,
   MC_LANG_ENGLISH | 'z'  | MC_ATTR_CAPS_LOCK,


   MC_LANG_ENGLISH | '~',
   MC_LANG_ENGLISH | '!',
   MC_LANG_ENGLISH | '@',
   MC_LANG_ENGLISH | '#',
   MC_LANG_ENGLISH | '$',
   MC_LANG_ENGLISH | '%',
   MC_LANG_ENGLISH | '^',
   MC_LANG_ENGLISH | '&',
   MC_LANG_ENGLISH | '*',
   MC_LANG_ENGLISH | '(',
   MC_LANG_ENGLISH | ')',
   MC_LANG_ENGLISH | '{',
   MC_LANG_ENGLISH | '+',
   MC_LANG_ENGLISH | '|',

   MC_LANG_ENGLISH | '"',
   MC_LANG_ENGLISH | '<',
   MC_LANG_ENGLISH | '>',
   MC_LANG_ENGLISH | 'P',
   MC_LANG_ENGLISH | 'Y',
   MC_LANG_ENGLISH | 'F',
   MC_LANG_ENGLISH | 'G',
   MC_LANG_ENGLISH | 'C',
   MC_LANG_ENGLISH | 'R',
   MC_LANG_ENGLISH | 'L',
   MC_LANG_ENGLISH | '?',
   MC_LANG_ENGLISH | '}',

   MC_LANG_ENGLISH | 'A',
   MC_LANG_ENGLISH | 'O',
   MC_LANG_ENGLISH | 'E',
   MC_LANG_ENGLISH | 'U',
   MC_LANG_ENGLISH | 'I',
   MC_LANG_ENGLISH | 'D',
   MC_LANG_ENGLISH | 'H',
   MC_LANG_ENGLISH | 'T',
   MC_LANG_ENGLISH | 'N',
   MC_LANG_ENGLISH | 'S',
   MC_LANG_ENGLISH | '_',

   MC_LANG_ENGLISH | ':',
   MC_LANG_ENGLISH | 'Q',
   MC_LANG_ENGLISH | 'J',
   MC_LANG_ENGLISH | 'K',
   MC_LANG_ENGLISH | 'X',
   MC_LANG_ENGLISH | 'B',
   MC_LANG_ENGLISH | 'M',
   MC_LANG_ENGLISH | 'W',
   MC_LANG_ENGLISH | 'V',
   MC_LANG_ENGLISH | 'Z'
};

uint32 han390Table[]={

   14,     // A line Size
   12,     // B line Size
   11,     // C line Size
   10,     // D line Size

   MC_LANG_ENGLISH  | '`',
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_H,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_SS,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_B,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAU,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAII,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UA,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_K,
   MC_LANG_ENGLISH  | '-',
   MC_LANG_ENGLISH  | '=',
   MC_LANG_ENGLISH  | '\\',

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_S,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_R,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AI,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_R,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_D,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_M,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_C,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_P,
   MC_LANG_ENGLISH  | '[',
   MC_LANG_ENGLISH  | ']',

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_Y,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_N,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_I,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_U     | MC_ATTR_def_noCOMBI,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_N,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_Y,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_G,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_J,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_B,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_T,

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_M,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_G,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AII,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AU    | MC_ATTR_def_noCOMBI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UA    | MC_ATTR_def_noCOMBI,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_S,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_H,
   MC_LANG_ENGLISH  | ',',
   MC_LANG_ENGLISH  | '.',
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AU,


   MC_LANG_ENGLISH  | '~',
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_J,
   MC_LANG_ENGLISH  | '@',
   MC_LANG_ENGLISH  | '#',
   MC_LANG_ENGLISH  | '$',
   MC_LANG_ENGLISH  | '%',
   MC_LANG_ENGLISH  | '^',
   MC_LANG_ENGLISH  | '&',
   MC_LANG_ENGLISH  | '*',
   MC_LANG_ENGLISH  | '(',
   MC_LANG_ENGLISH  | ')',
   MC_LANG_ENGLISH  | '_',
   MC_LANG_ENGLISH  | '+',
   MC_LANG_ENGLISH  | '|',

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_P,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_T,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_K,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAAI,
   MC_LANG_ENGLISH  | ';',
   MC_LANG_ENGLISH  | '<',
   MC_LANG_ENGLISH  | '7',
   MC_LANG_ENGLISH  | '8',
   MC_LANG_ENGLISH  | '9',
   MC_LANG_ENGLISH  | '>',
   MC_LANG_ENGLISH  | '{',
   MC_LANG_ENGLISH  | '}',

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_D,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_NH,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_RG,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_GG,
   MC_LANG_ENGLISH  | '/',
   MC_LANG_ENGLISH  | '\'',
   MC_LANG_ENGLISH  | '4',
   MC_LANG_ENGLISH  | '5',
   MC_LANG_ENGLISH  | '6',
   MC_LANG_ENGLISH  | ':',
   MC_LANG_ENGLISH  | '"',

   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_C,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_BS,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_RM,
   MC_LANG_HANGUL   | MC_TYPE_H3 | MC_OFFSET_H3_RH,
   MC_LANG_ENGLISH  | '!',
   MC_LANG_ENGLISH  | '0',
   MC_LANG_ENGLISH  | '1',
   MC_LANG_ENGLISH  | '2',
   MC_LANG_ENGLISH  | '3',
   MC_LANG_ENGLISH  | '?'
};

uint32 han2Table[]={

   14,     // A line Size
   12,     // B line Size
   11,     // C line Size
   10,     // D line Size

   MC_LANG_ENGLISH  | '`',
   MC_LANG_ENGLISH  | '1',
   MC_LANG_ENGLISH  | '2',
   MC_LANG_ENGLISH  | '3',
   MC_LANG_ENGLISH  | '4',
   MC_LANG_ENGLISH  | '5',
   MC_LANG_ENGLISH  | '6',
   MC_LANG_ENGLISH  | '7',
   MC_LANG_ENGLISH  | '8',
   MC_LANG_ENGLISH  | '9',
   MC_LANG_ENGLISH  | '0',
   MC_LANG_ENGLISH  | '-',
   MC_LANG_ENGLISH  | '=',
   MC_LANG_ENGLISH  | '\\',

   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_B,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_J,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_D,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_G,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_S,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAU,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AII,
   MC_LANG_ENGLISH  | '[',
   MC_LANG_ENGLISH  | ']',

   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_M,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_N,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_Y,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_R,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_H,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AU,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_I,
   MC_LANG_ENGLISH  | ';',
   MC_LANG_ENGLISH  | '\'',

   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_K,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_T,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_C,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_P,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_U,
   MC_LANG_ENGLISH  | ',',
   MC_LANG_ENGLISH  | '.',
   MC_LANG_ENGLISH  | '/',


   MC_LANG_ENGLISH  | '~',
   MC_LANG_ENGLISH  | '!',
   MC_LANG_ENGLISH  | '@',
   MC_LANG_ENGLISH  | '#',
   MC_LANG_ENGLISH  | '$',
   MC_LANG_ENGLISH  | '%',
   MC_LANG_ENGLISH  | '^',
   MC_LANG_ENGLISH  | '&',
   MC_LANG_ENGLISH  | '*',
   MC_LANG_ENGLISH  | '(',
   MC_LANG_ENGLISH  | ')',
   MC_LANG_ENGLISH  | '_',
   MC_LANG_ENGLISH  | '+',
   MC_LANG_ENGLISH  | '|',

   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_BB,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_JJ,
   MC_LANG_HANGUL   | MC_TYPE_H1 | MC_OFFSET_H1_DD,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_GG,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_SS,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAU,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IAAI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AAII,
   MC_LANG_ENGLISH  | '{',
   MC_LANG_ENGLISH  | '}',

   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_M,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_N,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_Y,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_R,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_H,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AU,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_AI,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_IA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_I,
   MC_LANG_ENGLISH  | ':',
   MC_LANG_ENGLISH  | '"',

   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_K,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_T,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_C,
   MC_LANG_HANGUL   | MC_TYPE_H4 | MC_OFFSET_H4_P,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UAA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_UA,
   MC_LANG_HANGUL   | MC_TYPE_H2 | MC_OFFSET_H2_U,
   MC_LANG_ENGLISH  | '<',
   MC_LANG_ENGLISH  | '>',
   MC_LANG_ENGLISH  | '?'
};

#define WRITE(fname,name,type) Write ( fname, name##Name, type, name##Table, sizeof(name##Table) )

void Write ( char* name, char* mapName, uint32 main_type, void* p, size_t sz)
{
  WriteFileType MapFile(name);
  MapFile.Write(mapName, MCP_NAME_SIZE);
  MapFile.Write(&main_type, sizeof(main_type));
  MapFile.Write(p,sz);
}

void pcs_main()
{
   WRITE("..\\etc\\han3-90.mcp",han390, MC_LANG_HANGUL);
   WRITE("..\\etc\\han2.mcp",han2, MC_LANG_HANGUL);
   WRITE("..\\etc\\qwerty.mcp",qwerty, MC_LANG_ENGLISH);
   WRITE("..\\etc\\dvorak.mcp",dvorak, MC_LANG_ENGLISH);
}
