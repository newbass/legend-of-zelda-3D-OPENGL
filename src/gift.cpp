#include "gift.h"
#include "boat.h"
#include "cannon.h"
#include "main.h"

Gift::Gift(float x, float y, float z, int pts, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    struck = 0;
    show=1;
    points = pts;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.5f,  0.0f,-0.5f,
         0.5f,  0.0f,-0.5f,
         0.0f,  1.0f, 0.0f,
         0.5f,  0.0f,-0.5f,
         0.5f,  0.0f, 0.5f,
         0.0f,  1.0f, 0.0f,
         0.5f,  0.0f, 0.5f,
        -0.5f,  0.0f, 0.5f,
         0.0f,  1.0f, 0.0f,
        -0.5f,  0.0f, 0.5f,
        -0.5f,  0.0f,-0.5f,
         0.0f,  1.0f, 0.0f,
        -0.5f,  0.0f,-0.5f,
         0.5f,  0.0f,-0.5f,
         0.0f, -1.0f, 0.0f,
         0.5f,  0.0f,-0.5f,
         0.5f,  0.0f, 0.5f,
         0.0f, -1.0f, 0.0f,
         0.5f,  0.0f, 0.5f,
        -0.5f,  0.0f, 0.5f,
         0.0f, -1.0f, 0.0f,
        -0.5f,  0.0f, 0.5f,
        -0.5f,  0.0f,-0.5f,
         0.0f, -1.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

// cannon_x =  cannon.position.x + 2.5*sin(boat.rotation*M_PI/180);
// cannon_z =  cannon.position.z + 2.5*cos(boat.rotation*M_PI/180);

// (abs(boat.position.x - this->position.x)*abs(boat.position.x - this->position.x)) + (abs(boat.position.z - this->position.z)*abs(boat.position.z - this->position.z)) <= 3.915*3.915)
int Gift::tick(Boat boat, Cannon cannon) {
    this->rotation += 1;
    if(this->position.y>=0)
    {
        if(this->position.x >= boat.position.x-1 && this->position.x <= boat.position.x+1 && this->position.z >= boat.position.z-1 && this->position.z <= boat.position.z+1)
        {
            this->position.y = -4;
            return 1;
        }
    }
    return 0;
}

