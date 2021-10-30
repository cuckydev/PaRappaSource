#include "prmenu.h"

#include <libetc.h>

#include "prapp.h"
#include "prcd.h"
#include "prcompo.h"
#include "prmemory.h"
#include "prrap.h"
#include "prvdatal.h"

//Menu state
u16 menu_debug;

//Menu interface
void Menu_CheckDebug(void) //FUN_80016ab4
{
	//Wait a moment, polling input
	u32 check = 0;
	for (int i = 0; i < 30 && ((check = PadRead(1)) == 0); i++)
		VSync(0);
	
	//Check debug input
	if (check != 0 && check == (PADL2 | PADR2 | PADL1 | PADR1 | PADRup | PADselect))
		menu_debug = 1;
}

void Menu_Opening(void) //FUN_80016b84
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
	App_Screen_In(Compo_Sony_Display, Compo_Sony_Flip, Compo_Sony_Init);
	App_Wait(150, 60);
	App_Screen_Out(Compo_Sony_Display, Compo_Sony_Flip);
	
	//Display "Masaya Presents" logo
	App_Screen_In(Compo_Masaya_Display, Compo_Masaya_Flip, Compo_Masaya_Init);
	App_Wait(150, 60);
	App_Screen_Out(Compo_Masaya_Display, Compo_Masaya_Flip);
	Memory_Reset();
}