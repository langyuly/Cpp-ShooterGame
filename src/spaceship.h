#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "movingobject.h"

class SpaceshipContainer : public MovingObjectContainer {
   public:
    // constructor & destructor
    SpaceshipContainer(int grid_width, int grid_height);
    ~SpaceshipContainer();

    // getter & setter

    // function support simulation loop
    void Run();
    void Stop();

    void GenerateNewSpaceship();
    void DestroyInvalidSpaceships();

   private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_t;

    std::vector<std::thread> threads;  // holds all threads that have been launched within this object

    bool running;
};

#endif