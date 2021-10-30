#ifndef PARAPPA_GUARD_BOOT_PRMEMORY_H
#define PARAPPA_GUARD_BOOT_PRMEMORY_H

#include "psx.h"

//Memory interface
void Memory_Init(void); //FUN_80025a00
void Memory_Reset(void); //FUN_80025a34
void *Memory_Push(int size); //FUN_80025a70
void Memory_Pop(void); //FUN_80025a70
void *Memory_EndAlloc(int size); //FUN_80025b28
int Memory_PushPoint(void *point, int index, int size); //FUN_80025bbc
int Memory_FindIndex(void *point); //FUN_80025bfc

#endif
