#ifndef PARAPPA_GUARD_BOOT_PRVDATAL_H
#define PARAPPA_GUARD_BOOT_PRVDATAL_H

#include "prcd.h"

//VData types
typedef struct
{
	char *name;
	u_long pad0[2];
	CD_File comod;
	u_long pad1[76];
} VData_Scene;

//VData files
extern CD_File vdata_s0_common_int;
extern CD_File vdata_ss_movie0_str;
extern CD_File vdata_s0_ycompo_int;
extern CD_File vdata_s0_zcompo_int;

//VData scenes
extern VData_Scene vdata_scene[9];

#endif
