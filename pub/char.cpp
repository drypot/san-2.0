                                                                                                                        /*
--------------------------------------------------------------------------------
   pub/char.cpp
   copyright(c) kyuhyun park
   1993.07.08
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/charlist.hpp>
#include <pub/io.hpp>
#include <cnt/array.hpp>

static byte johab_hangul_byte_ary[]=
   "ˆaˆbˆeˆhˆiˆjˆkˆqˆsˆtˆuˆvˆwˆxˆyˆ{ˆ|ˆ}ˆˆ‚ˆ…ˆ‰ˆ‘ˆ“ˆ•ˆ–ˆ—"
   "ˆ¡ˆ¢ˆ¥ˆ©ˆµˆ·ˆÁˆÅˆÉˆáˆâˆåˆèˆéˆëˆñˆóˆõˆöˆ÷ˆøˆûˆüˆı"
   "‰A‰E‰I‰Q‰S‰U‰V‰W‰a‰b‰c‰e‰h‰i‰q‰s‰u‰v‰w‰{‰‰…‰‰‰“‰•"
   "‰¡‰¢‰¥‰¨‰©‰«‰­‰°‰±‰³‰µ‰·‰¸‰Á‰Â‰Å‰É‰Ë‰Ñ‰Ó‰Õ‰×‰á‰å‰é‰ñ‰ö‰÷"
   "ŠAŠBŠEŠIŠQŠSŠUŠWŠaŠeŠiŠsŠuŠŠ‚Š…ŠˆŠ‰ŠŠŠ‹ŠŠ‘Š“Š•Š—Š˜"
   "Š¡Š¢Š¥Š©Š¶Š·ŠÁŠÕŠáŠâŠåŠéŠñŠóŠõ"
   "‹A‹E‹I‹a‹b‹e‹h‹i‹j‹q‹s‹u‹w‹‹¡‹¢‹¥‹¨‹©‹«‹±‹³‹µ‹·‹¸‹¼"
   "ŒaŒbŒcŒeŒiŒkŒqŒsŒuŒvŒwŒ{ŒŒ‚Œ…Œ‰Œ‘Œ“Œ•Œ–Œ—"
   "Œ¡Œ¢Œ©ŒáŒâŒãŒåŒéŒñŒóŒõŒöŒ÷"
   "ABEQUWaeiuv{¡¢¥§©±³µ·¸¹"
   "ÁÂÉÖ×áâ÷"
   "AEIQSWa‚…‰‘“•—˜"
   "¡©¶·ÁÂÅÉÑÓÖáåéñó"
   "Aabegikpqsuw{¡¢¥©±³µ·"
   "abcehijkqsuvwxy{}‚…‰‘“•–—"
   "¡¢¥©±·áâäåéëìñóõö÷ı"
   "‘A‘B‘E‘I‘Q‘S‘U‘V‘W‘a‘b‘e‘i‘q‘s‘v‘w‘z‘‘…"
   "‘¡‘¢‘¥‘©‘«‘±‘³‘µ‘·‘¼‘½‘Á‘Å‘É‘Ö"
   "’A’E’I’Q’S’U’a’b’e’i’s’u’w’’‚’…’ˆ’‰’‘’“’•’—’¡’¶’Á’á’å’é’ñ’ó"
   "“A“B“I“Q“S“W“a“b“e“i“j“k“q“s“u“w“x“|““…“‰“¡“¢“¥“©“¯“±“³“µ“·“¼"
   "”a”b”c”e”h”i”j”k”l”p”q”s”u”v”w”x”y”}””‚”…”‰”‘”“”•”–”—"
   "”¡”á”â”ã”å”è”é”ë”ì”ñ”ó”õ”÷”ù”ü"
   "•A•B•E•I•Q•S•U•V•W•a•e•i•v•w••…•¡•¢•¥•¨•©•«•­•±•³•µ•·•¹•»"
   "•Á•Å•É•á•ö"
   "–A–E–I–Q–S–U–a––‚–…–‰–‘–“–•–—–¡–¶–Á–×–á–å–é–ó–õ–÷"
   "—A—E—I—Q—W—a—b—e—h—i—k—q—s—u—w——¡—¢—¥—¨—©—±—³—µ—¶—·—¸"
   "˜a˜b˜e˜i˜q˜s˜u˜v˜w˜}˜˜‚˜…˜‰˜‘˜“˜•˜–˜—˜á˜â˜å˜é˜ë˜ì˜ñ˜ó˜õ˜ö˜÷˜ı"
   "™A™B™E™I™Q™S™U™V™W™a™v™¡™¢™¥™©™·™Á™É™á"
   "šAšEšš‚š…š‰šš‘š—šÁšášåšéšñšóš÷"
   "›a›b›e›h›i›q›s›u››…›‰›‘›“›¡›¥›©›±›³›µ›·"
   "œaœbœeœiœqœsœuœvœwœxœ|œ}œœ‚œ…œ‰œ‘œ“œ•œ–œ—"
   "œ¡œ¢œ¥œµœ·œáœâœåœéœñœóœõœöœ÷œı"
   "ABEIQSUWabeiqsuvw…“•¡¢¥©±³µ·"
   "ÁÅ×ö"
   "AEIQSUWaeisuw‚…‰‘“•—¡¶Ááâåéñõ÷"
   "ŸAŸBŸEŸIŸQŸSŸUŸWŸaŸbŸeŸiŸqŸsŸuŸwŸxŸ{Ÿ|Ÿ¡Ÿ¢Ÿ¥Ÿ©Ÿ±Ÿ³ŸµŸ·"
   " a b e g h i j k q s u w x { }  ‚ … ‰ ‘ “ • – — ˜"
   " ¡ ¢ © · á â å é ë ñ ó õ ÷ ø ı"
   "¡A¡B¡E¡I¡Q¡S¡U¡V¡W¡a¡b¡e¡i¡u¡v¡w¡y¡¡¡¡¢¡¤¡¥¡©¡«¡±¡³¡µ¡·¡Á¡Å¡Ö¡×"
   "¢A¢E¢I¢S¢U¢W¢a¢e¢i¢s¢u¢¢‚¢ƒ¢…¢ˆ¢‰¢Š¢‹¢‘¢“¢•¢—¢›¢"
   "¢¡¢¥¢©¢³¢µ¢Á¢á¢å¢é"
   "£A£E£I£Q£U£a£e£i£q£u£¡£¢£¥£¨£©£«£±£³£µ£¶£·£¹£»"
   "¤a¤b¤c¤d¤e¤h¤i¤j¤k¤l¤q¤s¤u¤w¤{¤¤‚¤…¤‰¤‘¤“¤•¤–¤—¤›"
   "¤¡¤¢¤¥¤³¤á¤â¤å¤è¤é¤ë¤ñ¤ó¤õ¤÷¤ø"
   "¥A¥B¥E¥H¥I¥Q¥S¥U¥V¥W¥a¥b¥e¥i¥s¥u¥v¥w¥{"
   "¥¥…¥¡¥¢¥£¥¥¥©¥±¥³¥µ¥·¥Á¥Å¥Ö¥á¥ö"
   "¦A¦B¦E¦I¦Q¦S¦a¦e¦¦‚¦…¦ˆ¦‰¦Š¦‹¦‘¦“¦•¦—¦›¦œ¦¡¦©¦¶¦Á¦á¦â¦å¦é¦÷"
   "§A§E§I§Q§U§W§a§b§e§i§q§s§u§¡§¢§¥§©§«§±§³§µ§·§¸§¹"
   "¨a¨b¨e¨i¨k¨q¨s¨u¨v¨w¨}¨¨‚¨…¨‰¨‘¨“¨•¨–¨—¨¡¨¢¨±¨á¨â¨å¨è¨é¨ñ¨õ¨ö¨÷"
   "©A©W©a©b©q©s©u©v©w©¡©¢©¥©©©±©³©·"
   "ªAªaªwªª‚ª…ª‰ª‘ª•ª—"
   "«A«W«a«e«i«q«s«¡«¢«¥«©«±«³«µ«·"
   "¬a¬b¬d¬e¬h¬i¬j¬k¬q¬s¬u¬v¬w¬{¬¬‚¬…¬‰¬‘¬“¬•¬–¬—¬¡¬¢¬¥¬©¬±¬³¬µ¬·"
   "¬Á¬Å¬É¬Ñ¬×¬á¬â¬ã¬ä¬å¬è¬é¬ë¬ì¬ñ¬ó¬õ¬ö¬÷¬ü"
   "­A­B­E­I­Q­S­U­V­W­a­b­e­i­q­s­u­v­w­­…­‰­—"
   "­¡­¢­£­¥­©­«­±­³­µ­·­»­Á­Â­Å­É­×­á­å­é­ñ­õ­ö"
   "®A®E®I®Q®S®U®a®b®e®i®q®s®u®w®®‚®…®ˆ®‰®‘®“®•®—®™®›®œ"
   "®¡®¶®Á®Â®Å®É®Ñ®×®á®â®å®é®ñ®ó®õ®÷"
   "¯A¯B¯I¯Q¯U¯W¯a¯b¯e¯i¯j¯q¯s¯u¯w¯¡¯¢¯¥¯¨¯©¯°¯±¯³¯µ¯·¯¼"
   "°a°b°d°e°i°q°s°v°w°}°°‚°…°‰°‘°“°–°—°·°á°â°å°é°ë°ñ°ó°ö°÷"
   "±A±E±I±W±¡±¢±¥±¨±©±«±±±³±·±Á±Â±Å±Ö±á±ö"
   "²A²E²I²Q²S²a²²‚²…²‰²‘²“²—²¡²¶²Á²á²å"
   "³W³a³b³e³i³k³p³q³s³³…³‰³‘³¡³¢³¥³©³±³³³µ³·"
   "´a´b´e´f´g´i´j´k´p´q´s´u´v´w´{´|´´‚´…´‰´‘´“´•´–´—"
   "´¡´¢´¥´©´¬´±´³´µ´·´»´½´Á´Å´É´Ó´á´â´å´æ´è´é´ê´ë´ñ´ó´ô´õ´ö´÷´ø´ú´ü"
   "µAµBµEµIµQµSµUµWµaµbµcµeµiµkµlµqµsµtµuµvµwµ{µ|µ}µµ…µ‰µ‘µ“µ•µ–"
   "µ¡µ¢µ¥µ©µªµ«µ­µ°µ±µ³µµµ·µ¹µÁµÂµÅµÉµÑµÓµÕµÖµ×µáµâµåµñµõµ÷"
   "¶A¶B¶E¶I¶Q¶S¶U¶W¶a¶b¶e¶i¶q¶s¶u¶w¶¶‚¶…¶‰¶Š¶‹¶‘¶“¶•¶—"
   "¶¡¶¢¶¥¶©¶±¶³¶¶¶·¶Á¶Â¶Å¶É¶Ñ¶Ó¶×¶á¶â¶å¶é¶ñ¶ó¶õ¶÷"
   "·A·B·E·I·Q·S·U·W·Y·a·b·e·i·o·q·s·u·w·x·y·z·{·|·}"
   "··…·‰·‘·•·¡·¢·¥·©·ª·«·°·±·³·µ·¶···¸·¼"
   "¸a¸b¸e¸g¸h¸i¸k¸q¸s¸u¸v¸w¸x¸¸‚¸…¸‰¸‘¸“¸•¸–¸—"
   "¸¡¸¢¸¥¸§¸©¸±¸·¸Á¸Å¸É¸á¸â¸å¸é¸ë¸ñ¸ó¸õ¸÷¸ø"
   "¹A¹B¹E¹I¹Q¹S¹U¹W¹a¹e¹i¹q¹s¹v¹w¹¹¡¹¢¹¥¹©¹«¹±¹³¹µ¹·¹¸¹¹¹½"
   "¹Á¹Â¹É¹Ó¹Õ¹×¹á¹ö¹÷"
   "ºAºEºIºQºSºUºWºaºbºeºwºº‚º…º‰ºŠº‹º‘º“º•º—º¡º¶ºÁºáºâºåºéºñºóºõ"
   "»A»E»I»Q»a»b»e»i»q»s»u»w»¡»¢»¥»¨»©»«»±»³»µ»·»¸»»»¼"
   "¼a¼b¼e¼g¼i¼l¼q¼s¼u¼v¼w¼¼‚¼…¼‰¼‘¼“¼•¼–¼—¼¡¼¥¼·¼á¼â¼å¼é¼ñ¼ó¼õ¼ö¼÷"
   "½A½W½a½v½¡½¢½¥½©½±½³½µ½·½¹½Á½Â½É½Ö½á½ö"
   "¾A¾E¾I¾Q¾S¾w¾¾‚¾…¾‰¾‘¾“¾—¾¡¾¶¾·¾á"
   "¿A¿a¿q¿u¿w¿¡¿¢¿¥¿©¿±¿³¿·¿¸¿½"
   "ÀaÀbÀeÀgÀiÀqÀsÀuÀvÀwÀxÀÀ‚À…À‰À‘À“À•À–À—"
   "À¡À¥À§À©À±À·ÀáÀâÀåÀéÀñÀóÀõÀöÀ÷"
   "ÁAÁBÁEÁIÁQÁSÁUÁWÁaÁeÁvÁÁ…Á—Á¡Á¢Á¥Á©Á±Á³ÁµÁ·ÁÁÁÅÁÉÁ×"
   "ÂAÂEÂIÂQÂSÂUÂWÂaÂqÂÂ‚Â…Â‰Â‘Â“Â•Â—Â¡Â¶ÂÁÂÅÂáÂåÂéÂñÂóÂõÂ÷"
   "ÃAÃEÃIÃQÃWÃaÃbÃeÃiÃqÃsÃuÃwÃ¡Ã¢Ã¥Ã¨Ã©ÃªÃ±Ã³ÃµÃ·"
   "ÄaÄbÄeÄiÄqÄsÄuÄwÄÄ‚Ä…Ä‰Ä‘Ä“Ä•Ä–Ä—Ä¡Ä¢Ä·ÄáÄâÄåÄèÄéÄñÄóÄõÄöÄ÷"
   "ÅAÅBÅEÅIÅQÅSÅUÅWÅaÅeÅiÅqÅsÅuÅvÅwÅÅ¡Å¢Å¥Å©Å±Å³ÅµÅ·ÅÁÅÂÅÅÅÉÅÑÅ×ÅáÅ÷"
   "ÆAÆIÆaÆÆ‚Æ…Æ‰Æ‘Æ“Æ•Æ—Æ¡Æ¥Æ©Æ·ÆÁÆ×ÆáÆâÆåÆéÆñÆóÆõÆ÷"
   "ÇAÇEÇIÇQÇaÇbÇeÇiÇqÇsÇwÇ¡Ç¢Ç¥Ç©Ç±Ç³ÇµÇ·"
   "ÈaÈbÈeÈiÈjÈqÈsÈuÈvÈwÈÈ‚È…È‰È‘È“È•È–È—È¡È·ÈáÈâÈåÈéÈëÈñÈóÈõÈöÈ÷"
   "ÉAÉBÉEÉIÉQÉSÉUÉWÉaÉeÉvÉÉ…É¡É¢É¥É©É±É³ÉµÉ·É¼ÉÁÉÅÉá"
   "ÊAÊEÊUÊWÊaÊÊ‚Ê…Ê‰Ê‘Ê“Ê•Ê—Ê¡Ê¶ÊÁÊáÊâÊåÊéÊñÊóÊ÷"
   "ËAËEËIËQËWËaËbËeËhËiËkËqËsËuËË…Ë‰Ë‘Ë“Ë¡Ë¢Ë¥Ë©Ë±Ë³ËµË·"
   "ÌaÌbÌcÌeÌiÌkÌqÌsÌuÌvÌwÌ{ÌÌ‚Ì…Ì‰Ì‘Ì“Ì•Ì–Ì—Ì¡Ì¢ÌáÌâÌåÌéÌñÌóÌõÌöÌ÷"
   "ÍAÍBÍEÍIÍQÍSÍUÍWÍaÍeÍiÍqÍsÍvÍwÍÍ‰Í“Í•Í¡Í¢Í¥Í©Í±Í³ÍµÍ·ÍÁÍ×"
   "ÎAÎEÎaÎeÎiÎsÎuÎÎ‚Î…ÎˆÎ‰Î‹Î‘Î“Î•Î—Î¡Î·ÎáÎåÎéÎñÎõ"
   "ÏAÏEÏIÏQÏUÏWÏaÏeÏiÏqÏsÏuÏ¡Ï¢Ï¥Ï©Ï±Ï³ÏµÏ·"
   "ĞaĞbĞeĞiĞnĞqĞsĞuĞwĞĞ‚Ğ…Ğ‰Ğ‘Ğ“Ğ•Ğ–Ğ—Ğ¡Ğ·ĞáĞâĞåĞéĞëĞñĞóĞõĞ÷"
   "ÑAÑBÑEÑIÑQÑSÑUÑWÑaÑbÑeÑiÑqÑsÑuÑvÑwÑÑ…Ñ‰Ñ“"
   "Ñ¡Ñ¢Ñ¥Ñ©Ñ®Ñ±Ñ³ÑµÑ·Ñ»ÑÁÑÂÑÅÑÉÑÕÑ×ÑáÑâÑåÑõÑ÷"
   "ÒAÒBÒEÒIÒSÒUÒWÒaÒeÒiÒsÒuÒÒ‚Ò…Ò‰ÒÒ‘Ò•Ò—"
   "Ò¡Ò¥Ò©Ò±Ò·ÒÁÒÂÒÅÒÉÒ×ÒáÒâÒåÒéÒñÒóÒõÒ÷"
   "ÓAÓBÓEÓIÓQÓUÓWÓaÓbÓeÓgÓhÓiÓjÓqÓsÓuÓwÓ{"
   "ÓÓ…Ó‰Ó‘Ó“Ó—Ó¡Ó¢Ó¥Ó©Ó±Ó³ÓµÓ·" ;

static char16 hangul_c16_ary[472] =
{
   0x8861,0x8862,0x8865,0x8869,  0x8871,0x8873,0x8877,0x8881,  0x8882,0x8897,0x88a2,0x88e1,  0x88e5,0x88e9,0x88f1,0x88f3,
   0x8941,0x8962,0x8965,0x8969,  0x8971,0x8977,0x8981,0x89a1,  0x89a2,0x89a5,0x89a9,0x89b7,  0x89b8,0x89c1,0x89c2,0x89c5,
   0x89c9,0x89d7,0x89e1,0x8a41,  0x8a57,0x8a61,0x8a81,0x8a82,  0x8a85,0x8a89,0x8a97,0x8aa5,  0x8aa9,0x8ac1,0x8ae1,0x8b41,
   0x8b45,0x8b49,0x8b62,0x8b65,  0x8b69,0x8b71,0x8b73,0x8b77,  0x8ba1,0x8ba5,0x8ba9,0x8bb1,  0x8bb3,0x9061,0x9062,0x9065,
   0x9069,0x9071,0x9073,0x9077,  0x9081,0x9097,0x9161,0x9165,  0x9171,0x9177,0x91a1,0x91a2,  0x91a5,0x91b7,0x9241,0x9261,
   0x9281,0x9285,0x9289,0x9341,  0x9362,0x9371,0x9377,0x93a1,  0x93a2,0x9461,0x9465,0x9469,  0x9471,0x9473,0x9477,0x9481,
   0x9482,0x94e2,0x95a1,0x95a2,  0x95a5,0x95a9,0x95b7,0x9681,  0x9685,0x9762,0x9777,0x9c61,  0x9c62,0x9c65,0x9c69,0x9c71,
   0x9c73,0x9c77,0x9c81,0x9c97,  0x9ca2,0x9cb7,0x9d61,0x9d62,  0x9d65,0x9d69,0x9d71,0x9d73,  0x9d77,0x9d81,0x9da1,0x9da2,
   0x9da5,0x9db7,0x9e41,0x9e61,  0x9e77,0x9e81,0x9f41,0x9f42,  0x9f45,0x9f49,0x9f57,0x9f62,  0x9f71,0x9f77,0x9fa1,0x9fa5,
   0x9fb1,0x9fb3,0xa061,0xa062,  0xa065,0xa069,0xa077,0xa081,  0xa082,0xa097,0xa162,0xa165,  0xa169,0xa177,0xa181,0xa1a1,
   0xa1a2,0xa1a9,0xa1b7,0xa261,  0xa281,0xa282,0xa285,0xa289,  0xa3a1,0xa3a5,0xa3a9,0xa462,  0xa465,0xa469,0xa477,0xa481,
   0xa482,0xa4e5,0xa4e9,0xa4f1,  0xa4f3,0xa562,0xa565,0xa569,  0xa577,0xa5a1,0xa5a2,0xa5a5,  0xa5a9,0xa5b7,0xa681,0xa682,
   0xa685,0xa689,0xa697,0xa7a1,  0xa7a5,0xa7b7,0xac61,0xac62,  0xac65,0xac69,0xac71,0xac73,  0xac77,0xac81,0xac82,0xac97,
   0xace1,0xace2,0xace5,0xace9,  0xacf1,0xacf3,0xacf7,0xad41,  0xada1,0xada2,0xada5,0xada9,  0xadb7,0xade1,0xae41,0xae81,
   0xae82,0xae85,0xae89,0xae97,  0xaf69,0xaf73,0xaf77,0xafa1,  0xafa2,0xafa5,0xafa9,0xafb1,  0xafb3,0xb077,0xb3a1,0xb461,
   0xb462,0xb465,0xb469,0xb471,  0xb473,0xb477,0xb481,0xb482,  0xb497,0xb4a1,0xb4a2,0xb4b7,  0xb4e1,0xb4e2,0xb4e5,0xb4e9,
   0xb4f1,0xb4f3,0xb545,0xb561,  0xb562,0xb565,0xb569,0xb571,  0xb573,0xb577,0xb581,0xb5a1,  0xb5a2,0xb5a5,0xb5a9,0xb5b7,
   0xb5c1,0xb5c5,0xb5c9,0xb5d7,  0xb5e1,0xb641,0xb661,0xb662,  0xb677,0xb681,0xb682,0xb685,  0xb689,0xb697,0xb6a5,0xb6a9,
   0xb6e1,0xb741,0xb742,0xb745,  0xb749,0xb757,0xb765,0xb769,  0xb771,0xb773,0xb777,0xb781,  0xb7a1,0xb7a2,0xb7a5,0xb7a9,
   0xb7b1,0xb7b3,0xb7b7,0xb861,  0xb862,0xb865,0xb871,0xb873,  0xb877,0xb881,0xb897,0xb8e1,  0xb8e2,0xb8e5,0xb8e9,0xb8f1,
   0xb8f3,0xb8f7,0xb941,0xb9a1,  0xb9a2,0xb9a5,0xb9a9,0xb9b7,  0xb9c1,0xba41,0xba81,0xba82,  0xba85,0xba89,0xba97,0xbb62,
   0xbb69,0xbb73,0xbb77,0xbba1,  0xbba2,0xbba5,0xbba9,0xbbb1,  0xbbb3,0xbbb7,0xc061,0xc062,  0xc065,0xc069,0xc071,0xc077,
   0xc081,0xc082,0xc0e1,0xc0e2,  0xc0e5,0xc0e9,0xc0f1,0xc0f3,  0xc0f7,0xc141,0xc1a1,0xc1a2,  0xc1a5,0xc1b7,0xc1c9,0xc241,
   0xc281,0xc282,0xc285,0xc289,  0xc297,0xc2e1,0xc362,0xc377,  0xc3a1,0xc3a2,0xc3a5,0xc3a9,  0xc3b1,0xc3b3,0xc3b7,0xc5e1,
   0xc861,0xc862,0xc865,0xc869,  0xc871,0xc873,0xc877,0xc881,  0xc882,0xc897,0xc8e1,0xc9a1,  0xc9b7,0xca41,0xca81,0xcb62,
   0xcb71,0xcc61,0xcc65,0xcc69,  0xcc81,0xcc97,0xcca2,0xcd65,  0xcd71,0xcd77,0xcd81,0xcda1,  0xcda2,0xce61,0xce91,0xce97,
   0xcfa1,0xcfa9,0xcfb3,0xd061,  0xd062,0xd065,0xd069,0xd071,  0xd073,0xd077,0xd081,0xd082,  0xd097,0xd0b7,0xd0e1,0xd0e5,
   0xd0e9,0xd0f1,0xd162,0xd165,  0xd169,0xd171,0xd173,0xd177,  0xd181,0xd1a1,0xd1a2,0xd1a5,  0xd1a9,0xd1b7,0xd1c1,0xd1c2,
   0xd1c5,0xd1c9,0xd1d7,0xd241,  0xd242,0xd257,0xd261,0xd281,  0xd285,0xd297,0xd385,0xd2c1,  0xd2e1,0xd341,0xd349,0xd357,
   0xd362,0xd365,0xd369,0xd371,  0xd373,0xd377,0xd381,0xd3a9
};

static char16 hanja_c16_ary [472]=
{
   0xe031,0xe04e,0xe059,0xe071,  0xe07b,0xe0a1,0xe0a7,0xe0bf,  0xe0d3,0xe0d5,0xe0d9,0xe0da,  0xe0eb,0xe0f7,0xe0fb,0xe134,
   0xe137,0xe13a,0xe141,0xe14c,  0xe153,0xe158,0xe197,0xe1af,  0xe1d6,0xe1dd,0xe1e7,0xe1ea,  0xe1fa,0xe1fb,0xe239,0xe23d,
   0xe24e,0xe252,0xe25f,0xe262,  0xe26b,0xe26f,0xe29a,0xe2d0,  0xe2d6,0xe2dc,0xe2e0,0xe2e6,  0xe2f0,0xe2f5,0xe2fb,0xe333,
   0xe342,0xe349,0xe34a,0xe351,  0xe360,0xe361,0xe36f,0xe376,  0xe37a,0xe3cc,0xe3cd,0xe3d1,  0xe3d2,0xe3d3,0xe3e2,0xe3ea,
   0xe3f3,0xe3f5,0xe3fe,0xe435,  0xe43c,0xe442,0xe443,0xe444,  0xe447,0xe44b,0xe44d,0xe45f,  0xe465,0xe466,0xe46d,0xe473,
   0xe474,0xe47c,0xe47d,0xe47e,  0xe492,0xe494,0xe495,0xe49b,  0xe49d,0xe49f,0xe4a1,0xe4b5,  0xe4ba,0xe4cb,0xe4d0,0xe4db,
   0xe4eb,0xe4ec,0xe4ee,0xe548,  0xe552,0xe55c,0xe55e,0xe56f,  0xe57a,0xe592,0xe593,0xe59c,  0xe5a5,0xe5ae,0xe5b7,0xe5b9,
   0xe5c3,0xe5c6,0xe5ce,0xe5d2,  0xe5d3,0xe5d5,0xe5e2,0xe5f4,  0xe5fb,0xe639,0xe63f,0xe644,  0xe645,0xe657,0xe65c,0xe66e,
   0xe675,0xe676,0xe67d,0xe697,  0xe6a3,0xe6a4,0xe6b1,0xe6bf,  0xe6c2,0xe6c8,0xe6cc,0xe6cd,  0xe6cf,0xe6d0,0xe6d6,0xe6f0,
   0xe6f9,0xe6fe,0xe734,0xe73c,  0xe742,0xe755,0xe75c,0xe768,  0xe776,0xe77b,0xe793,0xe795,  0xe7a0,0xe7a2,0xe7b1,0xe7b2,
   0xe7ca,0xe7d1,0xe7d3,0xe7d6,  0xe7e2,0xe7f8,0xe7fa,0xe838,  0xe83b,0xe84e,0xe85b,0xe85e,  0xe871,0xe89c,0xe8a7,0xe8c3,
   0xe8d7,0xe8df,0xe8e9,0xe8ed,  0xe8f6,0xe8f8,0xe935,0xe93c,  0xe940,0xe951,0xe961,0xe972,  0xe973,0xe974,0xe996,0xe9c1,
   0xe9c2,0xe9d5,0xe9da,0xe9e0,  0xea3d,0xea4b,0xea4f,0xea9d,  0xeaa1,0xeaad,0xeab2,0xeaba,  0xeabe,0xeadd,0xeae0,0xeae5,
   0xeaea,0xeb3a,0xeb49,0xeb69,  0xeb76,0xeb7e,0xeb94,0xeba6,  0xebaf,0xebd4,0xebdd,0xebe3,  0xebe4,0xebec,0xebf1,0xebf3,
   0xec62,0xec6e,0xec9b,0xec9f,  0xeca2,0xeca5,0xecaa,0xecb4,  0xecd0,0xecdf,0xecf7,0xecfb,  0xed37,0xed3a,0xed3b,0xed3c,
   0xed4e,0xed5c,0xed66,0xed6a,  0xed72,0xed76,0xed7d,0xed9a,  0xeda1,0xeda5,0xedb0,0xedb9,  0xedd8,0xede2,0xede7,0xeded,
   0xedef,0xedf5,0xedf7,0xedf8,  0xee42,0xee4f,0xee7a,0xee96,  0xeea5,0xeea9,0xeed1,0xeee9,  0xef39,0xef3e,0xef44,0xef45,
   0xef4e,0xef56,0xef68,0xef69,  0xef6e,0xef72,0xef77,0xefaf,  0xefb5,0xefcd,0xefed,0xeff6,  0xf035,0xf038,0xf03a,0xf055,
   0xf058,0xf071,0xf0bb,0xf0c2,  0xf0cf,0xf0d4,0xf0d9,0xf0e0,  0xf0e1,0xf0e7,0xf0ea,0xf0ee,  0xf133,0xf159,0xf161,0xf179,
   0xf194,0xf19f,0xf1a4,0xf1a8,  0xf1c2,0xf1cf,0xf1d4,0xf1da,  0xf1db,0xf232,0xf243,0xf247,  0xf263,0xf27c,0xf2b7,0xf2bf,
   0xf2c8,0xf2cb,0xf334,0xf34b,  0xf379,0xf37d,0xf391,0xf394,  0xf3a5,0xf3aa,0xf3ab,0xf3d3,  0xf3d5,0xf3e8,0xf3e9,0xf3ed,
   0xf3ee,0xf3ef,0xf3f3,0xf3fd,  0xf451,0xf456,0xf479,0xf49a,  0xf49c,0xf4a3,0xf4a7,0xf4b5,  0xf4bc,0xf4cb,0xf4d0,0xf4da,
   0xf4f0,0xf4fc,0xf532,0xf536,  0xf545,0xf558,0xf562,0xf56c,  0xf576,0xf57e,0xf59a,0xf5b5,  0xf5bb,0xf5bf,0xf5c9,0xf5ca,
   0xf5cd,0xf5e4,0xf5f0,0xf5f3,  0xf5f6,0xf5fc,0xf640,0xf645,  0xf646,0xf652,0xf661,0xf662,  0xf665,0xf66e,0xf66f,0xf671,
   0xf672,0xf692,0xf6a2,0xf6ac,  0xf6ae,0xf6b2,0xf6b5,0xf6ba,  0xf6c8,0xf6cb,0xf6cc,0xf6cd,  0xf6d1,0xf6d8,0xf6de,0xf6e4,
   0xf6e6,0xf6e7,0xf6f7,0xf732,  0xf735,0xf740,0xf744,0xf745,  0xf74f,0xf750,0xf755,0xf75f,  0xf77b,0xf793,0xf7a1,0xf7a3,
   0xf7a8,0xf7af,0xf7b9,0xf7bb,  0xf7c9,0xf7ce,0xf7dc,0xf7de,  0xf7ea,0xf7f1,0xf834,0xf846,  0xf848,0xf84d,0xf856,0xf85a,
   0xf852,0xf85f,0xf861,0xf865,  0xf87a,0xf87e,0xf891,0xf89d,  0xf8b1,0xf8ba,0xf8e3,0xf8e6,  0xf8ec,0xf8ef,0xf8f9,0xf939,
   0xf93f,0xf950,0xf955,0xf96d,  0xf993,0xf995,0xf998,0xf9a5,  0xf9b2,0xf9bc,0xf9bd,0xf9c1,  0xf9c4,0xf9cc,0xf9d1,0xf9d4,
   0xf9d9,0xf9da,0xf9de,0xf9e2,  0xf9e5,0xf9e9,0xf9ea,0xf9fe
};

static byte hanja_cnt_byte_ary[472] =
{
   29, 11, 24, 10,    20,  6, 24, 20,     2,  4,  1, 17,    12,  4,  7,  3,
    3,  7, 11,  6,     6, 45, 24, 39,     7, 10,  3, 16,     1, 12,  4, 17,
    4, 13,  3,  9,     4, 25, 54,  6,     6,  4,  6, 10,     5,  6,  6,  9,
    7,  1,  7, 15,     1, 14,  7,  4,    64,  1,  4,  1,     1, 15,  8,  9,
    2,  9,  5,  7,     6,  1,  1,  3,     4,  2, 18,  6,     1,  7,  6,  1,
    8,  1,  1,  2,     2,  1,  6,  2,     2,  2, 20,  5,    17,  5, 11, 16,
    1,  2, 40, 10,    10,  2, 17, 11,     6,  1,  9,  9,     9,  9,  2, 10,
    3,  8,  4,  1,     2, 13, 18,  7,    12,  6,  5,  1,    18,  5, 18,  7,
    1,  7,  8, 12,     1, 13, 14,  3,     6,  4,  1,  2,     1,  6, 26,  9,
    5,  4,  8,  6,    19,  7, 12, 14,     5,  6,  2, 11,     2, 15,  1, 24,
    7,  2,  3, 12,    22,  2, 12,  3,    19, 13,  3, 19,    25, 11, 28, 20,
    8, 10,  4,  9,     2, 11,  7,  4,    17, 16, 17,  1,     1, 16, 43,  1,
   19,  5,  6, 43,    14,  4, 60,  4,    12,  5,  8,  4,    31,  3,  5,  5,
   30, 15, 32, 13,     8,  4, 18,  9,    37,  9,  6,  1,     8,  5,  2, 61,
   12, 27,  4,  3,     3,  5, 10, 28,    15, 24,  4, 10,     3,  1,  1, 18,
   14, 10,  4,  8,     4,  7, 11,  7,     4, 11,  9, 31,    10,  5,  6,  2,
    6,  2,  1, 24,    13, 43, 10, 15,     4, 40, 24, 30,     5,  6,  1,  9,
    8, 18,  1,  5,     4,  5, 38,  6,    24, 32,  9, 13,     3,  2, 27,  3,
   25, 56,  7, 13,     5,  5,  7,  1,     6,  3,  4, 19,    38,  8, 24,  9,
   11,  5,  4, 26,    13,  5,  6,  1,    38, 17,  4, 28,    25, 41,  8,  9,
    3, 55, 23, 46,     4,  2,  3, 17,     5,  1, 40,  2,    19,  1,  4,  1,
    1,  3, 11, 34,     5, 35, 15,  2,     7,  3, 15,  7,    15,  5, 10, 22,
   12,  4,  4, 15,    19, 10, 10, 10,     8, 10, 27,  6,     4, 10,  1,  3,
   23, 12,  3,  3,     6, 18,  5,  1,    24,  3,  1,  3,     9,  1,  2,  1,
   14, 16, 10,  2,     4,  3,  5, 14,     3,  1,  1,  4,     7,  6,  6,  2,
    1, 16,  9,  3,    11,  4,  1, 10,     1,  5, 10, 28,     6, 14,  2,  5,
    7, 10,  2, 14,     5, 14,  2, 12,     7, 17, 18,  2,     5,  9,  4,  4,
    1,  2,  4, 21,     4,  1, 12, 20,     9, 41,  3,  6,     3, 10, 14,  6,
   17,  5, 24, 20,     2,  3, 13, 13,    10,  1,  4,  3,     8,  5,  3,  5,
    1,  4,  4,  3,     4,  1, 20,  1
};

bool cls_wchar::is_wansung ()
{
   return (
            is_inside ( bytes.high , 0xa1 , 0xac ) ||
            is_inside ( bytes.high , 0xb0 , 0xc8 ) ||
            is_inside ( bytes.high , 0xca , 0xfd )
          )
          &&
          (
            is_inside ( bytes.low , 0xa0 , 0xff )
          )
          ;
}

bool cls_wchar::is_johab ()
{
   return is_inside ( bytes.high , 0x84 , 0xd3 ) && is_inside ( bytes.low , 0x41 , 0xfd ) ||
          is_inside ( bytes.high , 0xd4 , 0xd4 ) && is_inside ( bytes.low , 0x80 , 0xff ) ||
          is_inside ( bytes.high , 0xd9 , 0xde ) && ( is_inside ( bytes.low , 0x30 , 0x7f ) || is_inside ( bytes.low , 0x90 , 0xff ) ) ||
          is_inside ( bytes.high , 0xe0 , 0xf9 ) && ( is_inside ( bytes.low , 0x30 , 0x7f ) || is_inside ( bytes.low , 0x90 , 0xff ) )
          ;
}

void cls_wchar::to_wansung ()
{
   if ( bytes.high < 0xd4 )
   {
      //
      //  hangul
      //

      if ( bytes.high >= 0x84 )
      {
         cls_wchar* wchar_ary = (cls_wchar*) johab_hangul_byte_ary;
         int start = 0;
         int end = (sizeof(johab_hangul_byte_ary) - 1) / 2 - 1 ;   // consider '\0' terminatior
         int index;
         cls_wchar tmp_wchar;

         while ( start <= end )
         {
            index = ( start + end ) / 2 ;
            tmp_wchar = wchar_ary[index];

            if ( bytes.high > tmp_wchar.bytes.low ) start = index + 1 ;
            ef ( bytes.high < tmp_wchar.bytes.low ) end   = index - 1 ;
            ef ( bytes.low > tmp_wchar.bytes.high ) start = index + 1 ;
            ef ( bytes.low < tmp_wchar.bytes.high ) end   = index - 1 ;
            el
            {
               bytes.high = byte((index / 94) + 0xb0);
               bytes.low = byte((index % 94) + 0xa1);
               return;
            }
         }
      }

      c16 = 0 /*0xb0a0*/;
      return;
   }

   if  ( bytes.high >= 0xe0 )
   {
      //
      //  hanja
      //

      if ( bytes.high < 0xfa )
      {
         if ( is_inside ( bytes.low , 0xa1 , 0xfe ) )
         {
            bytes.high = byte(( bytes.high - 0xe0 ) * 2 + 0xcb );
            return;
         }
         ef ( is_inside ( bytes.low , 0x91 , 0xa0 ) )
         {
            bytes.low = byte(bytes.low - ( 0x91 - 0x7f ) + ( 0xa0 - 0x30 ));
            bytes.high = byte((bytes.high - 0xe0) * 2 + 0xca);
            return;
         }
         ef ( is_inside ( bytes.low , 0x31 , 0x7e ) )
         {
            bytes.low = byte(bytes.low + (0xa0 - 0x30));
            bytes.high = byte((bytes.high - 0xe0) * 2 + 0xca);
            return;
         }
      }
      c16 = 0 /*0xcaa0*/;
      return;
   }

   {
      //
      //  graph
      //

      if ( is_inside ( bytes.high , 0xd9 , 0xde ) )
      {
         if ( is_inside ( bytes.low , 0xa1 , 0xfe ) )
         {
            bytes.high = byte((bytes.high - 0xd9) * 2 + 0xa2);
            return;
         }
         ef ( is_inside ( bytes.low , 0x91 , 0xa0 ) )
         {
            bytes.low = byte(bytes.low - (0x91 - 0x7f) + (0xa0 - 0x30));
            bytes.high = byte((bytes.high - 0xd9) * 2 + 0xa1);
            return;
         }
         ef ( is_inside ( bytes.low , 0x31 , 0x7e ) )
         {
            bytes.low = byte(bytes.low + (0xa0 - 0x30));
            bytes.high = byte((bytes.high - 0xd9) * 2 + 0xa1);
            return;
         }
      }
      ef (bytes.high == 0xd4)
      {
         if (bytes.low >= 0x80)
         {
            if (bytes.low < 0x80 + 0x60 - 2)
            {
               bytes.high = 0xad;
               bytes.low  = bytes.low - 0x80 + 0xa1;
               return;
            }
            else
            {
               bytes.high = 0xae;
               bytes.low  = bytes.low - 0x80 - (0x60-2) + 0xa1;
               return;
            }
         }
      }
      c16 = 0 /*0xa1a0*/;
      return;
   }
}

void cls_wchar::to_johab ()
{
   if ( is_inside ( bytes.high , 0xb0 , 0xc8 ) )
   {
      //
      //  hangul
      //

      if ( is_inside ( bytes.low , 0xa1 , 0xfe ) )
      {
         int index;
         index  = (int)(bytes.high-0xb0)*(0xfe-0xa1+1);
         index += bytes.low-0xa1;
         bytes.high = johab_hangul_byte_ary[index*2];
         bytes.low  = johab_hangul_byte_ary[index*2+1];
         return;
      }
   }

   if ( is_inside ( bytes.high , 0xa1 , 0xac ) )
   {
      //
      //  graph
      //

      if ( is_inside ( bytes.low , 0xa1 , 0xfe ) )
      {
         if (bytes.high & 1)
         {
            bytes.low  = byte(bytes.low > 0xee ? bytes.low - 0x70 + 0x12 : bytes.low - 0x70);
            bytes.high = byte((bytes.high - 0xa1) / 2 + 0xd9);
         }
         else
         {
            bytes.high = byte((bytes.high - 0xa1) / 2 + 0xd9);
         }
         return;
      }
   }

   if (bytes.high == 0xad)
   {
      bytes.high = 0xd4;
      bytes.low  = bytes.low - 0xa1 + 0x80;
      return;
   }

   if (bytes.high == 0xae)
   {
      bytes.high = 0xd4;
      bytes.low  = bytes.low - 0xa1 + 0x80 + (0x60 - 2);
      return;
   }

   if ( is_inside ( bytes.high , 0xca , 0xfd ) )
   {
      //
      // hanja
      //

      if ( is_inside ( bytes.low , 0xa1 , 0xfe ) )
      {
         if (bytes.high & 1)
         {
            bytes.high = byte((bytes.high-0xca)/2+0xe0);
         }
         else
         {
            bytes.low  = byte(bytes.low > 0xee ? bytes.low-0x70+0x12 : bytes.low-0x70);
            bytes.high = byte((bytes.high - 0xca) / 2 + 0xe0);
         }
         return;
      }
   }

   c16 = 0 /*c16_han_c_fill*/;
   return;
}

void cls_wchar::to_hangul()
{
   int i;
   forcnt (i, mac_cnt_of (hanja_c16_ary)) if (hanja_c16_ary[i] > this->c16 ) break;
   this->c16 = hangul_c16_ary[i-1];
}

void cls_wchar::set_hanja_page(cls_hanja_page* hanja_page)
{
   int index = binary_search(hangul_c16_ary, mac_cnt_of(hangul_c16_ary), c16);

   if ( index == -1 )
   {
      hanja_page->cnt = 0;
   }
   else
   {
      cls_wchar wchar;

      hanja_page->cnt = hanja_cnt_byte_ary[index];
      wchar.c16 = hanja_c16_ary[index];

      int i;
      forcnt ( i, hanja_page->cnt )
      {
         hanja_page->contents[i] = wchar.c16;

         int column = chcl_to_index ( wchar.bytes.low );
         if ( ++ column == 188 )
         {
            wchar.bytes.high++;
            column=0;
         }
         wchar.bytes.low = (byte) index_to_chcl (column);
      }
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

char16 h1_to_cardi_ary[32]=
{
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9,10,11,12,13,14,
   15,16,17,18,19, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

char16 h2_to_cardi_ary[32]=
{
    0, 0, 0, 1, 2, 3, 4, 5,
    0, 0, 6, 7, 8, 9,10,11,
    0, 0,12,13,14,15,16,17,
    0, 0,18,19,20,21, 0, 0
};

char16 h3_to_cardi_ary[32]=
{
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9,10,11,12,13,14,
   15,16, 0,17,18,19,20,21,
   22,23,24,25,26,27, 0, 0
};

char16 cardi_to_h1_ary[32]=
{
    1, 2, 3, 4, 5, 6, 7, 8,
    9,10,11,12,13,14,15,16,
   17,18,19,20,
};

char16 cardi_to_h2_ary[32]=
{
    2, 3, 4, 5, 6, 7,10,11,
   12,13,14,15,18,19,20,21,
   22,23,26,27,28,29,
};

char16 cardi_to_h3_ary[32]=
{
    1, 2, 3, 4, 5, 6, 7, 8,
    9,10,11,12,13,14,15,16,
   17,19,20,21,22,23,24,25,
   26,27,28,29,
};
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void to_wansung (char* p)
{
   while ( *p )
   {
      if ( is_single(*p) )
      {
         p++;
      }
      else
      {
         ( (cls_wchar*) p ) -> swap();
         ( (cls_wchar*) p ) -> to_wansung();
         ( (cls_wchar*) p ) -> swap();
         p+=2;
      }
   }
}

void to_wansung (char* p , size_t sz)
{
   char* end_pch = p + sz;

   while ( p < end_pch )
   {
      if ( is_single(*p) )
      {
         p++;
      }
      else
      {
         ( (cls_wchar*) p ) -> swap();
         ( (cls_wchar*) p ) -> to_wansung();
         ( (cls_wchar*) p ) -> swap();
         p+=2;
      }
   }
}

void to_wansung ( char16* p )
{
   while (*p)
   {
     if (is_double(*p)) ((cls_wchar*)p) -> to_wansung();
     p++;
   }
}

void to_wansung ( char16* p, size_t sz)
{
   char16* end_pnt = p + sz;

   while ( p < end_pnt )
   {
     if ( is_double(*p) ) ( (cls_wchar*) p ) -> to_wansung();
     p++;
   }
}

void to_johab ( char* p )
{
   while ( *p )
   {
      if ( is_single(*p) )
      {
         p++;
      }
      else
      {
         ( (cls_wchar*) p ) -> swap();
         ( (cls_wchar*) p ) -> to_johab();
         ( (cls_wchar*) p ) -> swap();
         p += 2;
      }
   }
}

void to_johab ( char* p , size_t sz )
{
   char* end_pch = p + sz;

   while ( p < end_pch )
   {
      if ( is_single(*p) )
      {
         p++;
      }
      else
      {
         ( (cls_wchar*) p ) -> swap();
         ( (cls_wchar*) p ) -> to_johab();
         ( (cls_wchar*) p ) -> swap();
         p += 2;
      }
   }
}

void to_johab (char16* p)
{
   while ( *p )
   {
     if ( is_double(*p) ) ( (cls_wchar*) p ) -> to_johab();
     p++;
   }
}

void to_johab (char16* p, size_t sz)
{
   char16* end_pnt = p + sz;

   while ( p < end_pnt )
   {
     if ( is_double(*p) ) ( (cls_wchar*) p ) -> to_johab();
     p++;
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

#define def_detect_buf_size 2048
#define def_detect_hit_rate 95
#define def_detect_sample_min 10

int detect_hangul_code_type ( char* fname , int default_code_type)
{
   cls_rfile file(fname);
   tem_array<byte> buf_byte_array(def_detect_buf_size);
   int check_cnt = 0;
   int wansung_cnt = 0;
   off_t buf_size = get_min ( (off_t) file.get_size() , (off_t) def_detect_buf_size );
   byte* buf_base_byte_pnt = buf_byte_array.get_base();
   byte* buf_limit_byte_pnt = buf_byte_array.get_base() + buf_size;
   cls_wchar han_wchar;

   file.read (buf_base_byte_pnt, buf_size);

   while ( buf_base_byte_pnt + 1 < buf_limit_byte_pnt )
   {
      if ( is_double(*buf_base_byte_pnt) )
      {
         han_wchar.bytes.high = *buf_base_byte_pnt++;
         han_wchar.bytes.low  = *buf_base_byte_pnt++;
         check_cnt ++;
         if ( han_wchar.is_wansung() ) wansung_cnt ++;
      }
      else
      {
         buf_base_byte_pnt ++;
      }
   }

   if ( check_cnt < def_detect_sample_min || wansung_cnt == 0 )
   {
      return default_code_type;
   }
   else
   {
      return (uint32)wansung_cnt * 100 / check_cnt < def_detect_hit_rate  ? def_ct_johab : def_ct_wansung ;
   }
}

int sp1_to_cardi (cls_wchar wchar)
{
   return wchar.bytes.high == 0xd4 && is_inside(wchar.bytes.low, 0x81, 0xfe) ? wchar.bytes.low - 0x80 : -1;
}

int sp2_to_cardi (cls_wchar wchar)
{
   if ( is_inside_less ( wchar.bytes.high , 0xd9 , 0xdf ) )
   {
      if ( is_inside ( wchar.bytes.low , 0x31 , 0x7e ) )
      {
         return (wchar.bytes.high - 0xd9) * 188 + (wchar.bytes.low - 0x31);
      }
      ef ( is_inside ( wchar.bytes.low , 0x91 , 0xfe ) )
      {
         return (wchar.bytes.high - 0xd9) * 188 + (wchar.bytes.low - 0x91 + 78);
      }
   }
   return -1;
}

int hnj_to_cardi (cls_wchar wchar)
{
   if ( is_inside_less ( wchar.bytes.high , 0xe0 , 0xfa ) )
   {
      if ( is_inside ( wchar.bytes.low , 0x31 , 0x7e ) )
      {
         return (wchar.bytes.high - 0xe0) * 188 + (wchar.bytes.low - 0x31);
      }
      ef ( is_inside ( wchar.bytes.low , 0x91 , 0xfe ) )
      {
         return (wchar.bytes.high - 0xe0) * 188 + (wchar.bytes.low - 0x91 + 78);
      }
   }
   return -1;
}
