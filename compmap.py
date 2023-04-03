import struct
import json

source_file = open("map.gms", "r")
dest_file = open("map.gm", "wb")

map_data = json.load(source_file)

for i in range(3):
	binary = struct.pack("4B", map_data["wall_colors"][i][0], map_data["wall_colors"][i][1], map_data["wall_colors"][i][2], map_data["wall_colors"][i][3])
	print(binary)
	dest_file.write(binary)