// primitive graphics for Hello World PSP
#ifndef __PG_H__
#define __PG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "psp/imageio.h"

//#include "syscall.h"

#define RGB(r,g,b) (short)((((b>>3) & 0x1F)<<10)|(((g>>3) & 0x1F)<<5)|(((r>>3) & 0x1F)<<0)|0x8000)
#define RGB_WHITE  RGB(255,255,255)
#define RGB_BLACK  RGB(0,0,0)
#define RGB_BLUE   RGB(0,0,255)
#define RGB_GREEN  RGB(0,255,0)
#define RGB_RED    RGB(255,0,0)
#define RGB_YELLOW RGB(255,255,0)

extern u32 new_pad, now_pad;

//480*272 = 60*34
#define CMAX_X 60
#define CMAX_Y 34
#define CMAX2_X 30
#define CMAX2_Y 17
#define CMAX4_X 15
#define CMAX4_Y 8

void ErrorMsg(const char *msg);
void pgwaitPress();
int get_pad(void);
int get_pad2(int *lx,int *ly);
void pgPrintCenter(unsigned long y,unsigned long color,const char *str);

void pgInit();
void pgWaitV();
void pgWaitVn(unsigned long count);
void pgScreenFrame(long mode,long frame);
void pgScreenFlip();
void pgScreenFlipV();
void pgScreenFlipV2();
void pgPrint(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrintSel(unsigned long x,unsigned long y,unsigned long color,char *str);
void pgPrintBG(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrintBGRev(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrintAllBG(unsigned long x,unsigned long y,unsigned long color,const char *str);
void pgPrint4(unsigned long x,unsigned long y,unsigned long color,unsigned long color2,const char *str);
void pgFillvram(unsigned long color);
void pgFillAllvram(unsigned long color);

void pgCopyScreen(void);

void pgDrawFrame(unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2, unsigned long color);
void pgFillBox(unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2, unsigned long color);

char *pgGetVramAddr(unsigned long x,unsigned long y);


void pgMain(unsigned long args, void *argp);

void readpad(void);

void mh_print(int x,int y,const char *str,int col);
void mh_printLimit(int x,int y,int Mx,int My,const char *str,int col);

void mh_print_light(int x,int y,const char *str,int col,int smoothing);
int mh_print_buffVert(int x,int y,int Mx,int My,const char *str,int col,unsigned short *vbuff,int pitch);
void mh_printSel(int x,int y,const char *str,int col);
void mh_printSel_light(int x,int y,const char *str,int col,int smoothing);
void mh_printCenter(unsigned long y,const char *str,unsigned long color);
int mh_length(const char *str);
int mh_trimlength(const char *str);

void pgFillBoxHalfer(unsigned long x1, unsigned long y1, unsigned long x2, unsigned long y2 );

void image_put(int x0,int y0,IMAGE* img,int fade,int add,int transp_col,int sz);
void image_put_light(int x0,int y0,IMAGE* img,int fade,int add,int transp_col,int smooth);
void image_put_mul(int x0,int y0,IMAGE* img,int mul,int add);

extern u32 now_tick;

//optimize
#ifndef WIN32
//long配列をコピー。配列境界は4バイトアラインされている必要あり
static inline void __memcpy4(void *d, void *s, unsigned long c)
{
	unsigned long *dl=(unsigned long *)d;
	unsigned long *sl=(unsigned long *)s;
	for (; c; --c) *dl++=*sl++;
}


//long配列にセット。配列境界は4バイトアラインされている必要あり
static inline void __memset4(void *d, unsigned long v, unsigned long c)
{	
	unsigned long *dl=(unsigned long *)d;		
	for (; c; --c) *dl++=v;
}


//long配列をコピー。配列境界は4バイトアラインされている必要あり
//コンパイラの最適化によって予期しないコードが生成されるため、十分に注意のこと。
static inline void __memcpy4aa(void *d, void *s, unsigned long c)
{
	unsigned long wk0,wk1,wk2,wk3;

	asm volatile (
		"		.set	push"				"\n"
		"		.set	noreorder"			"\n"

		"		move	%1,%4 "				"\n"
		"		move	%2,%5 "				"\n"
		"		move	%3,%6 "				"\n"

		"1:		lw		%0,0(%2) "			"\n"
		"		addiu	%3,%3,-1 "			"\n"
		"		addiu	%2,%2,4 "			"\n"
		"		sw		%0,0(%1) "			"\n"
		"		bnez	%3,1b "				"\n"
		"		addiu	%1,%1,4 "			"\n"

		"		.set	pop"				"\n"

			:	"=&r" (wk0),	// %0
				"=&r" (wk1),	// %1
				"=&r" (wk2),	// %2
				"=&r" (wk3)		// %3
			:	"r" (d),		// %4
				"r" (s),		// %5
				"r" (c)			// %6
	);
}

//long配列をコピー。配列境界は4バイトアラインされている必要あり
//s,dは参照渡し扱いになるので、リターン後は変更されていると考えたほうが良い
//コンパイラの最適化によって予期しないコードが生成されるため、十分に注意のこと。__memcpy4のほうが安全。
//といいますかcで書いても全然変わらないような。ｶﾞﾝｶﾞｯﾀのに。
static inline void __memcpy4a(unsigned long *d, unsigned long *s, unsigned long c)
{
	unsigned long wk,counter;

	asm volatile (
		"		.set	push"				"\n"
		"		.set	noreorder"			"\n"

		"		move	%1,%4 "				"\n"
		"1:		lw		%0,0(%3) "			"\n"
		"		addiu	%1,%1,-1 "			"\n"
		"		addiu	%3,%3,4 "			"\n"
		"		sw		%0,0(%2) "			"\n"
		"		bnez	%1,1b "				"\n"
		"		addiu	%2,%2,4 "			"\n"

		"		.set	pop"				"\n"

			:	"=&r" (wk),		// %0
				"=&r" (counter)	// %1
			:	"r" (d),		// %2
				"r" (s),		// %3
				"r" (c)			// %4
	);
}

#endif


static inline void cpy2x(unsigned long *d, unsigned long cc)
{
#ifdef __USE_MIPS32R2__
	unsigned long wk0;
	asm volatile (
		"		.set	push"				"\n"
		"		.set	noreorder"			"\n"

		"		.set	mips32r2"			"\n"
		
		"		srl		%0,%2,16"			"\n"
		"		ins 	%2,%2,16,16"		"\n"
		"		sw		%2,0(%1)"			"\n"
		"		ins 	%0,%0,16,16"		"\n"
		"		sw		%0,4(%1)"			"\n"
		
		"		.set	pop"				"\n"
		
			:	"=&r" (wk0)		// %0
			:	"r" (d),		// %1
				"r" (cc)		// %2
	);
#else
	*d      = (cc&0x0000ffff)|(cc<<16);
	*(d+1)  = (cc>>16)|(cc&0xffff0000);
#endif
}


void pgPrintDec(int x,int y,short col,unsigned int dec);


void pgMemClr(void* ptr,int size);
void pgMemCpy(void* dst,void* src,int size);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
