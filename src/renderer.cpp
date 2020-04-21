#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screenWidth,
                   const std::size_t screenHeight,
                   const std::size_t gridWidth, 
                   const std::size_t gridHeight)
    : _screenWidth(screenWidth),
      _screenHeight(screenHeight),
      _gridWidth(gridWidth),
      _gridHeight(gridHeight) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdlWindowPtr = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, _screenWidth,
                                   _screenHeight, SDL_WINDOW_SHOWN);

  if (nullptr == _sdlWindowPtr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdlRendererPtr = SDL_CreateRenderer(_sdlWindowPtr, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == _sdlRendererPtr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(_sdlRendererPtr);
  SDL_DestroyWindow(_sdlWindowPtr);
  SDL_Quit();
}

void Renderer::render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = _screenWidth / _gridWidth;
  block.h = _screenHeight / _gridHeight;

  // Clear screen
  SDL_SetRenderDrawColor(_sdlRendererPtr, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRendererPtr);

  // Render food
  SDL_SetRenderDrawColor(_sdlRendererPtr, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(_sdlRendererPtr, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(_sdlRendererPtr, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdlRendererPtr, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.headX) * block.w;
  block.y = static_cast<int>(snake.headY) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(_sdlRendererPtr, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdlRendererPtr, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdlRendererPtr, &block);

  // Update Screen
  SDL_RenderPresent(_sdlRendererPtr);
}

void Renderer::updateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdlWindowPtr, title.c_str());
}
