#include "prcd.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prcd.c: version 01-00 95/10/10 00:00:00";

//CD interface
void CD_Init(void) //FUN_8001a1cc
{
	CdlATV cdatv = {0x40, 0x40, 0x40, 0x40};
	CdInit();
	CdMix(&cdatv);
}

CdlFILE *CD_Find(CdlFILE *file, char *path) //FUN_8001a2b0
{
	if (path != NULL)
	{
		int i = 0;
		do
		{
			//Search for file
			CdlFILE *result = CdSearchFile(file, path);
			i++;
			if (result != NULL)
				return file; //Not result?
		} while (i < 4);
	}
	return NULL;
}

int CD_File_Find(CD_File *cd_file) //FUN_8001a324
{
	//Check file state
	if (cd_file->found != 1 && cd_file->path != NULL)
	{
		//Find file position
		if (CD_Find(&cd_file->file, cd_file->path) == NULL)
			return -1;
		
		//Set file state
		int pos = CdPosToInt(&cd_file->file.pos);
		cd_file->pos_start = pos;
		cd_file->found = 1;
		cd_file->pos_end = pos + (cd_file->file.size >> 11);
	}
	return 0;
}

int CD_Seek(CdlLOC *pos, int offset) //FUN_8001a89c
{
	//Offset then seek
	CdIntToPos(CdPosToInt(pos) + offset, pos);
	return CdControlB(CdlSetloc, (u_char*)pos, NULL) != 0;
}

int CD_Read(CdlFILE *file, int result, int offset) //FUN_8001a8f0
{
	//Seek to file
	CD_Seek(&file->pos, offset);
	return 0;
}

int CD_File_Read(CD_File *cd_file, int offset) //FUN_8001ac18
{
	//Attempt to read 4 times
	int result = 1;
	for (int i = 0; i < 4; i++)
	{
		//Find file
		if (i > 0)
			result = 0;
		if (CD_File_Find(cd_file) >= 0)
		{
			//Read file data
			CdlFILE file = cd_file->file;
			if ((result = CD_Read(&file, result, offset)) == 1)
				return 1;
		}
	}
	return result;
}
