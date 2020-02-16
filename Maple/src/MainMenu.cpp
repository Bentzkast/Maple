#include "Maple.h"
#include "Game_Internal.h"
#include "MainMenu.h"
#include <memory.h>
#include <stdio.h>

// TODO check mouse pos...
internal int hot_button = 0;

internal Asset_Handle text_asset_handle_title = { AT_INVALID ,0 };
internal Asset_Handle text_asset_handle_play = { AT_INVALID ,0 };
internal Asset_Handle text_asset_handle_exit = { AT_INVALID ,0 };

void MainMenuStart() {
	char game_title_text[] = "Maple";
	char play_text[] = "Play Game";
	char exit_text[] = "Exit Game";
	AssetFontCreate(&text_asset_handle_title, "Data/Font/Futured.ttf", 50, game_title_text);
	AssetFontCreate(&text_asset_handle_play, "Data/Font/Futured.ttf", 25, play_text, Maple_Color{ 200,200,200,255 });
	AssetFontCreate(&text_asset_handle_exit, "Data/Font/Futured.ttf", 25, exit_text, Maple_Color{ 200,200,200,255 });
}

Game_State MainMenuSimulate(float delta_time) {
	if (InputKeyStateGet(K_UP) == KS_Pressed) {
		hot_button = (hot_button - 1) < 0 ? 1 : (hot_button - 1);
	}
	if (InputKeyStateGet(K_DOWN) == KS_Pressed) {
		hot_button = (hot_button + 1) % 2;
	}

	if (InputKeyStateGet(K_FIRE1) == KS_Pressed) {
		switch (hot_button)
		{
		case 0: {
			return GS_GAMEPLAY;
		} break;
		case 1: {
			return GS_EXIT;
		} break;
		default:
			break;
		}
	}


	Vec2 screen_size = WindowGetScreenSize();

	RendererDrawColorSet(180, 180, 180, 255);
	// Window - TODO optimize double draw...?
	RendererPixelRectDraw(10, 10, screen_size.x - 20, screen_size.y - 20);

	// Title 
	RendererTextAssetDraw(screen_size.x / 2, screen_size.y / 4, text_asset_handle_title);
	// Buttons - TODO maybe a relative to screen size...


	Vec2 button_size = { 100, 25 };
	Vec2 button_pos = UtilsVecScale(screen_size, 0.5f);


	// Play
	RendererDrawColorSet(50, 50, 50, 255);
	if (hot_button == 0) {
		// Highlight
		RendererDrawColorSet(100, 100, 100, 255); // TTODO allow color passing ...
		RendererRectDraw(button_pos, UtilsVecAdd(button_size, Vec2{ 5,5 }));
	}
	else {
		RendererRectDraw(button_pos, button_size);
	}
	RendererTextAssetDraw(button_pos.x, button_pos.y, text_asset_handle_play);
	
	// Pad
	button_pos.y += 75;

	// Exit
	RendererDrawColorSet(50, 50, 50, 255);
	if (hot_button == 1) {
		// Highlight
		RendererDrawColorSet(100, 100, 100, 255); // TTODO allow color passing ...
		RendererRectDraw(button_pos, UtilsVecAdd(button_size, Vec2{ 5,5 }));
	}
	else {
		RendererRectDraw(button_pos, button_size);
	}
	RendererTextAssetDraw(button_pos.x, button_pos.y, text_asset_handle_exit);

	return GS_MAIN_MENU;
}