#ifndef PARAPPA_GUARD_MACROS_H
#define PARAPPA_GUARD_MACROS_H

//Used attribute
#if defined(__GNUC__) || defined(__GNUG__)
	#define ATTR_USED __attribute__((used))
#endif

#endif
