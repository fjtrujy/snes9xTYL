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
/**********************************************************************************************/
/* CPU-S9xOpcodes.CPP                                                                            */
/* This file contains all the opcodes                                                         */
/**********************************************************************************************/

// optimized by ruka.

#include "snes9x.h"
#include "memmap.h"
#include "debug.h"
#include "missing.h"
#include "apu.h"
#include "sa1.h"

#include "cpuexec.h"
#include "cpuaddr.h"
#include "cpuops.h"
#include "cpumacro.h"
#include "apu.h"

#ifdef SA1_OPCODES
#define S9xFixCyclesDecimal() 
#else
#define S9xFixCyclesDecimal() 
//#define S9xFixCyclesDecimal() S9xFixCycles();
#endif


/* ADC *************************************************************************************** */
static void Op69M1 (void)
{
    long OpAddress = Immediate8 ();
    ADC8 (OpAddress);
}

static void Op69M0 (void)
{
    long OpAddress = Immediate16 ();
    ADC16 (OpAddress);
}

static void Op65M1 (void)
{
    long OpAddress = Direct();
    ADC8 (OpAddress);
}

static void Op65M0 (void)
{
    long OpAddress = Direct();
    ADC16 (OpAddress);
}

static void Op75M1 (void)
{
    long OpAddress = DirectIndexedX();
    ADC8 (OpAddress);
}

static void Op75M0 (void)
{
    long OpAddress = DirectIndexedX();
    ADC16 (OpAddress);
}

static void Op72M1 (void)
{
    long OpAddress = DirectIndirect();
    ADC8 (OpAddress);
}

static void Op72M0 (void)
{
    long OpAddress = DirectIndirect();
    ADC16 (OpAddress);
}

static void Op61M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    ADC8 (OpAddress);
}

static void Op61M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    ADC16 (OpAddress);
}

static void Op71M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    ADC8 (OpAddress);
}

static void Op71M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    ADC16 (OpAddress);
}

static void Op67M1 (void)
{
    long OpAddress = DirectIndirectLong();
    ADC8 (OpAddress);
}

static void Op67M0 (void)
{
    long OpAddress = DirectIndirectLong();
    ADC16 (OpAddress);
}

static void Op77M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    ADC8 (OpAddress);
}

static void Op77M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    ADC16 (OpAddress);
}

static void Op6DM1 (void)
{
    long OpAddress = Absolute();
    ADC8 (OpAddress);
}

static void Op6DM0 (void)
{
    long OpAddress = Absolute();
    ADC16 (OpAddress);
}

static void Op7DM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ADC8 (OpAddress);
}

static void Op7DM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ADC16 (OpAddress);
}

static void Op79M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    ADC8 (OpAddress);
}

static void Op79M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    ADC16 (OpAddress);
}

static void Op6FM1 (void)
{
    long OpAddress = AbsoluteLong();
    ADC8 (OpAddress);
}

static void Op6FM0 (void)
{
    long OpAddress = AbsoluteLong();
    ADC16 (OpAddress);
}

static void Op7FM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    ADC8 (OpAddress);
}

static void Op7FM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    ADC16 (OpAddress);
}

static void Op63M1 (void)
{
    long OpAddress = StackRelative();
    ADC8 (OpAddress);
}

static void Op63M0 (void)
{
    long OpAddress = StackRelative();
    ADC16 (OpAddress);
}

static void Op73M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    ADC8 (OpAddress);
}

static void Op73M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    ADC16 (OpAddress);
}

/**********************************************************************************************/

/* AND *************************************************************************************** */
static void Op29M1 (void)
{
    Registers.AL &= *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.AL);
}

static void Op29M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.A.W &= *(uint16 *) CPU.PC;
#else
    Registers.A.W &= *CPU.PC + (*(CPU.PC + 1) << 8);
#endif
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.A.W);
}

static void Op25M1 (void)
{
    long OpAddress = Direct();
    AND8 (OpAddress);
}

static void Op25M0 (void)
{
    long OpAddress = Direct();
    AND16 (OpAddress);
}

static void Op35M1 (void)
{
    long OpAddress = DirectIndexedX();
    AND8 (OpAddress);
}

static void Op35M0 (void)
{
    long OpAddress = DirectIndexedX();
    AND16 (OpAddress);
}

static void Op32M1 (void)
{
    long OpAddress = DirectIndirect();
    AND8 (OpAddress);
}

static void Op32M0 (void)
{
    long OpAddress = DirectIndirect();
    AND16 (OpAddress);
}

static void Op21M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    AND8 (OpAddress);
}

static void Op21M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    AND16 (OpAddress);
}

static void Op31M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    AND8 (OpAddress);
}

static void Op31M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    AND16 (OpAddress);
}

static void Op27M1 (void)
{
    long OpAddress = DirectIndirectLong();
    AND8 (OpAddress);
}

static void Op27M0 (void)
{
    long OpAddress = DirectIndirectLong();
    AND16 (OpAddress);
}

static void Op37M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    AND8 (OpAddress);
}

static void Op37M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    AND16 (OpAddress);
}

static void Op2DM1 (void)
{
    long OpAddress = Absolute();
    AND8 (OpAddress);
}

static void Op2DM0 (void)
{
    long OpAddress = Absolute();
    AND16 (OpAddress);
}

static void Op3DM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    AND8 (OpAddress);
}

static void Op3DM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    AND16 (OpAddress);
}

static void Op39M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    AND8 (OpAddress);
}

static void Op39M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    AND16 (OpAddress);
}

static void Op2FM1 (void)
{
    long OpAddress = AbsoluteLong();
    AND8 (OpAddress);
}

static void Op2FM0 (void)
{
    long OpAddress = AbsoluteLong();
    AND16 (OpAddress);
}

static void Op3FM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    AND8 (OpAddress);
}

static void Op3FM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    AND16 (OpAddress);
}

static void Op23M1 (void)
{
    long OpAddress = StackRelative();
    AND8 (OpAddress);
}

static void Op23M0 (void)
{
    long OpAddress = StackRelative();
    AND16 (OpAddress);
}

static void Op33M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    AND8 (OpAddress);
}

static void Op33M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    AND16 (OpAddress);
}
/**********************************************************************************************/

/* ASL *************************************************************************************** */
static void Op0AM1 (void)
{
    A_ASL8 ();
}

static void Op0AM0 (void)
{
    A_ASL16 ();
}

static void Op06M1 (void)
{
    long OpAddress = Direct();
    ASL8 (OpAddress);
}

static void Op06M0 (void)
{
    long OpAddress = Direct();
    ASL16 (OpAddress);
}

static void Op16M1 (void)
{
    long OpAddress = DirectIndexedX();
    ASL8 (OpAddress);
}

static void Op16M0 (void)
{
    long OpAddress = DirectIndexedX();
    ASL16 (OpAddress);
}

static void Op0EM1 (void)
{
    long OpAddress = Absolute();
    ASL8 (OpAddress);
}

static void Op0EM0 (void)
{
    long OpAddress = Absolute();
    ASL16 (OpAddress);
}

static void Op1EM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ASL8 (OpAddress);
}

static void Op1EM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ASL16 (OpAddress);
}
/**********************************************************************************************/

/* BIT *************************************************************************************** */
static void Op89M1 (void)
{
    ICPU._Zero = Registers.AL & *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
}

static void Op89M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    ICPU._Zero = (Registers.A.W & *(uint16 *) CPU.PC) != 0;
#else
    ICPU._Zero = (Registers.A.W & (*CPU.PC + (*(CPU.PC + 1) << 8))) != 0;
#endif	
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    CPU.PC += 2;
}

static void Op24M1 (void)
{
    long OpAddress = Direct();
    BIT8 (OpAddress);
}

static void Op24M0 (void)
{
    long OpAddress = Direct();
    BIT16 (OpAddress);
}

static void Op34M1 (void)
{
    long OpAddress = DirectIndexedX();
    BIT8 (OpAddress);
}

static void Op34M0 (void)
{
    long OpAddress = DirectIndexedX();
    BIT16 (OpAddress);
}

static void Op2CM1 (void)
{
    long OpAddress = Absolute();
    BIT8 (OpAddress);
}

static void Op2CM0 (void)
{
    long OpAddress = Absolute();
    BIT16 (OpAddress);
}

static void Op3CM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    BIT8 (OpAddress);
}

static void Op3CM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    BIT16 (OpAddress);
}
/**********************************************************************************************/

/* CMP *************************************************************************************** */
static void OpC9M1 (void)
{
    long s9xInt32 = (int) Registers.AL - (int) *CPU.PC++;
    ICPU._Carry = s9xInt32 >= 0;
    SetZN8 ((uint8) s9xInt32);
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
}

static void OpC9M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS    
    long s9xInt32 = (long) Registers.A.W - (long) *(uint16 *) CPU.PC;
#else
    long s9xInt32 = (long) Registers.A.W -
	    (long) (*CPU.PC + (*(CPU.PC + 1) << 8));
#endif
    ICPU._Carry = s9xInt32 >= 0;
    SetZN16 ((uint16) s9xInt32);
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
}

static void OpC5M1 (void)
{
    long OpAddress = Direct();
    CMP8 (OpAddress);
}

static void OpC5M0 (void)
{
    long OpAddress = Direct();
    CMP16 (OpAddress);
}

static void OpD5M1 (void)
{
    long OpAddress = DirectIndexedX();
    CMP8 (OpAddress);
}

static void OpD5M0 (void)
{
    long OpAddress = DirectIndexedX();
    CMP16 (OpAddress);
}

static void OpD2M1 (void)
{
    long OpAddress = DirectIndirect();
    CMP8 (OpAddress);
}

static void OpD2M0 (void)
{
    long OpAddress = DirectIndirect();
    CMP16 (OpAddress);
}

static void OpC1M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    CMP8 (OpAddress);
}

static void OpC1M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    CMP16 (OpAddress);
}

static void OpD1M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    CMP8 (OpAddress);
}

static void OpD1M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    CMP16 (OpAddress);
}

static void OpC7M1 (void)
{
    long OpAddress = DirectIndirectLong();
    CMP8 (OpAddress);
}

static void OpC7M0 (void)
{
    long OpAddress = DirectIndirectLong();
    CMP16 (OpAddress);
}

static void OpD7M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    CMP8 (OpAddress);
}

static void OpD7M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    CMP16 (OpAddress);
}

static void OpCDM1 (void)
{
    long OpAddress = Absolute();
    CMP8 (OpAddress);
}

static void OpCDM0 (void)
{
    long OpAddress = Absolute();
    CMP16 (OpAddress);
}

static void OpDDM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    CMP8 (OpAddress);
}

static void OpDDM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    CMP16 (OpAddress);
}

static void OpD9M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    CMP8 (OpAddress);
}

static void OpD9M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    CMP16 (OpAddress);
}

static void OpCFM1 (void)
{
    long OpAddress = AbsoluteLong();
    CMP8 (OpAddress);
}

static void OpCFM0 (void)
{
    long OpAddress = AbsoluteLong();
    CMP16 (OpAddress);
}

static void OpDFM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    CMP8 (OpAddress);
}

static void OpDFM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    CMP16 (OpAddress);
}

static void OpC3M1 (void)
{
    long OpAddress = StackRelative();
    CMP8 (OpAddress);
}

static void OpC3M0 (void)
{
    long OpAddress = StackRelative();
    CMP16 (OpAddress);
}

static void OpD3M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    CMP8 (OpAddress);
}

static void OpD3M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    CMP16 (OpAddress);
}

/**********************************************************************************************/

/* CMX *************************************************************************************** */
static void OpE0X1 (void)
{
    long s9xInt32 = (int) Registers.XL - (int) *CPU.PC++;
    ICPU._Carry = s9xInt32 >= 0;
    SetZN8 ((uint8) s9xInt32);
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
}

static void OpE0X0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS    
    long s9xInt32 = (long) Registers.X.W - (long) *(uint16 *) CPU.PC;
#else
    long s9xInt32 = (long) Registers.X.W -
	    (long) (*CPU.PC + (*(CPU.PC + 1) << 8));
#endif
    ICPU._Carry = s9xInt32 >= 0;
    SetZN16 ((uint16) s9xInt32);
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
}

static void OpE4X1 (void)
{
    long OpAddress = Direct();
    CMX8 (OpAddress);
}

static void OpE4X0 (void)
{
    long OpAddress = Direct();
    CMX16 (OpAddress);
}

static void OpECX1 (void)
{
    long OpAddress = Absolute();
    CMX8 (OpAddress);
}

static void OpECX0 (void)
{
    long OpAddress = Absolute();
    CMX16 (OpAddress);
}

/**********************************************************************************************/

/* CMY *************************************************************************************** */
static void OpC0X1 (void)
{
    long s9xInt32 = (int) Registers.YL - (int) *CPU.PC++;
    ICPU._Carry = s9xInt32 >= 0;
    SetZN8 ((uint8) s9xInt32);
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
}

static void OpC0X0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS    
    long s9xInt32 = (long) Registers.Y.W - (long) *(uint16 *) CPU.PC;
#else
    long s9xInt32 = (long) Registers.Y.W -
	    (long) (*CPU.PC + (*(CPU.PC + 1) << 8));
#endif
    ICPU._Carry = s9xInt32 >= 0;
    SetZN16 ((uint16) s9xInt32);
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
}

static void OpC4X1 (void)
{
    long OpAddress = Direct();
    CMY8 (OpAddress);
}

static void OpC4X0 (void)
{
    long OpAddress = Direct();
    CMY16 (OpAddress);
}

static void OpCCX1 (void)
{
    long OpAddress = Absolute();
    CMY8 (OpAddress);
}

static void OpCCX0 (void)
{
    long OpAddress = Absolute();
    CMY16 (OpAddress);
}

/**********************************************************************************************/

/* DEC *************************************************************************************** */
static void Op3AM1 (void)
{
    A_DEC8 ();
}

static void Op3AM0 (void)
{
    A_DEC16 ();
}

static void OpC6M1 (void)
{
    long OpAddress = Direct();
    DEC8 (OpAddress);
}

static void OpC6M0 (void)
{
    long OpAddress = Direct();
    DEC16 (OpAddress);
}

static void OpD6M1 (void)
{
    long OpAddress = DirectIndexedX();
    DEC8 (OpAddress);
}

static void OpD6M0 (void)
{
    long OpAddress = DirectIndexedX();
    DEC16 (OpAddress);
}

static void OpCEM1 (void)
{
    long OpAddress = Absolute();
    DEC8 (OpAddress);
}

static void OpCEM0 (void)
{
    long OpAddress = Absolute();
    DEC16 (OpAddress);
}

static void OpDEM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    DEC8 (OpAddress);
}

static void OpDEM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    DEC16 (OpAddress);
}

// Wake SA1 Variants

static void OpC6M1_WS (void)
{
    long OpAddress = Direct ();
    DEC8WakeSA1 (OpAddress);
}

static void OpC6M0_WS (void)
{
    long OpAddress = Direct ();
    DEC16WakeSA1 (OpAddress);
}

static void OpD6M1_WS (void)
{
    long OpAddress = DirectIndexedX ();
    DEC8WakeSA1 (OpAddress);
}

static void OpD6M0_WS (void)
{
    long OpAddress = DirectIndexedX ();
    DEC16WakeSA1 (OpAddress);
}

static void OpCEM1_WS (void)
{
    long OpAddress = Absolute ();
    DEC8WakeSA1 (OpAddress);
}

static void OpCEM0_WS (void)
{
    long OpAddress = Absolute ();
    DEC16WakeSA1 (OpAddress);
}

static void OpDEM1_WS (void)
{
    long OpAddress = AbsoluteIndexedX ();
    DEC8WakeSA1 (OpAddress);
}

static void OpDEM0_WS (void)
{
    long OpAddress = AbsoluteIndexedX ();
    DEC16WakeSA1 (OpAddress);
}

/**********************************************************************************************/

/* EOR *************************************************************************************** */
static void Op49M1 (void)
{
    Registers.AL ^= *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.AL);
}

static void Op49M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.A.W ^= *(uint16 *) CPU.PC;
#else
    Registers.A.W ^= *CPU.PC + (*(CPU.PC + 1) << 8);
#endif
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.A.W);
}

static void Op45M1 (void)
{
    long OpAddress = Direct();
    EOR8 (OpAddress);
}

static void Op45M0 (void)
{
    long OpAddress = Direct();
    EOR16 (OpAddress);
}

static void Op55M1 (void)
{
    long OpAddress = DirectIndexedX();
    EOR8 (OpAddress);
}

static void Op55M0 (void)
{
    long OpAddress = DirectIndexedX();
    EOR16 (OpAddress);
}

static void Op52M1 (void)
{
    long OpAddress = DirectIndirect();
    EOR8 (OpAddress);
}

static void Op52M0 (void)
{
    long OpAddress = DirectIndirect();
    EOR16 (OpAddress);
}

static void Op41M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    EOR8 (OpAddress);
}

static void Op41M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    EOR16 (OpAddress);
}

static void Op51M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    EOR8 (OpAddress);
}

static void Op51M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    EOR16 (OpAddress);
}

static void Op47M1 (void)
{
    long OpAddress = DirectIndirectLong();
    EOR8 (OpAddress);
}

static void Op47M0 (void)
{
    long OpAddress = DirectIndirectLong();
    EOR16 (OpAddress);
}

static void Op57M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    EOR8 (OpAddress);
}

static void Op57M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    EOR16 (OpAddress);
}

static void Op4DM1 (void)
{
    long OpAddress = Absolute();
    EOR8 (OpAddress);
}

static void Op4DM0 (void)
{
    long OpAddress = Absolute();
    EOR16 (OpAddress);
}

static void Op5DM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    EOR8 (OpAddress);
}

static void Op5DM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    EOR16 (OpAddress);
}

static void Op59M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    EOR8 (OpAddress);
}

static void Op59M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    EOR16 (OpAddress);
}

static void Op4FM1 (void)
{
    long OpAddress = AbsoluteLong();
    EOR8 (OpAddress);
}

static void Op4FM0 (void)
{
    long OpAddress = AbsoluteLong();
    EOR16 (OpAddress);
}

static void Op5FM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    EOR8 (OpAddress);
}

static void Op5FM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    EOR16 (OpAddress);
}

static void Op43M1 (void)
{
    long OpAddress = StackRelative();
    EOR8 (OpAddress);
}

static void Op43M0 (void)
{
    long OpAddress = StackRelative();
    EOR16 (OpAddress);
}

static void Op53M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    EOR8 (OpAddress);
}

static void Op53M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    EOR16 (OpAddress);
}

/**********************************************************************************************/

/* INC *************************************************************************************** */
static void Op1AM1 (void)
{
    A_INC8 ();
}

static void Op1AM0 (void)
{
    A_INC16 ();
}

static void OpE6M1 (void)
{
    long OpAddress = Direct();
    INC8 (OpAddress);
}

static void OpE6M0 (void)
{
    long OpAddress = Direct();
    INC16 (OpAddress);
}

static void OpF6M1 (void)
{
    long OpAddress = DirectIndexedX();
    INC8 (OpAddress);
}

static void OpF6M0 (void)
{
    long OpAddress = DirectIndexedX();
    INC16 (OpAddress);
}

static void OpEEM1 (void)
{
    long OpAddress = Absolute();
    INC8 (OpAddress);
}

static void OpEEM0 (void)
{
    long OpAddress = Absolute();
    INC16 (OpAddress);
}

static void OpFEM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    INC8 (OpAddress);
}

static void OpFEM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    INC16 (OpAddress);
}

// Wake SA1 Variants

static void OpE6M1_WS (void)
{
    long OpAddress = Direct ();
    INC8WakeSA1 (OpAddress);
}

static void OpE6M0_WS (void)
{
    long OpAddress = Direct ();
    INC16WakeSA1 (OpAddress);
}

static void OpF6M1_WS (void)
{
    long OpAddress = DirectIndexedX ();
    INC8WakeSA1 (OpAddress);
}

static void OpF6M0_WS (void)
{
    long OpAddress = DirectIndexedX ();
    INC16WakeSA1 (OpAddress);
}

static void OpEEM1_WS (void)
{
    long OpAddress = Absolute ();
    INC8WakeSA1 (OpAddress);
}

static void OpEEM0_WS (void)
{
    long OpAddress = Absolute ();
    INC16WakeSA1 (OpAddress);
}

static void OpFEM1_WS (void)
{
    long OpAddress = AbsoluteIndexedX ();
    INC8WakeSA1 (OpAddress);
}

static void OpFEM0_WS (void)
{
    long OpAddress = AbsoluteIndexedX ();
    INC16WakeSA1 (OpAddress);
}

/**********************************************************************************************/
/* LDA *************************************************************************************** */
static void OpA9M1 (void)
{
    Registers.AL = *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.AL);
}

static void OpA9M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.A.W = *(uint16 *) CPU.PC;
#else
    Registers.A.W = *CPU.PC + (*(CPU.PC + 1) << 8);
#endif

    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.A.W);
}

static void OpA5M1 (void)
{
    long OpAddress = Direct();
    LDA8 (OpAddress);
}

static void OpA5M0 (void)
{
    long OpAddress = Direct();
    LDA16 (OpAddress);
}

static void OpB5M1 (void)
{
    long OpAddress = DirectIndexedX();
    LDA8 (OpAddress);
}

static void OpB5M0 (void)
{
    long OpAddress = DirectIndexedX();
    LDA16 (OpAddress);
}

static void OpB2M1 (void)
{
    long OpAddress = DirectIndirect();
    LDA8 (OpAddress);
}

static void OpB2M0 (void)
{
    long OpAddress = DirectIndirect();
    LDA16 (OpAddress);
}

static void OpA1M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    LDA8 (OpAddress);
}

static void OpA1M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    LDA16 (OpAddress);
}

static void OpB1M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    LDA8 (OpAddress);
}

static void OpB1M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    LDA16 (OpAddress);
}

static void OpA7M1 (void)
{
    long OpAddress = DirectIndirectLong();
    LDA8 (OpAddress);
}

static void OpA7M0 (void)
{
    long OpAddress = DirectIndirectLong();
    LDA16 (OpAddress);
}

static void OpB7M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    LDA8 (OpAddress);
}

static void OpB7M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    LDA16 (OpAddress);
}

static void OpADM1 (void)
{
    long OpAddress = Absolute();
    LDA8 (OpAddress);
}

static void OpADM0 (void)
{
    long OpAddress = Absolute();
    LDA16 (OpAddress);
}

static void OpBDM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LDA8 (OpAddress);
}

static void OpBDM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LDA16 (OpAddress);
}

static void OpB9M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    LDA8 (OpAddress);
}

static void OpB9M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    LDA16 (OpAddress);
}

static void OpAFM1 (void)
{
    long OpAddress = AbsoluteLong();
    LDA8 (OpAddress);
}

static void OpAFM0 (void)
{
    long OpAddress = AbsoluteLong();
    LDA16 (OpAddress);
}

static void OpBFM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    LDA8 (OpAddress);
}

static void OpBFM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    LDA16 (OpAddress);
}

static void OpA3M1 (void)
{
    long OpAddress = StackRelative();
    LDA8 (OpAddress);
}

static void OpA3M0 (void)
{
    long OpAddress = StackRelative();
    LDA16 (OpAddress);
}

static void OpB3M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    LDA8 (OpAddress);
}

static void OpB3M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    LDA16 (OpAddress);
}

/**********************************************************************************************/

/* LDX *************************************************************************************** */
static void OpA2X1 (void)
{
    Registers.XL = *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.XL);
}

static void OpA2X0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.X.W = *(uint16 *) CPU.PC;
#else
    Registers.X.W = *CPU.PC + (*(CPU.PC + 1) << 8);
#endif
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.X.W);
}

static void OpA6X1 (void)
{
    long OpAddress = Direct();
    LDX8 (OpAddress);
}

static void OpA6X0 (void)
{
    long OpAddress = Direct();
    LDX16 (OpAddress);
}

static void OpB6X1 (void)
{
    long OpAddress = DirectIndexedY();
    LDX8 (OpAddress);
}

static void OpB6X0 (void)
{
    long OpAddress = DirectIndexedY();
    LDX16 (OpAddress);
}

static void OpAEX1 (void)
{
    long OpAddress = Absolute();
    LDX8 (OpAddress);
}

static void OpAEX0 (void)
{
    long OpAddress = Absolute();
    LDX16 (OpAddress);
}

static void OpBEX1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    LDX8 (OpAddress);
}

static void OpBEX0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    LDX16 (OpAddress);
}
/**********************************************************************************************/

/* LDY *************************************************************************************** */
static void OpA0X1 (void)
{
    Registers.YL = *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.YL);
}

static void OpA0X0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.Y.W = *(uint16 *) CPU.PC;
#else
    Registers.Y.W = *CPU.PC + (*(CPU.PC + 1) << 8);
#endif

    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.Y.W);
}

static void OpA4X1 (void)
{
    long OpAddress = Direct();
    LDY8 (OpAddress);
}

static void OpA4X0 (void)
{
    long OpAddress = Direct();
    LDY16 (OpAddress);
}

static void OpB4X1 (void)
{
    long OpAddress = DirectIndexedX();
    LDY8 (OpAddress);
}

static void OpB4X0 (void)
{
    long OpAddress = DirectIndexedX();
    LDY16 (OpAddress);
}

static void OpACX1 (void)
{
    long OpAddress = Absolute();
    LDY8 (OpAddress);
}

static void OpACX0 (void)
{
    long OpAddress = Absolute();
    LDY16 (OpAddress);
}

static void OpBCX1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LDY8 (OpAddress);
}

static void OpBCX0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LDY16 (OpAddress);
}
/**********************************************************************************************/

/* LSR *************************************************************************************** */
static void Op4AM1 (void)
{
    A_LSR8 ();
}

static void Op4AM0 (void)
{
    A_LSR16 ();
}

static void Op46M1 (void)
{
    long OpAddress = Direct();
    LSR8 (OpAddress);
}

static void Op46M0 (void)
{
    long OpAddress = Direct();
    LSR16 (OpAddress);
}

static void Op56M1 (void)
{
    long OpAddress = DirectIndexedX();
    LSR8 (OpAddress);
}

static void Op56M0 (void)
{
    long OpAddress = DirectIndexedX();
    LSR16 (OpAddress);
}

static void Op4EM1 (void)
{
    long OpAddress = Absolute();
    LSR8 (OpAddress);
}

static void Op4EM0 (void)
{
    long OpAddress = Absolute();
    LSR16 (OpAddress);
}

static void Op5EM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LSR8 (OpAddress);
}

static void Op5EM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    LSR16 (OpAddress);
}

/**********************************************************************************************/

/* ORA *************************************************************************************** */
static void Op09M1 (void)
{
    Registers.AL |= *CPU.PC++;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed;
#endif
    SetZN8 (Registers.AL);
}

static void Op09M0 (void)
{
#ifdef FAST_LSB_WORD_ACCESS
    Registers.A.W |= *(uint16 *) CPU.PC;
#else
    Registers.A.W |= *CPU.PC + (*(CPU.PC + 1) << 8);
#endif
    CPU.PC += 2;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2;
#endif
    SetZN16 (Registers.A.W);
}

static void Op05M1 (void)
{
    long OpAddress = Direct();
    ORA8 (OpAddress);
}

static void Op05M0 (void)
{
    long OpAddress = Direct();
    ORA16 (OpAddress);
}

static void Op15M1 (void)
{
    long OpAddress = DirectIndexedX();
    ORA8 (OpAddress);
}

static void Op15M0 (void)
{
    long OpAddress = DirectIndexedX();
    ORA16 (OpAddress);
}

static void Op12M1 (void)
{
    long OpAddress = DirectIndirect();
    ORA8 (OpAddress);
}

static void Op12M0 (void)
{
    long OpAddress = DirectIndirect();
    ORA16 (OpAddress);
}

static void Op01M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    ORA8 (OpAddress);
}

static void Op01M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    ORA16 (OpAddress);
}

static void Op11M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    ORA8 (OpAddress);
}

static void Op11M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    ORA16 (OpAddress);
}

static void Op07M1 (void)
{
    long OpAddress = DirectIndirectLong();
    ORA8 (OpAddress);
}

static void Op07M0 (void)
{
    long OpAddress = DirectIndirectLong();
    ORA16 (OpAddress);
}

static void Op17M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    ORA8 (OpAddress);
}

static void Op17M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    ORA16 (OpAddress);
}

static void Op0DM1 (void)
{
    long OpAddress = Absolute();
    ORA8 (OpAddress);
}

static void Op0DM0 (void)
{
    long OpAddress = Absolute();
    ORA16 (OpAddress);
}

static void Op1DM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ORA8 (OpAddress);
}

static void Op1DM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ORA16 (OpAddress);
}

static void Op19M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    ORA8 (OpAddress);
}

static void Op19M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    ORA16 (OpAddress);
}

static void Op0FM1 (void)
{
    long OpAddress = AbsoluteLong();
    ORA8 (OpAddress);
}

static void Op0FM0 (void)
{
    long OpAddress = AbsoluteLong();
    ORA16 (OpAddress);
}

static void Op1FM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    ORA8 (OpAddress);
}

static void Op1FM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    ORA16 (OpAddress);
}

static void Op03M1 (void)
{
    long OpAddress = StackRelative();
    ORA8 (OpAddress);
}

static void Op03M0 (void)
{
    long OpAddress = StackRelative();
    ORA16 (OpAddress);
}

static void Op13M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    ORA8 (OpAddress);
}

static void Op13M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    ORA16 (OpAddress);
}

/**********************************************************************************************/

/* ROL *************************************************************************************** */
static void Op2AM1 (void)
{
    A_ROL8 ();
}

static void Op2AM0 (void)
{
    A_ROL16 ();
}

static void Op26M1 (void)
{
    long OpAddress = Direct();
    ROL8 (OpAddress);
}

static void Op26M0 (void)
{
    long OpAddress = Direct();
    ROL16 (OpAddress);
}

static void Op36M1 (void)
{
    long OpAddress = DirectIndexedX();
    ROL8 (OpAddress);
}

static void Op36M0 (void)
{
    long OpAddress = DirectIndexedX();
    ROL16 (OpAddress);
}

static void Op2EM1 (void)
{
    long OpAddress = Absolute();
    ROL8 (OpAddress);
}

static void Op2EM0 (void)
{
    long OpAddress = Absolute();
    ROL16 (OpAddress);
}

static void Op3EM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ROL8 (OpAddress);
}

static void Op3EM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ROL16 (OpAddress);
}
/**********************************************************************************************/

/* ROR *************************************************************************************** */
static void Op6AM1 (void)
{
    A_ROR8 ();
}

static void Op6AM0 (void)
{
    A_ROR16 ();
}

static void Op66M1 (void)
{
    long OpAddress = Direct();
    ROR8 (OpAddress);
}

static void Op66M0 (void)
{
    long OpAddress = Direct();
    ROR16 (OpAddress);
}

static void Op76M1 (void)
{
    long OpAddress = DirectIndexedX();
    ROR8 (OpAddress);
}

static void Op76M0 (void)
{
    long OpAddress = DirectIndexedX();
    ROR16 (OpAddress);
}

static void Op6EM1 (void)
{
    long OpAddress = Absolute();
    ROR8 (OpAddress);
}

static void Op6EM0 (void)
{
    long OpAddress = Absolute();
    ROR16 (OpAddress);
}

static void Op7EM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ROR8 (OpAddress);
}

static void Op7EM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    ROR16 (OpAddress);
}
/**********************************************************************************************/

/* SBC *************************************************************************************** */
static void OpE9M1 (void)
{
    long OpAddress = Immediate8 ();
    SBC8 (OpAddress);
}

static void OpE9M0 (void)
{
    long OpAddress = Immediate16 ();
    SBC16 (OpAddress);
}

static void OpE5M1 (void)
{
    long OpAddress = Direct();
    SBC8 (OpAddress);
}

static void OpE5M0 (void)
{
    long OpAddress = Direct();
    SBC16 (OpAddress);
}

static void OpF5M1 (void)
{
    long OpAddress = DirectIndexedX();
    SBC8 (OpAddress);
}

static void OpF5M0 (void)
{
    long OpAddress = DirectIndexedX();
    SBC16 (OpAddress);
}

static void OpF2M1 (void)
{
    long OpAddress = DirectIndirect();
    SBC8 (OpAddress);
}

static void OpF2M0 (void)
{
    long OpAddress = DirectIndirect();
    SBC16 (OpAddress);
}

static void OpE1M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    SBC8 (OpAddress);
}

static void OpE1M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    SBC16 (OpAddress);
}

static void OpF1M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    SBC8 (OpAddress);
}

static void OpF1M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    SBC16 (OpAddress);
}

static void OpE7M1 (void)
{
    long OpAddress = DirectIndirectLong();
    SBC8 (OpAddress);
}

static void OpE7M0 (void)
{
    long OpAddress = DirectIndirectLong();
    SBC16 (OpAddress);
}

static void OpF7M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    SBC8 (OpAddress);
}

static void OpF7M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    SBC16 (OpAddress);
}

static void OpEDM1 (void)
{
    long OpAddress = Absolute();
    SBC8 (OpAddress);
}

static void OpEDM0 (void)
{
    long OpAddress = Absolute();
    SBC16 (OpAddress);
}

static void OpFDM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    SBC8 (OpAddress);
}

static void OpFDM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    SBC16 (OpAddress);
}

static void OpF9M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    SBC8 (OpAddress);
}

static void OpF9M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    SBC16 (OpAddress);
}

static void OpEFM1 (void)
{
    long OpAddress = AbsoluteLong();
    SBC8 (OpAddress);
}

static void OpEFM0 (void)
{
    long OpAddress = AbsoluteLong();
    SBC16 (OpAddress);
}

static void OpFFM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    SBC8 (OpAddress);
}

static void OpFFM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    SBC16 (OpAddress);
}

static void OpE3M1 (void)
{
    long OpAddress = StackRelative();
    SBC8 (OpAddress);
}

static void OpE3M0 (void)
{
    long OpAddress = StackRelative();
    SBC16 (OpAddress);
}

static void OpF3M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    SBC8 (OpAddress);
}

static void OpF3M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    SBC16 (OpAddress);
}
/**********************************************************************************************/

/* STA *************************************************************************************** */
static void Op85M1 (void)
{
    long OpAddress = Direct();
    STA8 (OpAddress);
}

static void Op85M0 (void)
{
    long OpAddress = Direct();
    STA16 (OpAddress);
}

static void Op95M1 (void)
{
    long OpAddress = DirectIndexedX();
    STA8 (OpAddress);
}

static void Op95M0 (void)
{
    long OpAddress = DirectIndexedX();
    STA16 (OpAddress);
}

static void Op92M1 (void)
{
    long OpAddress = DirectIndirect();
    STA8 (OpAddress);
}

static void Op92M0 (void)
{
    long OpAddress = DirectIndirect();
    STA16 (OpAddress);
}

static void Op81M1 (void)
{
    long OpAddress = DirectIndexedIndirect();
    STA8 (OpAddress);
#ifdef noVAR_CYCLES
    if (CheckIndex ())
	CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op81M0 (void)
{
    long OpAddress = DirectIndexedIndirect();
    STA16 (OpAddress);
#ifdef noVAR_CYCLES
    if (CheckIndex ())
	CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op91M1 (void)
{
    long OpAddress = DirectIndirectIndexed();
    STA8 (OpAddress);
}

static void Op91M0 (void)
{
    long OpAddress = DirectIndirectIndexed();
    STA16 (OpAddress);
}

static void Op87M1 (void)
{
    long OpAddress = DirectIndirectLong();
    STA8 (OpAddress);
}

static void Op87M0 (void)
{
    long OpAddress = DirectIndirectLong();
    STA16 (OpAddress);
}

static void Op97M1 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    STA8 (OpAddress);
}

static void Op97M0 (void)
{
    long OpAddress = DirectIndirectIndexedLong();
    STA16 (OpAddress);
}

static void Op8DM1 (void)
{
    long OpAddress = Absolute();
    STA8 (OpAddress);
}

static void Op8DM0 (void)
{
    long OpAddress = Absolute();
    STA16 (OpAddress);
}

static void Op9DM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    STA8 (OpAddress);
}

static void Op9DM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    STA16 (OpAddress);
}

static void Op99M1 (void)
{
    long OpAddress = AbsoluteIndexedY();
    STA8 (OpAddress);
}

static void Op99M0 (void)
{
    long OpAddress = AbsoluteIndexedY();
    STA16 (OpAddress);
}

static void Op8FM1 (void)
{
    long OpAddress = AbsoluteLong();
    STA8 (OpAddress);
}

static void Op8FM0 (void)
{
    long OpAddress = AbsoluteLong();
    STA16 (OpAddress);
}

static void Op9FM1 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    STA8 (OpAddress);
}

static void Op9FM0 (void)
{
    long OpAddress = AbsoluteLongIndexedX();
    STA16 (OpAddress);
}

static void Op83M1 (void)
{
    long OpAddress = StackRelative();
    STA8 (OpAddress);
}

static void Op83M0 (void)
{
    long OpAddress = StackRelative();
    STA16 (OpAddress);
}

static void Op93M1 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    STA8 (OpAddress);
}

static void Op93M0 (void)
{
    long OpAddress = StackRelativeIndirectIndexed();
    STA16 (OpAddress);
}

// Wake SA1 Variants

static void Op85M1_WS (void)
{
    long addr = Direct ();
    STA8WakeSA1 (addr);
}

static void Op85M0_WS (void)
{
    long addr = Direct ();
    STA16WakeSA1 (addr);
}

static void Op95M1_WS (void)
{
    long addr = DirectIndexedX ();
    STA8WakeSA1 (addr);
}

static void Op95M0_WS (void)
{
    long addr = DirectIndexedX ();
    STA16WakeSA1 (addr);
}

static void Op92M1_WS (void)
{
    long addr = DirectIndirect ();
    STA8WakeSA1 (addr);
}

static void Op92M0_WS (void)
{
    long addr = DirectIndirect ();
    STA16WakeSA1 (addr);
}

static void Op81M1_WS (void)
{
    long addr = DirectIndexedIndirect ();
    STA8WakeSA1 (addr);
#ifdef noVAR_CYCLES
    if (CheckIndex ())
	CPU_Cycles += ONE_CYCLE;
#endif
}

static void Op81M0_WS (void)
{
    long addr = DirectIndexedIndirect ();
    STA16WakeSA1 (addr);
#ifdef noVAR_CYCLES
    if (CheckIndex ())
	CPU_Cycles += ONE_CYCLE;
#endif
}

static void Op91M1_WS (void)
{
    long addr = DirectIndirectIndexed ();
    STA8WakeSA1 (addr);
}

static void Op91M0_WS (void)
{
    long addr = DirectIndirectIndexed ();
    STA16WakeSA1 (addr);
}

static void Op87M1_WS (void)
{
    long addr = DirectIndirectLong ();
    STA8WakeSA1 (addr);
}

static void Op87M0_WS (void)
{
    long addr = DirectIndirectLong ();
    STA16WakeSA1 (addr);
}

static void Op97M1_WS (void)
{
    long addr = DirectIndirectIndexedLong ();
    STA8WakeSA1 (addr);
}

static void Op97M0_WS (void)
{
    long addr = DirectIndirectIndexedLong ();
    STA16WakeSA1 (addr);
}

static void Op8DM1_WS (void)
{
    long addr = Absolute ();
    STA8WakeSA1 (addr);
}

static void Op8DM0_WS (void)
{
    long addr = Absolute ();
    STA16WakeSA1 (addr);
}

static void Op9DM1_WS (void)
{
    long addr = AbsoluteIndexedX ();
    STA8WakeSA1 (addr);
}

static void Op9DM0_WS (void)
{
    long addr = AbsoluteIndexedX ();
    STA16WakeSA1 (addr);
}

static void Op99M1_WS (void)
{
    long addr = AbsoluteIndexedY ();
    STA8WakeSA1 (addr);
}

static void Op99M0_WS (void)
{
    long addr = AbsoluteIndexedY ();
    STA16WakeSA1 (addr);
}

static void Op8FM1_WS (void)
{
    long addr = AbsoluteLong ();
    STA8WakeSA1 (addr);
}

static void Op8FM0_WS (void)
{
    long addr = AbsoluteLong ();
    STA16WakeSA1 (addr);
}

static void Op9FM1_WS (void)
{
    long addr = AbsoluteLongIndexedX ();
    STA8WakeSA1 (addr);
}

static void Op9FM0_WS (void)
{
    long addr = AbsoluteLongIndexedX ();
    STA16WakeSA1 (addr);
}

static void Op83M1_WS (void)
{
    long addr = StackRelative ();
    STA8WakeSA1 (addr);
}

static void Op83M0_WS (void)
{
    long addr = StackRelative ();
    STA16WakeSA1 (addr);
}

static void Op93M1_WS (void)
{
    long addr = StackRelativeIndirectIndexed ();
    STA8WakeSA1 (addr);
}

static void Op93M0_WS (void)
{
    long addr = StackRelativeIndirectIndexed ();
    STA16WakeSA1 (addr);
}

/**********************************************************************************************/

/* STX *************************************************************************************** */
static void Op86X1 (void)
{
    long OpAddress = Direct();
    STX8 (OpAddress);
}

static void Op86X0 (void)
{
    long OpAddress = Direct();
    STX16 (OpAddress);
}

static void Op96X1 (void)
{
    long OpAddress = DirectIndexedY();
    STX8 (OpAddress);
}

static void Op96X0 (void)
{
    long OpAddress = DirectIndexedY();
    STX16 (OpAddress);
}

static void Op8EX1 (void)
{
    long OpAddress = Absolute();
    STX8 (OpAddress);
}

static void Op8EX0 (void)
{
    long OpAddress = Absolute();
    STX16 (OpAddress);
}

// Wake SA1 Variants

static void Op86X1_WS (void)
{
    long addr = Direct ();
    STX8WakeSA1 (addr);
}

static void Op86X0_WS (void)
{
    long addr = Direct ();
    STX16WakeSA1 (addr);
}

static void Op96X1_WS (void)
{
    long addr = DirectIndexedY ();
    STX8WakeSA1 (addr);
}

static void Op96X0_WS (void)
{
    long addr = DirectIndexedY ();
    STX16WakeSA1 (addr);
}

static void Op8EX1_WS (void)
{
    long addr = Absolute ();
    STX8WakeSA1 (addr);
}

static void Op8EX0_WS (void)
{
    long addr = Absolute ();
    STX16WakeSA1 (addr);
}

/**********************************************************************************************/

/* STY *************************************************************************************** */
static void Op84X1 (void)
{
    long OpAddress = Direct();
    STY8 (OpAddress);
}

static void Op84X0 (void)
{
    long OpAddress = Direct();
    STY16 (OpAddress);
}

static void Op94X1 (void)
{
    long OpAddress = DirectIndexedX();
    STY8 (OpAddress);
}

static void Op94X0 (void)
{
    long OpAddress = DirectIndexedX();
    STY16 (OpAddress);
}

static void Op8CX1 (void)
{
    long OpAddress = Absolute();
    STY8 (OpAddress);
}

static void Op8CX0 (void)
{
    long OpAddress = Absolute();
    STY16 (OpAddress);
}

// Wake SA1 Variants

static void Op84X1_WS (void)
{
    long addr = Direct ();
    STY8WakeSA1 (addr);
}

static void Op84X0_WS (void)
{
    long addr = Direct ();
    STY16WakeSA1 (addr);
}

static void Op94X1_WS (void)
{
    long addr = DirectIndexedX ();
    STY8WakeSA1 (addr);
}

static void Op94X0_WS (void)
{
    long addr = DirectIndexedX ();
    STY16WakeSA1 (addr);
}

static void Op8CX1_WS (void)
{
    long addr = Absolute ();
    STY8WakeSA1 (addr);
}

static void Op8CX0_WS (void)
{
    long addr = Absolute ();
    STY16WakeSA1 (addr);
}

/**********************************************************************************************/

/* STZ *************************************************************************************** */
static void Op64M1 (void)
{
    long OpAddress = Direct();
    STZ8 (OpAddress);
}

static void Op64M0 (void)
{
    long OpAddress = Direct();
    STZ16 (OpAddress);
}

static void Op74M1 (void)
{
    long OpAddress = DirectIndexedX();
    STZ8 (OpAddress);
}

static void Op74M0 (void)
{
    long OpAddress = DirectIndexedX();
    STZ16 (OpAddress);
}

static void Op9CM1 (void)
{
    long OpAddress = Absolute();
    STZ8 (OpAddress);
}

static void Op9CM0 (void)
{
    long OpAddress = Absolute();
    STZ16 (OpAddress);
}

static void Op9EM1 (void)
{
    long OpAddress = AbsoluteIndexedX();
    STZ8 (OpAddress);
}

static void Op9EM0 (void)
{
    long OpAddress = AbsoluteIndexedX();
    STZ16 (OpAddress);
}

// Wake SA1 Variants

static void Op64M1_WS (void)
{
    long addr = Direct ();
    STZ8WakeSA1 (addr);
}

static void Op64M0_WS (void)
{
    long addr = Direct ();
    STZ16WakeSA1 (addr);
}

static void Op74M1_WS (void)
{
    long addr = DirectIndexedX ();
    STZ8WakeSA1 (addr);
}

static void Op74M0_WS (void)
{
    long addr = DirectIndexedX ();
    STZ16WakeSA1 (addr);
}

static void Op9CM1_WS (void)
{
    long addr = Absolute ();
    STZ8WakeSA1 (addr);
}

static void Op9CM0_WS (void)
{
    long addr = Absolute ();
    STZ16WakeSA1 (addr);
}

static void Op9EM1_WS (void)
{
    long addr = AbsoluteIndexedX ();
    STZ8WakeSA1 (addr);
}

static void Op9EM0_WS (void)
{
    long addr = AbsoluteIndexedX ();
    STZ16WakeSA1 (addr);
}

/**********************************************************************************************/

/* TRB *************************************************************************************** */
static void Op14M1 (void)
{
    long OpAddress = Direct();
    TRB8 (OpAddress);
}

static void Op14M0 (void)
{
    long OpAddress = Direct();
    TRB16 (OpAddress);
}

static void Op1CM1 (void)
{
    long OpAddress = Absolute();
    TRB8 (OpAddress);
}

static void Op1CM0 (void)
{
    long OpAddress = Absolute();
    TRB16 (OpAddress);
}

// Wake SA1 Variants

static void Op14M1_WS (void)
{
    long OpAddress = Direct ();
    TRB8WakeSA1 (OpAddress);
}

static void Op14M0_WS (void)
{
    long OpAddress = Direct ();
    TRB16WakeSA1 (OpAddress);
}

static void Op1CM1_WS (void)
{
    long OpAddress = Absolute ();
    TRB8WakeSA1 (OpAddress);
}

static void Op1CM0_WS (void)
{
    long OpAddress = Absolute ();
    TRB16WakeSA1 (OpAddress);
}

/**********************************************************************************************/

/* TSB *************************************************************************************** */
static void Op04M1 (void)
{
    long OpAddress = Direct();
    TSB8 (OpAddress);
}

static void Op04M0 (void)
{
    long OpAddress = Direct();
    TSB16 (OpAddress);
}

static void Op0CM1 (void)
{
    long OpAddress = Absolute();
    TSB8 (OpAddress);
}

static void Op0CM0 (void)
{
    long OpAddress = Absolute();
    TSB16 (OpAddress);
}

// Wake SA1 Variants

static void Op04M1_WS (void)
{
    long OpAddress = Direct ();
    TSB8WakeSA1 (OpAddress);
}

static void Op04M0_WS (void)
{
    long OpAddress = Direct ();
    TSB16WakeSA1 (OpAddress);
}

static void Op0CM1_WS (void)
{
    long OpAddress = Absolute ();
    TSB8WakeSA1 (OpAddress);
}

static void Op0CM0_WS (void)
{
    long OpAddress = Absolute ();
    TSB16WakeSA1 (OpAddress);
}

/**********************************************************************************************/

/* Branch Instructions *********************************************************************** */
#ifndef SA1_OPCODES
#define BranchCheck()\
    if( CPU.BranchSkip)\
    {\
	CPU.BranchSkip = FALSE;\
	    if( CPU.PC - CPU.PCBase > OpAddress)\
	        return;\
    }

#else
#define BranchCheck()
#endif

#ifdef CPU_SHUTDOWN
#ifndef SA1_OPCODES
inline void CPUShutdown() {
  if (Settings.Shutdown && CPU.PC == CPU.WaitAddress) {
		// Don't skip cycles with a pending NMI or IRQ - could cause delayed
		// interrupt. Interrupts are delayed for a few cycles already, but
		//	 the delay could allow the shutdown code to cycle skip again.
		// Was causing screen flashing on Top Gear 3000.

		if (CPU.WaitCounter == 0 && !(CPU.Flags & (IRQ_PENDING_FLAG | NMI_FLAG))) {
		  CPU.WaitAddress = NULL;
		  //if (Settings.SA1)	S9xSA1ExecuteDuringSleep ();
		  			  
		  if ((IAPU_APUExecuting)) {
		  	if (CPU.Cycles>CPU.NextEvent) {
		  		cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
		  		old_cpu_cycles=CPU.NextEvent;
		  	}
		  }
		 	CPU.Cycles = CPU.NextEvent;
		 	
/*		  S9xUpdateAPUTimer();*/
		  if ((IAPU_APUExecuting)) {
				ICPU.CPUExecuting = FALSE;
////				if (CPU.Cycles-old_cpu_cycles<0) msgBoxLines("4",60);
//				/*else */cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;				
//				old_cpu_cycles=CPU.Cycles;
//				apu_glob_cycles=cpu_glob_cycles;
//				
//				if (cpu_glob_cycles>=0x00700000) {		
//					APU_EXECUTE2 ();
//				}
				UPDATE_APU_COUNTER();
			/*	do	{
			   	APU_EXECUTE1();			   	
				} while ((Uncache_APU_Cycles) < CPU.NextEvent);				*/
				
				ICPU.CPUExecuting = TRUE;
		  }
		}	else {
			if (CPU.WaitCounter >= 2) CPU.WaitCounter = 1;
			else CPU.WaitCounter--;
		}
	}
}
#else
inline void CPUShutdown()
{
    if (Settings.Shutdown && CPU.PC == CPU.WaitAddress)
    {
	if (CPU.WaitCounter >= 1)
	{
	    SA1.Executing = FALSE;
	    SA1.CPUExecuting = FALSE;
	}
	else
	    CPU.WaitCounter++;
    }
}
#endif
#else
#define CPUShutdown()
#endif

/* BCC */
static void Op90 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (!CheckCarry ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BCS */
static void OpB0 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (CheckCarry ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BEQ */
static void OpF0 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (CheckZero ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BMI */
static void Op30 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (CheckNegative ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BNE */
static void OpD0 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (!CheckZero ())
    {
	CPU.PC = CPU.PCBase + OpAddress;

#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BPL */
static void Op10 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (!CheckNegative ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BRA */
static void Op80 (void)
{
    long OpAddress = Relative();
    CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
    CPU.Cycles++;
#endif
#endif
    CPUShutdown ();
}

/* BVC */
static void Op50 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (!CheckOverflow ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}

/* BVS */
static void Op70 (void)
{
    long OpAddress = Relative();
    BranchCheck ();
    if (CheckOverflow ())
    {
	CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles++;
#endif
#endif
	CPUShutdown ();
    }
}
/**********************************************************************************************/

/* ClearFlag Instructions ******************************************************************** */
/* CLC */
static void Op18 (void)
{
    ClearCarry ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

/* CLD */
static void OpD8 (void)
{
    ClearDecimal ();
	S9xFixCyclesDecimal();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

/* CLI */
static void Op58 (void)
{
    ClearIRQ ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
/*    CHECK_FOR_IRQ(); */
}

/* CLV */
static void OpB8 (void)
{
    ClearOverflow ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}
/**********************************************************************************************/

/* DEX/DEY *********************************************************************************** */
static void OpCAX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.XL--;
    SetZN8 (Registers.XL);
}

static void OpCAX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.X.W--;
    SetZN16 (Registers.X.W);
}

static void Op88X1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.YL--;
    SetZN8 (Registers.YL);
}

static void Op88X0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.Y.W--;
    SetZN16 (Registers.Y.W);
}
/**********************************************************************************************/

/* INX/INY *********************************************************************************** */
static void OpE8X1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.XL++;
    SetZN8 (Registers.XL);
}

static void OpE8X0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.X.W++;
    SetZN16 (Registers.X.W);
}

static void OpC8X1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.YL++;
    SetZN8 (Registers.YL);
}

static void OpC8X0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef CPU_SHUTDOWN
    CPU.WaitAddress = NULL;
#endif

    Registers.Y.W++;
    SetZN16 (Registers.Y.W);
}

/**********************************************************************************************/

/* NOP *************************************************************************************** */
static void OpEA (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif

}
/**********************************************************************************************/

/* PUSH Instructions ************************************************************************* */
#define PushB(b)\
    S9xSetByte (b, Registers.S.W--);

#define PushBE(b)\
	S9xSetByte (b, Registers.S.W--);\
	Registers.SH=0x01;


#define PushW(w) \
    S9xSetByte ((w)>>8, Registers.S.W);\
	S9xSetByte ((w)&0xff, (Registers.S.W - 1)&0xFFFF);\
    Registers.S.W -= 2;

#define PushWE(w) \
    S9xSetByte ((w)>>8, Registers.S.W--);\
	Registers.SH=0x01;\
	S9xSetByte ((w)&0xff, (Registers.S.W--)&0xFFFF);\
    Registers.SH = 0x01;

#define PushWENew(w) \
    S9xSetByte ((w)>>8, Registers.S.W--);\
	S9xSetByte ((w)&0xff, (Registers.S.W--)&0xFFFF);\
    Registers.SH = 0x01;

static void OpF4E1 (void)
{
    long OpAddress = Absolute ();
    PushWENew ((unsigned short)OpAddress);
}
	
static void OpF4 (void)
{
    long OpAddress = Absolute();
    PushW ((unsigned short)OpAddress);
}

static void OpD4E1 (void)
{
    long OpAddress = DirectIndirect ();
    PushWENew ((unsigned short)OpAddress);
}

static void OpD4 (void)
{
    long OpAddress = DirectIndirect();
    PushW ((unsigned short)OpAddress);
}

static void Op62E1 (void)
{
    long OpAddress = RelativeLong ();
    PushWENew ((unsigned short)OpAddress);
}

static void Op62 (void)
{
    long OpAddress = RelativeLong ();
    PushW ((unsigned short)OpAddress);
}

static void Op48E1 (void)
{
    PushBE (Registers.AL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op48M1 (void)
{
    PushB (Registers.AL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op48M0 (void)
{
    PushW (Registers.A.W);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op8BE1 (void)
{
    PushBE (Registers.DB);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op8B (void)
{
    PushB (Registers.DB);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op0BE1 (void)
{
    PushWENew (Registers.D.W);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op0B (void)
{
    PushW (Registers.D.W);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op4BE1 (void)
{
    PushBE (Registers.PB);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op4B (void)
{
    PushB (Registers.PB);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op08E1 (void)
{
    S9xPackStatus ();
    PushBE (Registers.PL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op08 (void)
{
    S9xPackStatus ();
    PushB (Registers.PL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void OpDAE1 (void)
{
    PushBE (Registers.XL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void OpDAX1 (void)
{
    PushB (Registers.XL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void OpDAX0 (void)
{
    PushW (Registers.X.W);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op5AE1 (void)
{
    PushBE (Registers.YL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op5AX1 (void)
{
    PushB (Registers.YL);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void Op5AX0 (void)
{
    PushW (Registers.Y.W);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}
/**********************************************************************************************/

/* PULL Instructions ************************************************************************* */
#define PullW(w) \
	w = S9xGetByte (++Registers.S.W); \
	w |= (S9xGetByte (++Registers.S.W)<<8);

#define PullB(b)\
	b = S9xGetByte (++Registers.S.W);

#define PullBE(b)\
	Registers.S.W++;\
	Registers.SH=0x01;\
	b = S9xGetByte (Registers.S.W);

#define PullWE(w) \
	Registers.S.W++;\
	Registers.SH=0x01;\
	w = S9xGetByte (Registers.S.W); \
	Registers.S.W++; \
	Registers.SH=0x01;\
	w |= (S9xGetByte (Registers.S.W)<<8);

#define PullWENew(w) \
	PullW(w);\
	Registers.SH=0x01;	

static void Op68E1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullBE (Registers.AL);
    SetZN8 (Registers.AL);
}
	
static void Op68M1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullB (Registers.AL);
    SetZN8 (Registers.AL);
}

static void Op68M0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullW (Registers.A.W);
    SetZN16 (Registers.A.W);
}

static void OpABE1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullBE (Registers.DB);
    SetZN8 (Registers.DB);
    ICPU.ShiftedDB = Registers.DB << 16;
}

static void OpAB (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullB (Registers.DB);
    SetZN8 (Registers.DB);
    ICPU.ShiftedDB = Registers.DB << 16;
}

/* PHP */

static void Op2BE1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullWENew (Registers.D.W);
    SetZN16 (Registers.D.W);
}

static void Op2B (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullW (Registers.D.W);
    SetZN16 (Registers.D.W);
}

/* PLP */
/*static void Op28E1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullBE (Registers.PL);
    S9xUnpackStatus ();

    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
    S9xFixCycles();
}*/

static void Op28 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullB (Registers.PL);
    S9xUnpackStatus ();

    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
    S9xFixCycles();
}

static void OpFAE1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullBE (Registers.XL);
    SetZN8 (Registers.XL);
}

static void OpFAX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullB (Registers.XL);
    SetZN8 (Registers.XL);
}

static void OpFAX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullW (Registers.X.W);
    SetZN16 (Registers.X.W);
}

static void Op7AE1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullBE (Registers.YL);
    SetZN8 (Registers.YL);
}

static void Op7AX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullB (Registers.YL);
    SetZN8 (Registers.YL);
}

static void Op7AX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    PullW (Registers.Y.W);
    SetZN16 (Registers.Y.W);
}

/**********************************************************************************************/

/* SetFlag Instructions ********************************************************************** */
/* SEC */
static void Op38 (void)
{
    SetCarry ();
	S9xFixCyclesDecimal();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

/* SED */
static void OpF8 (void)
{
    SetDecimal ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
#ifdef DEBUGGER
    missing.decimal_mode = 1;
#endif
}

/* SEI */
static void Op78 (void)
{
    SetIRQ ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}
/**********************************************************************************************/

/* Transfer Instructions ********************************************************************* */
/* TAX8 */
static void OpAAX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.XL = Registers.AL;
    SetZN8 (Registers.XL);
}

/* TAX16 */
static void OpAAX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.X.W = Registers.A.W;
    SetZN16 (Registers.X.W);
}

/* TAY8 */
static void OpA8X1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.YL = Registers.AL;
    SetZN8 (Registers.YL);
}

/* TAY16 */
static void OpA8X0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.Y.W = Registers.A.W;
    SetZN16 (Registers.Y.W);
}

static void Op5B (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.D.W = Registers.A.W;
    SetZN16 (Registers.D.W);
}

static void Op1B (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.S.W = Registers.A.W;
    if (CheckEmulation())
	Registers.SH = 1;
}

static void Op7B (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.A.W = Registers.D.W;
    SetZN16 (Registers.A.W);
}

static void Op3B (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.A.W = Registers.S.W;
    SetZN16 (Registers.A.W);
}

static void OpBAX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.XL = Registers.SL;
    SetZN8 (Registers.XL);
}

static void OpBAX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.X.W = Registers.S.W;
    SetZN16 (Registers.X.W);
}

static void Op8AM1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.AL = Registers.XL;
    SetZN8 (Registers.AL);
}

static void Op8AM0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.A.W = Registers.X.W;
    SetZN16 (Registers.A.W);
}

static void Op9A (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.S.W = Registers.X.W;
    if (CheckEmulation())
	Registers.SH = 1;
}

static void Op9BX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.YL = Registers.XL;
    SetZN8 (Registers.YL);
}

static void Op9BX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.Y.W = Registers.X.W;
    SetZN16 (Registers.Y.W);
}

static void Op98M1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.AL = Registers.YL;
    SetZN8 (Registers.AL);
}

static void Op98M0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.A.W = Registers.Y.W;
    SetZN16 (Registers.A.W);
}

static void OpBBX1 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.XL = Registers.YL;
    SetZN8 (Registers.XL);
}

static void OpBBX0 (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    Registers.X.W = Registers.Y.W;
    SetZN16 (Registers.X.W);
}

/**********************************************************************************************/

/* XCE *************************************************************************************** */
static void OpFB (void)
{
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif

    uint8 A1 = ICPU._Carry;
    uint8 A2 = Registers.PH;
    ICPU._Carry = A2 & 1;
    Registers.PH = A1;

    if (CheckEmulation())
    {
	SetFlags (MemoryFlag | IndexFlag);
	Registers.SH = 1;
#ifdef DEBUGGER
	missing.emulate6502 = 1;
#endif
    }
    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
    S9xFixCycles();
}
/**********************************************************************************************/

/* BRK *************************************************************************************** */
static void Op00 (void)
{
#ifdef DEBUGGER
    if (CPU.Flags & TRACE_FLAG)
	S9xTraceMessage ("*** BRK");
#endif

#ifndef SA1_OPCODES
    CPU.BRKTriggered = TRUE;
#endif

    if (!CheckEmulation())
    {
	PushB (Registers.PB);
	PushW (CPU.PC - CPU.PCBase + 1);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
        CPU.Cycles += TWO_CYCLES;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 8;
#endif
#endif
	S9xSetPCBase (S9xGetWord (0xFFE6));
    }
    else
    {
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 6;
#endif
#endif
	S9xSetPCBase (S9xGetWord (0xFFFE));
    }
}
/**********************************************************************************************/

/* BRL ************************************************************************************** */
static void Op82 (void)
{
    long OpAddress = RelativeLong ();
    S9xSetPCBase (ICPU.ShiftedPB + OpAddress);
}
/**********************************************************************************************/

/* IRQ *************************************************************************************** */
void S9xOpcode_IRQ (void)
{
#ifdef DEBUGGER
    if (CPU.Flags & TRACE_FLAG)
	S9xTraceMessage ("*** IRQ");
#endif
    if (!CheckEmulation())
    {
	PushB (Registers.PB);
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
        CPU.Cycles += TWO_CYCLES;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 8;
#endif
#endif
#ifdef SA1_OPCODES
	S9xSA1SetPCBase (ROM_GLOBAL [0x2207] |
			 (ROM_GLOBAL [0x2208] << 8));
#else
	if (Settings.SA1 && (ROM_GLOBAL [0x2209] & 0x40))
	    S9xSetPCBase (ROM_GLOBAL [0x220e] | 
			  (ROM_GLOBAL [0x220f] << 8));
	else
	    S9xSetPCBase (S9xGetWord (0xFFEE));
#endif
    }
    else
    {
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 6;
#endif
#endif
#ifdef SA1_OPCODES
	S9xSA1SetPCBase (ROM_GLOBAL [0x2207] |
			 (ROM_GLOBAL [0x2208] << 8));
#else
	if (Settings.SA1 && (ROM_GLOBAL [0x2209] & 0x40))
	    S9xSetPCBase (ROM_GLOBAL [0x220e] | 
			  (ROM_GLOBAL [0x220f] << 8));
	else
	    S9xSetPCBase (S9xGetWord (0xFFFE));
#endif
    }
}

/**********************************************************************************************/

/* NMI *************************************************************************************** */
void S9xOpcode_NMI (void)
{
#ifdef DEBUGGER
    if (CPU.Flags & TRACE_FLAG)
	S9xTraceMessage ("*** NMI");
#endif
    if (!CheckEmulation())
    {
	PushB (Registers.PB);
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
	CPU.Cycles += TWO_CYCLES;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 8;
#endif
#endif
#ifdef SA1_OPCODES
	S9xSA1SetPCBase (ROM_GLOBAL [0x2205] |
			 (ROM_GLOBAL [0x2206] << 8));
#else
	if (Settings.SA1 && (ROM_GLOBAL [0x2209] & 0x20))
	    S9xSetPCBase (ROM_GLOBAL [0x220c] |
			  (ROM_GLOBAL [0x220d] << 8));
	else
	    S9xSetPCBase (S9xGetWord (0xFFEA));
#endif
    }
    else
    {
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 6;
#endif
#endif
#ifdef SA1_OPCODES
	S9xSA1SetPCBase (ROM_GLOBAL [0x2205] |
			 (ROM_GLOBAL [0x2206] << 8));
#else
	if (Settings.SA1 && (ROM_GLOBAL [0x2209] & 0x20))
	    S9xSetPCBase (ROM_GLOBAL [0x220c] |
			  (ROM_GLOBAL [0x220d] << 8));
	else
	    S9xSetPCBase (S9xGetWord (0xFFFA));
#endif
    }
}
/**********************************************************************************************/

/* COP *************************************************************************************** */
static void Op02 (void)
{
#ifdef DEBUGGER
    if (CPU.Flags & TRACE_FLAG)
	S9xTraceMessage ("*** COP");
#endif	
    if (!CheckEmulation())
    {
	PushB (Registers.PB);
	PushW (CPU.PC - CPU.PCBase + 1);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
        CPU.Cycles += TWO_CYCLES;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 8;
#endif
#endif
	S9xSetPCBase (S9xGetWord (0xFFE4));
    }
    else
    {
	PushW (CPU.PC - CPU.PCBase);
	S9xPackStatus ();
	PushB (Registers.PL);
	ClearDecimal ();
	SetIRQ ();

	Registers.PB = 0;
	ICPU.ShiftedPB = 0;
#ifdef VAR_CYCLES
	CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 6;
#endif
#endif
	S9xSetPCBase (S9xGetWord (0xFFF4));
    }
}
/**********************************************************************************************/

/* JML *************************************************************************************** */
static void OpDC (void)
{
    long OpAddress = AbsoluteIndirectLong ();
    Registers.PB = (uint8) (OpAddress >> 16);
    ICPU.ShiftedPB = OpAddress & 0xff0000;
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    S9xSetPCBase (OpAddress);
}

static void Op5C (void)
{
    long OpAddress = AbsoluteLong();
    Registers.PB = (uint8) (OpAddress >> 16);
    ICPU.ShiftedPB = OpAddress & 0xff0000;
    S9xSetPCBase (OpAddress);
}
/**********************************************************************************************/

/* JMP *************************************************************************************** */
static void Op4C (void)
{
    long OpAddress = Absolute();
    S9xSetPCBase (ICPU.ShiftedPB + (OpAddress & 0xffff));
#if defined(CPU_SHUTDOWN) && defined(SA1_OPCODES)
    CPUShutdown ();
#endif
}

static void Op6C (void)
{
    long OpAddress = AbsoluteIndirect ();
    S9xSetPCBase (ICPU.ShiftedPB + (OpAddress & 0xffff));
}

static void Op7C (void)
{
    long OpAddress = AbsoluteIndexedIndirect ();
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    S9xSetPCBase (ICPU.ShiftedPB + OpAddress);
}
/**********************************************************************************************/

/* JSL/RTL *********************************************************************************** */
static void Op22E1 (void)
{
    long OpAddress = AbsoluteLong ();
    PushB (Registers.PB);
    PushWENew (CPU.PC - CPU.PCBase - 1);
    Registers.PB = (uint8) (OpAddress >> 16);
    ICPU.ShiftedPB = OpAddress & 0xff0000;
    S9xSetPCBase (OpAddress);
}

static void Op22 (void)
{
    long OpAddress = AbsoluteLong();
    PushB (Registers.PB);
    PushW (CPU.PC - CPU.PCBase - 1);
    Registers.PB = (uint8) (OpAddress >> 16);
    ICPU.ShiftedPB = OpAddress & 0xff0000;
    S9xSetPCBase (OpAddress);
}

static void Op6BE1 (void)
{
    PullWENew (Registers.PCw);
    PullB (Registers.PB);
    ICPU.ShiftedPB = Registers.PB << 16;
    S9xSetPCBase (ICPU.ShiftedPB + ((Registers.PCw + 1) & 0xffff));
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
}

static void Op6B (void)
{
    PullW (Registers.PCw);
    PullB (Registers.PB);
    ICPU.ShiftedPB = Registers.PB << 16;
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    S9xSetPCBase (ICPU.ShiftedPB + ((Registers.PCw + 1) & 0xffff));
}
/**********************************************************************************************/

/* JSR/RTS *********************************************************************************** */
static void Op20 (void)
{
    long OpAddress = Absolute();
    PushW (CPU.PC - CPU.PCBase - 1);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    S9xSetPCBase (ICPU.ShiftedPB + (OpAddress & 0xffff));
}

static void OpFCE1 (void)
{
    long OpAddress = AbsoluteIndexedIndirect ();
    PushWENew (CPU.PC - CPU.PCBase - 1);
    S9xSetPCBase (ICPU.ShiftedPB + OpAddress);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
}

static void OpFC (void)
{
    long OpAddress = AbsoluteIndexedIndirect ();
    PushW (CPU.PC - CPU.PCBase - 1);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE;
#endif
    S9xSetPCBase (ICPU.ShiftedPB + OpAddress);
}

static void Op60 (void)
{
    PullW (Registers.PCw);
#ifdef VAR_CYCLES
    CPU.Cycles += ONE_CYCLE * 3;
#endif
    S9xSetPCBase (ICPU.ShiftedPB + ((Registers.PCw + 1) & 0xffff));
}

/**********************************************************************************************/

/* MVN/MVP *********************************************************************************** */
static void Op54X1 (void)
{
    uint32 SrcBank;

#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2 + TWO_CYCLES;
#endif
    
    Registers.DB = *CPU.PC++;
    ICPU.ShiftedDB = Registers.DB << 16;
    SrcBank = *CPU.PC++;

    S9xSetByte (S9xGetByte ((SrcBank << 16) + Registers.X.W), 
	     ICPU.ShiftedDB + Registers.Y.W);

    Registers.XL++;
    Registers.YL++;
    Registers.A.W--;
    if (Registers.A.W != 0xffff)
	CPU.PC -= 3;
}

static void Op54X0 (void)
{
    uint32 SrcBank;

#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2 + TWO_CYCLES;
#endif
    
    Registers.DB = *CPU.PC++;
    ICPU.ShiftedDB = Registers.DB << 16;
    SrcBank = *CPU.PC++;

    S9xSetByte (S9xGetByte ((SrcBank << 16) + Registers.X.W), 
	     ICPU.ShiftedDB + Registers.Y.W);

    Registers.X.W++;
    Registers.Y.W++;
    Registers.A.W--;
    if (Registers.A.W != 0xffff)
	CPU.PC -= 3;
}

static void Op44X1 (void)
{
    uint32 SrcBank;

#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2 + TWO_CYCLES;
#endif    
    Registers.DB = *CPU.PC++;
    ICPU.ShiftedDB = Registers.DB << 16;
    SrcBank = *CPU.PC++;
    S9xSetByte (S9xGetByte ((SrcBank << 16) + Registers.X.W), 
	     ICPU.ShiftedDB + Registers.Y.W);

    Registers.XL--;
    Registers.YL--;
    Registers.A.W--;
    if (Registers.A.W != 0xffff)
	CPU.PC -= 3;
}

static void Op44X0 (void)
{
    uint32 SrcBank;

#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeedx2 + TWO_CYCLES;
#endif    
    Registers.DB = *CPU.PC++;
    ICPU.ShiftedDB = Registers.DB << 16;
    SrcBank = *CPU.PC++;
    S9xSetByte (S9xGetByte ((SrcBank << 16) + Registers.X.W), 
	     ICPU.ShiftedDB + Registers.Y.W);

    Registers.X.W--;
    Registers.Y.W--;
    Registers.A.W--;
    if (Registers.A.W != 0xffff)
	CPU.PC -= 3;
}

/**********************************************************************************************/

/* REP/SEP *********************************************************************************** */
static void OpC2 (void)
{
    uint8 Work8 = ~*CPU.PC++;
    Registers.PL &= Work8;
    ICPU._Carry &= Work8;
    ICPU._Overflow &= (Work8 >> 6);
    ICPU._Negative &= Work8;
    ICPU._Zero |= ~Work8 & Zero;

#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed + ONE_CYCLE;
#endif
    if (CheckEmulation())
    {
	SetFlags (MemoryFlag | IndexFlag);
#ifdef DEBUGGER
	missing.emulate6502 = 1;
#endif
    }
    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
    S9xFixCycles();
/*    CHECK_FOR_IRQ(); */
}

static void OpE2 (void)
{
    uint8 Work8 = *CPU.PC++;
    Registers.PL |= Work8;
    ICPU._Carry |= Work8 & 1;
    ICPU._Overflow |= (Work8 >> 6) & 1;
    ICPU._Negative |= Work8;
    if (Work8 & Zero)
	ICPU._Zero = 0;
#ifdef VAR_CYCLES
    CPU.Cycles += CPU.MemSpeed + ONE_CYCLE;
#endif
    if (CheckEmulation())
    {
	SetFlags (MemoryFlag | IndexFlag);
#ifdef DEBUGGER
	missing.emulate6502 = 1;
#endif
    }
    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
    S9xFixCycles();
}
/**********************************************************************************************/

/* XBA *************************************************************************************** */
static void OpEB (void)
{
    uint8 Work8 = Registers.AL;
    Registers.AL = Registers.AH;
    Registers.AH = Work8;

    SetZN8 (Registers.AL);
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
}
/**********************************************************************************************/

/* RTI *************************************************************************************** */
static void Op40 (void)
{
    PullB (Registers.PL);
    S9xUnpackStatus ();
    PullW (Registers.PCw);
    if (!CheckEmulation())
    {
	PullB (Registers.PB);
	ICPU.ShiftedPB = Registers.PB << 16;
    }
    else
    {
	SetFlags (MemoryFlag | IndexFlag);
#ifdef DEBUGGER
	missing.emulate6502 = 1;
#endif
    }
    S9xSetPCBase (ICPU.ShiftedPB + Registers.PCw);
    
    if (CheckIndex ())
    {
	Registers.XH = 0;
	Registers.YH = 0;
    }
#ifdef VAR_CYCLES
    CPU.Cycles += TWO_CYCLES;
#endif
    S9xFixCycles();
/*    CHECK_FOR_IRQ(); */
}

/**********************************************************************************************/

/* STP/WAI/DB ******************************************************************************** */
// WAI
static void OpCB (void)
{
    if (CPU.IRQActive)
    {
#ifdef VAR_CYCLES
	CPU.Cycles += TWO_CYCLES;
#else
#ifndef SA1_OPCODES
	CPU.Cycles += 2;
#endif
#endif
    }
    else
    {
	//CPU.WaitingForInterrupt = TRUE;
	//CPU.PC--;
#ifdef CPU_SHUTDOWN
#ifndef SA1_OPCODES
	
	// We are basically moving all the checks for CPU.WaitingForInterrupt
    // in the S9xHandleFlags() method to here.
    // 
	if (((CPU.Flags & NMI_FLAG) && (CPU.NMICycleCount - 1 == 0)) ||
		((CPU.Flags & IRQ_PENDING_FLAG) && (CPU.IRQCycleCount == 0)))
	{
		// Take no action, the PC must remain as it is 
		// so that the next instruction is executed.
	}
	else
	{
		// Move the PC back to the WAI instruction
		//
		CPU.PC--;

		bool skip = false;
		if (!CPU.Flags)
			skip = true;
		else if ((CPU.Flags & IRQ_PENDING_FLAG) && (CPU.IRQCycleCount == 0) && CheckFlag (IRQ))
			skip = true;
		
		if (skip)
			if (CPU.Cycles < CPU.NextEvent)
				CPU.Cycles = CPU.NextEvent;
	}

	if (Settings.Shutdown)
	{
				
		if ((IAPU_APUExecuting)) {
		  	if (CPU.Cycles>CPU.NextEvent) {
		  		cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
		  		old_cpu_cycles=CPU.NextEvent;
		  	}
		}
	  CPU.Cycles = CPU.NextEvent;
	   
	  if ((IAPU_APUExecuting)) {
			ICPU.CPUExecuting = FALSE;
//			if (CPU.Cycles-old_cpu_cycles<0) msgBoxLines("5",60);
//			/*else */cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
//			old_cpu_cycles=CPU.Cycles;
//			apu_glob_cycles=cpu_glob_cycles;
//			
//			if (cpu_glob_cycles>=0x00700000) {		
//					APU_EXECUTE2 ();
//				}
			
			UPDATE_APU_COUNTER();
			/*do {
		  	  APU_EXECUTE1 ();		   
			} while ((Uncache_APU_Cycles) < CPU.NextEvent);		*/
		
			ICPU.CPUExecuting = TRUE;
	   }
	}
#else
	if (Settings.Shutdown)
	{
	    SA1.CPUExecuting = FALSE;
	    SA1.Executing = FALSE;
	}
#endif
#endif
    }
}

// Speedhack for main CPU
// Based on snes9x 3DS
//
static void CPUSpeedhack (void)
{
#ifndef SA1_OPCODES	
	
	CPU.WaitAddress = NULL;
	if ((IAPU_APUExecuting)) {
		if (CPU.Cycles>CPU.NextEvent) {
			cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
			old_cpu_cycles=CPU.NextEvent;
		}
	}

	CPU.Cycles = CPU.NextEvent;
			
	if ((IAPU_APUExecuting)) {
		ICPU.CPUExecuting = FALSE;
		
		UPDATE_APU_COUNTER();
		
		ICPU.CPUExecuting = TRUE;
	}
	
	// Executes the original opcode that we replaced.
	//
	(*ICPU.S9xOpcodes [SNESGameFixes.SpeedHackOriginalOpcode[0]].S9xOpcode) (); 

	// If we decide to skip, then we add cycles to the CPU.Cycles
	// until just before the next event.
	//
	int cyclesToSkip = SNESGameFixes.SpeedHackCycles[0];

	if (cyclesToSkip == -1)
		CPU.Cycles = CPU.NextEvent;
	else
	{
		while (CPU.Cycles + cyclesToSkip < CPU.NextEvent)
		{
			CPU.Cycles = CPU.Cycles + cyclesToSkip;
		}
	}
#endif
}

// Speedhack for SA1 games
// Based on snes9x 3DS
//
static void SA1Speedhack (void)
{
#ifdef SA1_OPCODES	
	// Executes the original opcode that we replaced.
	//
	(*ICPU.S9xOpcodes [SNESGameFixes.SpeedHackSA1OriginalOpcode[0]].S9xOpcode) (); 

	if (SA1.WaitCounter == 0)
		SA1.Executing = false;
	else
		SA1.WaitCounter--;
	
#endif
}

// SNESAdvance speedhack used on Opcode 0xDB (based on the speed-hacks branch of CatSFC)
//
static void SNESAdvance_OpDB (void)
{
#ifndef SA1_OPCODES
	uint8 NextByte;

	CPU.WaitAddress = NULL;
	if ((IAPU_APUExecuting)) {
		if (CPU.Cycles>CPU.NextEvent) {
			cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
			old_cpu_cycles=CPU.NextEvent;
		}
	}

	CPU.Cycles = CPU.NextEvent;
			
	if ((IAPU_APUExecuting)) {
		ICPU.CPUExecuting = FALSE;
		
		UPDATE_APU_COUNTER();
		
		ICPU.CPUExecuting = TRUE;
	}

	NextByte = *CPU.PC++;
	
	int8 BranchOffset = (NextByte & 0x7F) | ((NextByte & 0x40) << 1);
	// ^ -64 .. +63, sign extend bit 6 into 7 for unpacking
	long OpAddress = ((int) (CPU.PC - CPU.PCBase) + BranchOffset) & 0xffff;

	switch (NextByte & 0x80)
	{
	case 0x00: // BNE
		BranchCheck();
		if (!CheckZero ()) {
			CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
			CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
			CPU.Cycles++;
#endif
#endif
			CPUShutdown ();
		}
		return;
	case 0x80: // BEQ
		BranchCheck();
		if (CheckZero ()) {
			CPU.PC = CPU.PCBase + OpAddress;
#ifdef VAR_CYCLES
			CPU.Cycles += ONE_CYCLE;
#else
#ifndef SA1_OPCODES
			CPU.Cycles++;
#endif
#endif
			CPUShutdown ();
		}
		return;
	}
#endif
}

// SNESAdvance speedhack used on Opcode 0x42 (based on the speed-hacks branch of CatSFC)
//
static void SNESAdvance_Op42 (void)
{
#ifndef SA1_OPCODES
	
	uint8 b;
		
	CPU.WaitAddress = NULL;
	if ((IAPU_APUExecuting)) {
		if (CPU.Cycles>CPU.NextEvent) {
			cpu_glob_cycles += CPU.Cycles-old_cpu_cycles;
			old_cpu_cycles=CPU.NextEvent;
		}
	}
	
	CPU.Cycles = CPU.NextEvent;
			
/*	S9xUpdateAPUTimer();*/

	if ((IAPU_APUExecuting)) {
		ICPU.CPUExecuting = FALSE;
		
		UPDATE_APU_COUNTER();
		
		ICPU.CPUExecuting = TRUE;
	}
	
	//debug_log("toto");
	b=*CPU.PC++;
	
	//relative
	signed char s9xInt8=0xF0|(b&0xF);
	#ifdef VAR_CYCLES
  CPU.Cycles += CPU.MemSpeed;
	#endif    
	long OpAddress = ((int) (CPU.PC - CPU.PCBase) + s9xInt8) & 0xffff;
		
	switch (b&0xF0) {		
    case 0x10: //BPL
    	BranchCheck ();
    	if (!CheckNegative ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
    	}
    	return;
    case 0x30: //BMI
    	BranchCheck ();
    	if (CheckNegative ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
    	}
    	return;
    case 0x50: //BVC
    	BranchCheck ();
    	if (!CheckOverflow ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
    	}
    	return;
    case 0x70: //BVS
      BranchCheck ();
    	if (CheckOverflow ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
			}
    	return;
    case 0x80: //BRA			
    	//op80
    	CPU.PC = CPU.PCBase + OpAddress;
			#ifdef VAR_CYCLES
    		CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
    		CPU.Cycles++;
				#endif
			#endif
    	CPUShutdown ();
    	return;
    case 0x90: //BCC
      BranchCheck ();
	    if (!CheckCarry ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
   		}
    	return;
    case 0xB0: //BCS
      BranchCheck ();
		  if (CheckCarry ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
    	}
    	return;
    case 0xD0: //BNE
      BranchCheck ();
    	if (!CheckZero ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
    	}
    	return;
    case 0xF0: //BEQ
    	BranchCheck ();
    	if (CheckZero ()) {
				CPU.PC = CPU.PCBase + OpAddress;
				#ifdef VAR_CYCLES
				CPU.Cycles += ONE_CYCLE;
				#else
				#ifndef SA1_OPCODES
				CPU.Cycles++;
				#endif
				#endif
				CPUShutdown ();
			}
    	return;
	}
#endif
}

// STP
// Since snes9xTYL already uses opcode 0x42 to apply speedhacks from snesadvance.dat.
// We use opcode 0xDB instead of 0x42 to apply harcoded main CPU speedhacks ported from snes9x 3DS.
// With this change we avoid graphical glitches, crashes and black screens on several games.
static void OpDB (void)
{
	if (Settings.SpeedHack)
		CPUSpeedhack();
	else
		SNESAdvance_OpDB();
	//CPU.PC--;
	//CPU.Flags |= DEBUG_MODE_FLAG;
}

static void Op42 (void)
{	
	// It seems that applying SA1 speedhacks on opcode 0x42 don't give any trouble.
	// With this we avoid to apply an speedhack twice on every frame.
	SA1Speedhack();
	SNESAdvance_Op42();
}

/**********************************************************************************************/

/**********************************************************************************************/
/* CPU-S9xOpcodes Definitions                                                                    */
/**********************************************************************************************/
struct SOpcodes __attribute__((aligned(64))) S9xOpcodesE1[256] =
{
    {Op00},	 {Op01M1},    {Op02},      {Op03M1},    {Op04M1},
    {Op05M1},    {Op06M1},    {Op07M1},    {Op08E1},      {Op09M1},
    {Op0AM1},    {Op0BE1},      {Op0CM1},    {Op0DM1},    {Op0EM1},
    {Op0FM1},    {Op10},      {Op11M1},    {Op12M1},    {Op13M1},
    {Op14M1},    {Op15M1},    {Op16M1},    {Op17M1},    {Op18},
    {Op19M1},    {Op1AM1},    {Op1B},      {Op1CM1},    {Op1DM1},
    {Op1EM1},    {Op1FM1},    {Op20},      {Op21M1},    {Op22E1},
    {Op23M1},    {Op24M1},    {Op25M1},    {Op26M1},    {Op27M1},
    {Op28},      {Op29M1},    {Op2AM1},    {Op2BE1},      {Op2CM1},
    {Op2DM1},    {Op2EM1},    {Op2FM1},    {Op30},      {Op31M1},
    {Op32M1},    {Op33M1},    {Op34M1},    {Op35M1},    {Op36M1},
    {Op37M1},    {Op38},      {Op39M1},    {Op3AM1},    {Op3B},
    {Op3CM1},    {Op3DM1},    {Op3EM1},    {Op3FM1},    {Op40},
    {Op41M1},    {Op42},      {Op43M1},    {Op44X1},    {Op45M1},
    {Op46M1},    {Op47M1},    {Op48E1},    {Op49M1},    {Op4AM1},
    {Op4BE1},      {Op4C},      {Op4DM1},    {Op4EM1},    {Op4FM1},
    {Op50},      {Op51M1},    {Op52M1},    {Op53M1},    {Op54X1},
    {Op55M1},    {Op56M1},    {Op57M1},    {Op58},      {Op59M1},
    {Op5AE1},    {Op5B},      {Op5C},      {Op5DM1},    {Op5EM1},
    {Op5FM1},    {Op60},      {Op61M1},    {Op62E1},      {Op63M1},
    {Op64M1},    {Op65M1},    {Op66M1},    {Op67M1},    {Op68E1},
    {Op69M1},    {Op6AM1},    {Op6BE1},      {Op6C},      {Op6DM1},
    {Op6EM1},    {Op6FM1},    {Op70},      {Op71M1},    {Op72M1},
    {Op73M1},    {Op74M1},    {Op75M1},    {Op76M1},    {Op77M1},
    {Op78},      {Op79M1},    {Op7AE1},    {Op7B},      {Op7C},
    {Op7DM1},    {Op7EM1},    {Op7FM1},    {Op80},      {Op81M1},
    {Op82},      {Op83M1},    {Op84X1},    {Op85M1},    {Op86X1},
    {Op87M1},    {Op88X1},    {Op89M1},    {Op8AM1},    {Op8BE1},
    {Op8CX1},    {Op8DM1},    {Op8EX1},    {Op8FM1},    {Op90},
    {Op91M1},    {Op92M1},    {Op93M1},    {Op94X1},    {Op95M1},
    {Op96X1},    {Op97M1},    {Op98M1},    {Op99M1},    {Op9A},
    {Op9BX1},    {Op9CM1},    {Op9DM1},    {Op9EM1},    {Op9FM1},
    {OpA0X1},    {OpA1M1},    {OpA2X1},    {OpA3M1},    {OpA4X1},
    {OpA5M1},    {OpA6X1},    {OpA7M1},    {OpA8X1},    {OpA9M1},
    {OpAAX1},    {OpABE1},      {OpACX1},    {OpADM1},    {OpAEX1},
    {OpAFM1},    {OpB0},      {OpB1M1},    {OpB2M1},    {OpB3M1},
    {OpB4X1},    {OpB5M1},    {OpB6X1},    {OpB7M1},    {OpB8},
    {OpB9M1},    {OpBAX1},    {OpBBX1},    {OpBCX1},    {OpBDM1},
    {OpBEX1},    {OpBFM1},    {OpC0X1},    {OpC1M1},    {OpC2},
    {OpC3M1},    {OpC4X1},    {OpC5M1},    {OpC6M1},    {OpC7M1},
    {OpC8X1},    {OpC9M1},    {OpCAX1},    {OpCB},      {OpCCX1},
    {OpCDM1},    {OpCEM1},    {OpCFM1},    {OpD0},      {OpD1M1},
    {OpD2M1},    {OpD3M1},    {OpD4E1},      {OpD5M1},    {OpD6M1},
    {OpD7M1},    {OpD8},      {OpD9M1},    {OpDAE1},    {OpDB},
    {OpDC},      {OpDDM1},    {OpDEM1},    {OpDFM1},    {OpE0X1},
    {OpE1M1},    {OpE2},      {OpE3M1},    {OpE4X1},    {OpE5M1},
    {OpE6M1},    {OpE7M1},    {OpE8X1},    {OpE9M1},    {OpEA},
    {OpEB},      {OpECX1},    {OpEDM1},    {OpEEM1},    {OpEFM1},
    {OpF0},      {OpF1M1},    {OpF2M1},    {OpF3M1},    {OpF4E1},
    {OpF5M1},    {OpF6M1},    {OpF7M1},    {OpF8},      {OpF9M1},
    {OpFAE1},    {OpFB},      {OpFCE1},      {OpFDM1},    {OpFEM1},
    {OpFFM1}
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM1X1[256] =
{
    {Op00},	 {Op01M1},    {Op02},      {Op03M1},    {Op04M1},
    {Op05M1},    {Op06M1},    {Op07M1},    {Op08},      {Op09M1},
    {Op0AM1},    {Op0B},      {Op0CM1},    {Op0DM1},    {Op0EM1},
    {Op0FM1},    {Op10},      {Op11M1},    {Op12M1},    {Op13M1},
    {Op14M1},    {Op15M1},    {Op16M1},    {Op17M1},    {Op18},
    {Op19M1},    {Op1AM1},    {Op1B},      {Op1CM1},    {Op1DM1},
    {Op1EM1},    {Op1FM1},    {Op20},      {Op21M1},    {Op22},
    {Op23M1},    {Op24M1},    {Op25M1},    {Op26M1},    {Op27M1},
    {Op28},      {Op29M1},    {Op2AM1},    {Op2B},      {Op2CM1},
    {Op2DM1},    {Op2EM1},    {Op2FM1},    {Op30},      {Op31M1},
    {Op32M1},    {Op33M1},    {Op34M1},    {Op35M1},    {Op36M1},
    {Op37M1},    {Op38},      {Op39M1},    {Op3AM1},    {Op3B},
    {Op3CM1},    {Op3DM1},    {Op3EM1},    {Op3FM1},    {Op40},
    {Op41M1},    {Op42},      {Op43M1},    {Op44X1},    {Op45M1},
    {Op46M1},    {Op47M1},    {Op48M1},    {Op49M1},    {Op4AM1},
    {Op4B},      {Op4C},      {Op4DM1},    {Op4EM1},    {Op4FM1},
    {Op50},      {Op51M1},    {Op52M1},    {Op53M1},    {Op54X1},
    {Op55M1},    {Op56M1},    {Op57M1},    {Op58},      {Op59M1},
    {Op5AX1},    {Op5B},      {Op5C},      {Op5DM1},    {Op5EM1},
    {Op5FM1},    {Op60},      {Op61M1},    {Op62},      {Op63M1},
    {Op64M1},    {Op65M1},    {Op66M1},    {Op67M1},    {Op68M1},
    {Op69M1},    {Op6AM1},    {Op6B},      {Op6C},      {Op6DM1},
    {Op6EM1},    {Op6FM1},    {Op70},      {Op71M1},    {Op72M1},
    {Op73M1},    {Op74M1},    {Op75M1},    {Op76M1},    {Op77M1},
    {Op78},      {Op79M1},    {Op7AX1},    {Op7B},      {Op7C},
    {Op7DM1},    {Op7EM1},    {Op7FM1},    {Op80},      {Op81M1},
    {Op82},      {Op83M1},    {Op84X1},    {Op85M1},    {Op86X1},
    {Op87M1},    {Op88X1},    {Op89M1},    {Op8AM1},    {Op8B},
    {Op8CX1},    {Op8DM1},    {Op8EX1},    {Op8FM1},    {Op90},
    {Op91M1},    {Op92M1},    {Op93M1},    {Op94X1},    {Op95M1},
    {Op96X1},    {Op97M1},    {Op98M1},    {Op99M1},    {Op9A},
    {Op9BX1},    {Op9CM1},    {Op9DM1},    {Op9EM1},    {Op9FM1},
    {OpA0X1},    {OpA1M1},    {OpA2X1},    {OpA3M1},    {OpA4X1},
    {OpA5M1},    {OpA6X1},    {OpA7M1},    {OpA8X1},    {OpA9M1},
    {OpAAX1},    {OpAB},      {OpACX1},    {OpADM1},    {OpAEX1},
    {OpAFM1},    {OpB0},      {OpB1M1},    {OpB2M1},    {OpB3M1},
    {OpB4X1},    {OpB5M1},    {OpB6X1},    {OpB7M1},    {OpB8},
    {OpB9M1},    {OpBAX1},    {OpBBX1},    {OpBCX1},    {OpBDM1},
    {OpBEX1},    {OpBFM1},    {OpC0X1},    {OpC1M1},    {OpC2},
    {OpC3M1},    {OpC4X1},    {OpC5M1},    {OpC6M1},    {OpC7M1},
    {OpC8X1},    {OpC9M1},    {OpCAX1},    {OpCB},      {OpCCX1},
    {OpCDM1},    {OpCEM1},    {OpCFM1},    {OpD0},      {OpD1M1},
    {OpD2M1},    {OpD3M1},    {OpD4},      {OpD5M1},    {OpD6M1},
    {OpD7M1},    {OpD8},      {OpD9M1},    {OpDAX1},    {OpDB},
    {OpDC},      {OpDDM1},    {OpDEM1},    {OpDFM1},    {OpE0X1},
    {OpE1M1},    {OpE2},      {OpE3M1},    {OpE4X1},    {OpE5M1},
    {OpE6M1},    {OpE7M1},    {OpE8X1},    {OpE9M1},    {OpEA},
    {OpEB},      {OpECX1},    {OpEDM1},    {OpEEM1},    {OpEFM1},
    {OpF0},      {OpF1M1},    {OpF2M1},    {OpF3M1},    {OpF4},
    {OpF5M1},    {OpF6M1},    {OpF7M1},    {OpF8},      {OpF9M1},
    {OpFAX1},    {OpFB},      {OpFC},      {OpFDM1},    {OpFEM1},
    {OpFFM1}
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM1X0[256] =
{
    {Op00},	 {Op01M1},    {Op02},      {Op03M1},    {Op04M1},
    {Op05M1},    {Op06M1},    {Op07M1},    {Op08},      {Op09M1},
    {Op0AM1},    {Op0B},      {Op0CM1},    {Op0DM1},    {Op0EM1},
    {Op0FM1},    {Op10},      {Op11M1},    {Op12M1},    {Op13M1},
    {Op14M1},    {Op15M1},    {Op16M1},    {Op17M1},    {Op18},
    {Op19M1},    {Op1AM1},    {Op1B},      {Op1CM1},    {Op1DM1},
    {Op1EM1},    {Op1FM1},    {Op20},      {Op21M1},    {Op22},
    {Op23M1},    {Op24M1},    {Op25M1},    {Op26M1},    {Op27M1},
    {Op28},      {Op29M1},    {Op2AM1},    {Op2B},      {Op2CM1},
    {Op2DM1},    {Op2EM1},    {Op2FM1},    {Op30},      {Op31M1},
    {Op32M1},    {Op33M1},    {Op34M1},    {Op35M1},    {Op36M1},
    {Op37M1},    {Op38},      {Op39M1},    {Op3AM1},    {Op3B},
    {Op3CM1},    {Op3DM1},    {Op3EM1},    {Op3FM1},    {Op40},
    {Op41M1},    {Op42},      {Op43M1},    {Op44X0},    {Op45M1},
    {Op46M1},    {Op47M1},    {Op48M1},    {Op49M1},    {Op4AM1},
    {Op4B},      {Op4C},      {Op4DM1},    {Op4EM1},    {Op4FM1},
    {Op50},      {Op51M1},    {Op52M1},    {Op53M1},    {Op54X0},
    {Op55M1},    {Op56M1},    {Op57M1},    {Op58},      {Op59M1},
    {Op5AX0},    {Op5B},      {Op5C},      {Op5DM1},    {Op5EM1},
    {Op5FM1},    {Op60},      {Op61M1},    {Op62},      {Op63M1},
    {Op64M1},    {Op65M1},    {Op66M1},    {Op67M1},    {Op68M1},
    {Op69M1},    {Op6AM1},    {Op6B},      {Op6C},      {Op6DM1},
    {Op6EM1},    {Op6FM1},    {Op70},      {Op71M1},    {Op72M1},
    {Op73M1},    {Op74M1},    {Op75M1},    {Op76M1},    {Op77M1},
    {Op78},      {Op79M1},    {Op7AX0},    {Op7B},      {Op7C},
    {Op7DM1},    {Op7EM1},    {Op7FM1},    {Op80},      {Op81M1},
    {Op82},      {Op83M1},    {Op84X0},    {Op85M1},    {Op86X0},
    {Op87M1},    {Op88X0},    {Op89M1},    {Op8AM1},    {Op8B},
    {Op8CX0},    {Op8DM1},    {Op8EX0},    {Op8FM1},    {Op90},
    {Op91M1},    {Op92M1},    {Op93M1},    {Op94X0},    {Op95M1},
    {Op96X0},    {Op97M1},    {Op98M1},    {Op99M1},    {Op9A},
    {Op9BX0},    {Op9CM1},    {Op9DM1},    {Op9EM1},    {Op9FM1},
    {OpA0X0},    {OpA1M1},    {OpA2X0},    {OpA3M1},    {OpA4X0},
    {OpA5M1},    {OpA6X0},    {OpA7M1},    {OpA8X0},    {OpA9M1},
    {OpAAX0},    {OpAB},      {OpACX0},    {OpADM1},    {OpAEX0},
    {OpAFM1},    {OpB0},      {OpB1M1},    {OpB2M1},    {OpB3M1},
    {OpB4X0},    {OpB5M1},    {OpB6X0},    {OpB7M1},    {OpB8},
    {OpB9M1},    {OpBAX0},    {OpBBX0},    {OpBCX0},    {OpBDM1},
    {OpBEX0},    {OpBFM1},    {OpC0X0},    {OpC1M1},    {OpC2},
    {OpC3M1},    {OpC4X0},    {OpC5M1},    {OpC6M1},    {OpC7M1},
    {OpC8X0},    {OpC9M1},    {OpCAX0},    {OpCB},      {OpCCX0},
    {OpCDM1},    {OpCEM1},    {OpCFM1},    {OpD0},      {OpD1M1},
    {OpD2M1},    {OpD3M1},    {OpD4},      {OpD5M1},    {OpD6M1},
    {OpD7M1},    {OpD8},      {OpD9M1},    {OpDAX0},    {OpDB},
    {OpDC},      {OpDDM1},    {OpDEM1},    {OpDFM1},    {OpE0X0},
    {OpE1M1},    {OpE2},      {OpE3M1},    {OpE4X0},    {OpE5M1},
    {OpE6M1},    {OpE7M1},    {OpE8X0},    {OpE9M1},    {OpEA},
    {OpEB},      {OpECX0},    {OpEDM1},    {OpEEM1},    {OpEFM1},
    {OpF0},      {OpF1M1},    {OpF2M1},    {OpF3M1},    {OpF4},
    {OpF5M1},    {OpF6M1},    {OpF7M1},    {OpF8},      {OpF9M1},
    {OpFAX0},    {OpFB},      {OpFC},      {OpFDM1},    {OpFEM1},
    {OpFFM1}
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM0X0[256] =
{
    {Op00},	 {Op01M0},    {Op02},      {Op03M0},    {Op04M0},
    {Op05M0},    {Op06M0},    {Op07M0},    {Op08},      {Op09M0},
    {Op0AM0},    {Op0B},      {Op0CM0},    {Op0DM0},    {Op0EM0},
    {Op0FM0},    {Op10},      {Op11M0},    {Op12M0},    {Op13M0},
    {Op14M0},    {Op15M0},    {Op16M0},    {Op17M0},    {Op18},
    {Op19M0},    {Op1AM0},    {Op1B},      {Op1CM0},    {Op1DM0},
    {Op1EM0},    {Op1FM0},    {Op20},      {Op21M0},    {Op22},
    {Op23M0},    {Op24M0},    {Op25M0},    {Op26M0},    {Op27M0},
    {Op28},      {Op29M0},    {Op2AM0},    {Op2B},      {Op2CM0},
    {Op2DM0},    {Op2EM0},    {Op2FM0},    {Op30},      {Op31M0},
    {Op32M0},    {Op33M0},    {Op34M0},    {Op35M0},    {Op36M0},
    {Op37M0},    {Op38},      {Op39M0},    {Op3AM0},    {Op3B},
    {Op3CM0},    {Op3DM0},    {Op3EM0},    {Op3FM0},    {Op40},
    {Op41M0},    {Op42},      {Op43M0},    {Op44X0},    {Op45M0},
    {Op46M0},    {Op47M0},    {Op48M0},    {Op49M0},    {Op4AM0},
    {Op4B},      {Op4C},      {Op4DM0},    {Op4EM0},    {Op4FM0},
    {Op50},      {Op51M0},    {Op52M0},    {Op53M0},    {Op54X0},
    {Op55M0},    {Op56M0},    {Op57M0},    {Op58},      {Op59M0},
    {Op5AX0},    {Op5B},      {Op5C},      {Op5DM0},    {Op5EM0},
    {Op5FM0},    {Op60},      {Op61M0},    {Op62},      {Op63M0},
    {Op64M0},    {Op65M0},    {Op66M0},    {Op67M0},    {Op68M0},
    {Op69M0},    {Op6AM0},    {Op6B},      {Op6C},      {Op6DM0},
    {Op6EM0},    {Op6FM0},    {Op70},      {Op71M0},    {Op72M0},
    {Op73M0},    {Op74M0},    {Op75M0},    {Op76M0},    {Op77M0},
    {Op78},      {Op79M0},    {Op7AX0},    {Op7B},      {Op7C},
    {Op7DM0},    {Op7EM0},    {Op7FM0},    {Op80},      {Op81M0},
    {Op82},      {Op83M0},    {Op84X0},    {Op85M0},    {Op86X0},
    {Op87M0},    {Op88X0},    {Op89M0},    {Op8AM0},    {Op8B},
    {Op8CX0},    {Op8DM0},    {Op8EX0},    {Op8FM0},    {Op90},
    {Op91M0},    {Op92M0},    {Op93M0},    {Op94X0},    {Op95M0},
    {Op96X0},    {Op97M0},    {Op98M0},    {Op99M0},    {Op9A},
    {Op9BX0},    {Op9CM0},    {Op9DM0},    {Op9EM0},    {Op9FM0},
    {OpA0X0},    {OpA1M0},    {OpA2X0},    {OpA3M0},    {OpA4X0},
    {OpA5M0},    {OpA6X0},    {OpA7M0},    {OpA8X0},    {OpA9M0},
    {OpAAX0},    {OpAB},      {OpACX0},    {OpADM0},    {OpAEX0},
    {OpAFM0},    {OpB0},      {OpB1M0},    {OpB2M0},    {OpB3M0},
    {OpB4X0},    {OpB5M0},    {OpB6X0},    {OpB7M0},    {OpB8},
    {OpB9M0},    {OpBAX0},    {OpBBX0},    {OpBCX0},    {OpBDM0},
    {OpBEX0},    {OpBFM0},    {OpC0X0},    {OpC1M0},    {OpC2},
    {OpC3M0},    {OpC4X0},    {OpC5M0},    {OpC6M0},    {OpC7M0},
    {OpC8X0},    {OpC9M0},    {OpCAX0},    {OpCB},      {OpCCX0},
    {OpCDM0},    {OpCEM0},    {OpCFM0},    {OpD0},      {OpD1M0},
    {OpD2M0},    {OpD3M0},    {OpD4},      {OpD5M0},    {OpD6M0},
    {OpD7M0},    {OpD8},      {OpD9M0},    {OpDAX0},    {OpDB},
    {OpDC},      {OpDDM0},    {OpDEM0},    {OpDFM0},    {OpE0X0},
    {OpE1M0},    {OpE2},      {OpE3M0},    {OpE4X0},    {OpE5M0},
    {OpE6M0},    {OpE7M0},    {OpE8X0},    {OpE9M0},    {OpEA},
    {OpEB},      {OpECX0},    {OpEDM0},    {OpEEM0},    {OpEFM0},
    {OpF0},      {OpF1M0},    {OpF2M0},    {OpF3M0},    {OpF4},
    {OpF5M0},    {OpF6M0},    {OpF7M0},    {OpF8},      {OpF9M0},
    {OpFAX0},    {OpFB},      {OpFC},      {OpFDM0},    {OpFEM0},
    {OpFFM0}
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM0X1[256] =
{
    {Op00},	 {Op01M0},    {Op02},      {Op03M0},    {Op04M0},
    {Op05M0},    {Op06M0},    {Op07M0},    {Op08},      {Op09M0},
    {Op0AM0},    {Op0B},      {Op0CM0},    {Op0DM0},    {Op0EM0},
    {Op0FM0},    {Op10},      {Op11M0},    {Op12M0},    {Op13M0},
    {Op14M0},    {Op15M0},    {Op16M0},    {Op17M0},    {Op18},
    {Op19M0},    {Op1AM0},    {Op1B},      {Op1CM0},    {Op1DM0},
    {Op1EM0},    {Op1FM0},    {Op20},      {Op21M0},    {Op22},
    {Op23M0},    {Op24M0},    {Op25M0},    {Op26M0},    {Op27M0},
    {Op28},      {Op29M0},    {Op2AM0},    {Op2B},      {Op2CM0},
    {Op2DM0},    {Op2EM0},    {Op2FM0},    {Op30},      {Op31M0},
    {Op32M0},    {Op33M0},    {Op34M0},    {Op35M0},    {Op36M0},
    {Op37M0},    {Op38},      {Op39M0},    {Op3AM0},    {Op3B},
    {Op3CM0},    {Op3DM0},    {Op3EM0},    {Op3FM0},    {Op40},
    {Op41M0},    {Op42},      {Op43M0},    {Op44X1},    {Op45M0},
    {Op46M0},    {Op47M0},    {Op48M0},    {Op49M0},    {Op4AM0},
    {Op4B},      {Op4C},      {Op4DM0},    {Op4EM0},    {Op4FM0},
    {Op50},      {Op51M0},    {Op52M0},    {Op53M0},    {Op54X1},
    {Op55M0},    {Op56M0},    {Op57M0},    {Op58},      {Op59M0},
    {Op5AX1},    {Op5B},      {Op5C},      {Op5DM0},    {Op5EM0},
    {Op5FM0},    {Op60},      {Op61M0},    {Op62},      {Op63M0},
    {Op64M0},    {Op65M0},    {Op66M0},    {Op67M0},    {Op68M0},
    {Op69M0},    {Op6AM0},    {Op6B},      {Op6C},      {Op6DM0},
    {Op6EM0},    {Op6FM0},    {Op70},      {Op71M0},    {Op72M0},
    {Op73M0},    {Op74M0},    {Op75M0},    {Op76M0},    {Op77M0},
    {Op78},      {Op79M0},    {Op7AX1},    {Op7B},      {Op7C},
    {Op7DM0},    {Op7EM0},    {Op7FM0},    {Op80},      {Op81M0},
    {Op82},      {Op83M0},    {Op84X1},    {Op85M0},    {Op86X1},
    {Op87M0},    {Op88X1},    {Op89M0},    {Op8AM0},    {Op8B},
    {Op8CX1},    {Op8DM0},    {Op8EX1},    {Op8FM0},    {Op90},
    {Op91M0},    {Op92M0},    {Op93M0},    {Op94X1},    {Op95M0},
    {Op96X1},    {Op97M0},    {Op98M0},    {Op99M0},    {Op9A},
    {Op9BX1},    {Op9CM0},    {Op9DM0},    {Op9EM0},    {Op9FM0},
    {OpA0X1},    {OpA1M0},    {OpA2X1},    {OpA3M0},    {OpA4X1},
    {OpA5M0},    {OpA6X1},    {OpA7M0},    {OpA8X1},    {OpA9M0},
    {OpAAX1},    {OpAB},      {OpACX1},    {OpADM0},    {OpAEX1},
    {OpAFM0},    {OpB0},      {OpB1M0},    {OpB2M0},    {OpB3M0},
    {OpB4X1},    {OpB5M0},    {OpB6X1},    {OpB7M0},    {OpB8},
    {OpB9M0},    {OpBAX1},    {OpBBX1},    {OpBCX1},    {OpBDM0},
    {OpBEX1},    {OpBFM0},    {OpC0X1},    {OpC1M0},    {OpC2},
    {OpC3M0},    {OpC4X1},    {OpC5M0},    {OpC6M0},    {OpC7M0},
    {OpC8X1},    {OpC9M0},    {OpCAX1},    {OpCB},      {OpCCX1},
    {OpCDM0},    {OpCEM0},    {OpCFM0},    {OpD0},      {OpD1M0},
    {OpD2M0},    {OpD3M0},    {OpD4},      {OpD5M0},    {OpD6M0},
    {OpD7M0},    {OpD8},      {OpD9M0},    {OpDAX1},    {OpDB},
    {OpDC},      {OpDDM0},    {OpDEM0},    {OpDFM0},    {OpE0X1},
    {OpE1M0},    {OpE2},      {OpE3M0},    {OpE4X1},    {OpE5M0},
    {OpE6M0},    {OpE7M0},    {OpE8X1},    {OpE9M0},    {OpEA},
    {OpEB},      {OpECX1},    {OpEDM0},    {OpEEM0},    {OpEFM0},
    {OpF0},      {OpF1M0},    {OpF2M0},    {OpF3M0},    {OpF4},
    {OpF5M0},    {OpF6M0},    {OpF7M0},    {OpF8},      {OpF9M0},
    {OpFAX1},    {OpFB},      {OpFC},      {OpFDM0},    {OpFEM0},
    {OpFFM0}
};

// Wake SA1 opcodes

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesE1WakeSA1[256] =
{
    {Op00},        {Op01M1},      {Op02},        {Op03M1},      {Op04M1_WS},   
    {Op05M1},      {Op06M1},      {Op07M1},      {Op08E1},      {Op09M1},      
    {Op0AM1},      {Op0BE1},      {Op0CM1_WS},   {Op0DM1},      {Op0EM1},      
    {Op0FM1},      {Op10},        {Op11M1},      {Op12M1},      {Op13M1},      
    {Op14M1_WS},   {Op15M1},      {Op16M1},      {Op17M1},      {Op18},        
    {Op19M1},      {Op1AM1},      {Op1B},        {Op1CM1_WS},   {Op1DM1},      
    {Op1EM1},      {Op1FM1},      {Op20},        {Op21M1},      {Op22E1},      
    {Op23M1},      {Op24M1},      {Op25M1},      {Op26M1},      {Op27M1},      
    {Op28},        {Op29M1},      {Op2AM1},      {Op2BE1},      {Op2CM1},      
    {Op2DM1},      {Op2EM1},      {Op2FM1},      {Op30},        {Op31M1},      
    {Op32M1},      {Op33M1},      {Op34M1},      {Op35M1},      {Op36M1},      
    {Op37M1},      {Op38},        {Op39M1},      {Op3AM1},      {Op3B},        
    {Op3CM1},      {Op3DM1},      {Op3EM1},      {Op3FM1},      {Op40},        
    {Op41M1},      {Op42},        {Op43M1},      {Op44X1},      {Op45M1},      
    {Op46M1},      {Op47M1},      {Op48E1},      {Op49M1},      {Op4AM1},      
    {Op4BE1},      {Op4C},        {Op4DM1},      {Op4EM1},      {Op4FM1},      
    {Op50},        {Op51M1},      {Op52M1},      {Op53M1},      {Op54X1},      
    {Op55M1},      {Op56M1},      {Op57M1},      {Op58},        {Op59M1},      
    {Op5AE1},      {Op5B},        {Op5C},        {Op5DM1},      {Op5EM1},      
    {Op5FM1},      {Op60},        {Op61M1},      {Op62E1},      {Op63M1},      
    {Op64M1_WS},   {Op65M1},      {Op66M1},      {Op67M1},      {Op68E1},      
    {Op69M1},      {Op6AM1},      {Op6BE1},      {Op6C},        {Op6DM1},      
    {Op6EM1},      {Op6FM1},      {Op70},        {Op71M1},      {Op72M1},      
    {Op73M1},      {Op74M1_WS},   {Op75M1},      {Op76M1},      {Op77M1},      
    {Op78},        {Op79M1},      {Op7AE1},      {Op7B},        {Op7C},        
    {Op7DM1},      {Op7EM1},      {Op7FM1},      {Op80},        {Op81M1_WS},   
    {Op82},        {Op83M1_WS},   {Op84X1_WS},   {Op85M1_WS},   {Op86X1_WS},   
    {Op87M1_WS},   {Op88X1},      {Op89M1},      {Op8AM1},      {Op8BE1},      
    {Op8CX1_WS},   {Op8DM1_WS},   {Op8EX1_WS},   {Op8FM1_WS},   {Op90},        
    {Op91M1_WS},   {Op92M1_WS},   {Op93M1_WS},   {Op94X1_WS},   {Op95M1_WS},   
    {Op96X1_WS},   {Op97M1_WS},   {Op98M1},      {Op99M1_WS},   {Op9A},        
    {Op9BX1},      {Op9CM1_WS},   {Op9DM1_WS},   {Op9EM1_WS},   {Op9FM1_WS},   
    {OpA0X1},      {OpA1M1},      {OpA2X1},      {OpA3M1},      {OpA4X1},      
    {OpA5M1},      {OpA6X1},      {OpA7M1},      {OpA8X1},      {OpA9M1},      
    {OpAAX1},      {OpABE1},      {OpACX1},      {OpADM1},      {OpAEX1},      
    {OpAFM1},      {OpB0},        {OpB1M1},      {OpB2M1},      {OpB3M1},      
    {OpB4X1},      {OpB5M1},      {OpB6X1},      {OpB7M1},      {OpB8},        
    {OpB9M1},      {OpBAX1},      {OpBBX1},      {OpBCX1},      {OpBDM1},      
    {OpBEX1},      {OpBFM1},      {OpC0X1},      {OpC1M1},      {OpC2},        
    {OpC3M1},      {OpC4X1},      {OpC5M1},      {OpC6M1_WS},   {OpC7M1},      
    {OpC8X1},      {OpC9M1},      {OpCAX1},      {OpCB},        {OpCCX1},      
    {OpCDM1},      {OpCEM1_WS},   {OpCFM1},      {OpD0},        {OpD1M1},      
    {OpD2M1},      {OpD3M1},      {OpD4E1},      {OpD5M1},      {OpD6M1_WS},   
    {OpD7M1},      {OpD8},        {OpD9M1},      {OpDAE1},      {OpDB},        
    {OpDC},        {OpDDM1},      {OpDEM1_WS},   {OpDFM1},      {OpE0X1},      
    {OpE1M1},      {OpE2},        {OpE3M1},      {OpE4X1},      {OpE5M1},      
    {OpE6M1_WS},   {OpE7M1},      {OpE8X1},      {OpE9M1},      {OpEA},        
    {OpEB},        {OpECX1},      {OpEDM1},      {OpEEM1_WS},   {OpEFM1},      
    {OpF0},        {OpF1M1},      {OpF2M1},      {OpF3M1},      {OpF4E1},      
    {OpF5M1},      {OpF6M1_WS},   {OpF7M1},      {OpF8},        {OpF9M1},      
    {OpFAE1},      {OpFB},        {OpFCE1},      {OpFDM1},      {OpFEM1_WS},   
    {OpFFM1}       
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM1X1WakeSA1[256] =
{
    {Op00},        {Op01M1},      {Op02},        {Op03M1},      {Op04M1_WS},   
    {Op05M1},      {Op06M1},      {Op07M1},      {Op08},        {Op09M1},      
    {Op0AM1},      {Op0B},        {Op0CM1_WS},   {Op0DM1},      {Op0EM1},      
    {Op0FM1},      {Op10},        {Op11M1},      {Op12M1},      {Op13M1},      
    {Op14M1_WS},   {Op15M1},      {Op16M1},      {Op17M1},      {Op18},        
    {Op19M1},      {Op1AM1},      {Op1B},        {Op1CM1_WS},   {Op1DM1},      
    {Op1EM1},      {Op1FM1},      {Op20},        {Op21M1},      {Op22},        
    {Op23M1},      {Op24M1},      {Op25M1},      {Op26M1},      {Op27M1},      
    {Op28},        {Op29M1},      {Op2AM1},      {Op2B},        {Op2CM1},      
    {Op2DM1},      {Op2EM1},      {Op2FM1},      {Op30},        {Op31M1},      
    {Op32M1},      {Op33M1},      {Op34M1},      {Op35M1},      {Op36M1},      
    {Op37M1},      {Op38},        {Op39M1},      {Op3AM1},      {Op3B},        
    {Op3CM1},      {Op3DM1},      {Op3EM1},      {Op3FM1},      {Op40},        
    {Op41M1},      {Op42},        {Op43M1},      {Op44X1},      {Op45M1},      
    {Op46M1},      {Op47M1},      {Op48M1},      {Op49M1},      {Op4AM1},      
    {Op4B},        {Op4C},        {Op4DM1},      {Op4EM1},      {Op4FM1},      
    {Op50},        {Op51M1},      {Op52M1},      {Op53M1},      {Op54X1},      
    {Op55M1},      {Op56M1},      {Op57M1},      {Op58},        {Op59M1},      
    {Op5AX1},      {Op5B},        {Op5C},        {Op5DM1},      {Op5EM1},      
    {Op5FM1},      {Op60},        {Op61M1},      {Op62},        {Op63M1},      
    {Op64M1_WS},   {Op65M1},      {Op66M1},      {Op67M1},      {Op68M1},      
    {Op69M1},      {Op6AM1},      {Op6B},        {Op6C},        {Op6DM1},      
    {Op6EM1},      {Op6FM1},      {Op70},        {Op71M1},      {Op72M1},      
    {Op73M1},      {Op74M1_WS},   {Op75M1},      {Op76M1},      {Op77M1},      
    {Op78},        {Op79M1},      {Op7AX1},      {Op7B},        {Op7C},        
    {Op7DM1},      {Op7EM1},      {Op7FM1},      {Op80},        {Op81M1_WS},   
    {Op82},        {Op83M1_WS},   {Op84X1_WS},   {Op85M1_WS},   {Op86X1_WS},   
    {Op87M1_WS},   {Op88X1},      {Op89M1},      {Op8AM1},      {Op8B},        
    {Op8CX1_WS},   {Op8DM1_WS},   {Op8EX1_WS},   {Op8FM1_WS},   {Op90},        
    {Op91M1_WS},   {Op92M1_WS},   {Op93M1_WS},   {Op94X1_WS},   {Op95M1_WS},   
    {Op96X1_WS},   {Op97M1_WS},   {Op98M1},      {Op99M1_WS},   {Op9A},        
    {Op9BX1},      {Op9CM1_WS},   {Op9DM1_WS},   {Op9EM1_WS},   {Op9FM1_WS},   
    {OpA0X1},      {OpA1M1},      {OpA2X1},      {OpA3M1},      {OpA4X1},      
    {OpA5M1},      {OpA6X1},      {OpA7M1},      {OpA8X1},      {OpA9M1},      
    {OpAAX1},      {OpAB},        {OpACX1},      {OpADM1},      {OpAEX1},      
    {OpAFM1},      {OpB0},        {OpB1M1},      {OpB2M1},      {OpB3M1},      
    {OpB4X1},      {OpB5M1},      {OpB6X1},      {OpB7M1},      {OpB8},        
    {OpB9M1},      {OpBAX1},      {OpBBX1},      {OpBCX1},      {OpBDM1},      
    {OpBEX1},      {OpBFM1},      {OpC0X1},      {OpC1M1},      {OpC2},        
    {OpC3M1},      {OpC4X1},      {OpC5M1},      {OpC6M1_WS},   {OpC7M1},      
    {OpC8X1},      {OpC9M1},      {OpCAX1},      {OpCB},        {OpCCX1},      
    {OpCDM1},      {OpCEM1_WS},   {OpCFM1},      {OpD0},        {OpD1M1},      
    {OpD2M1},      {OpD3M1},      {OpD4},        {OpD5M1},      {OpD6M1_WS},   
    {OpD7M1},      {OpD8},        {OpD9M1},      {OpDAX1},      {OpDB},        
    {OpDC},        {OpDDM1},      {OpDEM1_WS},   {OpDFM1},      {OpE0X1},      
    {OpE1M1},      {OpE2},        {OpE3M1},      {OpE4X1},      {OpE5M1},      
    {OpE6M1_WS},   {OpE7M1},      {OpE8X1},      {OpE9M1},      {OpEA},        
    {OpEB},        {OpECX1},      {OpEDM1},      {OpEEM1_WS},   {OpEFM1},      
    {OpF0},        {OpF1M1},      {OpF2M1},      {OpF3M1},      {OpF4},        
    {OpF5M1},      {OpF6M1_WS},   {OpF7M1},      {OpF8},        {OpF9M1},      
    {OpFAX1},      {OpFB},        {OpFC},        {OpFDM1},      {OpFEM1_WS},   
    {OpFFM1}       
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM1X0WakeSA1[256] =
{
    {Op00},        {Op01M1},      {Op02},        {Op03M1},      {Op04M1_WS},   
    {Op05M1},      {Op06M1},      {Op07M1},      {Op08},        {Op09M1},      
    {Op0AM1},      {Op0B},        {Op0CM1_WS},   {Op0DM1},      {Op0EM1},      
    {Op0FM1},      {Op10},        {Op11M1},      {Op12M1},      {Op13M1},      
    {Op14M1_WS},   {Op15M1},      {Op16M1},      {Op17M1},      {Op18},        
    {Op19M1},      {Op1AM1},      {Op1B},        {Op1CM1_WS},   {Op1DM1},      
    {Op1EM1},      {Op1FM1},      {Op20},        {Op21M1},      {Op22},        
    {Op23M1},      {Op24M1},      {Op25M1},      {Op26M1},      {Op27M1},      
    {Op28},        {Op29M1},      {Op2AM1},      {Op2B},        {Op2CM1},      
    {Op2DM1},      {Op2EM1},      {Op2FM1},      {Op30},        {Op31M1},      
    {Op32M1},      {Op33M1},      {Op34M1},      {Op35M1},      {Op36M1},      
    {Op37M1},      {Op38},        {Op39M1},      {Op3AM1},      {Op3B},        
    {Op3CM1},      {Op3DM1},      {Op3EM1},      {Op3FM1},      {Op40},        
    {Op41M1},      {Op42},        {Op43M1},      {Op44X0},      {Op45M1},      
    {Op46M1},      {Op47M1},      {Op48M1},      {Op49M1},      {Op4AM1},      
    {Op4B},        {Op4C},        {Op4DM1},      {Op4EM1},      {Op4FM1},      
    {Op50},        {Op51M1},      {Op52M1},      {Op53M1},      {Op54X0},      
    {Op55M1},      {Op56M1},      {Op57M1},      {Op58},        {Op59M1},      
    {Op5AX0},      {Op5B},        {Op5C},        {Op5DM1},      {Op5EM1},      
    {Op5FM1},      {Op60},        {Op61M1},      {Op62},        {Op63M1},      
    {Op64M1_WS},   {Op65M1},      {Op66M1},      {Op67M1},      {Op68M1},      
    {Op69M1},      {Op6AM1},      {Op6B},        {Op6C},        {Op6DM1},      
    {Op6EM1},      {Op6FM1},      {Op70},        {Op71M1},      {Op72M1},      
    {Op73M1},      {Op74M1_WS},   {Op75M1},      {Op76M1},      {Op77M1},      
    {Op78},        {Op79M1},      {Op7AX0},      {Op7B},        {Op7C},        
    {Op7DM1},      {Op7EM1},      {Op7FM1},      {Op80},        {Op81M1_WS},   
    {Op82},        {Op83M1_WS},   {Op84X0_WS},   {Op85M1_WS},   {Op86X0_WS},   
    {Op87M1_WS},   {Op88X0},      {Op89M1},      {Op8AM1},      {Op8B},        
    {Op8CX0_WS},   {Op8DM1_WS},   {Op8EX0_WS},   {Op8FM1_WS},   {Op90},        
    {Op91M1_WS},   {Op92M1_WS},   {Op93M1_WS},   {Op94X0_WS},   {Op95M1_WS},   
    {Op96X0_WS},   {Op97M1_WS},   {Op98M1},      {Op99M1_WS},   {Op9A},        
    {Op9BX0},      {Op9CM1_WS},   {Op9DM1_WS},   {Op9EM1_WS},   {Op9FM1_WS},   
    {OpA0X0},      {OpA1M1},      {OpA2X0},      {OpA3M1},      {OpA4X0},      
    {OpA5M1},      {OpA6X0},      {OpA7M1},      {OpA8X0},      {OpA9M1},      
    {OpAAX0},      {OpAB},        {OpACX0},      {OpADM1},      {OpAEX0},      
    {OpAFM1},      {OpB0},        {OpB1M1},      {OpB2M1},      {OpB3M1},      
    {OpB4X0},      {OpB5M1},      {OpB6X0},      {OpB7M1},      {OpB8},        
    {OpB9M1},      {OpBAX0},      {OpBBX0},      {OpBCX0},      {OpBDM1},      
    {OpBEX0},      {OpBFM1},      {OpC0X0},      {OpC1M1},      {OpC2},        
    {OpC3M1},      {OpC4X0},      {OpC5M1},      {OpC6M1_WS},   {OpC7M1},      
    {OpC8X0},      {OpC9M1},      {OpCAX0},      {OpCB},        {OpCCX0},      
    {OpCDM1},      {OpCEM1_WS},   {OpCFM1},      {OpD0},        {OpD1M1},      
    {OpD2M1},      {OpD3M1},      {OpD4},        {OpD5M1},      {OpD6M1_WS},   
    {OpD7M1},      {OpD8},        {OpD9M1},      {OpDAX0},      {OpDB},        
    {OpDC},        {OpDDM1},      {OpDEM1_WS},   {OpDFM1},      {OpE0X0},      
    {OpE1M1},      {OpE2},        {OpE3M1},      {OpE4X0},      {OpE5M1},      
    {OpE6M1_WS},   {OpE7M1},      {OpE8X0},      {OpE9M1},      {OpEA},        
    {OpEB},        {OpECX0},      {OpEDM1},      {OpEEM1_WS},   {OpEFM1},      
    {OpF0},        {OpF1M1},      {OpF2M1},      {OpF3M1},      {OpF4},        
    {OpF5M1},      {OpF6M1_WS},   {OpF7M1},      {OpF8},        {OpF9M1},      
    {OpFAX0},      {OpFB},        {OpFC},        {OpFDM1},      {OpFEM1_WS},   
    {OpFFM1}       
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM0X1WakeSA1[256] =
{
    {Op00},        {Op01M0},      {Op02},        {Op03M0},      {Op04M0_WS},   
    {Op05M0},      {Op06M0},      {Op07M0},      {Op08},        {Op09M0},      
    {Op0AM0},      {Op0B},        {Op0CM0_WS},   {Op0DM0},      {Op0EM0},      
    {Op0FM0},      {Op10},        {Op11M0},      {Op12M0},      {Op13M0},      
    {Op14M0_WS},   {Op15M0},      {Op16M0},      {Op17M0},      {Op18},        
    {Op19M0},      {Op1AM0},      {Op1B},        {Op1CM0_WS},   {Op1DM0},      
    {Op1EM0},      {Op1FM0},      {Op20},        {Op21M0},      {Op22},        
    {Op23M0},      {Op24M0},      {Op25M0},      {Op26M0},      {Op27M0},      
    {Op28},        {Op29M0},      {Op2AM0},      {Op2B},        {Op2CM0},      
    {Op2DM0},      {Op2EM0},      {Op2FM0},      {Op30},        {Op31M0},      
    {Op32M0},      {Op33M0},      {Op34M0},      {Op35M0},      {Op36M0},      
    {Op37M0},      {Op38},        {Op39M0},      {Op3AM0},      {Op3B},        
    {Op3CM0},      {Op3DM0},      {Op3EM0},      {Op3FM0},      {Op40},        
    {Op41M0},      {Op42},        {Op43M0},      {Op44X1},      {Op45M0},      
    {Op46M0},      {Op47M0},      {Op48M0},      {Op49M0},      {Op4AM0},      
    {Op4B},        {Op4C},        {Op4DM0},      {Op4EM0},      {Op4FM0},      
    {Op50},        {Op51M0},      {Op52M0},      {Op53M0},      {Op54X1},      
    {Op55M0},      {Op56M0},      {Op57M0},      {Op58},        {Op59M0},      
    {Op5AX1},      {Op5B},        {Op5C},        {Op5DM0},      {Op5EM0},      
    {Op5FM0},      {Op60},        {Op61M0},      {Op62},        {Op63M0},      
    {Op64M0_WS},   {Op65M0},      {Op66M0},      {Op67M0},      {Op68M0},      
    {Op69M0},      {Op6AM0},      {Op6B},        {Op6C},        {Op6DM0},      
    {Op6EM0},      {Op6FM0},      {Op70},        {Op71M0},      {Op72M0},      
    {Op73M0},      {Op74M0_WS},   {Op75M0},      {Op76M0},      {Op77M0},      
    {Op78},        {Op79M0},      {Op7AX1},      {Op7B},        {Op7C},        
    {Op7DM0},      {Op7EM0},      {Op7FM0},      {Op80},        {Op81M0_WS},   
    {Op82},        {Op83M0_WS},   {Op84X1_WS},   {Op85M0_WS},   {Op86X1_WS},   
    {Op87M0_WS},   {Op88X1},      {Op89M0},      {Op8AM0},      {Op8B},        
    {Op8CX1_WS},   {Op8DM0_WS},   {Op8EX1_WS},   {Op8FM0_WS},   {Op90},        
    {Op91M0_WS},   {Op92M0_WS},   {Op93M0_WS},   {Op94X1_WS},   {Op95M0_WS},   
    {Op96X1_WS},   {Op97M0_WS},   {Op98M0},      {Op99M0_WS},   {Op9A},        
    {Op9BX1},      {Op9CM0_WS},   {Op9DM0_WS},   {Op9EM0_WS},   {Op9FM0_WS},   
    {OpA0X1},      {OpA1M0},      {OpA2X1},      {OpA3M0},      {OpA4X1},      
    {OpA5M0},      {OpA6X1},      {OpA7M0},      {OpA8X1},      {OpA9M0},      
    {OpAAX1},      {OpAB},        {OpACX1},      {OpADM0},      {OpAEX1},      
    {OpAFM0},      {OpB0},        {OpB1M0},      {OpB2M0},      {OpB3M0},      
    {OpB4X1},      {OpB5M0},      {OpB6X1},      {OpB7M0},      {OpB8},        
    {OpB9M0},      {OpBAX1},      {OpBBX1},      {OpBCX1},      {OpBDM0},      
    {OpBEX1},      {OpBFM0},      {OpC0X1},      {OpC1M0},      {OpC2},        
    {OpC3M0},      {OpC4X1},      {OpC5M0},      {OpC6M0_WS},   {OpC7M0},      
    {OpC8X1},      {OpC9M0},      {OpCAX1},      {OpCB},        {OpCCX1},      
    {OpCDM0},      {OpCEM0_WS},   {OpCFM0},      {OpD0},        {OpD1M0},      
    {OpD2M0},      {OpD3M0},      {OpD4},        {OpD5M0},      {OpD6M0_WS},   
    {OpD7M0},      {OpD8},        {OpD9M0},      {OpDAX1},      {OpDB},        
    {OpDC},        {OpDDM0},      {OpDEM0_WS},   {OpDFM0},      {OpE0X1},      
    {OpE1M0},      {OpE2},        {OpE3M0},      {OpE4X1},      {OpE5M0},      
    {OpE6M0_WS},   {OpE7M0},      {OpE8X1},      {OpE9M0},      {OpEA},        
    {OpEB},        {OpECX1},      {OpEDM0},      {OpEEM0_WS},   {OpEFM0},      
    {OpF0},        {OpF1M0},      {OpF2M0},      {OpF3M0},      {OpF4},        
    {OpF5M0},      {OpF6M0_WS},   {OpF7M0},      {OpF8},        {OpF9M0},      
    {OpFAX1},      {OpFB},        {OpFC},        {OpFDM0},      {OpFEM0_WS},   
    {OpFFM0}       
};

struct SOpcodes __attribute__((aligned(64))) S9xOpcodesM0X0WakeSA1[256] =
{
    {Op00},        {Op01M0},      {Op02},        {Op03M0},      {Op04M0_WS},   
    {Op05M0},      {Op06M0},      {Op07M0},      {Op08},        {Op09M0},      
    {Op0AM0},      {Op0B},        {Op0CM0_WS},   {Op0DM0},      {Op0EM0},      
    {Op0FM0},      {Op10},        {Op11M0},      {Op12M0},      {Op13M0},      
    {Op14M0_WS},   {Op15M0},      {Op16M0},      {Op17M0},      {Op18},        
    {Op19M0},      {Op1AM0},      {Op1B},        {Op1CM0_WS},   {Op1DM0},      
    {Op1EM0},      {Op1FM0},      {Op20},        {Op21M0},      {Op22},        
    {Op23M0},      {Op24M0},      {Op25M0},      {Op26M0},      {Op27M0},      
    {Op28},        {Op29M0},      {Op2AM0},      {Op2B},        {Op2CM0},      
    {Op2DM0},      {Op2EM0},      {Op2FM0},      {Op30},        {Op31M0},      
    {Op32M0},      {Op33M0},      {Op34M0},      {Op35M0},      {Op36M0},      
    {Op37M0},      {Op38},        {Op39M0},      {Op3AM0},      {Op3B},        
    {Op3CM0},      {Op3DM0},      {Op3EM0},      {Op3FM0},      {Op40},        
    {Op41M0},      {Op42},        {Op43M0},      {Op44X0},      {Op45M0},      
    {Op46M0},      {Op47M0},      {Op48M0},      {Op49M0},      {Op4AM0},      
    {Op4B},        {Op4C},        {Op4DM0},      {Op4EM0},      {Op4FM0},      
    {Op50},        {Op51M0},      {Op52M0},      {Op53M0},      {Op54X0},      
    {Op55M0},      {Op56M0},      {Op57M0},      {Op58},        {Op59M0},      
    {Op5AX0},      {Op5B},        {Op5C},        {Op5DM0},      {Op5EM0},      
    {Op5FM0},      {Op60},        {Op61M0},      {Op62},        {Op63M0},      
    {Op64M0_WS},   {Op65M0},      {Op66M0},      {Op67M0},      {Op68M0},      
    {Op69M0},      {Op6AM0},      {Op6B},        {Op6C},        {Op6DM0},      
    {Op6EM0},      {Op6FM0},      {Op70},        {Op71M0},      {Op72M0},      
    {Op73M0},      {Op74M0_WS},   {Op75M0},      {Op76M0},      {Op77M0},      
    {Op78},        {Op79M0},      {Op7AX0},      {Op7B},        {Op7C},        
    {Op7DM0},      {Op7EM0},      {Op7FM0},      {Op80},        {Op81M0_WS},   
    {Op82},        {Op83M0_WS},   {Op84X0_WS},   {Op85M0_WS},   {Op86X0_WS},   
    {Op87M0_WS},   {Op88X0},      {Op89M0},      {Op8AM0},      {Op8B},        
    {Op8CX0_WS},   {Op8DM0_WS},   {Op8EX0_WS},   {Op8FM0_WS},   {Op90},        
    {Op91M0_WS},   {Op92M0_WS},   {Op93M0_WS},   {Op94X0_WS},   {Op95M0_WS},   
    {Op96X0_WS},   {Op97M0_WS},   {Op98M0},      {Op99M0_WS},   {Op9A},        
    {Op9BX0},      {Op9CM0_WS},   {Op9DM0_WS},   {Op9EM0_WS},   {Op9FM0_WS},   
    {OpA0X0},      {OpA1M0},      {OpA2X0},      {OpA3M0},      {OpA4X0},      
    {OpA5M0},      {OpA6X0},      {OpA7M0},      {OpA8X0},      {OpA9M0},      
    {OpAAX0},      {OpAB},        {OpACX0},      {OpADM0},      {OpAEX0},      
    {OpAFM0},      {OpB0},        {OpB1M0},      {OpB2M0},      {OpB3M0},      
    {OpB4X0},      {OpB5M0},      {OpB6X0},      {OpB7M0},      {OpB8},        
    {OpB9M0},      {OpBAX0},      {OpBBX0},      {OpBCX0},      {OpBDM0},      
    {OpBEX0},      {OpBFM0},      {OpC0X0},      {OpC1M0},      {OpC2},        
    {OpC3M0},      {OpC4X0},      {OpC5M0},      {OpC6M0_WS},   {OpC7M0},      
    {OpC8X0},      {OpC9M0},      {OpCAX0},      {OpCB},        {OpCCX0},      
    {OpCDM0},      {OpCEM0_WS},   {OpCFM0},      {OpD0},        {OpD1M0},      
    {OpD2M0},      {OpD3M0},      {OpD4},        {OpD5M0},      {OpD6M0_WS},   
    {OpD7M0},      {OpD8},        {OpD9M0},      {OpDAX0},      {OpDB},        
    {OpDC},        {OpDDM0},      {OpDEM0_WS},   {OpDFM0},      {OpE0X0},      
    {OpE1M0},      {OpE2},        {OpE3M0},      {OpE4X0},      {OpE5M0},      
    {OpE6M0_WS},   {OpE7M0},      {OpE8X0},      {OpE9M0},      {OpEA},        
    {OpEB},        {OpECX0},      {OpEDM0},      {OpEEM0_WS},   {OpEFM0},      
    {OpF0},        {OpF1M0},      {OpF2M0},      {OpF3M0},      {OpF4},        
    {OpF5M0},      {OpF6M0_WS},   {OpF7M0},      {OpF8},        {OpF9M0},      
    {OpFAX0},      {OpFB},        {OpFC},        {OpFDM0},      {OpFEM0_WS},   
    {OpFFM0}       
};

void S9xUseInstructionSet(int set)
{
    if (set == 1)
    {
        for (int i = 0; i < 256; i++)
        {
            S9xOpcodesM1X1[i] = S9xOpcodesM1X1WakeSA1[i];
            S9xOpcodesM0X1[i] = S9xOpcodesM0X1WakeSA1[i];
            S9xOpcodesM1X0[i] = S9xOpcodesM1X0WakeSA1[i];
            S9xOpcodesM0X0[i] = S9xOpcodesM0X0WakeSA1[i];
            S9xOpcodesE1[i] = S9xOpcodesE1WakeSA1[i];
        }
    }
}