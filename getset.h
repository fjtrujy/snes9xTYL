/*
 * Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.
 *
 * (c) Copyright 1996 - 2001 Gary Henderson (gary.henderson@ntlworld.com) and
 *                           Jerremy Koot (jkoot@snes9x.com)
 *
 * Super FX C emulator code 
 * (c) Copyright 1997 - 1999 Ivar (ivar@snes9x.com) and
 *                           Gary Henderson.
 * Super FX assembler emulator code (c) Copyright 1998 zsKnight and _Demo_.
 *
 * DSP1 emulator code (c) Copyright 1998 Ivar, _Demo_ and Gary Henderson.
 * C4 asm and some C emulation code (c) Copyright 2000 zsKnight and _Demo_.
 * C4 C code (c) Copyright 2001 Gary Henderson (gary.henderson@ntlworld.com).
 *
 * DOS port code contains the works of other authors. See headers in
 * individual files.
 *
 * Snes9x homepage: http://www.snes9x.com
 *
 * Permission to use, copy, modify and distribute Snes9x in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Snes9x is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for Snes9x or software derived from Snes9x.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 *
 * Super NES and Super Nintendo Entertainment System are trademarks of
 * Nintendo Co., Limited and its subsidiary companies.
 */
#ifndef _GETSET_H_
#define _GETSET_H_

#include "ppu.h"
#include "dsp1.h"
#include "cpuexec.h"
#include "sa1.h"
#include "c4.h"
#include "bsx.h"
#include "spc7110.h"
#include "hwregisters.h"

INLINE uint8 S9xGetByte (uint32 Address)
{
#if defined(VAR_CYCLES) || defined(CPU_SHUTDOWN)
    int block;
    uint8 *GetAddress = CPU.MemoryMap [block = (Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#else
    uint8 *GetAddress = CPU.MemoryMap [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#endif    
#ifdef VAR_CYCLES
	CPU.Cycles += CPU.MemorySpeed [block];
#endif
    if (GetAddress >= (uint8 *) CMemory::MAP_LAST)
    {

#ifdef CPU_SHUTDOWN
		if (Memory.BlockIsRAM [block])
			CPU.WaitAddress = CPU.PCAtOpcodeStart;
#endif
		return (*(GetAddress + (Address & 0xffff)));
	}
    return S9xGetByteFromRegister(GetAddress, Address);
}

INLINE uint16 S9xGetWord (uint32 Address)
{
    if ((Address & 0x1fff) == 0x1fff)
    {
	return (S9xGetByte (Address) | (S9xGetByte (Address + 1) << 8));
    }
#if defined(VAR_CYCLES) || defined(CPU_SHUTDOWN)
    int block;
    uint8 *GetAddress = CPU.MemoryMap [block = (Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#else
    uint8 *GetAddress = CPU.MemoryMap [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#endif    
#ifdef VAR_CYCLES
	CPU.Cycles += CPU.MemorySpeed [block] << 1;
#endif
    if (GetAddress >= (uint8 *) CMemory::MAP_LAST)
    {
#ifdef CPU_SHUTDOWN
	if (Memory.BlockIsRAM [block])
	    CPU.WaitAddress = CPU.PCAtOpcodeStart;
#endif
#ifdef FAST_LSB_WORD_ACCESS
	return (*(uint16 *) (GetAddress + (Address & 0xffff)));
#else
	return (*(GetAddress + (Address & 0xffff)) |
		(*(GetAddress + (Address & 0xffff) + 1) << 8));
#endif	
    }
    return S9xGetWordFromRegister(GetAddress, Address);
}

INLINE void S9xSetByte (uint8 Byte, uint32 Address)
{
#if defined(CPU_SHUTDOWN)
    CPU.WaitAddress = NULL;
#endif
#if defined(VAR_CYCLES)
    int block;
    uint8 *SetAddress = CPU.MemoryWriteMap [block = ((Address >> MEMMAP_SHIFT) & MEMMAP_MASK)];
#else
    uint8 *SetAddress = CPU.MemoryWriteMap [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#endif
#ifdef VAR_CYCLES
	CPU.Cycles += CPU.MemorySpeed [block];
#endif
    if (SetAddress >= (uint8 *) CMemory::MAP_LAST)
    {
#ifdef CPU_SHUTDOWN
	SetAddress += Address & 0xffff;
	//if(Setting_SA1)
	if (SetAddress == SA1.WaitByteAddress1 ||
	    SetAddress == SA1.WaitByteAddress2)
	{
	    SA1.Executing = SA1.S9xOpcodes != NULL;
	    SA1.WaitCounter = 0;
	}
	*SetAddress = Byte;
#else
	*(SetAddress + (Address & 0xffff)) = Byte;
#endif
	return;
    }
    S9xSetByteToRegister(Byte, SetAddress, Address);
}

INLINE void CpuSetByteWakeSA1 (uint8 Byte, uint32 Address)
{
    int block;
    uint8 *SetAddress = CPU.MemoryWriteMap [block = ((Address >> MEMMAP_SHIFT) & MEMMAP_MASK)];

    CPU.Cycles += CPU.MemorySpeed [block];
	
    if (SetAddress >= (uint8 *) CMemory::MAP_LAST)
    {
        *(SetAddress + (Address & 0xffff)) = Byte;

 		if ((SetAddress + (Address & 0xffff)) == SA1.WaitByteAddress1 ||
			(SetAddress + (Address & 0xffff)) == SA1.WaitByteAddress2)
		{
            if (!SA1.Executing)
                SA1.Executing = !SA1.Waiting && SA1.S9xOpcodes != NULL;
            if (SA1.Executing) SA1.WaitCounter = 3;
		}       
        return;
    }
    S9xSetByteToRegister(Byte, SetAddress, Address);
}


INLINE void S9xSetWord(uint16 Word, uint32 Address)
{
#if defined(CPU_SHUTDOWN)
    CPU.WaitAddress = NULL;
#endif
#if defined (VAR_CYCLES)
    int block;
    uint8 *SetAddress = CPU.MemoryWriteMap [block = ((Address >> MEMMAP_SHIFT) & MEMMAP_MASK)];
#else
    uint8 *SetAddress = CPU.MemoryWriteMap [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#endif
#ifdef VAR_CYCLES
	CPU.Cycles += CPU.MemorySpeed [block] << 1;
#endif
    if (SetAddress >= (uint8 *) CMemory::MAP_LAST)
    {
#ifdef CPU_SHUTDOWN
	SetAddress += Address & 0xffff;
	//if(Setting_SA1)
	if (SetAddress == SA1.WaitByteAddress1 ||
	    SetAddress == SA1.WaitByteAddress2)
	{
	    SA1.Executing = SA1.S9xOpcodes != NULL;
	    SA1.WaitCounter = 0;
	}
	SetAddress -= Address & 0xffff;
#ifdef FAST_LSB_WORD_ACCESS
	*(uint16 *) SetAddress = Word;
#else
	*(SetAddress + (Address & 0xffff)) = (uint8) Word;
	*(SetAddress + ((Address + 1) & 0xffff)) = Word >> 8;
#endif
#else
#ifdef FAST_LSB_WORD_ACCESS
	*(uint16 *) (SetAddress + (Address & 0xffff)) = Word;
#else
	*(SetAddress + (Address & 0xffff)) = (uint8) Word;
	*(SetAddress + ((Address + 1) & 0xffff)) = Word >> 8;
#endif
#endif
	return;
    }
    S9xSetWordToRegister(Word, SetAddress, Address);
}

INLINE void CpuSetWordWakeSA1 (uint16 Word, uint32 Address)
{
#if defined(CPU_SHUTDOWN)
    CPU.WaitAddress = NULL;
#endif
#if defined (VAR_CYCLES)
    int block;
    uint8 *SetAddress = CPU.MemoryWriteMap [block = ((Address >> MEMMAP_SHIFT) & MEMMAP_MASK)];
#else
    uint8 *SetAddress = CPU.MemoryWriteMap [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
#endif
#ifdef VAR_CYCLES
	CPU.Cycles += CPU.MemorySpeed [block] << 1;
#endif
	if (SetAddress >= (uint8 *) CMemory::MAP_LAST)
	{
#ifdef CPU_SHUTDOWN
		if ((SetAddress + (Address & 0xffff)) == SA1.WaitByteAddress1 ||
				(SetAddress + (Address & 0xffff)) == SA1.WaitByteAddress2)
		{
			if (!SA1.Executing)
					SA1.Executing = !SA1.Waiting && SA1.S9xOpcodes != NULL;
			if (SA1.Executing) SA1.WaitCounter = 3;
		}       
#ifdef FAST_LSB_WORD_ACCESS
	*(uint16 *) SetAddress = Word;
#else
	*(SetAddress + (Address & 0xffff)) = (uint8) Word;
	*(SetAddress + ((Address + 1) & 0xffff)) = Word >> 8;
#endif
#else
#ifdef FAST_LSB_WORD_ACCESS
	*(uint16 *) (SetAddress + (Address & 0xffff)) = Word;
#else
	*(SetAddress + (Address & 0xffff)) = (uint8) Word;
	*(SetAddress + ((Address + 1) & 0xffff)) = Word >> 8;
#endif
#endif
	return;
    }		
	S9xSetWordToRegister(Word, SetAddress, Address);
}

INLINE uint8 *GetBasePointer (uint32 Address)
{
    uint8 *GetAddress = Map [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
    if (GetAddress >= (uint8 *) CMemory::MAP_LAST)
	return (GetAddress);

    switch ((int) GetAddress)
    {
	case CMemory::MAP_SPC7110_ROM:
		return (S9xGetBasePointerSPC7110(Address));
    case CMemory::MAP_PPU:
	return (ROM_GLOBAL - 0x2000);
    case CMemory::MAP_CPU:
	return (ROM_GLOBAL - 0x4000);
    case CMemory::MAP_DSP:
	return (ROM_GLOBAL - 0x6000);
    case CMemory::MAP_SA1RAM:
    case CMemory::MAP_LOROM_SRAM:
        return (SRAM + ((((Address&0xFF0000)>>1)|(Address&0x7FFF)) & Memory.SRAMMask) - (Address&0xffff));
    case CMemory::MAP_BWRAM:
	return (BWRAM - 0x6000);
    case CMemory::MAP_HIROM_SRAM:
        return (SRAM + (((Address & 0x7fff) - 0x6000 + ((Address & 0xf0000) >> 3)) & Memory.SRAMMask) - (Address&0xffff));
    case CMemory::MAP_C4:
	return (S9xGetBasePointerC4(Address & 0xffff));
    case CMemory::MAP_DEBUG:
#ifdef DEBUGGER
	printf ("GBP %06x\n", Address);
#endif

    default:
    case CMemory::MAP_NONE:
#ifdef DEBUGGER
	printf ("GBP %06x\n", Address);
#endif
	return (0);
    }
}

INLINE uint8 *S9xGetMemPointer (uint32 Address)
{
    uint8 *GetAddress = Map [(Address >> MEMMAP_SHIFT) & MEMMAP_MASK];
    if (GetAddress >= (uint8 *) CMemory::MAP_LAST)
	return (GetAddress + (Address & 0xffff));

    switch ((int) GetAddress)
    {
	case CMemory::MAP_SPC7110_ROM:
		return (S9xGetBasePointerSPC7110(Address) + (Address & 0xffff));
    case CMemory::MAP_PPU:
	return (ROM_GLOBAL - 0x2000 + (Address & 0xffff));
    case CMemory::MAP_CPU:
	return (ROM_GLOBAL - 0x4000 + (Address & 0xffff));
    case CMemory::MAP_DSP:
	return (ROM_GLOBAL - 0x6000 + (Address & 0xffff));
    case CMemory::MAP_SA1RAM:
    case CMemory::MAP_LOROM_SRAM:
        return (SRAM + ((((Address&0xFF0000)>>1)|(Address&0x7FFF)) & Memory.SRAMMask));
    case CMemory::MAP_BWRAM:
	return (BWRAM - 0x6000 + (Address & 0xffff));
    case CMemory::MAP_HIROM_SRAM:
        return (SRAM + (((Address & 0x7fff) - 0x6000 + ((Address & 0xf0000) >> 3)) & Memory.SRAMMask));
    case CMemory::MAP_C4:
	return (S9xGetMemPointerC4(Address & 0xffff));
    case CMemory::MAP_DEBUG:
#ifdef DEBUGGER
	printf ("GMP %06x\n", Address);
#endif
    default:
    case CMemory::MAP_NONE:
#ifdef DEBUGGER
	printf ("GMP %06x\n", Address);
#endif
	return (0);
    }
}

INLINE void S9xSetPCBase (uint32 Address)
{
    int block;
    uint8 *GetAddress = Map [block = (Address >> MEMMAP_SHIFT) & MEMMAP_MASK];

	CPU.MemSpeed = Memory.MemorySpeed [block];
	CPU.MemSpeedx2 = CPU.MemSpeed << 1;
 
   if (GetAddress >= (uint8 *) CMemory::MAP_LAST)
    {
		CPU.PCBase = GetAddress;
		CPU.PC = GetAddress + (Address & 0xffff);
		return;
    }
    S9xSetPCBaseOthers(GetAddress, Address);
}

#endif
