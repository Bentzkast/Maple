#include "Maple.h"
// Utility vec, rect etc...
internal uint32_t nLehmer = 0;


Vec2 UtilsVecAdd(Vec2 v1, Vec2 v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
Vec2 UtilsVecSub(Vec2 v1, Vec2 v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}

Vec2 UtilsVecScale(Vec2 v, float scale) {
	return { v.x * scale, v.y * scale };
}

float UtilsLerp(float v1, float v2, float value) {
	return (1 - value) * v1 + value * v2;
}

Vec2 LerpVec(Vec2 v1, Vec2 v2, float value) {
	return Vec2{ UtilsLerp(v1.x,v2.x,value), UtilsLerp(v1.y,v2.y,value) };
}

uint32_t LehmerRandom() {
	nLehmer += 0xe1206fc15;
	uint64_t temp = (uint64_t)nLehmer * 0x4a39b70d;
	uint32_t m1 = (temp >> 32) ^ temp;
	temp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (temp >> 32) ^ temp;

	return m2;
}

int UtilsRandInt(int min, int max) {
	return (LehmerRandom() % (max - min)) + min;
}

double UtilsRandDouble(double min, double max)
{
	return ((double)LehmerRandom() / (double)(0x7FFFFFFF)) * (max - min) + min;
}
