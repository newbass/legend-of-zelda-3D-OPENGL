#include "main.h"

#ifndef POWER_H
#define POWER_H


class Power {
public:
    Power() {}
    Power(float x, float y, float z, int flag, float ang, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    int flag;
    float distance;
private:
    VAO *object;
    //VAO *object2;
};

#endif // POWER_H
