#include "ui.h"

void render_fps(SDL_Renderer* renderer, int fps)
{
  SDL_Color color = {255, 0, 0};
  SDL_Surface* surface = TTF_RenderText_Solid(debug_font, ("FPS: " + std::to_string(fps)).c_str(), color);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect dstrect = {0, 0, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void render_ui(SDL_Renderer* renderer, int fps)
{
  render_fps(renderer, fps);
}
