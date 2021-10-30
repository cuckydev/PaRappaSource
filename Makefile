TARGET = parappa
TYPE = ps-exe

ifeq ($(UB), 1)
	CPPFLAGS += -DPARAPPA_UB
endif

SRCS = \
	src/boot/prapp.c \
	src/boot/prmenu.c \
	src/boot/prcd.c \
	src/boot/prcompo.c \
	src/boot/prvdatal.c \
	src/boot/prmain.c \
	src/boot/prmemory.c \
	src/boot/prrap.c \
	src/boot/prvtext.c \
	src/scn0/prscn0.c \
	mips/common/crt0/crt0.s

OVERLAYSCRIPT  ?= overlay.ld
OVERLAYSECTION ?= .scn0

CPPFLAGS += -Wall -Wextra -pedantic -Isrc/
LDFLAGS += -Wl,--start-group
# TODO: remove unused libraries
LDFLAGS += -lapi
#LDFLAGS += -lc
LDFLAGS += -lc2
#LDFLAGS += -lcard
LDFLAGS += -lcd
#LDFLAGS += -lcomb
LDFLAGS += -lds
LDFLAGS += -letc
LDFLAGS += -lgpu
LDFLAGS += -lgs
LDFLAGS += -lgte
#LDFLAGS += -lgun
#LDFLAGS += -lhmd
#LDFLAGS += -lmath
#LDFLAGS += -lmcrd
#LDFLAGS += -lmcx
LDFLAGS += -lpad
LDFLAGS += -lpress
#LDFLAGS += -lsio
LDFLAGS += -lsnd
LDFLAGS += -lspu
#LDFLAGS += -ltap
LDFLAGS += -Wl,--end-group

include mips/common.mk
