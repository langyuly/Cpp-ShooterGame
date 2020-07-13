#ifndef TANK_H
#define TANK_H

#include "bullet.h"

class Tank {
   public:
    // construtor / destructor
    Tank(float xpos, float ypos)
        : m_pos_x(xpos),
          m_pos_y(ypos) {}

    // Getter and Setter
    float GetPositionX() const;
    float GetPositionY() const;

    void SetBulletContainer(BulletContainer *container);

    //
    void MoveLeft();
    void MoveRight();
    void Shoot();

   private:
    float speed{1.0f};
    float m_pos_x;
    float m_pos_y;

    BulletContainer *bullet_generator;
};

#endif