#include "prvdatal.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prvdatal.c: version 01-00 95/10/10 00:00:00";

//VData files
CD_File vdata_s0_common_int = {"\\S0\\COMMON.INT;1", 0, 0, 0, {{0, 0, 0, 0}, 0, ""}, 0, 0};
CD_File vdata_ss_movie0_str = {"\\SS\\MOVIE0.STR;1", 0, 0, 0, {{0, 0, 0, 0}, 0, ""}, 0, 0};
CD_File vdata_s0_ycompo_int = {"\\S0\\YCOMPO.INT;1", 0, 0, 0, {{0, 0, 0, 0}, 0, ""}, 0, 0};
CD_File vdata_s0_zcompo_int = {"\\S0\\ZCOMPO.INT;1", 0, 0, 0, {{0, 0, 0, 0}, 0, ""}, 0, 0};

//VData scenes
VData_Scene vdata_scene[9] = {
	{
		"SCENE0",
		{},
		{"\\S0\\COMOD0.BIN;1", 0, 0, 0, {{0, 0, 0, 0}, 0, ""}, 0, 0},
		{},
	}
};
