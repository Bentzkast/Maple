#include "Maple.h"
#include "Maple_Internal.h"

extern SDL_Renderer* sdl_renderer;

internal Font_Asset loaded_fonts[100] = { NULL };
internal int active_loaded_font = 0;
internal int handle_id_to_font_asset[100] = { 0 };
internal int active_handle_id_count = 0;

// TODO clean...

bool AssetFontCreate(Asset_Handle* handle, const char * path, int font_size, char * text, Maple_Color color) {
	if (active_loaded_font >= 100) {
		SDL_Log("Full Capacity");
		handle->asset_type = AT_INVALID;
		handle->id = 0;
		return false;
	}

	TTF_Font* loaded_font = TTF_OpenFont(path, font_size);
	if (loaded_font == NULL) {
		SDL_Log("Could not load font: %s\n", TTF_GetError());
		handle->asset_type = AT_INVALID;
		handle->id = 0;
		return false;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(loaded_font, text, SDL_Color{ color.red,color.green,color.blue,color.alpha });
	if (text_surface == NULL) {
		SDL_Log("Could create surface: %s\n", TTF_GetError());
		handle->asset_type = AT_INVALID;
		handle->id = 0;
		return false;
	}
	SDL_Texture* loaded_texture = SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
	if (loaded_texture == NULL) {
		SDL_Log("Could not convert surface to texture: %s\n", TTF_GetError());
		handle->asset_type = AT_INVALID;
		handle->id = 0;
		return false;
	}
	SDL_FreeSurface(text_surface);


	handle->asset_type = AT_FONT;
	handle->id = active_handle_id_count;
	
	handle_id_to_font_asset[active_handle_id_count] = active_loaded_font;
	active_handle_id_count++;
	



	loaded_fonts[active_loaded_font].font = loaded_font;
	loaded_fonts[active_loaded_font].texture = loaded_texture;
	active_loaded_font++;


	return true;
}

Font_Asset AssetFontGet(Asset_Handle handle) {
	// No check...
	return loaded_fonts[handle_id_to_font_asset[handle.id]];
}

void AssetFontDelete(Asset_Handle* handle) {


	int font_asset_id = handle_id_to_font_asset[handle->id];
	// FIXME memory leak, programming pattern pool, union of list and linked list..
	// Problem with handle...
	// delete asset
	//loaded_fonts[font_asset_id] = pro

	// delete handle
	//handle_id_to_font_asset[]




	//loaded_fonts[handle->id] = loaded_fonts[]
}