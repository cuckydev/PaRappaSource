#include "prmain.h"

#include <libapi.h>
#include <libetc.h>

#include <libgte.h>
#include <libgpu.h>

#include "prcd.h"
#include "prcompo.h"
#include "prvdatal.h"
#include "prmemory.h"
#include "prrap.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prmain.c: version 01-00 95/10/10 00:00:00";

//Debug functions
void Debug_LoadFont(void)
{
	//Load and open font
	FntLoad(0x3C0, 0x100);
	SetDumpFnt(FntOpen(-156, -120, 320, 200, 0, 0x200));
	SetDispMask(-1);
}

//System initialization
void System_Init(void) //FUN_800154f4
{
	SetMem(2);
	ResetCallback();
	Compo_Init();
	Memory_Init();
	CD_Init();
	Rap_Init();
	Debug_LoadFont();
	
	srand(VSync(-1));
}

//Stage 0 functions
void Stage0_Load(void)
{
	CD_File_Read(&vdata_s0_common_int, 0);
	CD_File_Read(&vdata_s0_ycompo_int, 0);
}

//Game loop function
void Game_Loop(void) //FUN_80027fac
{
	Stage0_Load();
}

//Entry point
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	//Run game
	System_Init();
	Game_Loop();
	return 0;
}