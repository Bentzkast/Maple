#include "Maple.h"
// Utility vec, rect etc...

Vec2 UtilsVecAdd(Vec2 v1, Vec2 v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
Vec2 UtilsVecSub(Vec2 v1, Vec2 v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}

Vec2 UtilsVecScale(Vec2 v, float scale) {
	return { v.x * scale, v.y * scale };
}