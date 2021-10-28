#include "prcompo.h"

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

//Compo interface
void Compo_LoadTim(u32 *buffer)
{
	RECT rect;
	
	//Get image information
	GsIMAGE image;
	GsGetTimInfo(buffer + 1, &image);
	
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

