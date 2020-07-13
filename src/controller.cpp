#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "tank.h"

void Controller::HandleInput(bool &running, Tank &tank) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    tank.MoveLeft();
                    break;

                case SDLK_RIGHT:
                    tank.MoveRight();
                    break;

                case SDLK_SPACE:
                    tank.Shoot();
                    break;
            }
        }
    }
}