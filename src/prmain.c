#include "prmain.h"

#include <libapi.h>
#include <libetc.h>

#include <libgte.h>
#include <libgpu.h>

#include "prapp.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prmain.c: version 01-00 95/10/10 00:00:00";

//Entry point
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	//Run game
	App_Init();
	App_Loop();
	return 0;
}