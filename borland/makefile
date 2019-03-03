#
#  makefile (borland version)
#
#  kyuhyun park
#

#------------------
#  make directive
#------------------

.autodepend
.cacheautodepend

#--------------------
#  project
#--------------------

!ifndef prj
!error unknown project
!endif

#----------------
#  target
#----------------

!ifndef tar
tar = unknown
!endif

#----------------------
#  platform
#----------------------

!ifndef pf
pf = pm
!endif

!if $(pf) == novio
pf_cc_opt    = -sm
pf_link_opt  = -ai -LI:\BCOS2\LIB -B:0x10000
startup_obj  = C02.OBJ
std_lib_list = OS2 C2MT
!endif

!if $(pf) == vio
pf_cc_opt    = -sm
pf_link_opt  = -ap -LI:\BCOS2\LIB -B:0x10000
startup_obj  = C02.OBJ
std_lib_list = OS2 C2MT
!endif

!if $(pf) == pm
pf_cc_opt    = -sm -Ddef_pm
pf_link_opt  = -aa -LI:\BCOS2\LIB -B:0x10000
startup_obj  = C02.OBJ
std_lib_list = OS2 C2MT
!endif

!if $(pf) == owlpm
pf_cc_opt    = -sm -Ddef_owl -D_OWLDLL
pf_link_opt  = -aa -LI:\BCOS2\LIB -B:0x10000
startup_obj  = C02.OBJ
std_lib_list = OS2 C2MT BIDS2I OWLPMI
!endif

!if $(pf) == owlwin
pf_cc_opt   = -Ddef_owl -D_OWLDLL
pf_link_opt = -aa
startup_obj = C0W32.OBJ
std_lib_list = CW32 IMPORT32 BIDSFI OWLWF
!endif

!if $(pf) == nt
pf_cc_opt =
pf_link_opt = -ap -B:0x10000
!endif

!ifndef pf_cc_opt
!error unknown platform
!endif

#---------------------
#  debug info level
#---------------------

!ifndef dil
dil = 1
!endif

!if $(dil) == 2
dil_cc_opt   = -k -N  -v -Ddef_debug
dil_link_opt = -v
!endif

!if $(dil) == 1
dil_cc_opt   = -k- -N -Ddef_debug
dil_link_opt =
!endif

!if $(dil) == 0
dil_cc_opt   = -k- -N-
dil_link_opt = -Oc
!endif

!ifndef dil_cc_opt
!error unknown debug-info-level
!endif

#------------
#  type
#------------

!ifndef type
!error type not defined
!endif

#-----------
#  filter
#-----------

cc   = bcc
cpp  = bcc
link = tlink
lib  = tlib

common_cc_opt   = -c -H -Hc -Ii:\bcos2\include -I..
common_link_opt = -c -x -Toe

cc_opt   = $(common_cc_opt) $(pf_cc_opt) $(dil_cc_opt) $(cc_opt_prj) -H=obj\pch\$(pf)\$(dil)\c
cpp_opt  = $(common_cc_opt) $(pf_cc_opt) $(dil_cc_opt) $(cc_opt_prj) -P  -H=obj\pch\$(pf)\$(dil)\p
link_opt = $(common_link_opt) $(pf_link_opt) $(dil_link_opt) $(link_opt_prj)
lib_opt  = /C /E

#-------------
#  directory
#-------------

obj_dir     = obj\$(prj)\$(pf)\$(dil)

pub_obj_dir = obj\pub\$(pf)\$(dil)
cnt_obj_dir = obj\cnt\$(pf)\$(dil)
net_obj_dir = obj\net\$(pf)\$(dil)
vio_obj_dir = obj\vio\$(pf)\$(dil)
key_obj_dir = obj\key\$(pf)\$(dil)
win_obj_dir = obj\win\$(pf)\$(dil)

pub_lib = obj\pub\$(pf)\$(dil)\pub.lib
cnt_lib = obj\cnt\$(pf)\$(dil)\cnt.lib
#net_lib = obj\net\$(pf)\$(dil)\net.lib
fnt_lib = obj\fnt\$(pf)\$(dil)\fnt.lib
vio_lib = obj\vio\$(pf)\$(dil)\vio.lib
key_lib = obj\key\$(pf)\$(dil)\key.lib
win_lib = obj\win\$(pf)\$(dil)\win.lib

all_lib_list  = $(pub_lib) $(cnt_lib) $(net_lib) $(fnt_lib) $(vio_lib) $(key_lib) $(win_lib)
user_lib_list = $(all_lib_list)

bin_dir  = ..\binos2

#----------------------------
#  start
#----------------------------

!message $(prj)-$(tar)-$(pf)-$(dil)-$(type)

begin : main

!include $(prj).mif
!include $(type).mif

#-----------------
#  implicit rule
#-----------------

.suffixes: .exe .res .obj .rc .asm .cpp .c .h .l .y

.y.h :
   bison -d -o $(@R).c $<

.y.c :
   bison -d -o $(@R).c $<

.l.c :
   flex -t -L $(<) > $@

.c.obj :
   $(cc) $(cc_opt) -n$(@D) {$< }

.cpp.obj :
   $(cpp) $(cpp_opt) -n$(@D) {$< }

.rc.res :
   rc -nologo -r $< $@

