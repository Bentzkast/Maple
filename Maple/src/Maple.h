#pragma once
#include <stdint.h>

// Maple Engine API
#define internal static
#define count(a) (sizeof(a) / sizeof(a[0]))

// Color

union Maple_Color{
	struct {
		uint8_t alpha;
		uint8_t blue;
		uint8_t green;
		uint8_t red;
	};
	uint32_t color = 0x000000FF;
};

// Asset -------------
enum Asset_Type {
	AT_INVALID,
	AT_FONT,
	AT_SPRITE,
	AT_AUDIO,
	AT_COUNT
};

typedef struct  {
	Asset_Type asset_type;
	int id;
} Asset_Handle;


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

extern Key_State InputKeyStateGet(Input_Key key);

// Utils-------------------------------------------------

typedef struct {
	float x; 
	float y;
} Vec2;

typedef struct {
	float x;
	float y;
	float w;
	float h;
} Rect;

extern Vec2 UtilsVecAdd(Vec2 v1, Vec2 v2);
extern Vec2 UtilsVecSub(Vec2 v1, Vec2 v2);
extern Vec2 UtilsVecScale(Vec2 v, float scale);
extern float UtilsLerp(float v1, float v2, float value);
extern int UtilsRandInt(int min, int max);
extern double UtilsRandDouble(double min, double max);
extern void UtilsSeedSet(uint32_t seed);

// Renderer-------------------------------------------------------------

extern void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern void RendererPixelRectDraw(float x, float y, float w, float h);
extern void RendererRectDraw(Vec2 pos, Vec2 size);

extern void RendererTextAssetDraw(float x, float y, Asset_Handle asset_handle);


// Collision ---------------------------------

extern bool CollisionOverlapCheck(Vec2 p1, Vec2 half_size1, Vec2 p2, Vec2 half_size2);
extern bool CollisionForceCheck(Vec2 p1, Vec2* next_p1, Vec2 vel1, Vec2 half_size_1, Vec2 p2, Vec2 half_size_2);

// Window

extern Vec2 WindowGetScreenSize();
extern void WindowClose();

// Asset
extern bool AssetFontCreate(Asset_Handle* handle, const char * path, int font_size, char * text, Maple_Color color = {});
