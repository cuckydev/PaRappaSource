#include "prscn0.h"

#include <stdio.h>

//Version control ID
static const char rcsid[] = "@(#)prscn0.c: version 01-00 95/10/10 00:00:00";

//Scene 0 interface
int Scene0_SetPtr(void) //FUN_801c5b14
{
	printf("Scene 0 overlay success SetPtr\n");
	return 0;
}

void Scene0_Init(VData_Scene *scene_vdata, int scene) //FUN_801c4260
{
	printf("Scene 0 overlay success Init\n");
}

int Scene0_Loop(int scene) //FUN_801c4dc4
{
	printf("Scene 0 overlay success Loop\n");
	return 0;
}
