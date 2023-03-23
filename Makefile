run: build
	./COOM

build: COOM

COOM: main.o color.o draw.o util.o render.o player.o load.o logging.o
	gcc main.o color.o draw.o util.o render.o player.o load.o logging.o -o COOM -lstdc++ -lSDL2 -lm -ldl

main.o: main.cpp
	gcc main.cpp -c main.o

color.o: color.cpp
	gcc color.cpp -c main.o

draw.o: draw.cpp
	gcc draw.cpp -c draw.o

util.o: util.cpp
	gcc util.cpp -c util.o

render.o: render.cpp
	gcc render.cpp -c render.o

player.o: player.cpp
	gcc player.cpp -c player.o

load.o: load.cpp
	gcc load.cpp -c load.o

logging.o: logging.cpp
	gcc logging.cpp -c logging.o