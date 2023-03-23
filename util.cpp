#include "util.h"

/*
  Function: lerp
  Purpose: Linearly interpolate variables.

  Parameters:
    v1: First value of interpolation.
    v2: Second value of interpolation.
    fac: Interpolation factor.
  Returns: Interpolated value.
*/
template<typename T>
T lerp(T v1, T v2, float fac)
{
  return v1 * fac + v2 * (1 - fac);
}

/*
  Function: lerp_color
  Purpose: Linearly interpolate colors.

  Parameters:
    v1: First color of interpolation.
    v2: Second color of interpolation.
    fac: Interpolation factor.
  Returns: Interpolated color.
*/
color lerp_color(color v1, color v2, float fac)
{
  return color {lerp(v1.alpha, v2.alpha, fac), lerp(v1.red, v2.red, fac), lerp(v1.green, v2.green, fac), lerp(v1.blue, v2.blue, fac)};
}

/*
  Function: raycast
  Purpose: Casts a ray until it hits a wall.

  Parameters:
    start: Origin of the ray.
    dir: Direction of the ray.
    range: Distance ray is allowed to travel.
    end: Position of intersection.
    dist: Distance ray traveled.
    wall: Type of wall the ray hit.
    normal: Normal axis of the face that was hit.
  Returns: True if ray hit wall, otherwise false.
*/
bool raycast(vec2 start, vec2 dir, float range, vec2 &end, float &dist, uint8_t &wall, bool &normal)
{
  vec2 current = start;

  int cellX = floor(start.x);
  int cellY = floor(start.y);

  float tempdist = 0;

  while(true)
  {
    float dx, dy;

    if(dir.x > 0)
    {
      dx = (cellX + 1) - current.x;
    } else {
      dx = cellX - current.x;
    }

    if(dir.y > 0)
    {
      dy = (cellY + 1) - current.y;
    } else {
      dy = cellY - current.y;
    }

    float step;
    if(abs(dx / dir.x) <= abs(dy / dir.y))
    {
      step = dx / dir.x;

      if(dx > 0)
      {
        cellX++;
      } else {
        cellX--;
      }

      normal = false;
    } else {
      step = dy / dir.y;

      if(dy > 0)
      {
        cellY++;
      } else {
        cellY--;
      }

      normal = true;
    }

    tempdist += step;
    if(abs(tempdist) > range) return false;

    current.x += dir.x * step;
    current.y += dir.y * step;

    if(cellX >= 0 && cellY >= 0 && cellX < mapWidth && cellY < mapHeight)
    {
      if(map[cellX + cellY * mapWidth])
      {
        end = current;
        dist = abs(tempdist);
        wall = map[cellX + cellY * mapWidth];

        return true;
      }
    }
  }
}