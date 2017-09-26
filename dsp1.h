/*******************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.
 
  (c) Copyright 1996 - 2002 Gary Henderson (gary.henderson@ntlworld.com) and
                            Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2001 - 2004 John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2004 Brad Jorsch (anomie@users.sourceforge.net),
                            funkyass (funkyass@spam.shaw.ca),
                            Joel Yliluoma (http://iki.fi/bisqwit/)
                            Kris Bleakley (codeviolation@hotmail.com),
                            Matthew Kendora,
                            Nach (n-a-c-h@users.sourceforge.net),
                            Peter Bortas (peter@bortas.org) and
                            zones (kasumitokoduck@yahoo.com)

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003 zsKnight (zsknight@zsnes.com),
                            _Demo_ (_demo_@zsnes.com), and Nach

  C4 C++ code
  (c) Copyright 2003 Brad Jorsch

  DSP-1 emulator code
  (c) Copyright 1998 - 2004 Ivar (ivar@snes9x.com), _Demo_, Gary Henderson,
                            John Weidman, neviksti (neviksti@hotmail.com),
                            Kris Bleakley, Andreas Naive

  DSP-2 emulator code
  (c) Copyright 2003 Kris Bleakley, John Weidman, neviksti, Matthew Kendora, and
                     Lord Nightmare (lord_nightmare@users.sourceforge.net

  OBC1 emulator code
  (c) Copyright 2001 - 2004 zsKnight, pagefault (pagefault@zsnes.com) and
                            Kris Bleakley
  Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code
  (c) Copyright 2002 Matthew Kendora with research by
                     zsKnight, John Weidman, and Dark Force

  S-DD1 C emulator code
  (c) Copyright 2003 Brad Jorsch with research by
                     Andreas Naive and John Weidman
 
  S-RTC C emulator code
  (c) Copyright 2001 John Weidman
  
  ST010 C++ emulator code
  (c) Copyright 2003 Feather, Kris Bleakley, John Weidman and Matthew Kendora

  Super FX x86 assembler emulator code 
  (c) Copyright 1998 - 2003 zsKnight, _Demo_, and pagefault 

  Super FX C emulator code 
  (c) Copyright 1997 - 1999 Ivar, Gary Henderson and John Weidman


  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004 Marcus Comstedt (marcus@mc.pp.se) 

 
  Specific ports contains the works of other authors. See headers in
  individual files.
 
  Snes9x homepage: http://www.snes9x.com
 
  Permission to use, copy, modify and distribute Snes9x in both binary and
  source form, for non-commercial purposes, is hereby granted without fee,
  providing that this license information and copyright notice appear with
  all copies and any derived work.
 
  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software.
 
  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes
  charging money for Snes9x or software derived from Snes9x.
 
  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.
 
  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
*******************************************************************************/

#ifndef _DSP1_H_
#define _DSP1_H_

extern void  (*SetDSP)(uint8, uint16);
extern uint8 (*GetDSP)(uint16);

void  DSP1SetByte(uint8 byte, uint16 address);
uint8 DSP1GetByte(uint16 address);

void  DSP2SetByte(uint8 byte, uint16 address);
uint8 DSP2GetByte(uint16 address);

void  DSP3SetByte(uint8 byte, uint16 address);
uint8 DSP3GetByte(uint16 address);
void  DSP3_Reset();

void  DSP4SetByte(uint8 byte, uint16 address);
uint8 DSP4GetByte(uint16 address);

// Simple vector and matrix types
//typedef float MATRIX[3][3];
//typedef float VECTOR[3];

//enum AttitudeMatrix { MatrixA, MatrixB, MatrixC };

struct SDSP1 {
	uint8 	version;
	uint32	boundary;
	bool8	waiting4command;
	bool8	first_parameter;
	uint8	command;
	uint32	in_count;
	uint32	in_index;
	uint32	out_count;
	uint32	out_index;
	uint8	parameters[512];
	uint8	output[512];

	int16	CentreX;
	int16	CentreY;
	int16	VOffset;

	int16	VPlane_C;
	int16	VPlane_E;

	// Azimuth and Zenith angles
	int16	SinAas;
	int16	CosAas;
	int16	SinAzs;
	int16	CosAzs;

	// Clipped Zenith angle
	int16	SinAZS;
	int16	CosAZS;
	int16	SecAZS_C1;
	int16	SecAZS_E1;
	int16	SecAZS_C2;
	int16	SecAZS_E2;

	int16	Nx;
	int16	Ny;
	int16	Nz;
	int16	Gx;
	int16	Gy;
	int16	Gz;
	int16	C_Les;
	int16	E_Les;
	int16	G_Les;

	int16	matrixA[3][3];
	int16	matrixB[3][3];
	int16	matrixC[3][3];

	int16	Op00Multiplicand;
	int16	Op00Multiplier;
	int16	Op00Result;

	int16	Op20Multiplicand;
	int16	Op20Multiplier;
	int16	Op20Result;

	int16	Op10Coefficient;
	int16	Op10Exponent;
	int16	Op10CoefficientR;
	int16	Op10ExponentR;

	int16	Op04Angle;
	int16	Op04Radius;
	int16	Op04Sin;
	int16	Op04Cos;

	int16	Op0CA;
	int16	Op0CX1;
	int16	Op0CY1;
	int16	Op0CX2;
	int16	Op0CY2;

	int16	Op02FX;
	int16	Op02FY;
	int16	Op02FZ;
	int16	Op02LFE;
	int16	Op02LES;
	int16	Op02AAS;
	int16	Op02AZS;
	int16	Op02VOF;
	int16	Op02VVA;
	int16	Op02CX;
	int16	Op02CY;

	int16	Op0AVS;
	int16	Op0AA;
	int16	Op0AB;
	int16	Op0AC;
	int16	Op0AD;

	int16	Op06X;
	int16	Op06Y;
	int16	Op06Z;
	int16	Op06H;
	int16	Op06V;
	int16	Op06M;

	int16	Op01m;
	int16	Op01Zr;
	int16	Op01Xr;
	int16	Op01Yr;

	int16	Op11m;
	int16	Op11Zr;
	int16	Op11Xr;
	int16	Op11Yr;

	int16	Op21m;
	int16	Op21Zr;
	int16	Op21Xr;
	int16	Op21Yr;

	int16	Op0DX;
	int16	Op0DY;
	int16	Op0DZ;
	int16	Op0DF;
	int16	Op0DL;
	int16	Op0DU;

	int16	Op1DX;
	int16	Op1DY;
	int16	Op1DZ;
	int16	Op1DF;
	int16	Op1DL;
	int16	Op1DU;

	int16	Op2DX;
	int16	Op2DY;
	int16	Op2DZ;
	int16	Op2DF;
	int16	Op2DL;
	int16	Op2DU;

	int16	Op03F;
	int16	Op03L;
	int16	Op03U;
	int16	Op03X;
	int16	Op03Y;
	int16	Op03Z;

	int16	Op13F;
	int16	Op13L;
	int16	Op13U;
	int16	Op13X;
	int16	Op13Y;
	int16	Op13Z;

	int16	Op23F;
	int16	Op23L;
	int16	Op23U;
	int16	Op23X;
	int16	Op23Y;
	int16	Op23Z;

	int16	Op14Zr;
	int16	Op14Xr;
	int16	Op14Yr;
	int16	Op14U;
	int16	Op14F;
	int16	Op14L;
	int16	Op14Zrr;
	int16	Op14Xrr;
	int16	Op14Yrr;

	int16	Op0EH;
	int16	Op0EV;
	int16	Op0EX;
	int16	Op0EY;

	int16	Op0BX;
	int16	Op0BY;
	int16	Op0BZ;
	int16	Op0BS;

	int16	Op1BX;
	int16	Op1BY;
	int16	Op1BZ;
	int16	Op1BS;

	int16	Op2BX;
	int16	Op2BY;
	int16	Op2BZ;
	int16	Op2BS;

	int16	Op28X;
	int16	Op28Y;
	int16	Op28Z;
	int16	Op28R;

	int16	Op1CX;
	int16	Op1CY;
	int16	Op1CZ;
	int16	Op1CXBR;
	int16	Op1CYBR;
	int16	Op1CZBR;
	int16	Op1CXAR;
	int16	Op1CYAR;
	int16	Op1CZAR;
	int16	Op1CX1;
	int16	Op1CY1;
	int16	Op1CZ1;
	int16	Op1CX2;
	int16	Op1CY2;
	int16	Op1CZ2;

	uint16	Op0FRamsize;
	uint16	Op0FPass;

	int16	Op2FUnknown;
	int16	Op2FSize;

	int16	Op08X;
	int16	Op08Y;
	int16	Op08Z;
	int16	Op08Ll;
	int16	Op08Lh;

	int16	Op18X;
	int16	Op18Y;
	int16	Op18Z;
	int16	Op18R;
	int16	Op18D;

	int16	Op38X;
	int16	Op38Y;
	int16	Op38Z;
	int16	Op38R;
	int16	Op38D;
};


START_EXTERN_C
void S9xResetDSP1 ();

//#define S9xGetDSP(Address) DSP1GetByte(Address)
//#define S9xSetDSP(Byte, Address) DSP1SetByte(Byte, Address)
uint8 S9xGetDSP (uint16 Address);
void S9xSetDSP (uint8 Byte, uint16 Address);
END_EXTERN_C

#ifndef __GP32__ 
extern struct SDSP1 DSP1;
#else
EXTERN_C struct SDSP1 DSP1;
#endif

#endif
