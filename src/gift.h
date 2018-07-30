#include "main.h"
#include "boat.h"
#include "cannon.h"

#ifndef GIFT_H
#define GIFT_H


class Gift {
public:
    Gift() {}
    Gift(float x, float y, float z, int pts, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int tick(Boat boat, Cannon cannon);
    int struck;
    int show;
    int points;
private:
    VAO *object;
};

#endif // ROCK_H
