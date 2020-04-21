#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  // Constructor
  Game(std::size_t gridWidth, std::size_t gridHeight);

  // Public Methods
  void run(Controller const &&controller, Renderer &&renderer,
           const std::size_t &targetFrameDuration);

  // Getters
  int getScore() const;
  int getSize() const;

 private:

  // Private methods
  void placeFood_();
  void update_();

  // Private data
  Snake    _snake;
  SDL_Point _food;
  int   _score{0};

  std::random_device _dev;
  std::mt19937    _engine;
  std::uniform_int_distribution<int> _randomWidth;
  std::uniform_int_distribution<int> _randomHeight;

};

#endif