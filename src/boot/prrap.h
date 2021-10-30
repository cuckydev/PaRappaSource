#ifndef PARAPPA_GUARD_BOOT_PRRAP_H
#define PARAPPA_GUARD_BOOT_PRRAP_H

#include "psx.h"

//Rap interface
void Rap_Init(void); //FUN_80026e4c
void Rap_StopSeq(void); //FUN_80026fa4
int Rap_OpenVab(u8 *buffer); //FUN_80027078
void Rap_VabTransBody(u8 *buffer); //FUN_800270d4
void Rap_VabTransCompleted(int mode); //FUN_800270fc
int Rap_CloseVab(void); //FUN_80027120

#endif
