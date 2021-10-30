#ifndef PARAPPA_GUARD_BOOT_PRCD_H
#define PARAPPA_GUARD_BOOT_PRCD_H

#include "psx.h"

#include <libcd.h>

//CD types
typedef struct
{
	char *path;
	int l01;
	int l02;
	int found;
	CdlFILE file; //l04
	int pos_start;
	int pos_end;
} CD_File;

//CD interface
void CD_Init(void); //FUN_8001a1cc
CdlFILE *CD_Find(CdlFILE *file, char *path);
int CD_File_Find(CD_File *cd_file); //FUN_8001a324
int CD_Seek(CdlLOC *file, int offset); //FUN_8001a89c
int CD_Read(CdlFILE *file, int result, int offset); //FUN_8001a324
int CD_File_Read(CD_File *cd_file, int offset); //FUN_8001ac18
int CD_File_ReadRaw(CD_File *cd_file, u_long *to); //FUN_8001acf8

#endif
