#include "prcompo.h"

#include <libetc.h>

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prcompo.c: version 01-00 95/10/10 00:00:00";

//Compo state
int compo_activebuff;
GsOT compo_ot[2];
GsOT_TAG compo_tag[2][0x10];
PACKET *compo_work[2];

//Compo interface
void Compo_LoadTim_2(u8 *buffer, int palette) //FUN_8001adec
{
	RECT rect;
	
	//Get image information
	GsIMAGE image;
	GsGetTimInfo((u_long*)(buffer + 4), &image);
	
	//Load texture
	rect.x = image.px;
	rect.y = image.py;
	rect.w = image.pw;
	rect.h = image.ph;
	LoadImage(&rect, image.pixel);
	
	//Load palette
	if (palette && ((image.pmode >> 3) & 1) != 0)
		LoadClut2(image.clut, image.cx, image.cy);
}

void Compo_LoadTim(u8 *buffer) //FUN_8001ae7c
{
	RECT rect;
	
	//Get image information
	GsIMAGE image;
	GsGetTimInfo((u_long*)(buffer + 4), &image);
	
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
	RECT dst = {0, 0, 320, 480};
	ClearImage(&dst, r, g, b);
}

void Compo_SetSprite(GsSPRITE *sprite, const CompoSprite *compo_sprite, int shift, int shift_pal) //FUN_8001b25c
{
	sprite->attribute = compo_sprite->attribute;
	sprite->w = compo_sprite->width;
	sprite->h = compo_sprite->height;
	
	u32 uv_x = (compo_sprite->tex_x * 4) + (shift * compo_sprite->width);
	sprite->tpage = GetTPage(0, 1, (uv_x & 0xFF00) >> 2, compo_sprite->tex_y & 0xFF00);
	sprite->u = uv_x;
	sprite->v = compo_sprite->tex_y;
	
	sprite->cx = compo_sprite->pal_x;
	if (shift_pal == 0)
		sprite->cy = compo_sprite->pal_y;
	else
		sprite->cy = compo_sprite->pal_y + shift;
}

void Compo_FastSprite(s16 x, s16 y, const CompoSprite *compo_sprite, int shift, int shift_pal, u16 pri, GsOT *ot) //FUN_8001b590
{
	//Set sprite
	GsSPRITE sprite;
	sprite.x = x - 160;
	sprite.y = y - 120;
	Compo_SetSprite(&sprite, compo_sprite, shift, shift_pal);
	
	//Sort sprite into ot
	GsSortFastSprite(&sprite, ot, pri);
}

u8 tim_sony[] = {
	#include "tim_sony.h"
};

u8 tim_masaya[] = {
	#include "tim_masaya.h"
};

u16 pal_sony[] = {
	0x7FFF,0x7BDE,0x6B5A,0x5EF7,0x5AD6,0x4E73,0x4A52,0x4210,0x318C,0x294A,0x2108,0x18C6,0x14A5,0x0842,0x0421,0x8000
};

u16 pal_masaya[] = {
	0x7FFF,0x7FFE,0x7FDE,0x7BDE,0x7FDD,0x7FBD,0x7BBD,0x7FBC,0x7BBC,0x7F9C,0x7B9C,0x779C,0x7B9B,0x779B,0x7B7B,0x777B,
	0x737B,0x777A,0x737A,0x7B5A,0x775A,0x735A,0x6F5A,0x7759,0x7359,0x7339,0x6F39,0x6F19,0x7338,0x6F38,0x7318,0x6F18,
	0x6B18,0x7317,0x6F17,0x6B17,0x6EF7,0x6AF7,0x66F7,0x6EF6,0x6AF6,0x6ED6,0x6AD6,0x66D6,0x6AD5,0x66D5,0x6AB5,0x66B5,
	0x62B5,0x66B4,0x62B4,0x6A94,0x6694,0x6294,0x6293,0x6673,0x6273,0x5E73,0x6272,0x5E72,0x6252,0x5E52,0x5A52,0x6251,
	0x5E51,0x5A51,0x6231,0x5E31,0x5A31,0x5E30,0x5A30,0x5E10,0x5A10,0x5610,0x5E0F,0x5A0F,0x560F,0x5DEF,0x59EF,0x55EF,
	0x51EF,0x59EE,0x51EE,0x59CE,0x55CE,0x51CE,0x4DCE,0x55CD,0x51CD,0x55AD,0x51AD,0x4DAD,0x55AC,0x51AC,0x4DAC,0x598C,
	0x558C,0x518C,0x4D8C,0x558B,0x4D8B,0x498B,0x556B,0x516B,0x4D6B,0x496B,0x456B,0x516A,0x4D6A,0x496A,0x554A,0x514A,
	0x4D4A,0x494A,0x454A,0x5149,0x4D49,0x4949,0x4549,0x5129,0x4D29,0x4929,0x4529,0x4129,0x3D29,0x4D28,0x4928,0x4528,
	0x4128,0x4D08,0x4908,0x4508,0x4108,0x3D08,0x3908,0x4907,0x4507,0x4107,0x3D07,0x3907,0x3507,0x48E7,0x44E7,0x40E7,
	0x3CE7,0x38E7,0x34E7,0x30E7,0x44E6,0x40E6,0x3CE6,0x38E6,0x34E6,0x30E6,0x44C6,0x40C6,0x3CC6,0x38C6,0x34C6,0x30C6,
	0x2CC6,0x28C6,0x40C5,0x3CC5,0x38C5,0x34C5,0x30C5,0x2CC5,0x40A5,0x3CA5,0x38A5,0x34A5,0x30A5,0x2CA5,0x28A5,0x24A5,
	0x40A4,0x3CA4,0x38A4,0x34A4,0x30A4,0x2CA4,0x28A4,0x20A4,0x3C84,0x3884,0x3484,0x3084,0x2C84,0x2884,0x2484,0x2084,
	0x1C84,0x3883,0x3483,0x2883,0x1C83,0x3C63,0x3863,0x3463,0x3063,0x2C63,0x2863,0x2463,0x2063,0x1C63,0x1863,0x1463,
	0x3462,0x3062,0x2C62,0x2862,0x2462,0x2062,0x1C62,0x1862,0x1462,0x3842,0x3442,0x3042,0x2C42,0x2842,0x2442,0x2042,
	0x1C42,0x1842,0x1442,0x1042,0x0C42,0x3441,0x3041,0x2441,0x2041,0x1C41,0x1841,0x1441,0x1041,0x0C41,0x3021,0x2421,
	0x2021,0x1C21,0x1821,0x1421,0x1021,0x0C21,0x0821,0x0421,0x1020,0x0C20,0x0820,0x0420,0x0C00,0x0800,0x0400,0x8000
};

#ifdef PARAPPA_UB
u16 pal_fade[0xDA8]; //I honestly can't figure this out
#else
u16 pal_fade[31 * 256];
#endif

u16 Compo_FadeColour(u16 colour, int i)
{
	if (colour == 0)
		return 0;
	return ((((colour >> 10) & 0x1F) * i / 30) << 10) |
	       ((((colour >>  5) & 0x1F) * i / 30) <<  5) |
		   ((((colour >>  0) & 0x1F) * i / 30) <<  0);
}

void Compo_Sony_FadeInit(void) //FUN_8001bfc0
{
	//Get fade colours
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 31; j++)
			pal_fade[j * 16 + i] = Compo_FadeColour(pal_sony[i], j);
}

void Compo_Sony_FadeLoad(int x, int y, int i) //FUN_8001c05c
{
	//Load palette of given index
	LoadClut2((u_long*)&pal_fade[i * 16], x, y);
	DrawSync(0);
}

void Compo_Sony_Init(void) //FUN_8001c0a0
{
	//Load Tim and initialize fade
	Compo_LoadTim_2(tim_sony, 1);
	Compo_Sony_FadeInit();
}

void Compo_Masaya_FadeInit(void) //FUN_8001c0d0
{
	//Get fade colours
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 31; j++)
			pal_fade[j * 256 + i] = Compo_FadeColour(pal_masaya[i], j);
}

void Compo_Masaya_FadeLoad(int x, int y, int i) //FUN_8001c16c
{
	//Load palette of given index
	if (i < 0)
		i = 0;
	LoadClut((u_long*)&pal_fade[i * 256], x, y);
	DrawSync(0);
}

void Compo_Masaya_Init(void) //FUN_8001c1b8
{
	//Load Tim and initialize fade
	Compo_LoadTim_2(tim_masaya, 1);
	Compo_Masaya_FadeInit();
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

void Compo_Clear(int i) //FUN_8001e374
{
	//Clear ordering table
	GsClearOt(0, 0, &compo_ot[i]);
}

void Compo_Flip(int i) //FUN_8001e3b0
{
	//Draw ordering table
	GsDrawOt(&compo_ot[i]);
}

void Compo_Sony_Display(int i) //FUN_8001e408
{
	//Get work base and clear
	compo_activebuff = GsGetActiveBuff();
	GsSetWorkBase(compo_work[compo_activebuff]);
	Compo_Clear(compo_activebuff);
	
	//Load palette
	if (i < 30)
		Compo_Sony_FadeLoad(0x340, 0x1FF, i);
	if (i >= 120 && i < 150)
		Compo_Sony_FadeLoad(0x340, 0x1FF, 149 - i);
	
	//Display Sony logo
	static const CompoSprite sprite_sony_0 = {
		GsAONE | GsLOFF,
		0x280, 0x1DE,
		0xD8, 0xF,
		0x340, 0x1FF
	};
	static const CompoSprite sprite_sony_1 = {
		GsAONE | GsLOFF,
		0x280, 0x1EE,
		0x3C, 0xC,
		0x340, 0x1FF
	};
	static const CompoSprite sprite_sony_2 = {
		GsAONE | GsLOFF,
		0x29B, 0x1EE,
		0x40, 0xC,
		0x340, 0x1FF
	};
	Compo_FastSprite( 20, 106, &sprite_sony_0, 0, 0, 0, &compo_ot[compo_activebuff]);
	Compo_FastSprite(240, 106, &sprite_sony_1, 0, 0, 0, &compo_ot[compo_activebuff]);
	Compo_FastSprite(128, 122, &sprite_sony_2, 0, 0, 0, &compo_ot[compo_activebuff]);
}

void Compo_Sony_Flip(void) //FUN_8001e54c
{
	//Swap buffer then draw scene
	GsSwapDispBuff();
	GsSortClear(0, 0, 0, &compo_ot[compo_activebuff]);
	Compo_Flip(compo_activebuff);
}

void Compo_Masaya_Display(int i) //FUN_8001e5a4
{
	//Get work base and clear
	compo_activebuff = GsGetActiveBuff();
	GsSetWorkBase(compo_work[compo_activebuff]);
	Compo_Clear(compo_activebuff);
	
	//Load palette
	if (i < 30)
		Compo_Masaya_FadeLoad(0x340, 0x1FF, i);
	if (i >= 120 && i < 150)
		Compo_Masaya_FadeLoad(0x340, 0x1FF, 149 - i);
}

void Compo_Masaya_Flip(void) //FUN_8001e6b0
{
	//Use Sony screen's flip
	Compo_Sony_Flip();
}

void Compo_Init2(void) //FUN_8001e6d0
{
	//Initialize ordering tables
	for (int i = 0; i < 2; i++)
	{
		compo_ot[i].org = compo_tag[i];
		compo_ot[i].length = 4;
		compo_ot[i].offset = 0;
	}
}

void Compo_Init(void) //FUN_8001ed94
{
	Compo_Init1();
	Compo_Init2();
}
