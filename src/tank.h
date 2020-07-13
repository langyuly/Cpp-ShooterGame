#ifndef TANK_H
#define TANK_H

#include "bullet.h"
#include "movingobject.h"

class Tank : public MovingObject {
   public:
    // construtor / destructor
    Tank(int grid_width, int grid_height);

    void SetBulletContainer(BulletContainer *container);

    void MoveLeft();
    void MoveRight();
    void Shoot();

   private:
    BulletContainer *bullet_generator;
};

#endif