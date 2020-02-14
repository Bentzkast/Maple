#pragma once
#include <stdint.h>

// Maple Engine API
#define internal static

// Input ----------------------------
enum Input_Key {
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_COUNT
};

enum Key_State {
	KS_None,
	KS_Pressed,
	KS_Hold,
	KS_Released,
	KS_Count
};

typedef struct {
	bool is_pressed[K_COUNT];
	bool was_pressed[K_COUNT];
} Input_State;


// Input ------------------------------------------------
extern Key_State InputKeyStateGet(Input_Key key);

// Utils-------------------------------------------------
typedef struct {
	float x; 
	float y;
} Vec2;

extern Vec2 UtilsVecAdd(Vec2 v1, Vec2 v2);
extern Vec2 UtilsVecSub(Vec2 v1, Vec2 v2);
extern Vec2 UtilsVecScale(Vec2 v, float scale);


// Renderer-------------------------------------------------------------
extern void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern void RendererPixelDraw(float x, float y, float w, float h);
extern void RendererPixelDraw(Vec2 pos, Vec2 size);

