#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y, color_t color);
    double speed;
    bounding_box_t bounding_box();
    glm::vec3 position;
    float launch_speed,launch_speed_x,launch_speed_y,size,rotation;
    void draw(glm::mat4 VP) , set_position(float x, float y) , tick();
private:
    VAO *object;
};

#endif // BALL_H