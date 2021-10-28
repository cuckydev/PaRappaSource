#ifndef PARAPPA_GUARD_PRMEMORY_H
#define PARAPPA_GUARD_PRMEMORY_H

#include "psx.h"

//Memory interface
void Memory_Init(void); //FUN_80025a00
void Memory_Reset(void); //FUN_80025a34
void *Memory_Push(int size); //FUN_80025a70
void Memory_Pop(void); //FUN_80025a70
void *Memory_EndAlloc(int size); //FUN_80025b28

#endif
