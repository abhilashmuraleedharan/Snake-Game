#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  // Constructor
  Renderer(const std::size_t screenWidth, const std::size_t screenHeight,
           const std::size_t gridWidth, const std::size_t gridHeight);

  // Destructor
  ~Renderer();

  // Public methods
  void render(Snake const snake, SDL_Point const &food);
  void updateWindowTitle(int score, int fps);

 private:
  SDL_Window   *_sdlWindowPtr;
  SDL_Renderer *_sdlRendererPtr;

  const std::size_t _screenWidth;
  const std::size_t _screenHeight;
  const std::size_t _gridWidth;
  const std::size_t _gridHeight;
};

#endif