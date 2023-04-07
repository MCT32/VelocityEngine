#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include "vec2.h"

#define DEFAULT_POSITION vec2()
#define DEFAULT_ROTATION 0
#define DEFAULT_SIZE 0.5

extern uint8_t mapWidth, mapHeight;
extern uint8_t *map;

class entity
{
	vec2 position;
	float rotation;

	float size;

	vec2 velocity = vec2();

public:
	entity(float x, float y, float _rotation, float _size);
	entity(vec2 _position, float _rotation, float _size);
	entity(float x, float y, float _rotation);
	entity(vec2 _position, float _rotation);
	entity(float x, float y);
	entity(vec2 _position);
	entity();

	void setPosition(float x, float y);
	void setPosition(vec2 in);
	vec2 getPosition();

	void setRotation(float in);
	float getRotation();
	
	void setSize(float in);
	float getSize();

	void setVelocity(float x, float y);
	void setVelocity(vec2 in);
	vec2 getVelocity();

	void move(float x, float y);
	void move(vec2 delta);

	void moveAndCollide(vec2 delta);

	void rotate(float in);

	void update(float deltaTime);
};

#endif