#include "sail.h"
#include "boat.h"
#include "main.h"

Sail::Sail(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    //speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0, 0, -1, // triangle 1 : begin
        0, 0,  1,
        0, 5, -1, // triangle 1 : end

    };

    this->object = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, color, GL_FILL);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sail::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sail::tick(Boat boat) {
    this->position.z = boat.position.z - 0.5*sin(boat.rotation*M_PI/180);
    this->position.y = boat.position.y + 1;
    this->position.x = boat.position.x + 0.5*cos(boat.rotation*M_PI/180);

    if(boat.wind>0)
    {
        float tempangle = boat.windangle - boat.rotation;
        if(0<tempangle && tempangle<=90 || 180<tempangle && tempangle<=270)
            this->rotation = boat.rotation+10;
        else
            this->rotation = boat.rotation-10;
    }
    else
        this->rotation = boat.rotation;

    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

