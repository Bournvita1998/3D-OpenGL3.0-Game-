#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {};
    Monster(float x, float y, color_t color);
    glm::vec3 position;
    float launch_speed,launch_speed_x,launch_speed_y,size,rotation;
    void draw(glm::mat4 VP) , set_position(float x, float y) , tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H