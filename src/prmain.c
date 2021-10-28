#include "prmain.h"

#include <libapi.h>
#include <libetc.h>

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#include <libsnd.h>

#include "prcd.h"
#include "prvdatal.h"
#include "prmemory.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prmain.c: version 01-00 95/10/10 00:00:00";

//Gfx functions
void Gfx_ClearScreen(u_char r, u_char g, u_char b) //FUN_8001b1b0
{
	RECT dst = {0, 0, 320, 240};
	ClearImage(&dst, r, g, b);
}

void Gfx_Init1(void) //FUN_8001c470
{
	//FUN_8001c1e8();
	ResetGraph(0);
	PadInit(0);
	GsInitGraph(320, 240, 4, 0, 0);
	GsDefDispBuff(0, 0, 0, 240);
	GsInit3D();
	GsSetProjection(440);
	Gfx_ClearScreen(0, 0, 0);
}

void Gfx_Init2(void) //FUN_8001e6d0
{
	//iVar3 = 0;
	//puVar2 = &DAT_800872b0;
	//iVar1 = 0;
	//do {
	//	*(undefined **)((int)&DAT_8008728c + iVar1) = puVar2;
	//	puVar2 = puVar2 + 0x40;
	//	*(undefined4 *)((int)&DAT_80087288 + iVar1) = 4;
	//	*(undefined4 *)((int)&DAT_80087290 + iVar1) = 0;
	//	iVar3 = iVar3 + 1;
	//	iVar1 = iVar1 + 0x14;
	//} while (iVar3 < 2);
	//FUN_8001e33c(&DAT_80080cf8,&DAT_80083fc0);
}

void Gfx_Init(void) //FUN_8001ed94
{
	Gfx_Init1();
	Gfx_Init2();
}

//Sfx functions
void Sfx_Init(void) //FUN_80026e4c
{
	SsInitHot();
	SsSetTickMode(SS_NOTICK);
	SsStart();
	SsSetMVol(90, 90);
	SsSetSerialAttr(0, 0, 1);
	SsSetSerialVol(0, 0x7F, 0x7F);
	//DAT_800943a8 = 0;
	//DAT_800943aa = 0xffff;
	//DAT_800943ac = 0xffff;
	//DAT_800943b4 = 0;
}

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
	Gfx_Init();
	Memory_Init();
	CD_Init();
	Sfx_Init();
	Debug_LoadFont();
	
	srand(VSync(-1));
}

//Stage 0 functions
void Stage0_Load(void)
{
	CD_File_Read(&vdata_s0_common_int, 0);
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