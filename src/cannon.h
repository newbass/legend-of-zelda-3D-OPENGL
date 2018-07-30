#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void rotate(int flag);
    void move_forward(int flag);
    double speed;
    double speedw;
    int wind;
private:
    VAO *object;
};

#endif // CANNON_H
