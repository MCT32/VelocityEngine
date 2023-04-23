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

	accelerate(wishdir.normalize(), deltaTime);

    rotate(- float(relX) / 180 * SENSITIVITY);
}

void player::accelerate(vec2 wishdir, float deltaTime)
{
	friction(deltaTime);

	float current_speed = getVelocity().dot(wishdir);
	float add_speed = clip(MAX_SPEED - current_speed, 0.0f, MAX_ACCEL * deltaTime);

	setVelocity(getVelocity().add(wishdir.mul(add_speed)));
}

void player::friction(float deltaTime)
{
	float speed = getVelocity().length();
	if(!speed) return;

	float control = speed < STOPSPEED ? STOPSPEED : speed;
	float newspeed = speed - deltaTime * control * FRICTION;

	if(newspeed < 0) newspeed = 0;
	newspeed /= speed;

	setVelocity(getVelocity().mul(newspeed));
}