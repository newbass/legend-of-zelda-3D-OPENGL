#include "main.h"
#include "boat.h"
#include "cannon.h"

#ifndef DIAMOND_H
#define DIAMOND_H


class Diamond {
public:
    Diamond() {}
    Diamond(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick(Boat boat, Cannon cannon);
    int struck;
    int show;
private:
    VAO *object;
};

#endif // ROCK_H
