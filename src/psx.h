#ifndef PARAPPA_GUARD_PSX_H
#define PARAPPA_GUARD_PSX_H

//Standard library
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

//Common macros
#define sizeof_member(type, member) sizeof(((type *)0)->member)

#define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))
#define COUNT_OF_MEMBER(type, member) (sizeof_member(type, member) / sizeof_member(type, member[0]))

//Used attribute
#if defined(__GNUC__) || defined(__GNUG__)
	#define ATTR_USED __attribute__((used))
#endif

//Fixed size types
typedef u_char             u8;
typedef signed char        s8;
typedef u_short            u16;
typedef signed short       s16;
typedef u_long             u32;
typedef signed int         s32;
typedef unsigned long long u64;
typedef signed long long   s64;

#endif
