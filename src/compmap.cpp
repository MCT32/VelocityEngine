#include <json/json.h>
#include <fstream>
#include <iostream>

#include "config.h"

int main(int argc, char* argv[])
{
	Json::Value mapJson;

	std::ifstream mapSource;
	mapSource.open(argv[1]);

	std::ofstream mapDest;
	mapDest.open(argv[2]);

	Json::CharReaderBuilder builder;
	JSONCPP_STRING errs;

	if(!parseFromStream(builder, mapSource, &mapJson, &errs))
	{
		std::cout << errs << std::endl;
		return 1;
	}

	mapSource.close();

	uint8_t num_textures = mapJson["walls"].size();
	mapDest << num_textures;

	char* textures[num_textures];
	for(int i = 0; i < num_textures; i++)
	{
		textures[i] = (char*)malloc(TEXTURE_STRING_LENGTH);
		strcpy(textures[i], mapJson["walls"][i].asString().c_str());
		for(int j = 0; j < TEXTURE_STRING_LENGTH; j++) mapDest << textures[i][j];
	}

	for(int i = 0; i < 3; i++)
	{
		Json::Value color = mapJson["background"][i];

		uint8_t alpha = color[0].asUInt();
		uint8_t red = color[1].asUInt();
		uint8_t green = color[2].asUInt();
		uint8_t blue = color[3].asUInt();

		mapDest << alpha << red << green << blue;
	}
	
	float f;

	f = mapJson["playerPos"][0].asFloat();
	mapDest.write(reinterpret_cast<const char*>(&f), sizeof(float));
	f = mapJson["playerPos"][1].asFloat();
	mapDest.write(reinterpret_cast<const char*>(&f), sizeof(float));

	uint8_t w, h;
	w = mapJson["mapSize"][0].asUInt();
	h = mapJson["mapSize"][1].asUInt();

	mapDest << w << h;

	for(int y = h - 1; y >= 0; y--)
	{
		for(int x = 0; x < w; x++)
		{
			uint8_t wall = mapJson["mapData"][y][x].asUInt();
			mapDest.write(reinterpret_cast<const char*>(&wall), sizeof(uint8_t));
		}
	}

	mapDest.close();

	return 0;
}
