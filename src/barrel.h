#include "main.h"
#include "boat.h"
#include "cannon.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick(Boat boat, Cannon cannon);
    int struck;
private:
    VAO *object;
};

#endif // BARREL_H
