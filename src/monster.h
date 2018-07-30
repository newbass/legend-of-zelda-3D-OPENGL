#include "main.h"
#include "boat.h"
#include "cannon.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, int typ, color_t color, color_t color1);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick(Boat boat, Cannon cannon);
    int struck;
    int type;
    int alive;
    int flag;
    float accn;
    float speedy;
private:
    VAO *object1;
    VAO *object2;
};

#endif // MONSTER_H
