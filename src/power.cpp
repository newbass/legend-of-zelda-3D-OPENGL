#include "power.h"
#include "main.h"

Power::Power(float x, float y, float z, int flag, float ang, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = ang;
    flag = 0;
    distance = 4.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[10000] = { };
        int i=0,j=0;
        float radi=1;
        double ra= ((double)M_PI)/360.00;
        for(i=0;i<720;i++)
        {
            double rad= ra*i;
            vertex_buffer_data[9*(i)+0]= 0.0f;
            vertex_buffer_data[9*(i)+1]= 0.0f;
            vertex_buffer_data[9*(i)+2]= 0.0f;
            vertex_buffer_data[9*(i)+3]= radi*cos(rad);
            vertex_buffer_data[9*(i)+4]= 0.0f;
            vertex_buffer_data[9*(i)+5]= radi*sin(rad);
            rad = ra*(1+i);
            vertex_buffer_data[9*(i)+6]= radi*cos(rad);
            vertex_buffer_data[9*(i)+7]= 0.0f;
            vertex_buffer_data[9*(i)+8]= radi*sin(rad);
        }

    this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, color, GL_FILL);

    //this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color1, GL_FILL);
    //this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color2, GL_FILL);
}

void Power::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object1);
    draw3DObject(this->object);
}

void Power::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Power::tick() {
   // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

