#include "load.h"

/*
  Function: load_color
  Purpose: Loads a color from a binary file.

  Parameters:
    file: File to load from.
  Returns: Color loaded from file.
*/
color load_color(std::ifstream &file)
{
  char* buffer = new char[4 * sizeof(uint8_t)];
  file.read(&buffer[0], 4 * sizeof(uint8_t));

  return color {buffer[0], buffer[1], buffer[2], buffer[3]}; 
}

/*
  Function: load_float
  Purpose: Loads a float from a binary file.

  Parameters:
    file: File to load from.
  Returns: Float loaded from file.
*/
float load_float(std::ifstream &file)
{
  float buffer;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(float));

  return buffer;
}

/*
  Function: load_uint8_t
  Purpose: Loads a uint8_t from a binary file.

  Parameters:
    file: File to load from.
  Returns: Integer loaded from file.
*/
uint8_t load_uint8_t(std::ifstream &file)
{
  uint8_t buffer;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(uint8_t));

  return buffer;
}

/*
  Function: load_map
  Purpose: Loads map data from file.

  Parameters: None.
  Returns: Nothing.
*/
void load_map()
{
  std::ifstream mapfile ("map.gm", std::ifstream::binary);

  // Load wall colors
  for(int i = 0; i < 8; i++)
  {
    colors[i] = load_color(mapfile);
  }

  // Load floor, middle and roof colors
  for(int i = 0; i < 3; i++)
  {
    background_colors[i] = load_color(mapfile);
  }

  // Load player position
  Player.pos.x = load_float(mapfile);
  Player.pos.y = load_float(mapfile);

  mapWidth = load_uint8_t(mapfile);
  mapHeight = load_uint8_t(mapfile);

  map = new uint8_t[mapWidth * mapHeight];

  mapfile.read(reinterpret_cast<char*>(map), mapWidth * mapHeight * sizeof(uint8_t));
}