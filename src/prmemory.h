#ifndef PARAPPA_GUARD_PRMEMORY_H
#define PARAPPA_GUARD_PRMEMORY_H

#include "psx.h"

//Memory interface
void Memory_Init(void); //FUN_80025a00
void Memory_Reset(void); //FUN_80025a34
u_char *Memory_Alloc(int size); //FUN_80025a70
u_char *Memory_EndAlloc(int size); //FUN_80025b28

#endif
