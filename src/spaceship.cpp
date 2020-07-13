#include "spaceship.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>

SpaceshipContainer::SpaceshipContainer(int grid_width, int grid_height)
    : MovingObjectContainer(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_t(0, 20) {
    // launch drive function in a thread
    running = true;
    threads.emplace_back(std::thread(&SpaceshipContainer::Run, this));
}

SpaceshipContainer::~SpaceshipContainer() {
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

void SpaceshipContainer::Stop() {
    std::lock_guard<std::mutex> lck(mtx);
    running = false;
}

void SpaceshipContainer::Run() {
    double cycleDuration = 1;  // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true) {
        std::unique_lock<std::mutex> lck(mtx);
        if (!running) {
            break;
        }
        lck.unlock();

        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

        if (timeSinceLastUpdate >= cycleDuration) {
            cycleDuration = random_t(engine) * 100;

            // generate new spaceship if number is smaller than required
            GenerateNewSpaceship();
            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
        }
    }
}

void SpaceshipContainer::GenerateNewSpaceship() {
    int pos_x = random_w(engine);
    GenerateNewObject(pos_x * 1.0f, 0.0f, 0.0f, 1.0f);
}

void SpaceshipContainer::DestroyInvalidSpaceships() {
    DestroyInvalidObjects();
}
