TARGET = parappa
TYPE = ps-exe

ifeq ($(UB), 1)
	CPPFLAGS += -DPARAPPA_UB
endif

SRCS = \
	src/prapp.c \
	src/prmenu.c \
	src/prcd.c \
	src/prcompo.c \
	src/prvdatal.c \
	src/prmain.c \
	src/prmemory.c \
	src/prrap.c \
	src/prvtext.c \
	mips/common/crt0/crt0.s

CPPFLAGS += -Wall -Wextra -pedantic
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
