#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <mutex>
#include <vector>

class MovingObject {
   public:
    // constructor and destructor
    MovingObject(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}

    // Getters and Setters
    void SetSpeed(float init_speed);
    void SetDirection(float dir_x, float dir_y);
    void SetPosition(float x, float y);

    float GetPositionX() const;
    float GetPositionY() const;

    void SetInvalid(bool flag);
    bool GetInvalid();

    // object moves
    void Move();
    bool Collide(MovingObject& other);

   private:
    float m_speed{0.05f};

    float m_pos_x;
    float m_pos_y;
    float m_dir_x;
    float m_dir_y;

    int grid_width;
    int grid_height;

    bool invalid{false};
};

class MovingObjectContainer {
   public:
    // constructor & destructor
    MovingObjectContainer(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height){};

    // getter & setter
    std::vector<MovingObject>& GetObjects();

    // create and remove moving object(s)
    void GenerateNewObject(float pos_x, float pos_y, float dir_x, float dir_y);
    void DestroyInvalidObjects();

    // move all objects
    void MoveAll();

   protected:
    int grid_width;
    int grid_height;

    std::vector<MovingObject> moving_objects;

    std::mutex mtx;
};

#endif
