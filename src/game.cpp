#include "game.h"

#include <iostream>

#include "movingobject.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : tank(grid_width, grid_height) {
    bullet_container = std::make_shared<BulletContainer>(grid_width, grid_height),
    spaceship_container = std::make_unique<SpaceshipContainer>(grid_width, grid_height);
    tank.SetPosition(grid_width / 2, grid_height - 1);
    tank.SetBulletContainer(bullet_container);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        //controller.HandleInput(running, snake);
        controller.HandleInput(running, tank);
        Update();
        renderer.Render(tank, bullet_container->GetObjects(), spaceship_container->GetObjects());

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }

    spaceship_container->Stop();
}

void Game::Update() {
    // recompute position of all moving objects
    bullet_container->MoveAll();
    spaceship_container->MoveAll();
    // compute number of collisions between bullet and spaceship
    score += DetectCollision();
    // delete all objects that are invalid inside the vector
    bullet_container->DestroyInvalidBullets();
    spaceship_container->DestroyInvalidSpaceships();
}

int Game::DetectCollision() {
    int collision = 0;

    std::lock_guard<std::mutex> lck(mtx);
    std::vector<MovingObject> &bullets = bullet_container->GetObjects();
    std::vector<MovingObject> &spaceships = spaceship_container->GetObjects();

    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].GetInvalid()) {
            continue;
        }
        for (int j = 0; j < spaceships.size(); j++) {
            if (spaceships[j].GetInvalid()) {
                continue;
            }
            if (bullets[i].Collide(spaceships[j])) {
                bullets[i].SetInvalid(true);
                spaceships[j].SetInvalid(true);
                collision++;
                break;
            }
        }
    }

    return collision;
}

int Game::GetScore() const { return score; }