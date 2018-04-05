#include "main.h"

#ifndef CUBE_H
#define CUBE_H


class Cube {
public:
    Cube() {};
    Cube(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP) , set_position(float x, float y) , tick();
    // void set_position(float x, float y);
    // void tick();
    double speed;
    bounding_box_t bounding_box();
    float rotation;
    float launch_speed;
private:
    VAO *side[9];
    VAO *object;
};

#endif // CUBE_H
