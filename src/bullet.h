#ifndef BULLET_H
#define BULLET_H

#include "movingobject.h"

class BulletContainer : public MovingObjectContainer {
   public:
    // constructor & destructor
    BulletContainer(int grid_width, int grid_height)
        : MovingObjectContainer(grid_width, grid_height) {}

    void GenerateNewBullet(float pos_x, float pos_y);
    void DestroyInvalidBullets();
};

#endif