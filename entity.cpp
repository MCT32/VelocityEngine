#include "entity.h"

entity::entity(float x, float y, float _rotation, float _size)
{
	position = vec2(x, y);
	rotation = _rotation;

	size = _size;
}

entity::entity(vec2 _position, float _rotation, float _size)
{
	position = _position;
	rotation = _rotation;

	size = _size;
}

entity::entity(float x, float y, float _rotation)
{
	position = vec2(x, y);
	rotation = _rotation;

	size = DEFAULT_SIZE;
}

entity::entity(vec2 _position, float _rotation)
{
	position = _position;
	rotation = _rotation;

	size = DEFAULT_SIZE;
}

entity::entity(float x, float y)
{
	position = vec2(x, y);
	rotation = DEFAULT_ROTATION;

	size = DEFAULT_SIZE;
}

entity::entity(vec2 _position)
{
	position = _position;
	rotation = DEFAULT_ROTATION;

	size = DEFAULT_SIZE;
}

entity::entity()
{
	position = DEFAULT_POSITION;
	rotation = DEFAULT_ROTATION;

	size = DEFAULT_SIZE;
}

void entity::setPosition(float x, float y)
{
	position = vec2(x, y);
}

void entity::setPosition(vec2 in)
{
	position = in;
}

vec2 entity::getPosition()
{
	return position;
}

void entity::setRotation(float in)
{
	rotation = in;
}

float entity::getRotation()
{
	return rotation;
}

void entity::setSize(float in)
{
	size = in;
}

float entity::getSize()
{
	return size;
}

void entity::move(float x, float y)
{
	position = position.add(vec2(x, y));
}

void entity::move(vec2 delta)
{
	position = position.add(delta);
}