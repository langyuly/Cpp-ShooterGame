#include "tank.h"

void Tank::MoveLeft() {
    m_pos_x -= speed;
}

void Tank::MoveRight() {
    m_pos_x += speed;
}

float Tank::GetPositionX() const {
    return m_pos_x;
}

float Tank::GetPositionY() const {
    return m_pos_y;
}

void Tank::SetBulletContainer(BulletContainer *container) {
    bullet_generator = container;
}

void Tank::Shoot() {
    bullet_generator->GenerateNewBullet(m_pos_x, m_pos_y - 1.0f);
}