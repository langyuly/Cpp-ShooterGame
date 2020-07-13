#include "tank.h"

Tank::Tank(int grid_width, int grid_height)
    : MovingObject(grid_width, grid_height) {
    m_speed = 1.0f;
}

void Tank::MoveLeft() {
    m_pos_x -= m_speed;
}

void Tank::MoveRight() {
    m_pos_x += m_speed;
}

void Tank::SetBulletContainer(std::shared_ptr<BulletContainer> container) {
    bullet_container = container;
}

void Tank::Shoot() {
    bullet_container->GenerateNewBullet(m_pos_x, m_pos_y);
}