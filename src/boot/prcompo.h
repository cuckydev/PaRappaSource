#ifndef PARAPPA_GUARD_BOOT_PRCOMPO_H
#define PARAPPA_GUARD_BOOT_PRCOMPO_H

#include "psx.h"

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

//Compo types
typedef struct
{
	s32 attribute;
	s16 tex_x, tex_y;
	s16 width, height;
	s16 pal_x, pal_y;
} CompoSprite;

//Compo interface
void Compo_LoadTim_2(u8 *buffer, int palette); //FUN_8001adec
void Compo_LoadTim(u8 *buffer); //FUN_8001ae7c
void Compo_ClearScreen(u8 r, u8 g, u8 b); //FUN_8001b1b0
void Compo_SetSprite(GsSPRITE *sprite, const CompoSprite *compo_sprite, int shift, int shift_pal); //FUN_8001b25c
void Compo_FastSprite(s16 x, s16 y, const CompoSprite *compo_sprite, int shift, int shift_pal, u16 pri, GsOT *ot); //FUN_8001b590
void Compo_Sony_FadeInit(void); //FUN_8001bfc0
void Compo_Sony_Init(void); //FUN_8001c0a0
void Compo_Masaya_FadeInit(void); //FUN_8001c0d0
void Compo_Masaya_Init(void); //FUN_8001c1b8
void Compo_Init1(void); //FUN_8001c470
void Compo_Clear(int i); //FUN_8001e374
void Compo_Flip(int i); //FUN_8001e3b0
void Compo_Sony_Display(int i); //FUN_8001e408
void Compo_Sony_Flip(void); //FUN_8001e54c
void Compo_Masaya_Display(int i); //FUN_8001e5a4
void Compo_Masaya_Flip(void); //FUN_8001e6b0
void Compo_Init2(void); //FUN_8001e6d0
void Compo_Init(void); //FUN_8001ed94

#endif
