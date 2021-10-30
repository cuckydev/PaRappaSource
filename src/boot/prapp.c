#include "prapp.h"

#include <libapi.h>
#include <libetc.h>

#include <libgte.h>
#include <libgpu.h>

#include "prmenu.h"
#include "prcd.h"
#include "prcompo.h"
#include "prvdatal.h"
#include "prmemory.h"
#include "prrap.h"
#include "prvtext.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prapp.c: version 01-00 95/10/10 00:00:00";

//Function pointer addresses
typedef int (*App_Scene_SetPtr)(void);
typedef void (*App_Scene_Init)(VData_Scene*, int);
typedef int (*App_Scene_Loop)(int);

typedef struct
{
	App_Scene_SetPtr setptr;
	App_Scene_Init   init;
	App_Scene_Loop   loop;
} App_SceneFunc;

#include "scn0/prscn0.h"

App_SceneFunc app_scenefunc[9] = { //DAT_80048d28
	{
		Scene0_SetPtr,
		Scene0_Init,
		Scene0_Loop
	},
	{
		(App_Scene_SetPtr)0x801CA3BC,
		(App_Scene_Init)0x801C7284,
		(App_Scene_Loop)0x801C81EC
	},
	{
		(App_Scene_SetPtr)0x801C97EC,
		(App_Scene_Init)0x801C657C,
		(App_Scene_Loop)0x801C74E4
	},
	{
		(App_Scene_SetPtr)0x801C998C,
		(App_Scene_Init)0x801C6918,
		(App_Scene_Loop)0x801C7880
	},
	{
		(App_Scene_SetPtr)0x801CB348,
		(App_Scene_Init)0x801C7D20,
		(App_Scene_Loop)0x801C8C88
	},
	{
		(App_Scene_SetPtr)0x801C9310,
		(App_Scene_Init)0x801C60B0,
		(App_Scene_Loop)0x801C7030
	},
	{
		(App_Scene_SetPtr)0x801C9EA0,
		(App_Scene_Init)0x801C6AC4,
		(App_Scene_Loop)0x801C7A2C
	},
	{
		(App_Scene_SetPtr)0x801C5780,
		(App_Scene_Init)0x801C3870,
		(App_Scene_Loop)0x801C4870
	},
	{
		(App_Scene_SetPtr)0x801C5BDC,
		(App_Scene_Init)0x801C3870,
		(App_Scene_Loop)0x801C4834
	}
};

//App state
u16 app_scene;
u16 app_reload;

//App interface
void App_ReadOverlay(CD_File *cd_file)
{
	//Read CD file to heap
	printf("loading overlay %s\n", cd_file->path);
	CD_File_ReadRaw(cd_file, (u_long*)0x801C3870);
	printf("loaded overlay %s\n", cd_file->path);
}

void App_Init(void) //FUN_800154f4
{
	SetMem(2);
	ResetCallback();
	Compo_Init();
	Memory_Init();
	CD_Init();
	Rap_Init();
	VText_Init();
	
	srand(VSync(-1));
}

void App_Screen_In(void (*screen_display)(int i), void (*screen_flip)(void), void (*screen_init)(void)) //FUN_80015a4c
{
	screen_init();
	for (int i = 0; i < 30; i++)
	{
		screen_display(i);
		VSync(2);
		screen_flip();
	}
}

void App_Wait(int time_a, int time_b) //FUN_80015b00
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

void App_Screen_Out(void (*screen_display)(int i), void (*screen_flip)(void)) //FUN_80015c20
{
	for (int i = 120; i < 150; i++)
	{
		screen_display(i);
		VSync(2);
		screen_flip();
	}
}

void App_Loop(void) //FUN_80027fac
{
	//Run opening
	Menu_Opening();
	Menu_CheckDebug();
	
	//Game loop
	int scene_prev = 0, scene = 0;
	app_reload = 0;
	
	while (1)
	{
		//Check for reload
		if (app_reload == 1)
		{
			app_reload = 0;
			if (scene == 0)
				scene_prev = 0;
			//FUN_8001ef14();
			//scene = FUN_80015788(scene_prev);
			scene_prev = scene;
		}
		
		//Read COMOD overlay
		Memory_Reset();
		
		printf("bugging me\n");
		app_scene = scene;
		CD_File_Find(&vdata_scene[scene].comod); //Redundant, ReadOverlay ends up doing the same thing
		App_ReadOverlay(&vdata_scene[scene].comod);
		
		Memory_Reset();
		
		//Run COMOD overlay
		app_scenefunc[scene].setptr();
		app_scenefunc[scene].init(&vdata_scene[scene].name, scene);
		int next_scene = app_scenefunc[scene].loop(scene);
		
		while(1);
	}
}