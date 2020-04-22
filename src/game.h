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
  Game(std::size_t gridWidth, std::size_t gridHeight,
       Controller &&controller, Renderer &&renderer);

  // Public Methods
  void run(const std::size_t &targetFrameDuration);

  // Getters
  int getScore() const;
  int getSize() const;

 private:

  // Private methods
  void placeFood_();
  void update_(bool &running);

  // Private data
  Snake      _snake;
  Controller _gController;
  Renderer   _gRenderer;
  SDL_Point  _food;
  int        _score{0};

  std::random_device _dev;
  std::mt19937    _engine;
  std::uniform_int_distribution<int> _randomW;
  std::uniform_int_distribution<int> _randomH;

};

#endif