#ifndef PARAPPA_GUARD_PRAPP_H
#define PARAPPA_GUARD_PRAPP_H

#include "psx.h"

//App interface
void App_Init(void); //FUN_800154f4
void App_Screen_In(void (*screen_display)(int i), void (*screen_flip)(void), void (*screen_init)(void)); //FUN_80015a4c
void App_Wait(int time_a, int time_b); //FUN_80015b00
void App_Screen_Out(void (*display)(int i), void (*flip)(void)); //FUN_80015c20
void App_Loop(void);

#endif
