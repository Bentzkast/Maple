#include "Maple.h"
#include "Maple_Internal.h"

extern SDL_Renderer* sdl_renderer;

void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
}

void RendererRectDraw(Vec2 pos, Vec2 half_size) {
	RendererPixelRectDraw(pos.x - half_size.x, pos.y - half_size.y, half_size.x * 2.f, half_size.y * 2.f);
}


void RendererPixelRectDraw(float x, float y, float w, float h) {
	SDL_Rect rect{ static_cast<int>(x),static_cast<int>(y),static_cast<int>(w),static_cast<int>(h) };
	SDL_RenderFillRect(sdl_renderer, &rect);
}

// TODO free 
// TODO asset handle with type and id ...
void RendererTextAssetDraw(float x, float y, Asset_Handle handle) {
	if (handle.asset_type != AT_FONT) return;
	SDL_Texture* texture = AssetFontGet(handle).texture;

	SDL_Rect rect = { 0 };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x = (int)(x - rect.w / 2);
	rect.y = (int)(y - rect.h / 2);
	SDL_RenderCopy(sdl_renderer, texture, NULL, &rect);
}