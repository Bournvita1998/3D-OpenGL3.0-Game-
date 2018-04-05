#include "main.h"

#ifndef AIM_H
#define AIM_H


class Aim {
public:
    Aim() {};
    Aim(float x, float y, color_t color);
    glm::vec3 position;
    float launch_speed,rotation_h,rotation_z;
    void tick(),set_position(float x, float y),draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

#endif // CUBE_H
