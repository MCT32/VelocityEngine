#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[])
{
  SDL_Window* window = NULL;
  SDL_Surface* surface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
    "COOM",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (window == NULL)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  surface = SDL_GetWindowSurface(window);

  SDL_Event event;
  bool quit = false;

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_QUIT: quit = true; break;
      default:
        break;
      }
    }

    unsigned int* pixels = (unsigned int*)surface->pixels;

    for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++)
    {
      pixels[i] = 0xFFFFFFFF;
    }

    SDL_UpdateWindowSurface(window);
  }
}
