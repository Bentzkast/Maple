#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

typedef struct {
	TTF_Font* font;
	SDL_Texture* texture;
} Font_Asset;

Font_Asset AssetFontGet(Asset_Handle handle);