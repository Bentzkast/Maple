#pragma once
#include <stdint.h>

// Maple Engine API
#define internal static
#define count(a) (sizeof(a) / sizeof(a[0]))

// Input ----------------------------
enum Input_Key {
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_FIRE1,
	K_FIRE2,
	K_ITEM,
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
extern float UtilsLerp(float v1, float v2, float value);
extern int UtilsRandInt(int min, int max);
extern double UtilsRandDouble(double min, double max);

// Renderer-------------------------------------------------------------
extern void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern void RendererPixelRectDraw(float x, float y, float w, float h);
extern void RendererRectDraw(Vec2 pos, Vec2 size);

// Collision ---------------------------------
extern bool CollisionOverlapCheck(Vec2 p1, Vec2 half_size1, Vec2 p2, Vec2 half_size2);
extern bool CollisionForceCheck(Vec2 p1, Vec2* next_p1, Vec2 vel1, Vec2 half_size_1, Vec2 p2, Vec2 half_size_2);