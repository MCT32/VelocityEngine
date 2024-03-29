#include <string>
#include <map>
#include "load.h"
#include "config.h"

extern std::map<std::string, SDL_Surface*> textures;
extern std::string wall_textures[8];

/*
  Function: load_color
  Purpose: Loads a color from a binary file.

  Parameters:
    file: File to load from.
  Returns: Color loaded from file.
*/
SDL_Color load_color(std::ifstream &file)
{
  char* buffer = new char[4 * sizeof(uint8_t)];
  file.read(&buffer[0], 4 * sizeof(uint8_t));

  uint8_t alpha = buffer[0];
  uint8_t red = buffer[1];
  uint8_t green = buffer[2];
  uint8_t blue = buffer[3]; 

  delete[] buffer;

  return {red, green, blue, alpha};
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

char* load_string(std::ifstream &file, int buffer_length)
{
  char* buffer = reinterpret_cast<char*>(malloc(buffer_length));
  file.read(reinterpret_cast<char*>(buffer), buffer_length);
  return buffer;
}

void load_texture(std::string name)
{
  SDL_Surface* tex;

  tex = IMG_Load(("res/" + name + ".png").c_str());

  if(!tex) tex = IMG_Load(("res/" + std::string(name) + ".jpg").c_str());

  if(!tex)
  {
    log(log_level::Error, "Could not load texture.");
    return;
  }

  textures.insert({name, tex});
}

void unload_texture(std::string name)
{
  SDL_FreeSurface(textures[name]);
  textures.erase(name);
}

/*
  Function: load_map
  Purpose: Loads map data from file.

  Parameters: None.
  Returns: True if successful.
*/
bool load_map(std::string mapName)
{
  std::ifstream mapfile (mapName, std::ifstream::binary);
  if(mapfile.fail())
  {
    log(log_level::Error, "Failed to open map file");
    return false;
  }

  // Load textures
  log(log_level::Info, "Loading missing texture...");
  load_texture("MISSING");

  uint8_t num_textures = load_uint8_t(mapfile);
  log(log_level::Info, "Loading " + std::to_string(num_textures) + " textures...");

  std::string texture_names[num_textures];
  for(int i = 0; i < num_textures; i++)
  {
    texture_names[i] = std::string(load_string(mapfile, TEXTURE_STRING_LENGTH));
    log(log_level::Info, "Loading texture " + texture_names[i]);

    wall_textures[i] = texture_names[i];
    load_texture(texture_names[i]);
  }

  // Load floor, middle and roof colors
  for(int i = 0; i < 3; i++)
  {
    background_colors[i] = load_color(mapfile);
  }

  mapWidth = load_uint8_t(mapfile);
  mapHeight = load_uint8_t(mapfile);

  log(log_level::Info, "Loading map with dimentions " + std::to_string(mapWidth) + "x" + std::to_string(mapHeight));

  map = new uint8_t[mapWidth * mapHeight];

  mapfile.read(reinterpret_cast<char*>(map), mapWidth * mapHeight * sizeof(uint8_t));

  uint8_t num_entities = load_uint8_t(mapfile);
  for(int i = 0; i < num_entities; i++)
  {
    uint8_t id = load_uint8_t(mapfile);
    float x = load_float(mapfile);
    float y = load_float(mapfile);
    float rot = load_float(mapfile);

    switch(id)
    {
      case 0:
	log(log_level::Info, "Found player_start entity");
        Player = player(x, y, rot);
	break;
      default:
	log(log_level::Warning, "Entity id not recognised, skipping");
	break;
    }
  }

  mapfile.close();

  return true;
}
