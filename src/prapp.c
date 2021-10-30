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
typedef void (*App_ModeFunc1)(void);
typedef void (*App_ModeFunc2)(void*, int);
typedef int (*App_ModeFunc3)(int);

typedef struct
{
	App_ModeFunc1 func1;
	App_ModeFunc2 func2;
	App_ModeFunc3 func3;
} App_ModeFunc;

App_ModeFunc app_modefunc[9] = { //DAT_80048d28
	{
		(App_ModeFunc1)0x801C5B14,
		(App_ModeFunc2)0x801C4260,
		(App_ModeFunc3)0x801C4DC4
	},
	{
		(App_ModeFunc1)0x801CA3BC,
		(App_ModeFunc2)0x801C7284,
		(App_ModeFunc3)0x801C81EC
	},
	{
		(App_ModeFunc1)0x801C97EC,
		(App_ModeFunc2)0x801C657C,
		(App_ModeFunc3)0x801C74E4
	},
	{
		(App_ModeFunc1)0x801C998C,
		(App_ModeFunc2)0x801C6918,
		(App_ModeFunc3)0x801C7880
	},
	{
		(App_ModeFunc1)0x801CB348,
		(App_ModeFunc2)0x801C7D20,
		(App_ModeFunc3)0x801C8C88
	},
	{
		(App_ModeFunc1)0x801C9310,
		(App_ModeFunc2)0x801C60B0,
		(App_ModeFunc3)0x801C7030
	},
	{
		(App_ModeFunc1)0x801C9EA0,
		(App_ModeFunc2)0x801C6AC4,
		(App_ModeFunc3)0x801C7A2C
	},
	{
		(App_ModeFunc1)0x801C5780,
		(App_ModeFunc2)0x801C3870,
		(App_ModeFunc3)0x801C4870
	},
	{
		(App_ModeFunc1)0x801C5BDC,
		(App_ModeFunc2)0x801C3870,
		(App_ModeFunc3)0x801C4834
	}
};

//App state
u16 app_reload;

//App interface
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
	int mode_prev = 0, mode = 0;
	app_reload = 0;
	
	while (1)
	{
		//Check for reload
		if (app_reload == 1)
		{
			app_reload = 0;
			if (mode == 0)
				mode_prev = 0;
			//FUN_8001ef14();
			//mode = FUN_80015788(mode_prev);
			mode_prev = mode;
		}
		
		//Start mode
		Memory_Reset();
	}
}