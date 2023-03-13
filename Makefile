run: build
	./COOM

build: COOM

COOM: main.cpp
	gcc main.cpp -o COOM -lSDL2 -lm -ldl