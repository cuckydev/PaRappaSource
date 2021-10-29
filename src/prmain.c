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

//Game state
u16 game_debug;

u16 game_loopreload;

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

//Game functions
void Game_Screen_In(void (*display)(int i), void (*flip)(void), void (*init)(void)) //FUN_80015a4c
{
	init();
	for (int i = 0; i < 30; i++)
	{
		display(i);
		VSync(2);
		flip();
	}
}

void Game_Wait(int time_a, int time_b) //FUN_80015b00
{
	//Wait force time
	u32 timer;
	for (timer = time_b; timer > 0; timer--)
		VSync(2);
	
	//Wait skippable time
	u32 check = 0;
	for (timer = time_a - time_b; timer > 0;)
	{
		u32 next_check = PadRead(1);
		if (next_check != check)
			break;
		VSync(2);
		timer--;
		check = next_check;
	}
}

void Game_Screen_Out(void (*display)(int i), void (*flip)(void)) //FUN_80015c20
{
	for (int i = 120; i < 150; i++)
	{
		display(i);
		VSync(2);
		flip();
	}
}

void Game_CheckDebug(void) //FUN_80016ab4
{
	//Wait a moment, polling input
	u32 check = 0;
	for (int i = 0; i < 30 && ((check = PadRead(1)) == 0); i++)
		VSync(0);
	
	//Check debug input
	if (check != 0 && check == (PADL2 | PADR2 | PADL1 | PADR1 | PADRup | PADselect))
		game_debug = 1;
}

void Game_Opening(void) //FUN_80016b84
{
	//Load menu assets
	Memory_Reset();
	CD_File_Read(&vdata_s0_common_int, 0);
	Rap_CloseVab();
	Memory_Reset();
	CD_File_Read(&vdata_s0_zcompo_int, 0);
	Memory_Reset();
	Rap_StopSeq();
	
	//Display "Sony Computer Entertainment" logo
	Game_Screen_In(Compo_Sony_Display, Compo_Sony_Flip, Compo_Sony_Init);
	Game_Wait(150, 60);
	Game_Screen_Out(Compo_Sony_Display, Compo_Sony_Flip);
	
	//Display "Masaya Presents" logo
	Game_Screen_In(Compo_Masaya_Display, Compo_Masaya_Flip, Compo_Masaya_Init);
	Game_Wait(150, 60);
	Game_Screen_Out(Compo_Masaya_Display, Compo_Masaya_Flip);
	Memory_Reset();
}

void Game_Loop(void) //FUN_80027fac
{
	//Run opening
	Game_Opening();
	Game_CheckDebug();
	
	//Game loop
	int mode_prev = 0, mode = 0;
	game_loopreload = 0;
	
	while (1)
	{
		//Check for reload
		if (game_loopreload == 1)
		{
			game_loopreload = 0;
			if (mode == 0)
				gamemode_prev = 0;
			//FUN_8001ef14();
			//mode = FUN_80015788(mode_prev);
			mode_prev = mode;
		}
		
		//Start mode
		Memory_Reset();
	}
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