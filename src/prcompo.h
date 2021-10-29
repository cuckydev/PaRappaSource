#ifndef PARAPPA_GUARD_PRCOMPO_H
#define PARAPPA_GUARD_PRCOMPO_H

#include "psx.h"

//Compo interface
void Compo_LoadTim_2(u8 *buffer, int palette); //FUN_8001adec
void Compo_LoadTim(u8 *buffer); //FUN_8001ae7c
void Compo_ClearScreen(u8 r, u8 g, u8 b); //FUN_8001b1b0
void Compo_Sony_FadeInit(void); //FUN_8001bfc0
void Compo_Sony_Init(void); //FUN_8001c0a0
void Compo_Masaya_FadeInit(void); //FUN_8001c0d0
void Compo_Masaya_Init(void); //FUN_8001c1b8
void Compo_Init1(void); //FUN_8001c470
void Compo_Sony_Display(int i); //FUN_8001e408
void Compo_Sony_Flip(void); //FUN_8001e54c
void Compo_Masaya_Display(int i); //FUN_8001e5a4
void Compo_Masaya_Flip(void); //FUN_8001e6b0
void Compo_Init2(void); //FUN_8001e6d0
void Compo_Init(void); //FUN_8001ed94

#endif
