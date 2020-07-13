#ifndef CONTROLLER_H
#define CONTROLLER_H

class Tank;

class Controller {
   public:
    void HandleInput(bool &running, Tank &tank) const;
};

#endif