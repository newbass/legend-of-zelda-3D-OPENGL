#include "main.h"

#ifndef TREE_H
#define TREE_H


class Tree {
public:
    Tree() {}
    Tree(float x, float y, float z, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object2;
    VAO *object1;
};

#endif // TREE_H
