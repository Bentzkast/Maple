#include "Maple.h"

bool CollisionOverlapCheck(Vec2 p1, Vec2 half_size1, Vec2 p2, Vec2 half_size2) {
	if (p1.y - half_size1.y > p2.y + half_size2.y) return false;
	if (p1.y + half_size1.y < p2.y - half_size2.y) return false;
	if (p1.x - half_size1.x > p2.x + half_size2.x) return false;
	if (p1.x + half_size1.x < p2.x - half_size2.x) return false;
	return true;
}

bool
CollisionForceCheck(Vec2 p1, Vec2* next_p1, Vec2 vel1, Vec2 half_size_1, Vec2 p2, Vec2 half_size_2) {
	bool isColliding = false;

	{
		float diff = next_p1->y - p1.y;
		if (diff != 0) {
			float collision_point;
			if (vel1.y > 0) collision_point = p2.y - half_size_2.y - half_size_1.y;
			else collision_point = p2.y + half_size_2.y + half_size_1.y;
			float t_y = (collision_point - p1.y) / diff;
			if (t_y > 0 && t_y <= 1.f) {
				float target_x = UtilsLerp(p1.x, next_p1->x, t_y);
				if (target_x + half_size_1.x > p2.x - half_size_2.x && target_x - half_size_1.x < p2.x + half_size_2.x) {
					next_p1->y = UtilsLerp(p1.y, next_p1->y, t_y);
					isColliding = true;
				}
			}
		}
	}
	{
		float diff = next_p1->x - p1.x;
		if (diff != 0) {
			float collision_point;
			if (vel1.x > 0) collision_point = p2.x - half_size_2.x - half_size_1.x;
			else collision_point = p2.x + half_size_2.x + half_size_1.x;
			float t_x = (collision_point - p1.x) / diff;
			if (t_x > 0 && t_x <= 1.f) {
				float target_y = UtilsLerp(p1.y, next_p1->y, t_x);
				if (target_y + half_size_1.y > p2.y - half_size_2.y && target_y - half_size_1.y < p2.y + half_size_2.y) {
					next_p1->x = UtilsLerp(p1.x, next_p1->x, t_x);
					isColliding = true;
				}
			}
		}
	}

	return isColliding;
}