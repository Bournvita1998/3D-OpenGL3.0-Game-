#include "main.h"

#ifndef person_H
#define person_H


class person {
public:
    person() {}
    person(float x, float y,float z,float l , float b,float w, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    // bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
