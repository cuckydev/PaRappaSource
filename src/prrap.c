#include "prrap.h"

#include <libsnd.h>

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prrap.c: version 01-00 95/10/10 00:00:00";

//Rap state
s16 rap_vab; //DAT_800943a8

//Rap interface
void Rap_Init(void) //FUN_80026e4c
{
	//Initialize SND state
	SsInitHot();
	SsSetTickMode(SS_NOTICK);
	SsStart();
	SsSetMVol(90, 90);
	SsSetSerialAttr(0, 0, 1);
	SsSetSerialVol(0, 0x7F, 0x7F);
	
	//Initialize rap state
	rap_vab = 0;
	//DAT_800943aa = 0xffff;
	//DAT_800943ac = 0xffff;
	//DAT_800943b4 = 0;
}

int Rap_OpenVab(u8 *buffer) //FUN_80027078
{
	rap_vab = SsVabOpenHead(buffer, -1);
	return ~((int)rap_vab) >> 31;
}

void Rap_VabTransBody(u8 *buffer) //FUN_800270d4
{
	SsVabTransBody(buffer, rap_vab);
}

void Rap_VabTransCompleted(int mode) //FUN_800270fc
{
	SsVabTransCompleted(mode == 1);
}

int Rap_CloseVab(void) //FUN_80027120
{
	//Check if Vab should be closed
	if (rap_vab >= 0)
	{
		SsVabClose(rap_vab);
		rap_vab = -1;
	}
	return 0;
}
