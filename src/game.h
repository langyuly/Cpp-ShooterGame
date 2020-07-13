#ifndef GAME_H
#define GAME_H

#include <memory>
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
    std::shared_ptr<BulletContainer> bullet_container;
    std::unique_ptr<SpaceshipContainer> spaceship_container;

    int score{0};

    std::mutex mtx;

    // main logic of the game
    void Update();
    // detect collisions of bullets with spaceships
    int DetectCollision();
};

#endif