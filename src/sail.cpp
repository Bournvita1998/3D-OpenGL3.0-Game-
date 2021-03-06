#include "sail.h"
#include "main.h"

Sail::Sail(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    float a = 1 , b = -1 , c = 0, d = 20 , e = 18;
    this->launch_speed = 0;
    size = 1;
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {

        a,c,c,
        c,c,d,
        b,c,c,
        a,a,c,
        c,c,d,
        b,a,c,
        a,c,c,
        c,c,d,
        a,a,c,

        b,c,c,
        c,c,d,
        b,a,c,
        c,c,e,
        c,c,3, 
        -14,c,8

    };

    speed = 1;
    this->object = create3DObject(GL_TRIANGLES, 15, vertex_buffer_data, color, GL_FILL);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 scale    = glm::scale(glm::vec3(this->size, this->size, this->size));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = Matrices.model * translate * rotate * scale ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Sail::bounding_box() {
    bounding_box_t bbox = { this->position.x, this->position.y, this->size, this->size };
    return bbox;
}

void Sail::set_position(float x, float y) { this->position = glm::vec3(x, y, 0); }
void Sail::tick() { this->rotation += speed; }