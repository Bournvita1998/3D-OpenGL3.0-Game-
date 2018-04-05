#include "main.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {};
    Sail(float x, float y, color_t color);
    glm::vec3 position;
    float launch_speed,launch_speed_x,launch_speed_y,size,rotation;
    void tick(),set_position(float x, float y),draw(glm::mat4 VP);
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H