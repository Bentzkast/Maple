#include "Game.h"

struct Player {
	Vec2 pos, vel, acc, size;
};

internal Player player = { 0 };

void GameStart() {
	player.pos = { 500,500 };
	player.size = { 30,20 };
}

void GameSimulate(float delta_time) {
	RendererDrawColorSet(200, 200, 200, 255);
	
	player.acc = { 0 };
	if (InputKeyStateGet(K_LEFT) == KS_Hold) {
		player.acc.x = -8000;
	}
	if (InputKeyStateGet(K_RIGHT) == KS_Hold) {
		player.acc.x = 8000;
	}
	if (InputKeyStateGet(K_UP) == KS_Hold) {
		player.acc.y = -8000;
	}
	if (InputKeyStateGet(K_DOWN) == KS_Hold) {
		player.acc.y = 8000;
	}
	player.acc = UtilsVecSub(player.acc, UtilsVecScale(player.vel, 10.f));
	player.vel = UtilsVecAdd(player.vel, UtilsVecScale(player.acc, delta_time));
	player.pos = UtilsVecAdd(UtilsVecAdd(player.pos, UtilsVecScale(player.vel, delta_time)), UtilsVecScale(player.acc, .5f * delta_time * delta_time));

	RendererPixelDraw(player.pos, player.size);
	RendererPixelDraw(Vec2{ 500,100 }, Vec2{ 50,50 });
}