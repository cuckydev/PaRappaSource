#include "prvtext.h"

#include <libgte.h>
#include <libgpu.h>

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prvtext.c: version 01-00 95/10/10 00:00:00";

//VText interface
void VText_Init(void)
{
	//Load and open font
	FntLoad(0x3C0, 0x100);
	SetDumpFnt(FntOpen(-156, -120, 320, 200, 0, 0x200));
	SetDispMask(-1);
}
