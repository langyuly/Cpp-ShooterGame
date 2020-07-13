#ifndef TANK_H
#define TANK_H

#include "bullet.h"
#include "movingobject.h"

class Tank : public MovingObject {
   public:
    // construtor / destructor
    Tank(int grid_width, int grid_height);

    // setter & getter
    void SetBulletContainer(std::shared_ptr<BulletContainer> container);

    // basic funtionalities of tank
    void MoveLeft();
    void MoveRight();
    void Shoot();

   private:
    std::shared_ptr<BulletContainer> bullet_container;
};

#endif