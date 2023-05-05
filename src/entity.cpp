#include "entity.h"

entity::entity(float x, float y, float rotation, float size): position(vec2(x, y)), rotation(rotation), size(size){}

entity::entity(vec2 position, float rotation, float size): position(position), rotation(rotation), size(size){}

entity::entity(float x, float y, float rotation): position(vec2(x, y)), rotation(rotation), size(DEFAULT_SIZE){}

entity::entity(vec2 position, float rotation): position(position), rotation(rotation), size(DEFAULT_SIZE){}

entity::entity(float x, float y): position(vec2(x, y)), rotation(DEFAULT_ROTATION), size(DEFAULT_SIZE){}

entity::entity(vec2 position): position(position), rotation(DEFAULT_ROTATION), size(DEFAULT_SIZE){}

entity::entity(): position(DEFAULT_POSITION), rotation(DEFAULT_ROTATION), size(DEFAULT_SIZE){}

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

void entity::setVelocity(float x, float y)
{
  velocity = vec2(x, y);
}

void entity::setVelocity(vec2 in)
{
  velocity = in;
}

vec2 entity::getVelocity()
{
  return velocity;
}

void entity::move(float x, float y)
{
	position = position.add(vec2(x, y));
}

void entity::move(vec2 delta)
{
	position = position.add(delta);
}

void entity::moveAndCollide(vec2 delta)
{
  move(delta);
  int x = floor(position.x);
  int y = floor(position.y);

  // +x
  if(x < mapWidth - 1 && map[x + 1 + y * mapWidth])
  {
    if(position.x + size / 2 > x + 1)
    {
      position.x = x + 1 - size / 2;

      if(velocity.x > 0) velocity.x = 0;
    }
  }

  // -x
  if(x > 0 && map[x - 1 + y * mapWidth])
  {
    if(position.x - size / 2 < x)
    {
      position.x = x + size / 2;

      if(velocity.x < 0) velocity.x = 0;
    }
  }

  // +y
  if(y < mapHeight - 1 && map[x + (y + 1) * mapWidth])
  {
    if(position.y + size / 2 > y + 1)
    {
      position.y = y + 1 - size / 2;

      if(velocity.y > 0) velocity.y = 0;
    }
  }

  // -y
  if(y > 0 && map[x + (y - 1) * mapWidth])
  {
    if(position.y - size / 2 < y)
    {
      position.y = y + size / 2;

      if(velocity.y < 0) velocity.y = 0;
    }
  }

  // +x +y
  if(x < mapWidth - 1 && y < mapHeight - 1 && map[x + 1 + (y + 1) * mapWidth])
  {
    if(x + 1 - position.x >= y + 1 - position.y)
    {
      if(position.x + size / 2 > x + 1)
      {
        position.x = x + 1 - size / 2;

        if(velocity.x > 0) velocity.x = 0;
      }
    } else {
      if(position.y + size / 2 > y + 1)
      {
        position.y = y + 1 - size / 2;

        if(velocity.y > 0) velocity.y = 0;
      }
    }
  }

  // -x +y
  if(x > 0 - 1 && y < mapHeight - 1 && map[x - 1 + (y + 1) * mapWidth])
  {
    if(position.x - x >= y + 1 - position.y)
    {
      if(position.x - size / 2 < x)
      {
        position.x = x + size / 2;

        if(velocity.x < 0) velocity.x = 0;
      }
    } else {
      if(position.y + size / 2 > y + 1)
      {
        position.y = y + 1 - size / 2;

        if(velocity.y > 0) velocity.y = 0;
      }
    }
  }

  // +x -y
  if(x < mapWidth - 1 && y > 0 && map[x + 1 + (y - 1) * mapWidth])
  {
    if(x + 1 - position.x >= position.y - y)
    {
      if(position.x + size / 2 > x + 1)
      {
        position.x = x + 1 - size / 2;

        if(velocity.x > 0) velocity.x = 0;
      }
    } else {
      if(position.y - size / 2 < y)
      {
        position.y = y + size / 2;

        if(velocity.y < 0) velocity.y = 0;
      }
    }
  }

  // -x -y
  if(x > 0 && y > 0 && map[x - 1 + (y - 1) * mapWidth])
  {
    if(position.x - x >= position.y - y)
    {
      if(position.x - size / 2 < x)
      {
        position.x = x + size / 2;

        if(velocity.x < 0) velocity.x = 0;
      }
    } else {
      if(position.y - size / 2 < y)
      {
        position.y = y + size / 2;

        if(velocity.y < 0) velocity.y = 0;
      }
    }
  }
}

void entity::rotate(float in)
{
  rotation += in;
}

void entity::update(float deltaTime)
{
  moveAndCollide(velocity.mul(deltaTime));
}
