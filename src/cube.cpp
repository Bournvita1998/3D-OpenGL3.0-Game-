#include "cube.h"
#include "main.h"

Cube::Cube(float x, float y, color_t color) {
    this->launch_speed = 0;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // side[10] = {s1,s2,s3,s4,s5,s6,s7,s8,s9};
    speed = 1.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

        // First face

       float a1 = 3.0f;
       float  a2 = 6.0f;
       float a3 = 2.0f;

       float  b1 = 4.0f;
       float  b2 = -6.0f;
       float  b3 = -2.0f;

       float c1 = -3.0f;
       float c2 = -6.0f;
       float c3 = -2.0f;

       float d1 = -4.0f;
       float d2 = 12.0f;
       float d3 = -12.0f;

       float z = 0.0f;
    static const GLfloat vertex_buffer_data[] = {

        a1,a2,a3, b1,b2,b3, a1,a2,b3,
        a1,a2,a3, b1,b2,b3, b1,b2,a3,

        c1,a2,c3, b1,c2,b3, d1,c2,c3,
        c1,a2,c3, b1,c2,b3, a1,a2,b3,

        c1,a2,c3, a1,a2,a3, c1,a2,a3,
        c1,a2,c3, a1,a2,a3, a1,a2,b3,

        c1,a2,c3, a1,a2,c3, z,d2,a1,
        a1,a2,c3, a1,a2,a3, z,d2,a1,

        a1,a2,a3, c1,a2,a3, z,d2,a1,
        c1,a2,a3, c1,a2,c3, z,d2,a1,

        d1,b2,c3, c1,a2,a3, d1,b2,a3,
        d1,b2,c3, c1,a2,a3, c1,a2,c3,

        b1,b2,a3, d1,b2,c3, b1,b2,c3,
        b1,b2,a3, d1,b2,c3, d1,b2,a3,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_CUBE1, GL_FILL);
    this->side[1] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+18, COLOR_CUBE2, GL_FILL);
    this->side[2] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+36, COLOR_CUBE3, GL_FILL);
    this->side[3] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+54, COLOR_CUBE4, GL_FILL);
    this->side[4] = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+72, COLOR_CUBE5, GL_FILL);
    this->side[5] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+90, COLOR_CUBE6, GL_FILL);
    this->side[6] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+99, COLOR_CUBE7, GL_FILL);
    this->side[7] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+108, COLOR_CUBE8, GL_FILL);
    this->side[8] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data+117, COLOR_CUBE9, GL_FILL);
        
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->side[1]);
    draw3DObject(this->side[2]);
    draw3DObject(this->side[3]);
    draw3DObject(this->side[4]);
    draw3DObject(this->side[5]);
    draw3DObject(this->side[6]);
    draw3DObject(this->side[7]);
    draw3DObject(this->side[8]);
}

bounding_box_t Cube::bounding_box() {
    bounding_box_t bbox = { this->position.x, this->position.y, 9, 9};
    return bbox;
}

void Cube::tick() {
}

void Cube::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
