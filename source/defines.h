#include <stdarg.h>

#define SDA 0x803e4d20

#define ADDR_FONT 0x81693cd8
#define ADDR_GFX 0x81729c40

#define DecToColor(r, g, b, a) (((r + 0x100) * 0x100 + g) * 0x100 + b) * 0x100 + a
#define DGXGraphics__texturePrintf(gfxunk, font, x, y, fmt, ...) 	DGXGraphics__texturePrintf(gfxunk, font, x, y, fmt __VA_OPT__(, ) __VA_ARGS__)
#define OSReport(...)  OSReport(__VA_ARGS__)

typedef unsigned char bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 1
#endif

#ifndef nullptr
#define nullptr 0
#endif

#define u32 unsigned int
#define s32 signed int
#define u16 signed short
#define s16 signed short
#define u8 unsigned char
#define s8 signed char

// Custom typedefs

typedef struct
{
	float x;
	float y;
	float z;
} Vector3f;

void drawAll3D(u32* unk);
u32* alloc(int allocsize);
u32* setupCamera(int allocSpace, u32* unk);
void updateManager(int mgrId);
void updateManagerAlternative(int mgrId);
void something(u32** obj);
void funcInSwingyWhoCares(u32* unk2, u32* unk3);

void memclear(char* zone, int size) {
	for (int i = 0; i < size; i++) {
		zone[i] = 0;
	}
}
void memcpy(char* paste, char* copy, int size) {
	for (int i = 0; i < size; i++) {
		paste[i] = copy[i];
	}
}
inline int SDAword(int offset) {
	int toReturn;
	__asm("lwz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int SDAshort(int offset) {
	int toReturn;
	__asm("lhz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int SDAbyte(int offset) {
	int toReturn;
	__asm("lbz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline void SDAstoreword(int offset, int val) {
	__asm("stw %0, %1(13)" :: "r" (val), "X" (offset));
}
inline void SDAstorehalf(int offset, int val) {
	__asm("sth %0, %1(13)" :: "r" (val), "X" (offset));
}
inline void SDAstorebyte(int offset, int val) {
	__asm("stb %0, %1(13)" :: "r" (val), "X" (offset));
}

inline int TOCword(int offset) {
	int toReturn;
	__asm("lwz %0, %1(2)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
