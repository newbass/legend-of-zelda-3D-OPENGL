#include "main.h"
#include "boat.h"
#include "cannon.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z, int aliv, color_t color, color_t color1);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick(Boat boat, Cannon cannon);
    int struck;
    int alive;
    int flag;
    int lifes;
    int count;
    float accn;
    float speedy;
private:
    VAO *object1;
    VAO *object2;
};

#endif // BOSS_H
