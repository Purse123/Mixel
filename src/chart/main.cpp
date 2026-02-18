#include <SDL2/SDL.h>		// https://wiki.libsdl.org/SDL2/FrontPage
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "pie.hpp"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL initialization error: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (TTF_Init() < 0) {
    std::cerr << "SDL_ttf initialization error: " << TTF_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  SDL_Window* window = SDL_CreateWindow("Pie chat with label",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					WINDOW_WIDTH, WINDOW_HEIGHT,
					SDL_WINDOW_RESIZABLE);

  if (!window) {
    std::cerr << "couldnot open window: " << SDL_GetError() << std::endl;
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
					      SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    std::cerr << "renderer couldnt load: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  TTF_Font* font = TTF_OpenFont("./AnekLatin-Light.ttf", 16);
  if (!font) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    std::cerr << "Continuing without text labels..." << std::endl;
  }

  PieChart chart(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200, font);

  chart.addSlice(PieSlice("Product A", 30, 255, 0, 0));
  chart.addSlice(PieSlice("Product B", 25, 0, 255, 0));
  chart.addSlice(PieSlice("Product C", 20, 0, 0, 255));
  chart.addSlice(PieSlice("Product D", 15, 255, 255, 0));
  chart.addSlice(PieSlice("Product E", 10, 255, 0, 255));

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	running = false;
	break;
	
      case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	  running = false;
	}
	break;

      default:
	break;
      }
    }

    // clear
    // int SDL_SetRenderDrawColor(SDL_Renderer* renderer; r,g,b,a: Uint8 g);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draw
    chart.draw(renderer);
    
    // update
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  
  if (font) TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
  return 0;
}
