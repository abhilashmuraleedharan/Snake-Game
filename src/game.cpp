#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t gridWidth, std::size_t gridHeight)
    : _snake(gridWidth, gridHeight),
      _engine(_dev()),
      _randomWidth(1,  static_cast<int>(gridWidth)),
      _randomHeight(1, static_cast<int>(gridHeight)) {
  placeFood_();
}

void Game::run(Controller const &&controller, Renderer &&renderer,
               const std::size_t &targetFrameDuration) {
  Uint32 titleTimestamp = SDL_GetTicks();
  Uint32 frameStart;
  Uint32 frameEnd;
  Uint32 frameDuration;
  int  frameCount = 0;
  bool running = true;

  while (running) {
    frameStart = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.handleInput(running, _snake);
    update_();
    renderer.render(_snake, _food);

    frameEnd = SDL_GetTicks();

    /*
     * Keep track of how long each frame loop through 
     * the input/update/render cycle
     */
    frameCount++;
    frameDuration = frameEnd - frameStart;

    // After every second, update the window title.
    if (frameEnd - titleTimestamp >= 1000) {
      renderer.updateWindowTitle(_score, frameCount);
      frameCount = 0;
      titleTimestamp = frameEnd;
    }

    /*
     * If the time for this frame is too small (i.e. frameDuration is
     * smaller than the target ms_per_frame), delay the loop to
     * achieve the correct frame rate.
     */
    if (frameDuration < targetFrameDuration) {
      SDL_Delay(targetFrameDuration - frameDuration);
    }
  }
}

void Game::placeFood_() {
  int x, y;
  while (true) {
    x = _randomWidth(_engine);
    y = _randomHeight(_engine);
    /*
     * Check that the location is not occupied by a snake item 
     * before placing food.
     */
    if (!_snake.snakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::update_() {
  if (!_snake.alive) return;

  _snake.update();

  int newX = static_cast<int>(_snake.headX);
  int newY = static_cast<int>(_snake.headY);

  // Check if there's food over here
  if (_food.x == newX && _food.y == newY) {
    _score++;
    placeFood_();
    // Grow snake and increase speed.
    _snake.growBody();
    _snake.speed += 0.02;
  }
}

int Game::getScore() const { return _score; }
int Game::getSize()  const { return _snake.size; }