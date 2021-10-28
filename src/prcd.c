#include "prcd.h"

#include <libetc.h>

#include "prcompo.h"
#include "prmemory.h"
#include "prrap.h"

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

int CD_ReadSectors(u8 *buffer, int sectors, int mode) //FUN_8001a818
{
	int result;
	
	//Read sectors
	do
	{
		result = CdRead(sectors, (u_long*)buffer, (mode == 1) * CdlModeSpeed);
	} while (result == 0);
	
	//Sync
	VSync(3);
	do
	{
		result = CdReadSync(1, NULL);
	} while (result > 0);
	
	return sectors & -(result == 0);
}

int CD_Seek(CdlLOC *pos, int offset) //FUN_8001a89c
{
	//Offset then seek
	CdIntToPos(CdPosToInt(pos) + offset, pos);
	return CdControlB(CdlSetloc, (u_char*)pos, NULL) != 0;
}

int CD_Read(CdlFILE *file, int mode, int offset) //FUN_8001a8f0
{
	//Seek to file
	if (CD_Seek(&file->pos, offset) != 0)
	{
		while (1)
		{
			//Allocate 4 sector header
			u32 *header = Memory_EndAlloc(2048 * 4);
			if (header == NULL)
				exit(1);
			
			//Read sectors and reseek(?)
			if (CD_ReadSectors((u8*)header, 4, mode) == 0 || CD_Seek(&file->pos, 4) == 0)
				break;
			
			//Handle read based off case
			switch (header[0])
			{
				case 1: //Tim
				{
					//Allocate buffer according to header
					u8 *buffer = Memory_Push(header[2] << 11);
					u32 *headerp = header + 4;
					if (buffer == NULL)
						exit(1);
					
					//Read sectors
					if (CD_ReadSectors(buffer, header[2], mode) == 0)
						return 0;
					
					//Read data
					for (int i = 0; i < (int)header[1];)
					{
						Compo_LoadTim(buffer);
						u32 len = *headerp;
						headerp += 5;
						i++;
						buffer += len;
					}
					
					Memory_Pop();
					if (header[1] == 0)
						return 0;
					break;
				}
				case 2: //Vab
				{
					//Allocate buffers according to header
					u8 *buffer1 = Memory_Push(header[4]);
					if (buffer1 == NULL)
						exit(1);
					
					u8 *buffer2 = Memory_Push(header[9]);
					if (buffer2 == NULL)
						exit(1);
					
					//Read sectors
					if (CD_ReadSectors(buffer1, header[2], mode) == 0)
					{
						Memory_Pop();
						Memory_Pop();
						return 0;
					}
					
					//Read data
					Rap_CloseVab();
					Rap_Init();
					if (Rap_OpenVab(buffer1) != 0)
					{
						Rap_VabTransBody(buffer1);
						Rap_VabTransCompleted(1);
					}
					
					Memory_Pop();
					if (header[2] == 0)
						return 0;
					break;
				}
				default:
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int CD_File_Read(CD_File *cd_file, int offset) //FUN_8001ac18
{
	//Attempt to read 4 times
	int mode = 1;
	for (int i = 0; i < 4; i++)
	{
		//Find file
		if (i > 0)
			mode = 0; //Use 1x read if we've failed to read before
		if (CD_File_Find(cd_file) >= 0)
		{
			//Read file data
			CdlFILE file = cd_file->file;
			if ((mode = CD_Read(&file, mode, offset)) == 1)
				return 1;
		}
	}
	return mode;
}
