#include <SDL.h>
#include "Maple.h"
extern SDL_Renderer* sdl_renderer;

void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
}

void RendererRectDraw(Vec2 pos, Vec2 half_size) {
	RendererPixelRectDraw(pos.x - half_size.x, pos.y - half_size.y, half_size.x * 2.f, half_size.y * 2.f);
}


void RendererPixelRectDraw(float x, float y, float w, float h) {
	SDL_Rect rect{ x,y,w,h };
	SDL_RenderFillRect(sdl_renderer, &rect);
}