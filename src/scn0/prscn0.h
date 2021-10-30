#ifndef PARAPPA_GUARD_S0_PRSCN0_H
#define PARAPPA_GUARD_S0_PRSCN0_H

#include "psx.h"

#include "boot/prvdatal.h"

//Scene 0 interface
int Scene0_SetPtr(void); //FUN_801c5b14
void Scene0_Init(VData_Scene *scene_vdata, int scene); //FUN_801c4260
int Scene0_Loop(int scene); //FUN_801c4dc4

#endif
