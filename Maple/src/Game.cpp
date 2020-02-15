#include "Game.h"
#include <stdio.h>

// TODO WIN / LOSE(x) CONDITION....
// TODO SIMPLE BOSSS
// TODO MAIN MENU
// TODO SOUND
// TODO enemy projectile...

struct Player {
	Vec2 pos, vel, acc, half_size;
	float fire_rate;
	float timer;
	int hit_points;
};

struct Projectile {
	Vec2 pos, vel, acc, half_size;
};

struct Enemy {
	Vec2 pos, vel, acc, half_size;
	float fire_rate;
	float timer;
	int hit_points;
};


const int PROJECTILE_CAP = 60;
const int ENEMY_CAP = 60;

internal float left_kill_barrier = -1000;
internal float right_kill_barrier = 2000;

internal Player player = { 0 };
internal Projectile projectiles_player_array[PROJECTILE_CAP] = { 0 };
internal int active_projectile_player = 0;

internal Enemy enemies_array[ENEMY_CAP] = { 0 };
internal Projectile projectiles_enemy_array[PROJECTILE_CAP] = { 0 };
internal int active_projectile_enemies = 0;
internal int spawned_enemy = 0;
internal float enemy_wave_spawn_timer = 0;
internal float enemy_wave_spawn_rate = 0;
internal int enemy_wave_count = 0;

internal Enemy enemy_boss = { 0 };

// TODO create a proper game state, temporary solution..
internal bool is_game_over = false;

void GameStart() {
	player.pos = { 500,500 };
	player.half_size = { 15,10 };
	player.fire_rate = .257f;
	player.hit_points = 5;

	enemy_wave_spawn_rate = 8.f;

	// Spawn A wave....
	// TODO continuos spawning...
	EnemyWaveCreate(10);
}

// TODO maybe instead of seperate spawn routine..., over load this one....
void EnemyWaveCreate(int wavesize)
{
	for (int i = 0; i < wavesize; i++)
	{
		// random spawning...
		enemies_array[spawned_enemy].pos.y = UtilsRandInt(20, 650);
		enemies_array[spawned_enemy].pos.x = UtilsRandInt(1280, 1800);
		enemies_array[spawned_enemy].vel.x = -UtilsRandInt(100, 200);
		enemies_array[spawned_enemy].half_size = Vec2{ 20,10 };
		enemies_array[spawned_enemy].hit_points = 1;
		enemies_array[spawned_enemy].fire_rate = 0.75f;
		spawned_enemy++;
	}
	enemy_wave_count++;
}

void EnemyBossCreate(int level) {

	enemies_array[spawned_enemy].pos = Vec2 { 1500, 360 };
	enemies_array[spawned_enemy].vel.x = -50;
	enemies_array[spawned_enemy].half_size = Vec2{ 70,50 };
	enemies_array[spawned_enemy].hit_points = 30;
	enemies_array[spawned_enemy].fire_rate = 0.75f;
	spawned_enemy++;
}

void GameSimulate(float delta_time) {

	if (is_game_over) {
		RendererDrawColorSet(200, 200, 200, 255);
		RendererPixelRectDraw(10, 10, 1260, 700);
		// temporary game over screen
		return;
	}


	// Inputs.....
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

	// player update....
	player.acc = UtilsVecSub(player.acc, UtilsVecScale(player.vel, 10.f));
	player.vel = UtilsVecAdd(player.vel, UtilsVecScale(player.acc, delta_time));
	player.pos = UtilsVecAdd(UtilsVecAdd(player.pos, UtilsVecScale(player.vel, delta_time)), UtilsVecScale(player.acc, .5f * delta_time * delta_time));


	// Player shootting....
	if (player.timer < player.fire_rate) { player.timer += delta_time; }
	if (InputKeyStateGet(K_FIRE1) == KS_Hold && player.timer >= player.fire_rate) {
		printf("FIRE TIMER:%f\n", player.timer);
		// spawn new projectile from pool
		// FIRE routine...
		projectiles_player_array[active_projectile_player].pos = player.pos;
		projectiles_player_array[active_projectile_player].acc.x = 6000;
		//projectiles_array[current_active_projectile_index].vel.x = 300;

		active_projectile_player++;
		player.timer = 0;
	}


	RendererDrawColorSet(239, 116, 45, 255); // ORANGE...
	// Enemies
	Enemy* active_enemy_array[20] = { 0 };
	int active_enemy = 0;
	for (Enemy* enemy = enemies_array; enemy != (enemies_array + spawned_enemy); enemy++)
	{
		enemy->pos = UtilsVecAdd(enemy->pos, UtilsVecScale(enemy->vel, delta_time));

		// In screen
		if (enemy->pos.x < 1280 && enemy->pos.x > 0 && enemy->hit_points > 0) {
			active_enemy_array[active_enemy] = enemy;
			active_enemy++;
			RendererRectDraw(enemy->pos, enemy->half_size);
			// shoot stuff

			// FIRE routine
			if (enemy->timer < enemy->fire_rate) { enemy->timer += delta_time; }
			if (enemy->timer >= enemy->fire_rate) {
				projectiles_enemy_array[active_projectile_enemies].acc.x = -2500;
				projectiles_enemy_array[active_projectile_enemies].pos = enemy->pos;
				active_projectile_enemies++;
				enemy->timer = 0;
			}
		}
	}

	RendererDrawColorSet(200, 200, 20, 255); // YELLOW
	// projectile movement and draw
	for (int i = 0; i < active_projectile_player; i++)
	{
		projectiles_player_array[i].vel = UtilsVecAdd(projectiles_player_array[i].vel, UtilsVecScale(projectiles_player_array[i].acc, delta_time));
		Vec2 desired_pos = UtilsVecAdd(projectiles_player_array[i].pos, UtilsVecScale(projectiles_player_array[i].vel, delta_time));

		bool destroy_projectile = false;
		if (projectiles_player_array[i].pos.x > right_kill_barrier || projectiles_player_array[i].pos.x < left_kill_barrier) {
			destroy_projectile = true;
		}
		else {
			for (int e = 0; e < active_enemy; e++)
			{
				if (CollisionForceCheck(projectiles_player_array[i].pos, &desired_pos, projectiles_player_array[i].vel, Vec2{ 7.5,2.5 }, active_enemy_array[e]->pos, active_enemy_array[e]->half_size)) {
					destroy_projectile = true; // this could happen multiple time in this round, ie 2 enemy 1 shout.,..
					// reduce enemy hit point...
					active_enemy_array[e]->hit_points -= 1;
				}
			}
		}
		projectiles_player_array[i].pos = desired_pos;
		RendererRectDraw(projectiles_player_array[i].pos, Vec2{ 7.5,2.5 });

		// Last thing to do or weird teleport behaviour
		if (destroy_projectile) {
			projectiles_player_array[i] = projectiles_player_array[active_projectile_player - 1];
			active_projectile_player--;
			projectiles_player_array[active_projectile_player] = { 0 };
		}
	}

	RendererDrawColorSet(220, 20, 20, 255); // RED
	for (int i = 0; i < active_projectile_enemies; i++)
	{
		Projectile * projectile = projectiles_enemy_array + i;
		projectile->vel = UtilsVecAdd(projectile->vel, UtilsVecScale(projectile->acc, delta_time));
		Vec2 desired_pos = UtilsVecAdd(projectile->pos, UtilsVecScale(projectile->vel, delta_time));

		bool destroy_projectile = false;
		if (projectile->pos.x > right_kill_barrier || projectile->pos.x < left_kill_barrier) {
			destroy_projectile = true;
		}
		else {
			// Check collision with player...
			if (CollisionForceCheck(projectile->pos, &desired_pos, projectile->vel, Vec2{ 7.5,2.5 }, player.pos, player.half_size)) {
				destroy_projectile = true; // this could happen multiple time in this round, ie 2 enemy 1 shout.,..
				// reduce player hit point...
				player.hit_points -= 1;
			}
		}
		projectile->pos = desired_pos;
		RendererRectDraw(projectile->pos, Vec2{ 7.5,2.5 });

		// Last thing to do or weird teleport behaviour
		if (destroy_projectile) {
			projectiles_enemy_array[i] = projectiles_enemy_array[active_projectile_enemies - 1];
			active_projectile_enemies--;
			projectiles_enemy_array[active_projectile_enemies] = { 0 };
		}
	}

	// Check overlap...
	for( int i = 0; i < active_enemy; i++)
	{
		if (CollisionOverlapCheck(player.pos, player.half_size, active_enemy_array[i]->pos, active_enemy_array[i]->half_size)) {
			player.hit_points--;

		}
	}

	// Check player dead
	if (player.hit_points <= 0) {
		is_game_over = true;
	}

	//TODO KILL & recycle enemy...
	for (int i = 0; i < spawned_enemy; i++) {
		if (enemies_array[i].hit_points <= 0 || enemies_array[i].pos.x > right_kill_barrier || enemies_array[i].pos.x < left_kill_barrier) {
			enemies_array[i] = enemies_array[spawned_enemy - 1];
			spawned_enemy--;
			enemies_array[spawned_enemy] = { 0 };
		}
	}


	//printf("[Deltatime] %f\n", delta_time);
	//printf("[LehmerRandom] %d\n", UtilsRandInt(1,10));
	// TODO PERF CONSOLE...
	printf("[active_projectile/cap] %d / %d", active_projectile_player, PROJECTILE_CAP);
	printf("[active_enemy/spawned_enemy/cap] %d / %d / %d\n", active_enemy,spawned_enemy,ENEMY_CAP);


	RendererDrawColorSet(20, 200, 20, 255); // GREEN

	RendererRectDraw(player.pos, player.half_size);

	if(enemy_wave_spawn_timer < enemy_wave_spawn_rate) enemy_wave_spawn_timer += delta_time;
	if (enemy_wave_spawn_timer >= enemy_wave_spawn_rate) {
		EnemyWaveCreate(UtilsRandInt(5, 10));
		enemy_wave_spawn_timer = 0;
	}
	if (enemy_wave_count == 3) {
		EnemyBossCreate(0);
		enemy_wave_count = 0;
	}
}