#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    float a = 1.0f , b = -1.0f;
    size = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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
        a,b,a,

        0.5,0,1,
        1,0,1,
        0.75,0,1.7,
        -0.5,0,1,
        -1,0,1,
        -0.75,0,1.7,
    };

    this->rotation = 0;
    this->launch_speed = 0;
    speed = 1;
    this->object = create3DObject(GL_TRIANGLES, 14*3, vertex_buffer_data, color, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 scale    = glm::scale(glm::vec3(this->size, this->size, this->size));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model = Matrices.model * translate * rotate * scale;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Monster::bounding_box() {
    bounding_box_t bbox = { this->position.x, this->position.y, this->size, this->size };
    return bbox;
}

void Monster::set_position(float x, float y) {this->position = glm::vec3(x, y, 0);}
void Monster::tick() {this->rotation += speed;}