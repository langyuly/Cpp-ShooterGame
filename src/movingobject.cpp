#include "movingobject.h"

#include <iostream>

MovingObject::MovingObject(int grid_width, int grid_height)
    : grid_width(grid_width),
      grid_height(grid_height) {
    m_speed = 0.05f;
}

void MovingObject::SetSpeed(float init_speed) {
    m_speed = init_speed;
}

void MovingObject::SetDirection(float dir_x, float dir_y) {
    m_dir_x = dir_x;
    m_dir_y = dir_y;
}

void MovingObject::SetPosition(float x, float y) {
    m_pos_x = x;
    m_pos_y = y;
}

float MovingObject::GetPositionX() const {
    return m_pos_x;
}

float MovingObject::GetPositionY() const {
    return m_pos_y;
}

void MovingObject::SetInvalid(bool flag) {
    invalid = flag;
}

bool MovingObject::GetInvalid() {
    return invalid;
}

void MovingObject::Move() {
    m_pos_x += m_speed * m_dir_x;
    m_pos_y += m_speed * m_dir_y;

    if (m_pos_x < 0 || m_pos_x >= grid_width ||
        m_pos_y < 0 || m_pos_y >= grid_height) {
        invalid = true;
    }
}

bool MovingObject::Collide(MovingObject& other) {
    float a_min_y = std::min(m_pos_y, m_pos_y - m_speed * m_dir_y);
    float a_max_y = std::max(m_pos_y, m_pos_y - m_speed * m_dir_y);
    float b_min_y = std::min(other.m_pos_y, other.m_pos_y - other.m_speed * other.m_dir_y);
    float b_max_y = std::max(other.m_pos_y, other.m_pos_y - other.m_speed * other.m_dir_y);

    return (static_cast<int>(m_pos_x) == static_cast<int>(other.m_pos_x) && a_min_y <= b_max_y && b_min_y <= a_max_y);
}

std::vector<MovingObject>& MovingObjectContainer::GetObjects() {
    std::lock_guard<std::mutex> lck(mtx);
    return moving_objects;
}

void MovingObjectContainer::GenerateNewObject(float pos_x, float pos_y, float dir_x, float dir_y) {
    std::lock_guard<std::mutex> lck(mtx);

    MovingObject new_object(grid_width, grid_height);
    new_object.SetPosition(pos_x, pos_y);
    new_object.SetDirection(dir_x, dir_y);
    moving_objects.emplace_back(new_object);
}

// check object valid flag and delete all invalid objects
void MovingObjectContainer::DestroyInvalidObjects() {
    std::lock_guard<std::mutex> lck(mtx);

    for (int i = 0; i < moving_objects.size(); i++) {
        // delete invalid object by copying last element to it, and delete the last element
        if (moving_objects[i].GetInvalid()) {
            if (i != moving_objects.size()) {
                moving_objects[i] = moving_objects.back();
            }
            moving_objects.pop_back();
        }
    }
}

void MovingObjectContainer::MoveAll() {
    std::lock_guard<std::mutex> lck(mtx);

    for (int i = 0; i < moving_objects.size(); i++) {
        moving_objects[i].Move();
    }
}