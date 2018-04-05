#include "main.h"

#ifndef POOL_H
#define POOL_H


class Pool {
public:
    Pool() {};
    Pool(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP), set_position(float x, float y) , tick();
    // void set_position(float x, float y);
    // void tick();
    double speed;
    float rotation;
private:
    VAO *object;
};

#endif // POOL_H
