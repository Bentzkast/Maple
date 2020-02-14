#include <SDL.h>
#include "Maple.h"
extern SDL_Renderer* sdl_renderer;

void RendererDrawColorSet(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, a);
}

void RendererPixelDraw(Vec2 pos, Vec2 size) {
	RendererPixelDraw(pos.x, pos.y, size.x, size.y);
}

void RendererPixelDraw(float x, float y, float w, float h) {
	SDL_Rect rect{ x,y,w,h };
	SDL_RenderFillRect(sdl_renderer, &rect);
}