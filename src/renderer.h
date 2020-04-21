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

  /*
   * Rule of 5 implementation
   * Adopting a "No copy, only move" memory management policy
   */
  Renderer(const Renderer &) = delete;             // Delete copy constructor
  Renderer &operator=(const Renderer &) = delete;  // Delete copy assignment operator

  // Move Constructor
  Renderer(Renderer &&source);

  // Move Assignment Operator
  Renderer &operator=(Renderer &&source);

  // Public methods
  void render(Snake const &snake, SDL_Point const &food);
  void updateWindowTitle(int score, int fps);

 private:
  SDL_Window   *_sdlWindowPtr;
  SDL_Renderer *_sdlRendererPtr;

  std::size_t _screenWidth;
  std::size_t _screenHeight;
  std::size_t _gridWidth;
  std::size_t _gridHeight;
};

#endif