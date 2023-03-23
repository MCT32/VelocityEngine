#ifndef VEC2_H
#define VEC2_H 1

#include <math.h>

class vec2
{
public:
	float x, y;

	vec2(float ix, float iy) : x(ix), y(iy)
	{}

	vec2() : x(0), y(0)
	{}

	float length()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	vec2 normalize()
	{
		float len = length();
		return vec2(x / len, y / len);
	}

	vec2 rotate(float angle)
	{
		return vec2(x*cos(angle) - y*sin(angle), x*sin(angle) + y*cos(angle));
	}

	vec2 add(vec2 other)
	{
		return vec2(x + other.x, y + other.y);
	}

	vec2 sub(vec2 other)
	{
		return vec2(x - other.x, y - other.y);
	}

	vec2 mul(float value)
	{
		return vec2(x * value, y * value);
	}
};

#endif