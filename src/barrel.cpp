#include "barrel.h"
#include "boat.h"
#include "cannon.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    struck = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -2.0f, 0.0f,-2.0f,
         2.0f, 0.0f,-2.0f,
         0.0f, 1.0f, 0.0f,
         2.0f, 0.0f,-2.0f,
         2.0f, 0.0f, 2.0f,
         0.0f, 1.0f, 0.0f,
         2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f, 2.0f,
         0.0f, 1.0f, 0.0f,
        -2.0f, 0.0f, 2.0f,
        -2.0f, 0.0f,-2.0f,
         0.0f, 1.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
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

void Barrel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

// cannon_x =  cannon.position.x + 2.5*sin(boat.rotation*M_PI/180);
// cannon_z =  cannon.position.z + 2.5*cos(boat.rotation*M_PI/180);

// (abs(boat.position.x - this->position.x)*abs(boat.position.x - this->position.x)) + (abs(boat.position.z - this->position.z)*abs(boat.position.z - this->position.z)) <= 3.915*3.915)
int Barrel::tick(Boat boat, Cannon cannon) {
    float cannon_x =  cannon.position.x + 2.5*sin(boat.rotation*M_PI/180);
    float cannon_z =  cannon.position.z + 2.5*cos(boat.rotation*M_PI/180);

    float cannon_xr =  cannon.position.x + sqrt(2)*sin((boat.rotation+45)*M_PI/180);
    float cannon_zr =  cannon.position.z + sqrt(2)*cos((boat.rotation+45)*M_PI/180);

    float cannon_xl =  cannon.position.x + sqrt(2)*sin((boat.rotation-45)*M_PI/180);
    float cannon_zl =  cannon.position.z + sqrt(2)*cos((boat.rotation-45)*M_PI/180);


    if(struck==0 && (((this->position.x-2 <= cannon_x && cannon_x <= this->position.x+2) && (this->position.z-2 <= cannon_z && cannon_z <= this->position.z+2)) || ((cannon_x <= this->position.x-2 && this->position.x-2 <= cannon_xr) && (cannon_zr <= this->position.z-2 && this->position.z-2 <= cannon_z)) || ((cannon_xr <= this->position.x+2 && this->position.x+2 <= cannon_x) && (cannon_z <= this->position.z+2 && this->position.z+2 <= cannon_zr)) || ((cannon_x <= this->position.x-2 && this->position.x-2 <= cannon_xl) && (cannon_z <= this->position.z+2 && this->position.z+2 <= cannon_zl)) || ((cannon_xl <= this->position.x+2 && this->position.x+2 <= cannon_x) && (cannon_zl <= this->position.z-2 && this->position.z-2 <= cannon_z)) || ((cannon_xl <= this->position.x-2 && this->position.x-2 <= cannon_x) && (cannon_z <= this->position.z-2 && this->position.z-2 <= cannon_zl)) || ((cannon_x <= this->position.x+2 && this->position.x+2 <= cannon_xl) && (cannon_zl <= this->position.z+2 && this->position.z+2 <= cannon_z)) || ((cannon_xr <= this->position.x-2 && this->position.x-2 <= cannon_x) && (cannon_zr <= this->position.z+2 && this->position.z+2 <= cannon_z)) || ((cannon_x <= this->position.x+2 && this->position.x+2 <= cannon_xr) && (cannon_z <= this->position.z-2 && this->position.z-2 <= cannon_zr))))
    {
        //std::cout<<"STRUCK";
        struck=1;
        return 1;
    }
    else if(!(((this->position.x-2 <= cannon_x && cannon_x <= this->position.x+2) && (this->position.z-2 <= cannon_z && cannon_z <= this->position.z+2)) || ((cannon_x <= this->position.x-2 && this->position.x-2 <= cannon_xr) && (cannon_zr <= this->position.z-2 && this->position.z-2 <= cannon_z)) || ((cannon_xr <= this->position.x+2 && this->position.x+2 <= cannon_x) && (cannon_z <= this->position.z+2 && this->position.z+2 <= cannon_zr)) || ((cannon_x <= this->position.x-2 && this->position.x-2 <= cannon_xl) && (cannon_z <= this->position.z+2 && this->position.z+2 <= cannon_zl)) || ((cannon_xl <= this->position.x+2 && this->position.x+2 <= cannon_x) && (cannon_zl <= this->position.z-2 && this->position.z-2 <= cannon_z)) || ((cannon_xl <= this->position.x-2 && this->position.x-2 <= cannon_x) && (cannon_z <= this->position.z-2 && this->position.z-2 <= cannon_zl)) || ((cannon_x <= this->position.x+2 && this->position.x+2 <= cannon_xl) && (cannon_zl <= this->position.z+2 && this->position.z+2 <= cannon_z)) || ((cannon_xr <= this->position.x-2 && this->position.x-2 <= cannon_x) && (cannon_zr <= this->position.z+2 && this->position.z+2 <= cannon_z)) || ((cannon_x <= this->position.x+2 && this->position.x+2 <= cannon_xr) && (cannon_z <= this->position.z-2 && this->position.z-2 <= cannon_zr))))
    {
        //std::cout<<"ANTI-STRUCK\n";
        struck=0;
        return 0;
    }
    return 0;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

