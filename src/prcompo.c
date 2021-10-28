#include "prcompo.h"

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prcompo.c: version 01-00 95/10/10 00:00:00";

//Compo interface
void Compo_LoadTim(u8 *buffer) //FUN_8001ae7c
{
	RECT rect;
	
	//Get image information
	GsIMAGE image;
	GsGetTimInfo(buffer + 4, &image);
	
	//Load texture
	rect.x = image.px;
	rect.y = image.py;
	rect.w = image.pw;
	rect.h = image.ph;
	LoadImage(&rect, image.pixel);
	DrawSync(0);
	
	//Load palette
	if (((image.pmode >> 3) & 1) != 0)
	{
		rect.x = image.cx;
		rect.y = image.cy;
		rect.w = image.cw;
		rect.h = image.ch;
		LoadImage(&rect, image.clut);
		DrawSync(0);
	}
}

void Compo_ClearScreen(u8 r, u8 g, u8 b) //FUN_8001b1b0
{
	RECT dst = {0, 0, 320, 240};
	ClearImage(&dst, r, g, b);
}

void Compo_Init1(void) //FUN_8001c470
{
	//FUN_8001c1e8();
	ResetGraph(0);
	PadInit(0);
	GsInitGraph(320, 240, 4, 0, 0);
	GsDefDispBuff(0, 0, 0, 240);
	GsInit3D();
	GsSetProjection(440);
	Compo_ClearScreen(0, 0, 0);
}

void Compo_Init2(void) //FUN_8001e6d0
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

void Compo_Init(void) //FUN_8001ed94
{
	Compo_Init1();
	Compo_Init2();
}
