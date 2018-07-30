#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;
    speedw = 0;
    wind = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         0.0f, 0.0f,-2.5f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         0.0f, 0.0f,-2.5f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
         0.0f, 0.0f,-2.5f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         0.0f, 0.0f,-2.5f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         0.0f, 0.0f, 2.5f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         0.0f, 0.0f, 2.5f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         0.0f, 0.0f, 2.5f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         0.0f, 0.0f, 2.5f,
    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
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

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    if(speed>0)
    {
        speed -= 0.02/60;
        if(speed<=0)speed=0;
    }
    else if(speed<0)
    {
        speed += 0.02/60;
        if(speed>=0)speed=0;
    }

    move_forward(1);
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Cannon::rotate(int flag){
    if(flag<0)
        this->rotation -= abs(flag)*0.3;
    else
        this->rotation += abs(flag)*0.3;
}

void Cannon::move_forward(int flag){
    if(flag<0);
        //this->rotation -= 0.3;
    else
    {
        if(wind==0)
        {
            this->position.z += speed*cos(this->rotation*M_PI/180.0f);
            this->position.x += speed*sin(this->rotation*M_PI/180.0f);
        }
        else if(wind>0)
        {
            this->position.z += speedw*cos(this->rotation*M_PI/180.0f);
            this->position.x += speedw*sin(this->rotation*M_PI/180.0f);
        }
    }
}

