#include "player.h"

void player::processInput(const uint8_t* pKeystate, float deltaTime, int relX)
{
	vec2 wishdir = vec2();
	if(pKeystate[SDL_SCANCODE_W])
	{
		wishdir = wishdir.add(vec2(0, 1).rotate(getRotation()));
	}
	if(pKeystate[SDL_SCANCODE_S])
	{
		wishdir = wishdir.add(vec2(0, -1).rotate(getRotation()));
	}
	if(pKeystate[SDL_SCANCODE_D])
	{
		wishdir = wishdir.add(vec2(1, 0).rotate(getRotation()));
	}
	if(pKeystate[SDL_SCANCODE_A])
	{
		wishdir = wishdir.add(vec2(-1, 0).rotate(getRotation()));
	}

	setVelocity(wishdir.normalize());

    rotate(- float(relX) / 180 * SENSITIVITY);
}