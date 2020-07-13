#ifndef GAME_H
#define GAME_H

#include <mutex>
#include <vector>

#include "bullet.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "tank.h"

class Game {
   public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;

   private:
    Tank tank;
    BulletContainer bullet_container;
    SpaceshipContainer spaceship_container;

    int score{0};

    std::mutex mtx;

    void Update();
    int DetectCollision();
};

#endif