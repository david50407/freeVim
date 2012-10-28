# Makefile for Vim on Win32 (Windows 2000/XP/2003)
# and Win64, using the Microsoft Visual C++ compilers. Known to work with
# VC6 (VS98), VC7.0 (VS2002), VC7.1 (VS2003), VC8 (VS2005),
# VC9 (VS2008), VC10 (VS2010), and VC11 (VS2012).

TARGETOS = BOTH
OBJDIR = ObjG
MAKE = nmake
link = link

# Win32.mak requires that CPU be set appropriately.
# To cross-compile for Win64, set CPU=AMD64 or CPU=IA64.

!ifdef CPU
ASSEMBLY_ARCHITECTURE=$(CPU)
# Using I386 for $ASSEMBLY_ARCHITECTURE doesn't work for VC7.
! if ("$(ASSEMBLY_ARCHITECTURE)" == "i386") || ("$(ASSEMBLY_ARCHITECTURE)" == "I386")
ASSEMBLY_ARCHITECTURE = x86
! endif
!else
CPU = $(PROCESSOR_ARCHITECTURE)
ASSEMBLY_ARCHITECTURE = $(PROCESSOR_ARCHITECTURE)
! if ("$(CPU)" == "x86") || ("$(CPU)" == "X86")
CPU = i386
! endif
!endif

# Build a retail version by default

!if "$(DEBUG)" == "yes"
DEBUG = 1
!else
! undef DEBUG
MAKEFLAGS_GVIMEXT = DEBUG=yes
!endif

# Get all sorts of useful, standard macros from the Platform SDK.

# !include <Win32.mak>

# Flag to turn on Win64 compatibility warnings for VC7.x and VC8.
WP64CHECK = /Wp64

#>>>>> path of the compiler and linker; name of include and lib directories
# PATH = c:\msvc20\bin;$(PATH)
# INCLUDE = c:\msvc20\include
# LIB = c:\msvc20\lib

!ifndef CTAGS
CTAGS = ctags
!endif

# Set which version of the CRT to use
!if defined(USE_MSVCRT)
# CVARS = $(cvarsdll)
# !elseif defined(MULTITHREADED)
# CVARS = $(cvarsmt)
!else
# CVARS = $(cvars)
# CVARS = $(cvarsmt)
!endif

# need advapi32.lib for GetUserName()
# need shell32.lib for ExtractIcon()
# gdi32.lib and comdlg32.lib for printing support
# ole32.lib and uuid.lib are needed for FEAT_SHORTCUT
CON_LIB = oldnames.lib kernel32.lib advapi32.lib shell32.lib gdi32.lib \
          comdlg32.lib ole32.lib uuid.lib /machine:$(CPU) /nodefaultlib
!if "$(DELAYLOAD)" == "yes"
CON_LIB = $(CON_LIB) /DELAYLOAD:comdlg32.dll /DELAYLOAD:ole32.dll DelayImp.lib
!endif

### Set the default $(WINVER) to make it work with VC++7.0 (VS.NET)
#  When set to 0x0500 ":browse" stops working.
!ifndef WINVER
WINVER = 0x0400
!endif

# If you have a fixed directory for $VIM or $VIMRUNTIME, other than the normal
# default, use these lines.
#VIMRCLOC = somewhere
#VIMRUNTIMEDIR = somewhere

CFLAGS = -c /W3 /nologo $(CVARS) -I. -Iproto -DHAVE_PATHDEF -DWIN32 -DFEAT_MENU \
		$(DEFINES) -DWINVER=$(WINVER) -D_WIN32_WINNT=$(WINVER) \
		/Fo$(OUTDIR)/ 

#>>>>> end of choices
###########################################################################

OS_TYPE	= winnt
DEL_TREE = rmdir /s /q

INTDIR=$(OBJDIR)
OUTDIR=$(OBJDIR)

# Derive version of VC being used from nmake if not specified
!if "$(MSVCVER)" == ""
! if "$(_NMAKE_VER)" == "6.00.8168.0"
MSVCVER = 6.0
CPU = ix86
! endif
! if "$(_NMAKE_VER)" == "7.00.9466"
MSVCVER = 7.0
! endif
! if "$(_NMAKE_VER)" == "7.10.3077"
MSVCVER = 7.1
! endif
! if "$(_NMAKE_VER)" == "8.00.50727.42"
MSVCVER = 8.0
! endif
! if "$(_NMAKE_VER)" == "8.00.50727.762"
MSVCVER = 8.0
! endif
! if "$(_NMAKE_VER)" == "9.00.20706.01"
MSVCVER = 9.0
! endif
! if "$(_NMAKE_VER)" == "9.00.21022.08"
MSVCVER = 9.0
! endif
! if "$(_NMAKE_VER)" == "9.00.30729.01"
MSVCVER = 9.0
! endif
! if "$(_NMAKE_VER)" == "9.00.30729.01"
MSVCVER = 9.0
! endif
! if "$(_NMAKE_VER)" == "10.00.20506.01"
MSVCVER = 10.0
! endif
! if "$(_NMAKE_VER)" == "10.00.30128.01"
MSVCVER = 10.0
! endif
! if "$(_NMAKE_VER)" == "10.00.30319.01"
MSVCVER = 10.0
! endif
! if "$(_NMAKE_VER)" == "11.00.50727.1"
MSVCVER = 11.0
! endif
!endif

# Abort bulding VIM if version of VC is unrecognised.
!ifndef MSVCVER
! message *** ERROR
! message Cannot determine Visual C version being used.  If you are using the
! message Windows SDK then you must have the environment variable MSVCVER set to
! message your version of the VC compiler.  If you are not using the Express
! message version of Visual C, you can either set MSVCVER or update this makefile
! message to handle the new value for _NMAKE_VER, "$(_NMAKE_VER)".
! error Make aborted.
!endif

!if ("$(MSVCVER)" == "8.0") || ("$(MSVCVER)" == "9.0") || ("$(MSVCVER)" == "10.0") || ("$(MSVCVER)" == "11.0")
MSVCNEW = 1
!endif

# Convert processor ID to MVC-compatible number
!if !defined(MSVCNEW)
! if "$(CPUNR)" == "i386"
CPUARG = /G3
! elseif "$(CPUNR)" == "i486"
CPUARG = /G4
! elseif "$(CPUNR)" == "i586"
CPUARG = /G5
! elseif "$(CPUNR)" == "i686"
CPUARG = /G6
! elseif "$(CPUNR)" == "pentium4"
CPUARG = /G7 /arch:SSE2
! else
CPUARG =
! endif
!else
# VC8/9 only allows specifying SSE architecture
! if "$(CPUNR)" == "pentium4"
CPUARG = /arch:SSE2
! endif
!endif

LIBC =
DEBUGINFO = /Zi

!ifndef DEBUG
VIM = vim
! if "$(OPTIMIZE)" == "SPACE"
OPTFLAG = /O1
! elseif "$(OPTIMIZE)" == "SPEED"
OPTFLAG = /O2
! else # MAXSPEED
OPTFLAG = /Ox
! endif

! ifdef MSVCNEW
# Use link time code generation if not worried about size
!  if "$(OPTIMIZE)" != "SPACE"
OPTFLAG = $(OPTFLAG) /GL
!  endif
! endif

# (/Wp64 is deprecated in VC9 and generates an obnoxious warning.)
! if ("$(MSVCVER)" == "7.0") || ("$(MSVCVER)" == "7.1") || ("$(MSVCVER)" == "8.0") 
CFLAGS=$(CFLAGS) $(WP64CHECK)
! endif

CFLAGS = $(CFLAGS) $(OPTFLAG) -DNDEBUG $(CPUARG)
RCFLAGS = $(rcflags) $(rcvars) -DNDEBUG
! ifdef USE_MSVCRT
CFLAGS = $(CFLAGS) /MD
LIBC = msvcrt.lib
! else
LIBC = libcmt.lib
CFLAGS = $(CFLAGS) /Zl /MT
! endif
!else  # DEBUG
VIM = vimd
! if ("$(CPU)" == "i386") || ("$(CPU)" == "ix86")
DEBUGINFO = /ZI
! endif
CFLAGS = $(CFLAGS) -D_DEBUG -DDEBUG /Od
RCFLAGS = $(rcflags) $(rcvars) -D_DEBUG -DDEBUG
# The /fixed:no is needed for Quantify. Assume not 4.? as unsupported in VC4.0.
! if "$(MSVCVER)" == "4.0"
LIBC =
! else
LIBC = /fixed:no
! endif
! ifdef USE_MSVCRT
CFLAGS = $(CFLAGS) /MDd
LIBC = $(LIBC) msvcrtd.lib
! else
LIBC = $(LIBC) libcmtd.lib
CFLAGS = $(CFLAGS) /Zl /MTd
! endif
!endif # DEBUG

INCL =	vim.h os_win32.h ascii.h feature.h globals.h keymap.h macros.h \
	proto.h option.h structs.h term.h

OBJ = \
	$(OUTDIR)\blowfish.obj \
	$(OUTDIR)\buffer.obj \
	$(OUTDIR)\charset.obj \
	$(OUTDIR)\diff.obj \
	$(OUTDIR)\digraph.obj \
	$(OUTDIR)\edit.obj \
	$(OUTDIR)\eval.obj \
	$(OUTDIR)\ex_cmds.obj \
	$(OUTDIR)\ex_cmds2.obj \
	$(OUTDIR)\ex_docmd.obj \
	$(OUTDIR)\ex_eval.obj \
	$(OUTDIR)\ex_getln.obj \
	$(OUTDIR)\fileio.obj \
	$(OUTDIR)\fold.obj \
	$(OUTDIR)\getchar.obj \
	$(OUTDIR)\hardcopy.obj \
	$(OUTDIR)\hashtab.obj \
	$(OUTDIR)\main.obj \
	$(OUTDIR)\mark.obj \
	$(OUTDIR)\mbyte.obj \
	$(OUTDIR)\memfile.obj \
	$(OUTDIR)\memline.obj \
	$(OUTDIR)\menu.obj \
	$(OUTDIR)\message.obj \
	$(OUTDIR)\misc1.obj \
	$(OUTDIR)\misc2.obj \
	$(OUTDIR)\move.obj \
	$(OUTDIR)\normal.obj \
	$(OUTDIR)\ops.obj \
	$(OUTDIR)\option.obj \
	$(OUTDIR)\os_mswin.obj \
	$(OUTDIR)\os_win32.obj \
	$(OUTDIR)\pathdef.obj \
	$(OUTDIR)\popupmnu.obj \
	$(OUTDIR)\quickfix.obj \
	$(OUTDIR)\regexp.obj \
	$(OUTDIR)\screen.obj \
	$(OUTDIR)\search.obj \
	$(OUTDIR)\sha256.obj \
	$(OUTDIR)\spell.obj \
	$(OUTDIR)\syntax.obj \
	$(OUTDIR)\tag.obj \
	$(OUTDIR)\term.obj \
	$(OUTDIR)\ui.obj \
	$(OUTDIR)\undo.obj \
	$(OUTDIR)\window.obj \
	$(OUTDIR)\vim.res

!if "$(IME)" == "yes"
CFLAGS = $(CFLAGS) -DFEAT_MBYTE_IME
! ifndef DYNAMIC_IME
DYNAMIC_IME = yes
! endif
! if "$(DYNAMIC_IME)" == "yes"
CFLAGS = $(CFLAGS) -DDYNAMIC_IME
! else
IME_LIB = imm32.lib
! endif
!endif

!if "$(GIME)" == "yes"
CFLAGS = $(CFLAGS) -DGLOBAL_IME
OBJ = $(OBJ) $(OUTDIR)\dimm_i.obj $(OUTDIR)\glbl_ime.obj
MBYTE = yes
!endif

!if "$(MBYTE)" == "yes"
CFLAGS = $(CFLAGS) -DFEAT_MBYTE
!endif

SUBSYSTEM = windows
CFLAGS = $(CFLAGS) -DFEAT_GUI_FREEVIM
RCFLAGS = $(RCFLAGS) -DFEAT_GUI_FREEVIM
VIM = g$(VIM)
GUI_INCL = \
	gui.h \
	regexp.h \
	ascii.h \
	ex_cmds.h \
	farsi.h \
	feature.h \
	globals.h \
	gui_beval.h \
	keymap.h \
	macros.h \
	option.h \
	os_dos.h \
	os_win32.h \
	freeVim/freevim.h
GUI_OBJ = \
	$(OUTDIR)\gui.obj \
	$(OUTDIR)\gui_beval.obj \
	$(OUTDIR)\gui_freevim.obj \
	$(OUTDIR)\main_freevim.obj
#	$(OUTDIR)\gui_w32.obj \
#	$(OUTDIR)\os_w32exe.obj
GUI_LIB = \
	gdi32.lib version.lib $(IME_LIB) \
	winspool.lib comctl32.lib advapi32.lib shell32.lib \
	/machine:$(CPU) /nodefaultlib

# iconv.dll library (dynamically loaded)
!ifndef ICONV
ICONV = yes
!endif
!if "$(ICONV)" == "yes"
CFLAGS = $(CFLAGS) -DDYNAMIC_ICONV
!endif

# libintl.dll library
!ifndef GETTEXT
GETTEXT = yes
!endif
!if "$(GETTEXT)" == "yes"
CFLAGS = $(CFLAGS) -DDYNAMIC_GETTEXT
!endif

#
# FEATURES: TINY, SMALL, NORMAL, BIG or HUGE
#
!if "$(FEATURES)"==""
FEATURES = BIG
!endif
CFLAGS = $(CFLAGS) -DFEAT_$(FEATURES)

#
# Always generate the .pdb file, so that we get debug symbols that can be used
# on a crash (doesn't add overhead to the executable).
# Generate edit-and-continue debug info when no optimization - allows to
# debug more conveniently (able to look at variables which are in registers)
#
CFLAGS = $(CFLAGS) /Fd$(OUTDIR)/ $(DEBUGINFO)
LINK_PDB = /PDB:$(VIM).pdb -debug

#
# End extra feature include
#
!message

conflags = /nologo /subsystem:$(SUBSYSTEM)

PATHDEF_SRC = $(OUTDIR)\pathdef.c

!IF "$(MAP)" == "yes"
# "/map" is for debugging
conflags = $(conflags) /map
!ELSEIF "$(MAP)" == "lines"
# "/mapinfo:lines" is for debugging, only works for VC6 and later
conflags = $(conflags) /map /mapinfo:lines
!ENDIF

LINKARGS1 = $(linkdebug) $(conflags)
LINKARGS2 = $(CON_LIB) $(GUI_LIB) $(LIBC) user32.lib $(LINK_PDB)

# Report link time code generation progress if used. 
!ifndef DEBUG
! ifdef MSVCNEW
!  if "$(OPTIMIZE)" != "SPACE"
LINKARGS1 = $(LINKARGS1) /LTCG:STATUS
!  endif
! endif
!endif

all:	$(VIM).exe vimrun.exe install.exe uninstal.exe xxd/xxd.exe \
		GvimExt/gvimext.dll

$(VIM).exe: $(OUTDIR) $(OBJ) $(GUI_OBJ) \
		version.c version.h
	$(CC) $(CFLAGS) version.c
	$(link) $(LINKARGS1) -out:$(VIM).exe $(OBJ) $(GUI_OBJ) \
		$(OUTDIR)\version.obj $(LINKARGS2)

$(VIM): $(VIM).exe

$(OUTDIR):
	if not exist $(OUTDIR)/nul  mkdir $(OUTDIR)

install.exe: dosinst.c
	$(CC) /nologo -DNDEBUG -DWIN32 dosinst.c kernel32.lib shell32.lib \
		user32.lib ole32.lib advapi32.lib uuid.lib
	- if exist install.exe del install.exe
	ren dosinst.exe install.exe

uninstal.exe: uninstal.c
	$(CC) /nologo -DNDEBUG -DWIN32 uninstal.c shell32.lib advapi32.lib

vimrun.exe: vimrun.c
	$(CC) /nologo -DNDEBUG vimrun.c

xxd/xxd.exe: xxd/xxd.c
	cd xxd
	$(MAKE) /NOLOGO -f Make_mvc.mak
	cd ..

GvimExt/gvimext.dll: GvimExt/gvimext.cpp GvimExt/gvimext.rc GvimExt/gvimext.h
	cd GvimExt
	$(MAKE) /NOLOGO -f Makefile $(MAKEFLAGS_GVIMEXT)
	cd ..


tags: notags
	$(CTAGS) *.c *.cpp *.h if_perl.xs proto\*.pro

notags:
	- if exist tags del tags

clean:
	- if exist $(OUTDIR)/nul $(DEL_TREE) $(OUTDIR)
	- if exist *.obj del *.obj
	- if exist $(VIM).exe del $(VIM).exe
	- if exist $(VIM).ilk del $(VIM).ilk
	- if exist $(VIM).pdb del $(VIM).pdb
	- if exist $(VIM).map del $(VIM).map
	- if exist $(VIM).ncb del $(VIM).ncb
	- if exist vimrun.exe del vimrun.exe
	- if exist install.exe del install.exe
	- if exist uninstal.exe del uninstal.exe
	- if exist if_perl.c del if_perl.c
	- if exist dimm.h del dimm.h
	- if exist dimm_i.c del dimm_i.c
	- if exist dimm.tlb del dimm.tlb
	- if exist dosinst.exe del dosinst.exe
	- if exist mzscheme_base.c del mzscheme_base.c
	cd xxd
	$(MAKE) /NOLOGO -f Make_mvc.mak clean
	cd ..
	cd GvimExt
	$(MAKE) /NOLOGO -f Makefile clean
	cd ..
	cd GvimExt
	$(MAKE) /NOLOGO -f Makefile clean
	cd ..
	- if exist testdir\*.out del testdir\*.out

test:
	cd testdir
	$(MAKE) /NOLOGO -f Make_dos.mak win32
	cd ..

testclean:
	cd testdir
	$(MAKE) /NOLOGO -f Make_dos.mak clean
	cd ..

###########################################################################

# Create a default rule for transforming .c files to .obj files in $(OUTDIR)
# Batch compilation is supported by nmake 1.62 (part of VS 5.0) and later)
.c{$(OUTDIR)/}.obj::
	$(CC) $(CFLAGS) $<

# Create a default rule for transforming .cpp files to .obj files in $(OUTDIR)
# Batch compilation is supported by nmake 1.62 (part of VS 5.0) and later)
.cpp{$(OUTDIR)/}.obj::
	$(CC) $(CFLAGS) $<

$(OUTDIR)/blowfish.obj:	$(OUTDIR) blowfish.c  $(INCL)

$(OUTDIR)/buffer.obj:	$(OUTDIR) buffer.c  $(INCL)

$(OUTDIR)/charset.obj:	$(OUTDIR) charset.c  $(INCL)

$(OUTDIR)/diff.obj:	$(OUTDIR) diff.c  $(INCL)

$(OUTDIR)/digraph.obj:	$(OUTDIR) digraph.c  $(INCL)

$(OUTDIR)/edit.obj:	$(OUTDIR) edit.c  $(INCL)

$(OUTDIR)/eval.obj:	$(OUTDIR) eval.c  $(INCL)

$(OUTDIR)/ex_cmds.obj:	$(OUTDIR) ex_cmds.c  $(INCL)

$(OUTDIR)/ex_cmds2.obj:	$(OUTDIR) ex_cmds2.c  $(INCL)

$(OUTDIR)/ex_docmd.obj:	$(OUTDIR) ex_docmd.c  $(INCL) ex_cmds.h

$(OUTDIR)/ex_eval.obj:	$(OUTDIR) ex_eval.c  $(INCL) ex_cmds.h

$(OUTDIR)/ex_getln.obj:	$(OUTDIR) ex_getln.c  $(INCL)

$(OUTDIR)/fileio.obj:	$(OUTDIR) fileio.c  $(INCL)

$(OUTDIR)/fold.obj:	$(OUTDIR) fold.c  $(INCL)

$(OUTDIR)/getchar.obj:	$(OUTDIR) getchar.c  $(INCL)

$(OUTDIR)/hardcopy.obj:	$(OUTDIR) hardcopy.c  $(INCL)

$(OUTDIR)/hashtab.obj:	$(OUTDIR) hashtab.c  $(INCL)

$(OUTDIR)/gui.obj:	$(OUTDIR) gui.c  $(INCL) $(GUI_INCL)

$(OUTDIR)/gui_beval.obj:	$(OUTDIR) gui_beval.c $(INCL) $(GUI_INCL)

$(OUTDIR)/gui_freevim.obj:	$(OUTDIR) freeVim\gui_freevim.cpp $(INCL) $(GUI_INCL)
	$(CC) $(CFLAGS) $(XPM_INC) freeVim\gui_freevim.cpp

$(OUTDIR)/gui_w32.obj:	$(OUTDIR) gui_w32.c gui_w48.c $(INCL) $(GUI_INCL)

$(OUTDIR)/main_freevim.obj:	$(OUTDIR) freeVim/main.cpp $(INCL)
	$(CC) $(CFLAGS) $(XPM_INC) freeVim\main.cpp /Fo$(OUTDIR)\main_freevim.obj

$(OUTDIR)/main.obj:	$(OUTDIR) main.c  $(INCL)

$(OUTDIR)/mark.obj:	$(OUTDIR) mark.c  $(INCL)

$(OUTDIR)/memfile.obj:	$(OUTDIR) memfile.c  $(INCL)

$(OUTDIR)/memline.obj:	$(OUTDIR) memline.c  $(INCL)

$(OUTDIR)/menu.obj:	$(OUTDIR) menu.c  $(INCL)

$(OUTDIR)/message.obj:	$(OUTDIR) message.c  $(INCL)

$(OUTDIR)/misc1.obj:	$(OUTDIR) misc1.c  $(INCL)

$(OUTDIR)/misc2.obj:	$(OUTDIR) misc2.c  $(INCL)

$(OUTDIR)/move.obj:	$(OUTDIR) move.c  $(INCL)

$(OUTDIR)/mbyte.obj: $(OUTDIR) mbyte.c  $(INCL)

$(OUTDIR)/normal.obj:	$(OUTDIR) normal.c  $(INCL)

$(OUTDIR)/option.obj:	$(OUTDIR) option.c  $(INCL)

$(OUTDIR)/ops.obj:	$(OUTDIR) ops.c  $(INCL)

$(OUTDIR)/os_mswin.obj:	$(OUTDIR) os_mswin.c  $(INCL)

$(OUTDIR)/os_win32.obj:	$(OUTDIR) os_win32.c  $(INCL) os_win32.h

$(OUTDIR)/os_w32exe.obj:	$(OUTDIR) os_w32exe.c  $(INCL)

$(OUTDIR)/pathdef.obj:	$(OUTDIR) $(PATHDEF_SRC) $(INCL)
	$(CC) $(CFLAGS) $(PATHDEF_SRC)

$(OUTDIR)/popupmnu.obj:	$(OUTDIR) popupmnu.c  $(INCL)

$(OUTDIR)/quickfix.obj:	$(OUTDIR) quickfix.c  $(INCL)

$(OUTDIR)/regexp.obj:	$(OUTDIR) regexp.c  $(INCL)

$(OUTDIR)/screen.obj:	$(OUTDIR) screen.c  $(INCL)

$(OUTDIR)/search.obj:	$(OUTDIR) search.c  $(INCL)

$(OUTDIR)/sha256.obj:	$(OUTDIR) sha256.c  $(INCL)

$(OUTDIR)/spell.obj:	$(OUTDIR) spell.c  $(INCL)

$(OUTDIR)/syntax.obj:	$(OUTDIR) syntax.c  $(INCL)

$(OUTDIR)/tag.obj:	$(OUTDIR) tag.c  $(INCL)

$(OUTDIR)/term.obj:	$(OUTDIR) term.c  $(INCL)

$(OUTDIR)/ui.obj:	$(OUTDIR) ui.c  $(INCL)

$(OUTDIR)/undo.obj:	$(OUTDIR) undo.c  $(INCL)

$(OUTDIR)/window.obj:	$(OUTDIR) window.c  $(INCL)

$(OUTDIR)/xpm_w32.obj: $(OUTDIR) xpm_w32.c
	$(CC) $(CFLAGS) $(XPM_INC) xpm_w32.c

$(OUTDIR)/vim.res:	$(OUTDIR) vim.rc gvim.exe.mnf version.h tools.bmp \
				tearoff.bmp vim.ico vim_error.ico \
				vim_alert.ico vim_info.ico vim_quest.ico
	$(RC) /l 0x409 /Fo$(OUTDIR)/vim.res $(RCFLAGS) vim.rc

iid_ole.c if_ole.h vim.tlb: if_ole.idl
	midl /nologo /error none /proxy nul /iid iid_ole.c /tlb vim.tlb \
		/header if_ole.h if_ole.idl

dimm.h dimm_i.c: dimm.idl
	midl /nologo /error none /proxy nul dimm.idl

$(OUTDIR)/dimm_i.obj: $(OUTDIR) dimm_i.c $(INCL)

$(OUTDIR)/glbl_ime.obj:	$(OUTDIR) glbl_ime.cpp  dimm.h $(INCL)

# $CFLAGS may contain backslashes and double quotes, escape them both.
E0_CFLAGS = $(CFLAGS:\=\\)
E_CFLAGS = $(E0_CFLAGS:"=\")
# ") stop the string

$(PATHDEF_SRC): auto
	@echo creating $(PATHDEF_SRC)
	@echo /* pathdef.c */ > $(PATHDEF_SRC)
	@echo #include "vim.h" >> $(PATHDEF_SRC)
	@echo char_u *default_vim_dir = (char_u *)"$(VIMRCLOC:\=\\)"; >> $(PATHDEF_SRC)
	@echo char_u *default_vimruntime_dir = (char_u *)"$(VIMRUNTIMEDIR:\=\\)"; >> $(PATHDEF_SRC)
	@echo char_u *all_cflags = (char_u *)"$(CC:\=\\) $(E_CFLAGS)"; >> $(PATHDEF_SRC)
	@echo char_u *all_lflags = (char_u *)"$(link:\=\\) $(LINKARGS1:\=\\) $(LINKARGS2:\=\\)"; >> $(PATHDEF_SRC)
	@echo char_u *compiled_user = (char_u *)"$(USERNAME)"; >> $(PATHDEF_SRC)
	@echo char_u *compiled_sys = (char_u *)"$(USERDOMAIN)"; >> $(PATHDEF_SRC)

auto:
	if not exist auto/nul mkdir auto

# End Custom Build
proto.h: \
	proto/blowfish.pro \
	proto/buffer.pro \
	proto/charset.pro \
	proto/diff.pro \
	proto/digraph.pro \
	proto/edit.pro \
	proto/eval.pro \
	proto/ex_cmds.pro \
	proto/ex_cmds2.pro \
	proto/ex_docmd.pro \
	proto/ex_eval.pro \
	proto/ex_getln.pro \
	proto/fileio.pro \
	proto/getchar.pro \
	proto/hardcopy.pro \
	proto/hashtab.pro \
	proto/main.pro \
	proto/mark.pro \
	proto/memfile.pro \
	proto/memline.pro \
	proto/menu.pro \
	proto/message.pro \
	proto/misc1.pro \
	proto/misc2.pro \
	proto/move.pro \
	proto/mbyte.pro \
	proto/normal.pro \
	proto/ops.pro \
	proto/option.pro \
	proto/os_mswin.pro \
	proto/os_win32.pro \
	proto/popupmnu.pro \
	proto/quickfix.pro \
	proto/regexp.pro \
	proto/screen.pro \
	proto/search.pro \
	proto/sha256.pro \
	proto/spell.pro \
	proto/syntax.pro \
	proto/tag.pro \
	proto/term.pro \
	proto/ui.pro \
	proto/undo.pro \
	proto/window.pro \
	$(NETBEANS_PRO)

.SUFFIXES: .cod .i

# Generate foo.cod (mixed source and assembly listing) from foo.c via "nmake
# foo.cod"
.c.cod:
	$(CC) $(CFLAGS) /FAcs $<

# Generate foo.i (preprocessor listing) from foo.c via "nmake foo.i"
.c.i:
	$(CC) $(CFLAGS) /P /C $<


# vim: set noet sw=8 ts=8 sts=0 wm=0 tw=0:
