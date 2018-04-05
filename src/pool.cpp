#include "pool.h"
#include "main.h"

Pool::Pool(float x, float y, color_t color) {
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    float a = 32767, b = -32767;

    static const GLfloat vertex_buffer_data[] = {

        b,b,b,
        b,b,a,
        b,a,a,
        a,a,b,
        b,b,b,
        b,a,b,

        a,b,a,
        b,b,b,
        a,b,b,
        a,a,b,
        a,b,b,
        b,b,b,

        b,b,b,
        b,a,a, 
        b,a,b, 
        a,b,a, 
        b,b,a, 
        b,b,b,

        b,a,a,
        b,b,a,
        a,b,a,
        a,a,a,
        a,b,b,
        a,a,b,

        a,b,b,
        a,a,a,
        a,b,a,
        a,a,a,
        a,a,b,
        b,a,b,

        a,a,a,
        b,a,b,
        b,a,a,
        a,a,a,
        b,a,a,
        a,b,a

    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.2;

}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = rotate * Matrices.model * translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pool::tick() {}

void Pool::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}