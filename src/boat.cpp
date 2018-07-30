#include "boat.h"
#include "main.h"
#include <bits/stdc++.h>
#include <algorithm>

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;
    speedw = 0;
    speedy = 0;
    mode = 0;
    heliheight = 10;
    heliangle = 0;
    hunt = 0;
    wind = 0;
    jump=0;
    point=0;
    shoot = 0;
    fire = 0;
    boss = 0;
    health = 100;
    windangle = 0;
    windspeed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
         1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
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

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick(int k, int m, int is) {
    if(wind==0)
    {
        int r = rand()%2000;
        //std::cout<<r<<std::endl;
        //int r = 1;
        if(r<2)
        {
            wind = rand()%501 + 2000;
            windangle = rand()%360;
            windspeed = ((float)(rand()%10))/100;
            std::cout<<wind<<" "<<windangle<<" "<<windspeed<<std::endl;

            float tempangle = windangle - this->rotation;
            speedw = speed + windspeed*(cos(tempangle*M_PI/180));
            float windperp = windspeed*(sin(tempangle*M_PI/180));
//            if(speed!=0)
//                this->rotation += atan(windperp/speed);
//            else
//                this->rotation = windangle-180;
        }
    }
    else if(wind>0)
    {
        float tempangle = windangle - this->rotation;
        speedw = speed + windspeed*(cos(tempangle*M_PI/180));
        float windperp = windspeed*(sin(tempangle*M_PI/180));
//        if(speed!=0)
//            this->rotation += atan(windperp/speed);
//        else
//            this->rotation = windangle-180;
        wind--;
    }

//  std::cout<<speed<<std::endl;
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
    //std::cout<<"speedy: "<<speedy<<std::endl;

    if(this->position.y > 1)
    {
        //std::cout<<"jump: "<<this->position.y<<std::endl;
        speedy += -0.03/60;
        //else speedy = 0;
    }
    else if(this->position.y<1)
    {
        this->position.y=1;
        speedy=0;
        jump = 0;
    }
    else
        jump = 0;

    //if(m==1)
    //    health-=0.8;

    if(k==0&&m==0&&is==0)
        move_forward(1);
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Boat::rotate(int flag){
    if(flag<0)
        this->rotation -= abs(flag)*0.3;
    else
        this->rotation += abs(flag)*0.3;
}

void Boat::move_forward(int flag){
    if(flag<0);
        //this->rotation -= 0.3;
    else
    {
        this->position.y += speedy;
        if(speedy!=0)
        {
           // std::cout<<"speedy: "<<speedy<<std::endl;
           // std::cout<<"y: "<<this->position.y<<std::endl;
        }
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

