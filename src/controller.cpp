#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::changeDirection_(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::handleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          changeDirection_(snake, Snake::Direction::kUp,
                           Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          changeDirection_(snake, Snake::Direction::kDown,
                           Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          changeDirection_(snake, Snake::Direction::kLeft,
                           Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          changeDirection_(snake, Snake::Direction::kRight,
                           Snake::Direction::kLeft);
          break;
      }
    }
  }
}