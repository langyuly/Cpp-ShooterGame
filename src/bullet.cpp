#include "bullet.h"

void BulletContainer::GenerateNewBullet(float pos_x, float pos_y) {
    GenerateNewObject(pos_x, pos_y, 0.0f, -1.0f);
}

void BulletContainer::DestroyInvalidBullets() {
    DestroyInvalidObjects();
}