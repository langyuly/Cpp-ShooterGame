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

void Tank::SetBulletContainer(BulletContainer *container) {
    bullet_generator = container;
}

void Tank::Shoot() {
    bullet_generator->GenerateNewBullet(m_pos_x, m_pos_y);
}