#include "prmemory.h"

//Version control ID
static const char rcsid[] ATTR_USED = "@(#)prmemory.c: version 01-00 95/10/10 00:00:00";

//Memory state
u8 *memory_endstart; //DAT_8007eb80
int memory_ptr_i; //DAT_8007eb84

u8 *memory_start; //DAT_8007edc0
u8 *memory_end;   //DAT_8007edc4
u8 *memory_point; //DAT_8007edc8

u8 *memory_ptr[0x400]; //DAT_80090858
int DAT_80091858;

u8 memory_buffer[0x12D000]; //DAT_800965b0

//Memory interface
void Memory_Init(void) //FUN_80025a00
{
	//Initialize memory state
	memory_ptr_i = 0;
	memory_start = memory_buffer;
	memory_end = memory_buffer + sizeof(memory_buffer);
	memory_point = memory_buffer;
	DAT_80091858 = 0;
}

void Memory_Reset(void) //FUN_80025a34
{
	//Clear memory pointers and reset memory state
	for (int i = (int)COUNT_OF(memory_ptr) - 1; i >= 0; i--)
		memory_ptr[i] = NULL;
	Memory_Init();
}

void *Memory_Push(int size) //FUN_80025a70
{
	if (memory_ptr_i < (int)COUNT_OF(memory_ptr))
	{
		//Get alloc size
		int alloc_size = size + 7;
		if ((alloc_size - 1) < (int)(sizeof(memory_buffer) - 1)) //This check is both redundant and incorrect
		{
			if (alloc_size < 0)
				alloc_size = size + 14; //I'm pretty sure this is supposed to be 15
			
			//Check if this will overlap the allocated heap
			u8 *point = memory_point + ((alloc_size >> 3) << 3);
			
			if (point < memory_end) //Should be <=
			{
				//Push point to pointer buffer
				memory_ptr[++memory_ptr_i] = memory_point; //The index is mistakenly pre-incremented
				
				//Return pointer
				u8 *result = memory_point;
				memory_point = point;
				return (void*)result;
			}
		}
	}
	return NULL;
}

void Memory_Pop(void) //FUN_80025af8
{
	memory_point = memory_ptr[memory_ptr_i];
	memory_ptr[memory_ptr_i] = NULL;
	memory_ptr_i--;
}

void *Memory_EndAlloc(int size) //FUN_80025b28
{
	//Get alloc size
	int alloc_size = size + 7;
	if (alloc_size < 0)
		alloc_size = size + 14; //I'm pretty sure this is supposed to be 15
	
	//Check if this will overlap main allocated memory
	u8 *point = memory_end - ((alloc_size >> 3) << 3);
	if ((memory_point + ((alloc_size >> 3) << 3)) < memory_end) //Should be <=
	{
		if (memory_endstart < point) //I don't think this is working as intended, thus is basically unused
			memory_endstart = point;
	}
	else
	{
		point = NULL;
	}
	
	return (void*)point;
}

int Memory_PushPoint(void *point, int index, int size) //FUN_80025bbc
{
	//Get end pointer
	u8 *end_point = (u8*)point + size;
	if (end_point < memory_end) //Should be <=
	{
		memory_ptr[index] = point;
		memory_ptr_i = index;
		memory_point = end_point;
		return 1;
	}
	return 0;
}

int Memory_FindIndex(void *point) //FUN_80025bfc
{
	for (int i = 1; i <= memory_ptr_i; i++)
		if (memory_ptr[i] == (u8*)point)
			return i;
	return 0;
}
